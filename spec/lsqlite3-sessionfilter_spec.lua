-- ========================================================================
-- lsqlite3 session: per-session table-filter isolation
--
-- Regression tests for removing the module-level (process-wide) singleton
-- that used to hold the ses:attach(fn) filter callback.  Before the fix a
-- single pair of static ints (session_filter_cb / session_cb_udata) was
-- shared by every session, so attaching a filter on session B silently
-- replaced the filter of session A - and across threads / Lua states it
-- could even read a ref owned by another state.
--
-- The filter is now owned by each session (stored in its userdata and
-- passed to SQLite through the pCtx of sqlite3session_table_filter), so:
--   * two live sessions with different filters both keep working;
--   * re-attaching a new filter only affects that one session;
--   * deleting a session releases its own filter refs.
--
-- Run:
--   busted spec/lsqlite3-sessionfilter_spec.lua
-- ========================================================================

local ROOT = os.getenv("PWD") or "."
if ROOT == "" or not ROOT:match("^/") then
  local p = io.popen("cd")
  if p then ROOT = (p:read("*a") or "."):gsub("%s+$", ""); p:close() end
end
package.loaded.lsqlite3 = nil
package.cpath = ROOT .. "/?.so;" .. package.cpath
local sqlite3 = require("lsqlite3")

local probe = sqlite3.open_memory()
if type(probe) ~= "userdata" or type(probe.create_session) ~= "function" then
  pending("SQLITE_ENABLE_SESSION not enabled in the loaded lsqlite3 module; "
          .. "rebuild via `make lsqlite3.so`.", true)
  return
end
probe:close()

local function new_ab_db()
  local db = sqlite3.open_memory()
  db:exec("CREATE TABLE a(id INTEGER PRIMARY KEY, v TEXT)")
  db:exec("CREATE TABLE b(id INTEGER PRIMARY KEY, v TEXT)")
  db:exec("INSERT INTO a VALUES(1,'a0')")
  db:exec("INSERT INTO b VALUES(1,'b0')")
  return db
end

-- table names touched by a changeset, in order
local function collect_tabs(db, cs)
  local it = db:iterate_changeset(cs)
  local tabs = {}
  local rc = it:next()
  while rc == sqlite3.ROW do
    local zTab = (it:op())
    tabs[#tabs + 1] = zTab
    rc = it:next()
  end
  it:finalize()
  return tabs
end

describe("lsqlite3 session: per-session filter isolation", function()
  it("two live sessions with different filters both keep theirs", function()
    local db = new_ab_db()

    local seenA, seenB = {}, {}
    local sesA = db:create_session()
    sesA:attach(function(zTab)
      seenA[#seenA + 1] = zTab
      return zTab == "a" and 1 or 0          -- A only records table a
    end)
    -- Before the fix this attach() replaced A's filter with B's, so A's
    -- changeset below would silently lose the table-a change.
    local sesB = db:create_session()
    sesB:attach(function(zTab)
      seenB[#seenB + 1] = zTab
      return zTab == "b" and 1 or 0          -- B only records table b
    end)

    db:exec("UPDATE a SET v='a1' WHERE id=1")
    db:exec("UPDATE b SET v='b1' WHERE id=1")

    -- every change on the db asks every attached session's filter (a 0
    -- return just means "not for me"), so both filters are consulted...
    assert.is_true(#seenA >= 1, "sesA filter should have been consulted")
    assert.is_true(#seenB >= 1, "sesB filter should have been consulted")

    -- ...but the decisive check is what each session actually captured:
    -- sesA must record table a only and sesB table b only.  Under the old
    -- module-global design, sesB:attach() had replaced sesA's filter, so
    -- sesA's changeset would have contained b instead of a.
    assert.is_equal("a", table.concat(collect_tabs(db, sesA:changeset()), ","))
    assert.is_equal("b", table.concat(collect_tabs(db, sesB:changeset()), ","))

    sesA:delete()
    sesB:delete()
    db:close()
  end)

  it("re-attaching a new filter only affects that one session", function()
    local db = new_ab_db()

    local calls = {}
    local sesA = db:create_session()
    sesA:attach(function(zTab)
      calls[#calls + 1] = "A1:" .. zTab
      return 1
    end)
    local sesB = db:create_session()
    sesB:attach(function(zTab)
      calls[#calls + 1] = "B:" .. zTab
      return zTab == "b" and 1 or 0
    end)

    -- replace A's filter only
    sesA:attach(function(zTab)
      calls[#calls + 1] = "A2:" .. zTab
      return zTab == "a" and 1 or 0
    end)

    db:exec("UPDATE a SET v='a1' WHERE id=1")
    db:exec("UPDATE b SET v='b1' WHERE id=1")

    -- A's old filter must never be consulted again after re-attaching...
    local all = table.concat(calls, ",")
    assert.is_false(all:find("A1:", 1, true) ~= nil)

    -- ...and A (new filter) recorded a only while B (untouched) recorded b only
    assert.is_equal("a", table.concat(collect_tabs(db, sesA:changeset()), ","))
    assert.is_equal("b", table.concat(collect_tabs(db, sesB:changeset()), ","))

    sesA:delete()
    sesB:delete()
    db:close()
  end)

  it("deleting a session releases its filter (gc stays harmless)", function()
    local db = sqlite3.open_memory()
    db:exec("CREATE TABLE t(id INTEGER PRIMARY KEY, v TEXT)")
    db:exec("INSERT INTO t VALUES(1,'x')")

    local ses = db:create_session()
    ses:attach(function() return 1 end)
    -- explicit delete (this also unrefs the per-session filter)
    ses:delete()
    -- running the gc later must not crash (lsession_delete is idempotent:
    -- it is now wired as __gc as well as the explicit delete method)
    collectgarbage("collect")

    -- and a fresh session on the same db still works
    local ses2 = db:create_session()
    ses2:attach(function(zTab) return 1 end)
    db:exec("INSERT INTO t VALUES(2,'y')")
    assert.is_equal("t", table.concat(collect_tabs(db, ses2:changeset()), ","))
    ses2:delete()
    db:close()
  end)
end)
