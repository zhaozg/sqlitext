-- ========================================================================
-- lsqlite3 busy_handler: crash regression + functional coverage
--
-- Background (the crash in the field):
--
--   sdb (the lsqlite3 connection struct) stores the lua_State *L that was
--   current when the database was opened (newdb -> db->L).  Under LuaJIT a
--   coroutine is a separate lua_State, so opening a connection inside a
--   coroutine makes db->L point at that coroutine's thread.
--
--   If the connection outlives the coroutine that opened it (typical luvi
--   pattern: open the db in a request coroutine, cache the handle, let the
--   coroutine die) and the coroutine is garbage-collected, its thread object
--   (the lua_State) is freed.  db->L then dangles.  The very next time
--   SQLite has to invoke the busy handler while another connection holds a
--   lock, db_busy_callback() calls lua_rawgeti() on the freed state and the
--   process dies with EXC_BAD_ACCESS inside lj_tab_getint():
--
--     lua_rawgeti(L, LUA_REGISTRYINDEX, db->busy_cb)   -- L is freed
--
--   Reproduced stack (single main thread, LuaJIT):
--     frame #0 lua_rawgeti + ...
--     frame #1 db_busy_callback (lsqlite3.c)   user=sdb, tries=0
--     frame #2 sqlite3InvokeBusyHandler
--     ... sqlite3_step ...
--
-- Fix (binding/lua/lsqlite3.c):
--
--   newdb() now pins the thread that owns db->L with a registry reference
--   (sdb.state_ref); cleanupdb() releases it when the handle is closed or
--   collected.  The opening coroutine can no longer be freed while the
--   connection is alive, so every sqlite->Lua callback keeps a valid state.
--
-- These tests are single-threaded but deterministic.  They only need the
-- stock lsqlite3 module (no session / graph extension).
--
-- Run:
--   busted spec/lsqlite3-busy_handler_spec.lua
-- ========================================================================

local ROOT = os.getenv("PWD") or "."
if ROOT == "" or not ROOT:match("^/") then
  local p = io.popen("cd")
  if p then ROOT = (p:read("*a") or "."):gsub("%s+$", ""); p:close() end
end
package.loaded.lsqlite3 = nil
package.cpath = ROOT .. "/?.so;" .. package.cpath
local sqlite3 = require("lsqlite3")

-- unique file-backed database path (two connections contend on this file)
local function dbpath()
  local f = os.tmpname()
  os.remove(f)
  return f
end

-- Open a db *inside a fresh coroutine*, register nothing yet, and yield the
-- handle out.  Return (db, co).  Caller decides whether to drop/collect the
-- coroutine (regression) or keep it alive (control).
local function open_db_in_coroutine(path)
  local co = coroutine.create(function()
    local db = sqlite3.open(path)
    db:exec("CREATE TABLE t(x)")
    db:exec("INSERT INTO t VALUES(0)")
    coroutine.yield(db)
    error("coroutine was resumed after yielding the db handle")
  end)
  local ok, db = coroutine.resume(co)
  assert(ok, "failed to open db in coroutine: " .. tostring(db))
  return db, co
end

-- Setup: lock `path` exclusively (write lock) with a second connection.
-- The db whose busy handler we are testing must have its writer statement
-- prepared *before* this lock is taken so prepare() doesn't need a schema
-- lock of its own.
local function with_writer_locked(path, db, fn)
  local dbA = sqlite3.open(path)
  local st = db:prepare("INSERT INTO t VALUES(1)")
  assert(st, "prepare on locked schema failed")
  assert.equal(sqlite3.OK, dbA:exec("BEGIN IMMEDIATE"))
  local rc = fn(st)
  st:finalize()
  dbA:exec("ROLLBACK")
  dbA:close()
  return rc
end

describe("lsqlite3 busy_handler basics", function()
  it("invokes the Lua callback on lock contention and honours 'retry=false'", function()
    local path = dbpath()
    local db = sqlite3.open(path)
    db:exec("CREATE TABLE t(x)")

    local calls = 0
    db:busy_handler(function(tries)
      calls = calls + 1
      return false -- decline -> caller should get SQLITE_BUSY
    end)

    local rc = with_writer_locked(path, db, function(st)
      return st:step()
    end)
    assert.is_equal(sqlite3.BUSY, rc)
    assert.is_equal(1, calls)
    db:close()
    os.remove(path)
  end)

  it("keeps retrying while the callback returns true", function()
    local path = dbpath()
    local db = sqlite3.open(path)
    db:exec("CREATE TABLE t(x)")

    local calls = 0
    db:busy_handler(function(tries)
      calls = calls + 1
      return calls < 2 -- retry once, then give up
    end)

    local rc = with_writer_locked(path, db, function(st)
      return st:step()
    end)
    assert.is_equal(sqlite3.BUSY, rc)
    assert.is_equal(2, calls, "handler should have been retried")
    db:close()
    os.remove(path)
  end)

  it("clears the handler when called with no function", function()
    local path = dbpath()
    local db = sqlite3.open(path)
    db:exec("CREATE TABLE t(x)")

    local calls = 0
    db:busy_handler(function(tries)
      calls = calls + 1
      return false
    end)
    db:busy_handler() -- clear -> SQLite's default busy behaviour returns BUSY

    local rc = with_writer_locked(path, db, function(st)
      return st:step()
    end)
    assert.is_equal(sqlite3.BUSY, rc)
    assert.is_equal(0, calls, "cleared handler must not be invoked")
    db:close()
    os.remove(path)
  end)
end)

describe("lsqlite3 busy_handler vs LuaJIT coroutine lifetime", function()
  it("calls the handler safely after the opening coroutine was collected "
     .. "(regression: db->L use-after-free)", function()
    local path = dbpath()
    local db, co = open_db_in_coroutine(path)

    -- Drop the opening coroutine and force collection.  Without the fix the
    -- coroutine's lua_State (== db->L) is freed here and the busy callback
    -- below crashes inside lua_rawgeti().  With the fix the thread is pinned
    -- by sdb.state_ref and stays valid until db:close().
    co = nil
    collectgarbage("collect")
    collectgarbage("collect")
    -- churn the allocator to reuse / scribble over a freed thread block, so
    -- the UAF really crashes instead of silently reading stale memory.
    for i = 1, 200000 do
      local s = string.rep("x", 64)
      local t = { s, i, { s } }
    end
    collectgarbage("collect")

    -- register the handler *after* the opening coroutine is gone: the crash
    -- is caused by db->L (captured at open time), not by where busy_handler
    -- is registered.
    local calls = 0
    local seen = {}
    db:busy_handler(function(ud, tries)
      calls = calls + 1
      seen[#seen + 1] = tries
      return false
    end)

    local rc = with_writer_locked(path, db, function(st)
      return st:step()
    end)

    -- the Lua callback really ran on the (still referenced) thread
    assert.is_equal(sqlite3.BUSY, rc)
    assert.is_equal(1, calls)
    assert.is_equal(0, seen[1])

    -- and the connection is still fully usable afterwards
    assert.is_equal(sqlite3.OK, db:exec("INSERT INTO t VALUES(42)"))
    local v
    for row in db:nrows("SELECT COUNT(*) AS c FROM t") do
      v = row.c
    end
    assert.is_equal(2, v)

    db:close()
    os.remove(path)
  end)

  it("a db handle closed in the main thread releases the pinned coroutine "
     .. "(no leak, coroutine becomes collectable again)", function()
    local path = dbpath()
    local db = open_db_in_coroutine(path)

    -- sanity: handler works while the db is open (opening coroutine pinned)
    local calls = 0
    db:busy_handler(function(tries)
      calls = calls + 1
      return false
    end)
    local rc = with_writer_locked(path, db, function(st)
      return st:step()
    end)
    assert.is_equal(sqlite3.BUSY, rc)
    assert.is_equal(1, calls)

    -- close the handle; afterwards nothing should keep referencing the old
    -- coroutine and the process must still exit cleanly.
    db:close()
    os.remove(path)
    collectgarbage("collect")
    collectgarbage("collect")
  end)
end)
