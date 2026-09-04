# lsqlite3 Session 扩展与数据库同步框架

> 针对 `binding/lua/lsqlite3.c` 中集成（`SQLITE_ENABLE_SESSION`）的 SQLite
> **Session Extension** 的 Lua 使用手册。内容包括：
>
> 1. 功能与启用方式
> 2. 全部 API 接口说明（数据库级、会话级、迭代器、rebaser）
> 3. 基于 changeset 实现**多副本 / 多节点数据库同步**的思路与框架
>
> 相关文件：
>
> - 绑定实现：`binding/lua/lsqlite3.c`（`#ifdef SQLITE_ENABLE_SESSION`）
> - 单元测试：`spec/lsqlite3-session_spec.lua`（busted，50+ 用例）
> - 入门示例：`examples/session.lua`
> - 底层 C 接口：`src/sqlite3.h` 中 `sqlite3session_*` / `sqlite3changeset_*`
>   / `sqlite3rebaser_*` 系列

---

## 1. 什么是 Session Extension

SQLite 的 Session Extension 允许把一个数据库连接上发生的一组行级变更
（INSERT / UPDATE / DELETE）记录成**独立于数据库文件的二进制增量**，即
**changeset**（变更集）。changeset 可以被：

- 序列化成一个**二进制安全的 Lua string**，通过网络 / 文件 / BLOB 传输；
- 反序列化后**应用到另一个副本**上（`apply_changeset`），从而把该副本增量更新到
  发送方的状态；
- 求逆（撤销）、拼接（合并）、迭代（审计 / 二次处理）；
- 配合 **rebaser** 做“冲突日志回放”，实现类似 OT（操作转换）的增量重放。

它不复制整个数据库文件，因此非常适合**离线优先、周期性同步**的架构
（IoT、移动端、桌面端多副本等）。

### 1.1 需要哪些编译开关

模块必须以如下宏编译，Session 系列函数才会被导出：

```make
-DSQLITE_ENABLE_SESSION -DSQLITE_ENABLE_PREUPDATE_HOOK
```

- `SQLITE_ENABLE_SESSION`：session / changeset / rebaser 主体；
- `SQLITE_ENABLE_PREUPDATE_HOOK`：为 UPDATE 记录**修改前的旧值**，冲突检测依赖
  这些旧值。**生产同步务必两个都开。**

本项目 `Makefile` 的 `lsqlite3.so` 目标已默认带上这两个宏；重建即可：

```bash
make lsqlite3.so
busted --lua=luajit spec/lsqlite3-session_spec.lua   # 自检
```

若载入的模块缺少 session API，`db.create_session` 会是 `nil`（方法没注册）。可以先探测：

```lua
local sqlite3 = require("lsqlite3")
local db = sqlite3.open_memory()
assert(type(db.create_session) == "function", "session support not compiled in")
```

### 1.2 对象模型

Session 扩展在 Lua 侧暴露三类用户数据（full userdata）与一组数据库方法：

```
sqlite3 数据库 (sdb)
  ├── db:create_session(...)   → session（记录变更）
  ├── db:create_rebaser()      → rebaser（重放 / 转换变更）
  ├── db:iterate_changeset(cs) → changeset iterator（逐条读取变更）
  ├── db:invert_changeset / db:concat_changeset / db:apply_changeset
```

```
session ──changeset()/patchset()──▶ 二进制 string（可传输）
               │
               ▼
db:apply_changeset(cs) ──▶ 应用到另一副本（冲突时回调仲裁）
```

多数对象（数据库、prepared statement、iterator、rebaser 等）都带 `__gc` / `__tostring`，
可交由 GC 回收；唯独 **session 对象没有注册 `__gc`**（见 2.3），用完必须显式
`:delete()`，且在 `db:close()` 之前释放。

---

## 2. API 接口参考

### 2.1 常用常量

模块以 `sqlite3.XXX` 导出（数值与 `sqlite3.h` 一致）：

| Lua 常量 | 值 | 含义 |
|---|---|---|
| `sqlite3.INSERT` | 18 | changeset 中操作码：插入 |
| `sqlite3.UPDATE` | 23 | changeset 中操作码：更新 |
| `sqlite3.DELETE` | 9  | changeset 中操作码：删除 |
| `sqlite3.ROW` | 100 | `iter:next()` 读到一条变更 |
| `sqlite3.DONE` | 101 | `iter:next()` 遍历结束 |
| `sqlite3.CHANGESET_DATA` | 1 | 冲突：目标行与变更的 old 不符 |
| `sqlite3.CHANGESET_NOTFOUND` | 2 | 冲突：变更要求更新的行不存在 |
| `sqlite3.CHANGESET_CONFLICT` | 3 | 冲突：PK 与现有行冲突（如 INSERT） |
| `sqlite3.CHANGESET_CONSTRAINT` | 4 | 冲突：违反约束（UNIQUE / NOT NULL / CHECK） |
| `sqlite3.CHANGESET_FOREIGN_KEY` | 5 | 冲突：违反外键约束 |
| `sqlite3.CHANGESET_OMIT` | 0 | 冲突处理：跳过该变更并继续 |
| `sqlite3.CHANGESET_REPLACE` | 1 | 冲突处理：删除冲突行后重试该变更 |
| `sqlite3.CHANGESET_ABORT` | 2 | 冲突处理：中止整个 apply，回滚 |
| `sqlite3.CHANGESETAPPLY_NOSAVEPOINT` | 1 | apply 时不套外层 SAVEPOINT |

> 操作码与 authorizer 动作码是同一组常量，因此可直接用 `sqlite3.INSERT` 等判断
> `iter:op()` 返回值，无需另记数字。

### 2.2 数据库级方法

#### `db:create_session([zDb])` → session | nil, err

在 `db` 上新建一个**变更记录会话**。`zDb` 是数据库 schema 名，默认 `"main"`。
一个连接可同时存在多个 session，各记各的变更。

```lua
local ses = db:create_session()        -- 或 db:create_session("main")
```

会话创建后默认处于**启用**状态，但还没“看见”任何表——必须先用 `ses:attach()` 声明
要记录哪些表。

#### `db:iterate_changeset(changeset[, flags])` → iterator

把二进制 changeset 包成一个**只读迭代器**，用于逐条审计或二次处理。

```lua
local it = db:iterate_changeset(cs)
local rc = it:next()                       -- ROW / DONE / 错误码
while rc == sqlite3.ROW do
  local tab, op, indirect = it:op()        -- 表名, INSERT/UPDATE/DELETE, 是否间接
  -- it:pk() / it:old() / it:new() ...
  rc = it:next()
end
it:finalize()
```

`flags` 透传给 `sqlite3changeset_start_v2`（默认 0）。SQLite 还提供
`SQLITE_CHANGESETSTART_INVERT`（= 0x0002，倒序/反向迭代），当前未作为 Lua 常量导出，
如需使用可直接传数值。

#### `db:invert_changeset(changeset)` → inverted string | nil, err

对 changeset 求逆：把原来“把 A 变成 B”的变更反转为“把 B 变回 A”的变更，可用来
做**撤销**或回滚已同步内容。非法缓冲区返回 `nil, 错误码`。

#### `db:concat_changeset{ cs1, cs2, ... }` → merged string | nil, err

把多个 changeset **归并**为一个等价的 changeset（内部使用 SQLite changegroup，
会压缩/去冗余）。注意输入必须是**基于同一基线按先后顺序**的变更集，且所有表结构
一致。

```lua
local merged = db:concat_changeset { csA, csB }   -- 表参数：一个字符串数组
```

#### `db:apply_changeset(changeset, ...)` → 见下

把一段 changeset 应用到 `db`。这是同步的核心。支持的调用形式
（`db` 与 `cs` 之外，按需往后传参数）：

```lua
-- 1) 最小形式：不做过滤；遇冲突一律 OMIT（跳过该变更，继续）
local ok = db:apply_changeset(cs)

-- 2) 只提供冲突处理回调（冲突回调在前，udata 可选）
db:apply_changeset(cs, conflict_handler[, udata[, rebaser[, flags]]])

-- 3) 同时提供表过滤回调 + 冲突处理回调
db:apply_changeset(cs, table_filter, conflict_handler[, udata[, rebaser[, flags]]])
```

**参数说明：**

- `table_filter(zTab, udata)`：对每个表调用一次，返回“真值”才应用该表的变更；
  缺省 = 全放行。
- `conflict_handler(udata, eConflict, iter, zTab, op, indirect)`：目标库中发生冲突时
  回调，必须返回三个**整型常量**之一：`CHANGESET_OMIT / CHANGESET_REPLACE /
  CHANGESET_ABORT`（返回其它值、非整型或布尔值会报错并使本次 apply 失败）。
  - 参数里的 `iter` 是**只读冲突迭代器**，只能调用 `iter:op()/pk()/old()/new()/
    conflict()/fk_conflicts()` 查看“这一条变更想要做什么”以及“目标库里当前是什么”；
    在冲突迭代器上调用 `next()/finalize()` 会返回 `nil, 错误码`（既不推进也不释放），
    请只用读取方法。
  - 缺省（未提供回调）= 一律 `OMIT`（跳过该变更，继续）。
  - 返回 `CHANGESET_ABORT` 时整体回滚，apply 返回 `nil, 4`（`SQLITE_ABORT`）。
  - 回调中抛出 Lua 错误会向外传播并使本次 apply 失败。
- `udata`：透传给两个回调（见上），用于注入上下文
  （节点 id、策略对象等）。
- `rebaser`：提供后，apply 会把本次冲突的“重放日志（rebase log）”同时
  **配置进该 rebaser**，并把该日志作为返回值交给你（见 2.6 与 4.5）。
  日志只在**确实发生冲突**时才有内容；没有冲突时返回的是空串 `""`。
- `flags`：目前只有 `sqlite3.CHANGESETAPPLY_NOSAVEPOINT`（=1）；
  SQLite 侧另有 `CHANGESETAPPLY_INVERT` 等位，未导出为常量，按需直接传数值。

**返回值：**

- 无 rebaser：成功 → `true`；出错 → `nil, errcode`。
- 有 rebaser：成功 → 返回 **rebase log 字符串**（二进制）；发生冲突时非空，
  无冲突为空串 `""`（本仓库绑定已修正为二进制安全返回）；出错 → `nil, errcode`。

**默认行为 / 原子性：**

- 默认在事务（SAVEPOINT）中应用：任一变更导致 ABORT 或硬错误即**整体回滚**；
  加 `CHANGESETAPPLY_NOSAVEPOINT` 后可关闭该保护。
- 过滤掉的表、OMIT 掉的变更不影响事务结果。
- `apply_changeset` **不要求**目标库与源库同构到逐字节，但目标库**必须**已包含
  变更所涉及的表与主键结构（schema 需先同步好）。

#### `db:create_rebaser()` → rebaser

新建一个空 rebaser，用于 4.5 的“变更重放 / 消除重复冲突”场景。

### 2.3 session（会话）方法

会话用于“捕获”本连接上发生的变化。典型生命周期：

```lua
local ses = db:create_session()   -- 新建
ses:attach()                      -- 声明关注哪些表（默认全部）
...  db:exec(...)  -- 业务写入
local cs = ses:changeset()        -- 取走增量（不会清空会话）
ses:delete()                      -- 用完即弃（推荐一轮一会话，见 4.6）
```

> **生命周期提示**：session 用户数据没有 `__gc` 终结器。用完请显式调用
> `ses:delete()`，并**在 `db:close()` 之前**释放，避免底层悬垂。
> 一轮同步建议“建会话 → attach → 写入 → 取 changeset → delete”，而不是长期复用
> 同一个会话（否则 changeset 会不断累积、重复发送历史）。

| 方法 | 说明 |
|---|---|
| `ses:attach([arg])` | 开始记录。`arg` 为 `nil` 时记录全部表；传表名 `"t1"` 只记录该表；传**函数**时作为表过滤器 `fn(zTab, udata)`（真值=记录）。 |
| `ses:enable([bool])` | 开 / 关捕获。传入 `true`/`false` 设置并返回**新状态**（布尔）；不传参 = 查询当前状态（默认开启）。 |
| `ses:indirect([bool])` | 设置“间接变更”标记：开启后记录的变更都带 indirect=true（可用于区分本机直接写入与被同步写入）；返回规则同 `enable`。 |
| `ses:isempty()` | 是否尚未记录任何变更。 |
| `ses:changeset()` | 返回已捕获变更的**完整 changeset**（二进制 string）。 |
| `ses:patchset()` | 返回**精简版** patchset（只含 PK 与发生变化的列，体积更小）。patchset 缺少 UPDATE 的完整旧值，冲突检测能力弱，通常用于“小增量 + 服务器权威仲裁”场景。 |
| `ses:diff(fromDb, tbl)` | 见下。 |
| `ses:delete()` | 释放底层 session。 |

#### `ses:diff(zFromDb, zTbl)` → true | nil, err

对“同一连接上另挂接的一个数据库”（`ATTACH DATABASE ... AS zFromDb`）与当前库做
差异，并**把差异作为变更补录进本会话**。补录得到的 changeset 语义是：
**“把它应用到 `zFromDb` 上，即可把 `zFromDb` 更新成当前库的样子。”**

这是**不传整个文件做全量基线同步**的利器：

```lua
db:exec("ATTACH DATABASE '/path/peer.db' AS peer")
local ses = db:create_session()
ses:attach()                    -- 需要先 attach 目标表
ses:diff("peer", "todos")       -- 计算 main 与 peer 的差异
local cs = ses:changeset()      -- 可发给 peer 应用
```

规则（经测试验证）：

- 只在 main 有、peer 没有的行 → `INSERT`；
- 两边都有但值不同 → `UPDATE`（`old`=peer 值，`new`=main 值）；
- 只在 peer 有、main 没有的行 → `DELETE`；
- 表必须有主键；会话需先 `attach` 到该表。

### 2.4 changeset iterator（迭代器）方法

由 `db:iterate_changeset(cs)` 返回；也可在冲突回调中作为只读句柄使用。

| 方法 | 说明 |
|---|---|
| `it:next()` | 前进到下一条变更。返回 `sqlite3.ROW` 表示成功；`sqlite3.DONE` 表示结束；其余为错误码（如 11=`SQLITE_CORRUPT`，见 3.3）。 |
| `it:op()` | 返回 `zTab, op, indirect`（表名、操作码、是否间接）。 |
| `it:pk()` | 返回 `{列1是PK?, 列2是PK?, ...}` 的布尔数组。 |
| `it:old()` | 旧值数组（长度=表列数）；仅 UPDATE / DELETE 有意义。对 INSERT 调用返回 `nil, 21`（`SQLITE_MISUSE`，两个返回值，不抛异常）。 |
| `it:new()` | 新值数组；仅 INSERT / UPDATE 有意义。对 DELETE 调用返回 `nil, 21`（`SQLITE_MISUSE`）。 |
| `it:conflict()` | 冲突发生时目标库“当前行”的值数组；仅冲突迭代器可用。 |
| `it:fk_conflicts()` | 已遇到的违反外键的变更条数（冲突回调内有效）。 |
| `it:finalize()` | 显式释放；返回 `true`（也有 `__gc`，可不调用）。 |

**数组取值约定**（与 spec 测试一致；数组**长度恒等于表的列数**，下标从 1 起）：

- 数组下标 = **表列序号**（1 起），不是“变化列序号”；
- 该列不在记录中（如 UPDATE 中未改动的列）→ 槽位值为 `false`；
- 该列为空串 / 普通值时就是该值本身；值为 SQL `NULL` 时该槽位是 `nil`
  （数组会出现空洞，遍历请用固定列数 / `ipairs`，不要依赖 `#`）；
- 整条记录与操作类型不匹配（如对 INSERT 取 old、对 DELETE 取 new）→ 方法返回
  `nil, 21` 两个值——请**先用 `it:op()` 判断类型再读取**。

```lua
local tab, op, indirect = it:op()
-- 例表 t(id INTEGER PRIMARY KEY, a TEXT, b TEXT)
if op == sqlite3.UPDATE then
  local old, new = it:old(), it:new()
  --   UPDATE t SET a='x' WHERE id=1
  --     old = {1, '旧a', false}            -- PK + 被改列的旧值
  --     new = {false, 'x', false}          -- 只含被改列新值，不含 PK
elseif op == sqlite3.DELETE then
  local old = it:old()          -- {1, a, b} 整行
elseif op == sqlite3.INSERT then
  local new = it:new()          -- {1, a, b} 整行
end
```

### 2.5 操作码与冲突码速查

判断变更性质统一用 `sqlite3.INSERT / UPDATE / DELETE`；发生冲突时 `eConflict`
为 `sqlite3.CHANGESET_*` 五选一；你的回调返回 `CHANGESET_OMIT / REPLACE / ABORT`
三选一。组合策略在第 4 章展开。

### 2.6 rebaser 方法

```lua
local reb = db:create_rebaser()
assert(reb:configure(rebase_log))   -- 载入一段 rebase log（本仓库绑定补充的方法）
local out = reb:rebase(changeset)   -- 按已记录冲突“改写”一段 changeset
reb:delete()                        -- 有 __gc，可交由 GC
```

| 方法 | 说明 |
|---|---|
| `reb:rebase(cs)` | 依据 rebaser 内已配置的冲突日志，把 `cs` 改写为新 changeset 返回。空配置时≈原样返回。 |
| `reb:configure(rebase_log)` | **载入**一段 rebase log（由本机 `apply_changeset(..., rebaser)` 或对端传来），返回 `true`；非法缓冲区返回 `nil, errcode`。注意：`configure` 是本仓库在绑定层**新增**的方法（上游 lsqlite3 只会在 apply 时自动配置，不能手动载入）；它使跨进程/延迟 rebase 成为可能。 |
| `reb:delete()` | 释放（也有 `__gc`）。 |

详细语义见 4.5。

---

## 3. 关键行为与坑位

### 3.1 Schema 约束

- **每张需要同步的表必须有主键**（推荐 `INTEGER PRIMARY KEY` 或显式
  `PRIMARY KEY(...)`）。没有主键的普通 `ROWID` 表不会被 Session 捕获，也无法可靠
  冲突仲裁。
- 不含 `WITHOUT ROWID` 限制；但跨节点同步强烈建议用**应用生成的稳定主键**
  （UUID 字符串 / 复合键），避免两个节点同时 `AUTOINCREMENT` 撞号。
- 虚拟表、以及无主键的表不会被记录。

### 3.2 变更集只含 DML，且无序

- changeset 只包含行级 `INSERT/UPDATE/DELETE`；**DDL（建表、加列等）不在其中**。
  Schema 变更必须走独立的发布通道。
- changeset 内部的变更顺序**不等于**原 SQL 执行顺序，不要假设顺序；多行间有
  外键 / 唯一约束依赖时尤其小心（可用 `concat_changeset` 归并、或应用时关闭
  FK 检查）。
- 一个 UPDATE 记录里，`old` 含 **PK + 被改列的旧值**；`new` 只含**被改列的新值**
  （**不含 PK**，PK 槽位为 `false`；直接改动 PK 的语句会被拆成 DELETE + INSERT）。
  两者其余槽位均为 `false`。因此要拿版本号做仲裁，请确保每次 UPDATE 都改写你的
  版本列，否则它在记录里是 `false`，回调中读不到新旧版本号。

### 3.3 二进制与错误处理

- changeset / patchset / rebase log 都是**二进制安全字符串**，可含 `\0`。不要当文本打印、
  也不要直接拼进 `TEXT` 列——入库应绑定为 `BLOB`；走 JSON / 网络传输时 base64
  编码（见 4.1）。
- 方法出错统一返回 `nil, 错误码`（如 `11 = SQLITE_CORRUPT`）；只有参数错误或
  回调抛错才会 `error()`。
- 冲突回调返回 `CHANGESET_ABORT` 时，apply 回滚已应用部分并返回 `nil, 4`
  （`SQLITE_ABORT`）。
- 若目标库**缺少**变更涉及的表，`apply_changeset` 不会报错，而是**静默跳过**该表
  （SQLite 仅记一条 `SQLITE_SCHEMA` 日志，`sqlite3_log` 可观察）——所以请先同步
  schema 再同步数据，必要时应用后自行比对行数做校验。

### 3.4 回调与事务边界

- 冲突回调发生在 apply 的内部事务里，尽量只做“读 + 返回常量”，不要把会话级
  副作用放进去（会被回滚）。
- 目标库开 `PRAGMA foreign_keys=ON` 时，变更顺序或孤儿行会触发
  `CHANGESET_FOREIGN_KEY` 冲突；多数同步实现选择 apply 期间临时
  `PRAGMA foreign_keys=OFF`，靠业务保证整体一致。
- **`apply_changeset` 的回调是“每次调用独立”的（不是模块级单例）**：绑定把本次
  apply 的 filter / conflict / udata 引用放进这一次调用的上下文里，经
  `sqlite3changeset_apply_v2` 的 `pCtx` 传给回调，apply 返回后立即释放。因此：
  - 多线程 / 多 Lua state 各自调用 `apply_changeset` 互不覆盖，线程安全；
  - 允许在某个回调里再对**另一个连接**调用 `apply_changeset`，内外两套回调各自生效；
  - 回调若抛出 Lua 错误，绑定**不会在 SQLite 帧内 longjmp**（那会把连接锁“焊死”）：
    先把错误暂存，让 apply 干净 ABORT / 回滚、释放写锁，返回后再把错误抛给调用方。
- **`ses:attach(fn)` 的过滤回调也是“每个 session 独立”的**：绑定把该 session 的
  filter / udata 引用存进这个 session 自己的上下文，经 `sqlite3session_table_filter`
  的 `pCtx` 传给 SQLite。因此多个 session 各自 `attach(fn)` 传不同过滤函数会“并存”，
  互不覆盖；多线程 / 多 Lua state 下各自 session 也安全（不再有进程级共享引用）。
  对同一 session 再次 `attach(fn)` 会替换它自己的旧过滤函数。
- 闭包生命周期：`apply_changeset` 的回调在本次调用结束后即被释放；`ses:attach(fn)`
  注册的回调会被该 session 持有，直到该 session 被 `delete()` / 被 GC 回收，或再次
  `attach(fn)` 替换。

---

## 4. 基于该模块的数据库同步框架

### 4.1 总体思路

把“两个/多个副本收敛到一致”拆成三步：

1. **记录**：本机业务写库时，session 记录增量（`attach` + 每轮一个新会话）；
2. **传输**：把二进制 changeset 发给对端（网络 / 文件 / 消息队列，必要时
   base64）；
3. **应用**：对端用 `apply_changeset` 把增量落库，冲突交给回调仲裁
   （OMIT / REPLACE / ABORT），并把结果（可选 rebase log）回传。

同步方向可以是单向（主→从）、双向（两节点互为对方应用）或多跳（星形中心 /
网格）。Session 扩展本身无方向性，双向同步只是“各发各的变更集，各自应用对方
变更集”的叠加。

### 4.2 同步友好的表设计

以最常见的“待办清单”为例：

```sql
CREATE TABLE todos(
  id         TEXT PRIMARY KEY,        -- 应用生成 UUID，跨节点不撞号
  text       TEXT NOT NULL,
  done       INTEGER NOT NULL DEFAULT 0,
  updated_at INTEGER NOT NULL,        -- 逻辑时间戳 / 版本号（冲突仲裁依据）
  deleted    INTEGER NOT NULL DEFAULT 0  -- 软删除标记（推荐，见下）
);
```

- **稳定主键**（UUID / 复合键）：这是多副本同步的地基；
- **版本列 `updated_at`**：每次写都单调递增（`os.time()*1000`、Lamport 时钟或
  数据库 `unixepoch()`），冲突回调据此做 Last-Write-Wins；
- **软删除**：跨节点并发“A 删、B 改”这类 delete-vs-update 很难无信息地合并。
  用 `deleted=1` 的 UPDATE 表达删除，让所有变更都走 UPDATE，仲裁就统一了。
  离线端可周期把已同步且 `deleted=1` 的行物理清理。

### 4.3 基础框架：`collect` + `apply`

一个最小引擎骨架：`collect` 负责“拍增量”，`apply` 负责“落增量 + 仲裁”。
（完整可跑示例见 4.4，双向同步模型见 spec section 10。）

```lua
local sqlite3 = require("lsqlite3")
local Sync = {}

-- 打开（或创建）一个节点库；apply 期间临时关掉 FK，便于处理变更顺序
function Sync.open(path)
  local db = path and sqlite3.open(path) or sqlite3.open_memory()
  db:exec("PRAGMA foreign_keys=OFF")
  return db
end

-- 收集“本窗口内”的增量（一轮一个会话，用完即弃，见 4.6）
-- fn(db) 内完成本次要同步的业务写入
function Sync.collect(db, fn)
  local ses = db:create_session()
  ses:attach()                      -- 全表；局部同步可传表名 / 过滤器
  fn(db)
  local cs = ses:changeset()        -- 二进制 string（可为空串）
  ses:delete()
  return cs
end

-- 把对端变更集应用到本机
-- arbitration(u, eConflict, iter) -> OMIT | REPLACE | ABORT
function Sync.apply(db, cs, arbitration, udata)
  if not cs or #cs == 0 then return true end
  local ok, err = db:apply_changeset(
    cs,
    function() return true end,                  -- 表过滤：全放行
    function(u, eConflict, iter, zTab, op, ind)
      return arbitration(u, eConflict, iter, zTab, op, ind)
    end,
    udata)
  assert(ok, "apply_changeset failed: " .. tostring(err))
  return true
end

return Sync
```

### 4.4 可运行的验证：两节点双向收敛

下面给出**可直接用 `luajit` 运行**的自包含示例：两个节点初始同构，先在互不冲突的行
上各自修改并互相同步；随后对同一行并发修改，用 Last-Write-Wins 收敛到同一最终值。
（`spec/lsqlite3-session_spec.lua` section 10 用同一模型写成自动化用例。）

```lua
local sqlite3 = require("lsqlite3")
local REPLACE = sqlite3.CHANGESET_REPLACE
local OMIT    = sqlite3.CHANGESET_OMIT

local SCHEMA = [[
  CREATE TABLE todos(
    id         TEXT PRIMARY KEY,        -- 应用生成 UUID，跨节点不撞号
    text       TEXT NOT NULL,
    done       INTEGER NOT NULL DEFAULT 0,
    updated_at INTEGER NOT NULL,        -- 逻辑版本号（仲裁依据）
    deleted    INTEGER NOT NULL DEFAULT 0  -- 软删除标记
  );
]]

-- 新建一个与 seed 相同快照的节点
local function node(seed)
  local db = sqlite3.open_memory()
  db:exec(SCHEMA)
  for _, r in ipairs(seed or {}) do
    db:exec(string.format("INSERT INTO todos VALUES('%s','%s',0,%d,0)",
                          r[1], r[2], r[3]))
  end
  return db
end

-- 拍下 fn(db) 这批写入的增量 changeset（一轮一个会话）
local function collect(db, fn)
  local ses = db:create_session()
  ses:attach()
  fn(db)
  local cs = ses:changeset()
  ses:delete()
  return cs
end

-- LWW 仲裁：updated_at 大者胜；相等时本机（目标库）优先。
-- 列序：1=id 2=text 3=done 4=updated_at 5=deleted
local function lww(u, eConflict, iter)
  local cur  = iter:conflict()           -- 目标库当前行（全列）
  local inc  = iter:new() or iter:old()  -- 变更想写入的新行 / 删除前的旧行
  local curTs = cur and cur[4] or -1
  local incTs = inc and inc[4] or -1
  return (incTs >= curTs) and REPLACE or OMIT
end

local function apply(db, cs)
  if not cs or #cs == 0 then return end
  local ok, err = db:apply_changeset(cs, function() return true end, lww)
  assert(ok, "apply failed: " .. tostring(err))
end

local function dump(db, label)
  local out = {}
  for r in db:nrows("SELECT id,text,updated_at FROM todos ORDER BY id") do
    out[#out + 1] = string.format("%s=%s@%d", r.id, r.text, r.updated_at)
  end
  print(label .. ": " .. table.concat(out, "  "))
end

-- 场景 1：不同行各自编辑 -> 交换后无冲突收敛
local seed = { {"a","alpha",0}, {"b","beta",0} }
local A, B = node(seed), node(seed)

local csA = collect(A, function(d)
  d:exec("UPDATE todos SET text='alpha-A', updated_at=100 WHERE id='a'") end)
local csB = collect(B, function(d)
  d:exec("UPDATE todos SET text='beta-B',  updated_at=100 WHERE id='b'") end)

apply(B, csA)                     -- A -> B
apply(A, csB)                     -- B -> A
dump(A, "A")                      -- a=alpha-A@100  b=beta-B@100
dump(B, "B")                      -- 与 A 一致

-- 场景 2：同一行并发修改 -> LWW 收敛
local C, D = node({ {"x","shared",10} }), node({ {"x","shared",10} })
local csC = collect(C, function(d)
  d:exec("UPDATE todos SET text='from-C', updated_at=20 WHERE id='x'") end)
local csD = collect(D, function(d)
  d:exec("UPDATE todos SET text='from-D', updated_at=30 WHERE id='x'") end)

apply(D, csC)   -- D 应用 C(ts=20)：本机 ts=30 更新 -> OMIT，D 保留 from-D
apply(C, csD)   -- C 应用 D(ts=30)：30>=20   -> REPLACE，C 变为 from-D
dump(C, "C")    -- 都收敛到 x=from-D@30
dump(D, "D")
```

### 4.5 用 rebaser 消除“重复冲突”（冲突日志回放）

LWW 双向同步里，**同一处冲突**可能要在不同节点上反复仲裁。SQLite 的 rebaser 把
“本节点已经做过的仲裁结论”固化成一段 **rebase log**，再用它改写后续要外发的
changeset，让网络里其它节点不必重演同一次冲突。

> 方向约定（`sqlite3.h` 语义）：A、B 都从 S0 出发各自产生变更集 csA、csB。B 把
> csA 应用进来（发生冲突并仲裁）→ 拿到 rebase log；B 随后要把自己的 csB 发给 A，
> 若直接发，A 会撞上同一次冲突。正确做法是：B 用该 log 把 csB **rebase** 成 csB'，
> 再发给 A，A 就能干净地应用。

```lua
-- 节点 B：应用 A 的变更，同时捕获 rebase log（并已自动配置进 reb）
local reb = B:create_rebaser()
local log = B:apply_changeset(
  csA,
  function() return true end,   -- 表过滤
  conflict_handler,             -- 仲裁：OMIT / REPLACE / ABORT
  nil, reb)                     -- udata=nil, rebaser=reb

-- 节点 B：把待发往 A 的本地变更集 rebase（已按 B 的仲裁改写）
local csB2 = reb:rebase(csB)    -- 可能变成空串 = 无需再发给 A

-- 节点 A：应用改写后的变更集，通常不再冲突
A:apply_changeset(csB2)
```

要点：

- `apply_changeset(...)` 的返回值就是 rebase log：发生冲突时是**非空二进制字符串**；
  没有冲突时返回空串 `""`（本仓库绑定已保证二进制安全，不受内嵌 `\0` 截断）。
- 传 rebaser 参数后 apply 已自动替你 `configure` 过它，随后直接 `reb:rebase(...)` 即可。
- 需要跨进程 / 延迟 rebase 时，用本仓库绑定**新增**的 `reb:configure(log)` 在任意
  连接上重新载入日志（上游 lsqlite3 没有此方法）。
- 对多个远端变更集依次仲裁时，可把同一个 rebaser 反复传给多次 apply，配置会按调用
  顺序叠加，最后一次性 `rebase` 本地变更集。

### 4.6 工程建议（防回环 / 防泄漏 / 防历史放大）

- **一轮一个新会话**：离线收集期用“建会话 → attach → 写入 → 取 changeset → delete”，
  不要长期复用会话——否则 changeset 会不断累积并重复发送历史（见 2.3）。
- **应用远端变更时避免“回环 echo”**：让 apply 发生在“没有活动 session”的时刻，或在
  apply 前 `ses:enable(false)`、结束后重建会话；否则刚同步进来的行会被当成本地新变更
  再次广播出去。spec section 10 即按该模型编写。
- **会话没有 `__gc`**：务必 `ses:delete()` 且在 `db:close()` 之前释放（见 2.3）。
- **冲突仲裁保持纯读**：只读 `iter` + 返回常量；不要在回调里再发起 `apply_changeset`
  （回调是模块级单例，见 3.4）。
- **对端数据先校验再落库**：收到二进制 changeset / rebase log 后，可先用
  `invert_changeset` / `iterate_changeset` 走一遍做合法性检查（非法输入返回
  `nil, 错误码`），确认无误再 apply。
