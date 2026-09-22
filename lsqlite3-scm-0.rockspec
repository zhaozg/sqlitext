-- lsqlite3 rockspec (SCM / development snapshot)
--
-- 用法（在本仓库根目录执行，即 Makefile / graph.mk 所在目录）：
--
--     luarocks make --local lsqlite3-scm-0.rockspec
--
-- 本 rockspec 直接驱动仓库里的 Makefile（含 graph.mk），只构建/安装 Lua 绑定
-- 目标 `lsqlite3.so`，不会构建 bin/ 下的命令行工具
-- (sqlite3 / secure / cevfs / vector / graph)。
--
-- 关于链接方式的说明（macOS 上最容易踩的坑）：
--   LuaRocks 会通过 LIBFLAG 告诉 make 如何生成一个可 dlopen 的 Lua 模块，
--   macOS 上是 "-bundle -undefined dynamic_lookup -all_load"，这样 Lua 的
--   符号在链接期保持未解析、加载时再从宿主进程（luajit）解析。
--   因此这里 **不需要** 也不应该再链接 -lluajit：LuaRocks 在 macOS 上
--   (cfg.link_lua_explicitly == false) 根本不会推导 LUA_LIBDIR / LUALIB，
--   若在 rockspec 里写 $(LUA_LIBDIR) 会被替换成空串，最终变成
--   `-L -lluajit-5.1`，`-lluajit-5.1` 被 `-L` 当成参数吞掉，链接必然失败。

package = "lsqlite3"
version = "scm-0"

rockspec_format = "3.0"

source = {
   url = "git+https://github.com/zhaozg/sqlitext.git",
}

description = {
   summary = "LuaSQLite3 binding for LuaJIT, with GraphQLite / sqlite-vec / session built in",
   detailed = [[
lsqlite3 is a Lua binding for the SQLite3 library.

This build statically bundles the SQLite3 amalgamation together with:

  * GraphQLite  -- openCypher graph queries via the cypher() SQL function
  * sqlite-vec  -- vector search / vec0 virtual tables
  * the session & preupdate-hook extensions

so a single lsqlite3.so module provides all of them.
]],
   homepage = "https://github.com/zhaozg/sqlitext",
   license = "MIT",
}

dependencies = {
   "lua >= 5.1",
}

test_dependencies = {
   "busted",
}

test = {
   type = "busted",
}

build = {
   type = "make",

   -- Makefile 的默认目标 (default: makedir all) 会连带构建 readline 命令行工具，
   -- 这里只指定 Lua 绑定这一个目标，对应 Makefile 中的 `lsqlite3.so:` 规则。
   build_target = "lsqlite3.so",

   build_variables = {
      -- 让编译带上优化 (-O2 -fPIC)，否则 Makefile 里 $(CFLAGS) 为空、sqlite3.c
      -- 会以 -O0 构建（同时也消除 LuaRocks 的 "CFLAGS was not passed" 警告）。
      CFLAGS = "$(CFLAGS)",
      -- Makefile 默认用 `pkg-config luajit --cflags` 取头文件路径；
      -- 显式传入 LuaRocks 探测到的路径，机器上没有 luajit.pc 也能编译。
      LUA_CFLAGS = "-I$(LUA_INCDIR)",
      -- 显式置空：链接由 $(LIBFLAG) 负责，Lua 符号延迟到加载时解析，
      -- 不需要（也不能）在这里链接 libluajit。
      LUA_LIBS = "",
   },

   install_variables = {
      -- Makefile 的安装规则是 `cp -a lsqlite3.so $(LUA_LIBDIR)`。
      -- $(LIBDIR) 指向本 rock 自己的 lib/ 目录，之后由 LuaRocks 负责 deploy。
      LUA_LIBDIR = "$(LIBDIR)",
   },
}
