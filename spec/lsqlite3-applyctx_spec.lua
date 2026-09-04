-- ========================================================================
-- lsqlite3 session: apply_changeset callback isolation / error handling
--
-- Regression tests for the db_apply_changeset() multithreading fix:
--
--   * Previously the conflict/filter callback Lua references for
--     apply_changeset() were held in module-level (process-wide) `static`
--     variables.  Any second apply_changeset() call -- from another thread
--     or even *nested inside a live callback* -- would overwrite those
--     shared refs, so the outer apply would keep invoking the inner apply's
--     callback (or nil) after the inner call returned.
--
--   * Previously a Lua error raised inside a session callback was turned
--     into lua_error() directly in the callback, i.e. a longjmp through the
--     sqlite3changeset_apply_v2() frames while it held the connection
--     mutex / SAVEPOINT / file write-lock.  The error must instead be
--     parked in the per-call context and re-raised only after SQLite has
--     cleanly aborted and released its locks.
--
-- These tests are single-threaded but deterministic: they nest an apply
-- inside a conflict callback (the documented "module singleton" failure
-- mode) and verify each apply keeps using its own callback.
--
-- Run:
--   busted spec/lsqlite3-applyctx_spec.lua
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

local CHANGESET_OMIT = sqlite3.CHANGESET_OMIT

-- minimal in-memory db: t(id INTEGER PRIMARY KEY, a TEXT, b TEXT)
local function new_db(rows)
  local db = sqlite3.open_memory()
  db:exec("CREATE TABLE t(id INTEGER PRIMARY KEY, a TEXT, b TEXT)")
  for _, r in ipairs(rows or { {1, "x0", "P"}, {2, "y0", "Q"} }) do
    db:exec(string.format("INSERT INTO t VALUES(%d,'%s','%s')", r[1], r[2], r[3]))
  end
  return db
end

local function dump(db)
  local out = {}
  for a, b in db:urows("SELECT id,a FROM t ORDER BY id") do
    out[#out + 1] = tostring(a) .. "=" .. tostring(b)
  end
  return table.concat(out, " ")
end

-- run fn(db) inside a session and return the binary changeset
local function record(db, fn)
  local ses = db:create_session()
  ses:attach()
  fn(db)
  local cs = ses:changeset()
  ses:delete()
  return cs
end

describe("lsqlite3 session: apply_changeset callback isolation", function()
  it("keeps its own conflict callback when another apply is nested inside it", function()
    -- outer apply: csO updates rows 1 and 2; dstO holds different values so
    -- the conflict callback must fire twice.
    local srcO = new_db({ {1, "o0", "P"}, {2, "o1", "Q"} })
    local csO = record(srcO, function(d)
      d:exec("UPDATE t SET a='oX' WHERE id=1")
      d:exec("UPDATE t SET a='oX' WHERE id=2")
    end)
    local dstO = new_db({ {1, "O1", "P"}, {2, "O2", "Q"} })

    -- inner apply: csI updates row 5; dstI holds a different value so its
    -- conflict callback must fire once.
    local srcI = new_db({ {5, "i0", "P"} })
    local csI = record(srcI, function(d)
      d:exec("UPDATE t SET a='iX' WHERE id=5")
    end)
    local dstI = new_db({ {5, "I1", "P"} })

    local outer_calls, inner_calls = 0, 0

    local ok, err = dstO:apply_changeset(csO, function(ud, eC)
      outer_calls = outer_calls + 1
      if outer_calls == 1 then
        -- nested apply while the outer conflict callback is still live.
        -- Before the fix this overwrote the shared callback refs and the
        -- outer apply would afterwards call the *inner* conflict callback.
        local ok2 = dstI:apply_changeset(csI, function(ud2, eC2)
          inner_calls = inner_calls + 1
          return CHANGESET_OMIT
        end)
        assert.is_true(ok2)
      end
      return CHANGESET_OMIT
    end)
    assert.is_true(ok, err)

    -- both conflicts of the outer changeset were handled by the outer
    -- callback, and the inner one only by the inner callback.
    assert.is_equal(2, outer_calls)
    assert.is_equal(1, inner_calls)

    srcO:close(); dstO:close()
    srcI:close(); dstI:close()
  end)

  it("does not leak the filter callback across separate apply calls", function()
    local src = new_db({ {1, "a0", "P"}, {2, "b0", "Q"} })
    local cs = record(src, function(d)
      d:exec("UPDATE t SET a='a1' WHERE id=1")
      d:exec("UPDATE t SET a='b1' WHERE id=2")
    end)
    local dst = new_db({ {1, "a0", "P"}, {2, "b0", "Q"} })

    -- first apply uses a filter that only accepts table "t" (records calls)
    local first = {}
    local ok = dst:apply_changeset(cs,
      function(zTab) first[#first + 1] = zTab; return 1 end,
      function() return CHANGESET_OMIT end)
    assert.is_true(ok)
    assert.is_equal("t", table.concat(first, ","))

    -- second apply on the same db passes a *different* filter that rejects
    -- everything; the previous filter must not linger in module state.
    local second = {}
    local ok2 = dst:apply_changeset(cs,
      function(zTab) second[#second + 1] = zTab; return 0 end,
      function() return CHANGESET_OMIT end)
    assert.is_true(ok2)
    assert.is_equal("t", table.concat(second, ","))
    -- second apply skipped the whole table, so nothing changed
    assert.is_equal("1=a1 2=b1", dump(dst))

    src:close(); dst:close()
  end)
end)

describe("lsqlite3 session: apply_changeset error handling", function()
  it("re-raises a Lua error from the conflict callback and leaves db usable", function()
    local src = new_db({ {1, "a0", "P"} })
    local cs = record(src, function(d) d:exec("UPDATE t SET a='a1' WHERE id=1") end)
    local dst = new_db({ {1, "zz", "Z"} }) -- baseline mismatch -> conflict

    local threw
    local ok, err = pcall(function()
      dst:apply_changeset(cs, function() error("boom from conflict cb") end)
    end)
    threw = not ok

    -- the Lua error must surface to the caller (not get swallowed)
    assert.is_true(threw, "expected the callback error to surface")
    -- ...and only after SQLite aborted cleanly, so the db is fully usable:
    -- no leaked write-lock / dangling savepoint from the failed apply.
    dst:exec("INSERT INTO t VALUES(2,'ok','Q')")
    assert.is_equal("1=zz 2=ok", dump(dst))

    src:close(); dst:close()
  end)

  it("re-raises a Lua error from the table filter callback", function()
    local src = new_db({ {1, "a0", "P"} })
    local cs = record(src, function(d) d:exec("UPDATE t SET a='a1' WHERE id=1") end)
    local dst = new_db({ {1, "a0", "P"} }) -- no conflict at all

    local ok, err = pcall(function()
      dst:apply_changeset(cs,
        function() error("boom from filter cb") end, -- table filter
        function() return CHANGESET_OMIT end)        -- conflict handler
    end)
    assert.is_false(ok)
    -- db remains usable after the failed apply
    dst:exec("INSERT INTO t VALUES(2,'ok','Q')")
    assert.is_equal("1=a0 2=ok", dump(dst))

    src:close(); dst:close()
  end)
end)
