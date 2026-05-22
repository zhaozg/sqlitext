# AGENT.md: 使用 busted 为 lsqlite3 编写单元测试

本文档指导 AI Agent 如何使用 **busted** 测试框架、**LuaJIT** 和 **Lua 5.1** 语法，
为 `lsqlite3`（Lua SQLite3 绑定）及其加载的扩展（如 GraphQLite）编写全面的单元测试。

## 1. 环境准备

- 测试运行器：`busted`（必须用它跑，不能用 `luajit test.lua` 直接跑）
- Lua 实现：`luajit`（兼容 Lua 5.1）

## 2. 测试文件结构

建议将测试文件放在 `test/` 目录下，命名以 `_spec.lua` 结尾，例如：

```
project/
├── test/
│   ├── sqlite_basic_spec.lua
│   ├── sqlite_ext_graphqlite_spec.lua
│   └── helper.lua          # 公共辅助函数
```

---

## 3. 测试模板（直接复制改造）

```lua
-- test/example_spec.lua
local sqlite3 = require("lsqlite3")

describe("数据库模块", function()
    local db

    before_each(function()
        db = sqlite3.open_memory()   -- 每个用例独立内存库
    end)

    after_each(function()
        db:close()
    end)

    it("可以执行建表并插入", function()
        db:exec("CREATE TABLE users (id INTEGER, name TEXT)")
        db:exec("INSERT INTO users VALUES (1, 'Alice')")
        local row = db:first_row("SELECT name FROM users WHERE id = 1")
        assert.are.equal("Alice", row.name)
    end)

    it("参数化查询", function()
        db:exec("CREATE TABLE t (v INTEGER)")
        local stmt = db:prepare("INSERT INTO t VALUES (?)")
        stmt:bind_values(42)
        stmt:step()
        stmt:finalize()
        local res = db:first_row("SELECT v FROM t")
        assert.are.equal(42, res.v)
    end)

    it("错误处理", function()
        local ok, err = pcall(db.exec, db, "SELECT * FROM no_table")
        assert.is_false(ok)
        assert.is_not_nil(string.find(err or "", "no such table"))
    end)
end)
```

## 4. 测试扩展（GraphQLite 示例）

```lua
local helper = {}

function helper.load_extension(db, path)
    db:exec("PRAGMA load_extension = 1;")
    local ok, err = pcall(db.exec, db, string.format("SELECT load_extension('%s')", path))
    assert(ok, "加载扩展失败: " .. tostring(err))
end

-- 在测试中使用
describe("GraphQLite", function()
    local db
    before_each(function()
        db = sqlite3.open_memory()
        helper.load_extension(db, "./build/graphqlite.dylib")  -- 改实际路径
    end)

    it("执行 Cypher 查询", function()
        local cypher = "CREATE (p:Person {name: 'Alice'}) RETURN p.name"
        local sql = string.format("SELECT cypher('%s')", cypher:gsub("'", "''"))
        local stmt = db:prepare(sql)
        stmt:step()
        local json = stmt:get_value(0)   -- 返回 JSON 字符串
        assert.is_true(string.find(json, "Alice"))
        stmt:finalize()
    end)
end)
```

## 5. 运行命令

```bash
# 基本
busted

# 指定文件
busted test/xxx_spec.lua

# 显式用 LuaJIT
busted --lua=luajit

# 详细输出
busted --verbose

# 只跑匹配某个模式的测试
busted --pattern="transaction"
```

## 6. 核心断言（busted + luassert）

```lua
assert.are.equal(expected, actual)
assert.are.same(expected_table, actual_table)   -- 深度比较
assert.is_true(x)
assert.is_false(x)
assert.is_nil(x)
assert.has.errors(function() ... end)
assert.is_not.equal(a, b)
```

## 7. 关键注意事项（踩坑预警）

1. **每次测试独立**：用 `before_each` 建内存库，避免用例间污染。
2. **加载扩展**：必须先执行 `PRAGMA load_extension = 1;` 再 `SELECT load_extension(...)`。
3. **Cypher 字符串转义**：单引号要写成 `''`（SQL 标准），示例中已用 `gsub` 处理。
4. **JSON 结果**：`cypher()` 返回 JSON 字符串，建议用 `dkjson` 解析后再断言（若需要精确对比）。
5. **不用直接跑 `luajit test.lua`**：必须用 `busted` 命令。

## 8. AI 个性化建议（记住这些就够了）

- 这是 **精简实战版**，不要自行扩展成教科书。
- 优先测试 **内存数据库**（`:memory:`），除非必须测文件持久化。
- 对扩展的测试，把加载逻辑写在 `before_each` 或 helper 中，集中管理路径。
- 善用 `assert.has.errors` 测试异常 SQL。
- 复杂 JSON 断言前，先用 `json.decode` 转成 Lua table，再用 `assert.are.same` 比较。
