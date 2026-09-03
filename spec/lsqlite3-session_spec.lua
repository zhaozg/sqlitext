-- ========================================================================
-- lsqlite3 session extension unit tests
--
-- Covers the SQLite Session Extension exposed by binding/lua/lsqlite3.c
-- (v0.9.7 + session.patch): create_session / changeset / patchset /
-- apply_changeset / invert_changeset / concat_changeset /
-- iterate_changeset / create_rebaser plus the filter & conflict callbacks.
--
-- Run:
--   busted spec/lsqlite3-session_spec.lua
--   busted --lua=luajit spec/lsqlite3-session_spec.lua
--
-- Behavioural notes (verified against this binding, LuaJIT, Lua 5.1):
--   * iterate_changeset reports a binary changeset; the ordering of changes
--     inside it is NOT the same as the statement execution order, so tests
--     group by operation code instead of assuming an order.
--   * For an UPDATE change the unchanged columns appear as the "?" marker
--     in old/new; DELETE carries the full old row, INSERT the full new row.
--   * A patchset UPDATE stores only PK values plus (column-index, value)
--     pairs for changed columns.
-- ========================================================================

-- Load the project-local .so (rebuilt with SQLITE_ENABLE_SESSION).  Busted
-- may otherwise resolve a system install that lacks the session API.
local ROOT = os.getenv("PWD") or "."
if ROOT == "" or not ROOT:match("^/") then
  local p = io.popen("cd")
  if p then ROOT = (p:read("*a") or "."):gsub("%s+$", ""); p:close() end
end
package.loaded.lsqlite3 = nil
package.cpath = ROOT .. "/?.so;" .. package.cpath
local sqlite3 = require("lsqlite3")

-- ------------------------------------------------------------------
-- capability guard: report as pending when the session API is missing
-- ------------------------------------------------------------------
local probe = sqlite3.open_memory()
if type(probe) ~= "userdata" or type(probe.create_session) ~= "function" then
  pending("SQLITE_ENABLE_SESSION / SQLITE_ENABLE_PREUPDATE_HOOK not enabled "
          .. "in the loaded lsqlite3 module; rebuild via `make lsqlite3.so`.",
          true)
  return
end

-- ------------------------------------------------------------------
-- constants (mirror sqlite3.h)
-- ------------------------------------------------------------------
local ROW, DONE = sqlite3.ROW, sqlite3.DONE
local INSERT, UPDATE, DELETE = sqlite3.INSERT, sqlite3.UPDATE, sqlite3.DELETE
local CHANGESET_DATA       = sqlite3.CHANGESET_DATA
local CHANGESET_NOTFOUND   = sqlite3.CHANGESET_NOTFOUND
local CHANGESET_CONFLICT   = sqlite3.CHANGESET_CONFLICT
local CHANGESET_CONSTRAINT = sqlite3.CHANGESET_CONSTRAINT
local CHANGESET_FOREIGN_KEY = sqlite3.CHANGESET_FOREIGN_KEY
local CHANGESET_OMIT       = sqlite3.CHANGESET_OMIT
local CHANGESET_REPLACE    = sqlite3.CHANGESET_REPLACE
local CHANGESET_ABORT      = sqlite3.CHANGESET_ABORT

-- ------------------------------------------------------------------
-- helpers
-- ------------------------------------------------------------------
local M = {}

-- in-memory db with t(id INTEGER PRIMARY KEY, a TEXT, b TEXT)
function M.new_db(rows)
  local db = sqlite3.open_memory()
  db:exec("CREATE TABLE t(id INTEGER PRIMARY KEY, a TEXT, b TEXT)")
  for _, r in ipairs(rows or { {1, "x0", "P"}, {2, "y0", "Q"} }) do
    db:exec(string.format("INSERT INTO t VALUES(%d,'%s','%s')", r[1], r[2], r[3]))
  end
  return db
end

-- sorted dump "id=a id=a ..." (first two columns of the given table)
function M.dump(db, tbl, c1, c2)
  tbl, c1, c2 = tbl or "t", c1 or "id", c2 or "a"
  local out = {}
  for a, b in db:urows("SELECT " .. c1 .. "," .. c2
                       .. " FROM " .. tbl .. " ORDER BY " .. c1) do
    out[#out + 1] = tostring(a) .. "=" .. tostring(b)
  end
  return table.concat(out, " ")
end

-- Render a value record from old()/new()/pk() to a comparable string.
-- "?" = column not part of the record; false = not a PK / not changed.
function M.vdump(t)
  if not t then return "-" end
  local out = {}
  for i = 1, #t do
    local v = t[i]
    if v == false or v == "?" then
      out[i] = "?"
    elseif v == nil then
      out[i] = "nil"
    elseif v == "" then
      out[i] = '""'
    else
      out[i] = tostring(v)
    end
  end
  return table.concat(out, ",")
end

-- run fn(db) inside a session and return the binary changeset
function M.record(db, fn, arg)
  local ses = db:create_session()
  ses:attach(arg)          -- nil = all tables, string = one table, fn = filter
  fn(db)
  local cs = ses:changeset()
  ses:delete()
  return cs
end

-- iterate a changeset/patchset into records:
-- { tab, op, indirect, pk, old, new }  (pk/old/new are vdump() strings)
function M.iter_ops(db, cs)
  local ops = {}
  local it = db:iterate_changeset(cs)
  local rc = it:next()
  while rc == ROW do
    local tab, op, ind = it:op()
    local rec = { tab = tab, op = op, indirect = ind }
    local ok
    ok, rec.pk = pcall(M.vdump, it:pk())
    if not ok then rec.pk = "-" end
    if op == INSERT then
      rec.new = M.vdump(it:new())
    elseif op == DELETE then
      rec.old = M.vdump(it:old())
    else
      rec.old = M.vdump(it:old())
      rec.new = M.vdump(it:new())
    end
    ops[#ops + 1] = rec
    rc = it:next()
  end
  it:finalize()
  return ops, rc
end

-- ------------------------------------------------------------------
-- 1. API surface & constants
-- ------------------------------------------------------------------
describe("lsqlite3 session: API surface", function()
  it("exposes the session methods on db objects", function()
    local db = sqlite3.open_memory()
    for _, m in ipairs({ "create_session", "iterate_changeset",
                         "invert_changeset", "concat_changeset",
                         "apply_changeset", "create_rebaser" }) do
      assert.is_equal("function", type(db[m]), m .. " should be a method")
    end
    db:close()
  end)

  it("returns a session userdata with expected methods", function()
    local db = sqlite3.open_memory()
    local ses = db:create_session()
    assert.is_equal("userdata", type(ses))
    for _, m in ipairs({ "attach", "changeset", "patchset", "isempty",
                         "enable", "indirect", "diff", "delete" }) do
      assert.is_equal("function", type(ses[m]), "session:" .. m)
    end
    assert.match("sqlite session", tostring(ses))
    db:close()
  end)

  it("returns a changeset iterator with expected methods", function()
    local db = M.new_db()
    local cs = M.record(db, function(d) d:exec("UPDATE t SET a='zz' WHERE id=1") end)
    local it = db:iterate_changeset(cs)
    for _, m in ipairs({ "op", "pk", "new", "old", "next", "conflict",
                         "fk_conflicts", "finalize" }) do
      assert.is_equal("function", type(it[m]), "iter:" .. m)
    end
    it:finalize()
    db:close()
  end)

  it("returns a rebaser userdata with rebase/delete", function()
    local db = sqlite3.open_memory()
    local reb = db:create_rebaser()
    assert.is_equal("userdata", type(reb))
    assert.is_equal("function", type(reb.rebase))
    assert.is_equal("function", type(reb.delete))
    reb:delete()
    db:close()
  end)

  it("registers the documented session constants", function()
    assert.is_equal(1, sqlite3.CHANGESET_DATA)
    assert.is_equal(2, sqlite3.CHANGESET_NOTFOUND)
    assert.is_equal(3, sqlite3.CHANGESET_CONFLICT)
    assert.is_equal(4, sqlite3.CHANGESET_CONSTRAINT)
    assert.is_equal(5, sqlite3.CHANGESET_FOREIGN_KEY)
    assert.is_equal(0, sqlite3.CHANGESET_OMIT)
    assert.is_equal(1, sqlite3.CHANGESET_REPLACE)
    assert.is_equal(2, sqlite3.CHANGESET_ABORT)
    assert.is_equal(1, sqlite3.CHANGESETAPPLY_NOSAVEPOINT)
    -- statement opcodes carried inside changesets
    assert.is_equal(18, sqlite3.INSERT)
    assert.is_equal(23, sqlite3.UPDATE)
    assert.is_equal(9, sqlite3.DELETE)
    assert.is_equal(100, sqlite3.ROW)
    assert.is_equal(101, sqlite3.DONE)
  end)
end)

-- ------------------------------------------------------------------
-- 2. recording behaviour
-- ------------------------------------------------------------------
describe("lsqlite3 session: recording", function()
  it("records nothing before attach and everything after", function()
    local db = M.new_db()
    local ses = db:create_session()
    db:exec("UPDATE t SET a='pre' WHERE id=1")   -- before attach: invisible
    assert.is_true(ses:isempty())
    assert.is_equal(0, #ses:changeset())

    ses:attach()
    db:exec("UPDATE t SET a='post' WHERE id=1")
    assert.is_false(ses:isempty())
    assert.is_true(#ses:changeset() > 0)
    ses:delete()
    db:close()
  end)

  it("records INSERT, UPDATE and DELETE with full payloads", function()
    local db = M.new_db({ {1, "x0", "P"}, {2, "y0", "Q"} })
    local cs = M.record(db, function(d)
      d:exec("INSERT INTO t VALUES(3,'z0','R')")
      d:exec("UPDATE t SET a='x1' WHERE id=1")
      d:exec("DELETE FROM t WHERE id=2")
    end)
    local ops = M.iter_ops(db, cs)
    local by = {}
    for _, o in ipairs(ops) do by[o.op] = o end
    -- all three kinds were captured exactly once
    assert.is_equal(3, #ops)
    assert.is_not_nil(by[INSERT], "INSERT change missing")
    assert.is_not_nil(by[UPDATE], "UPDATE change missing")
    assert.is_not_nil(by[DELETE], "DELETE change missing")
    -- pk flags: id is the only PK column; non-PK columns render as "?"
    assert.is_equal("true,?,?", by[UPDATE].pk)
    -- DELETE carries the whole old row; INSERT the whole new row
    assert.is_equal("2,y0,Q", by[DELETE].old)
    assert.is_equal("3,z0,R", by[INSERT].new)
    -- UPDATE records changed columns; the untouched b column is "?"
    assert.is_equal("1,x0,?", by[UPDATE].old)
    assert.is_equal("?,x1,?", by[UPDATE].new)
    assert.is_false(by[INSERT].indirect)   -- direct changes are not indirect
    db:close()
  end)

  it("only attaches the named table when requested", function()
    local db = sqlite3.open_memory()
    db:exec("CREATE TABLE t(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("CREATE TABLE u(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("INSERT INTO t VALUES(1,'x'); INSERT INTO u VALUES(1,'x')")
    local ses = db:create_session()
    ses:attach("t")
    db:exec("UPDATE t SET a='t1'; UPDATE u SET a='u1'")
    local ops = M.iter_ops(db, ses:changeset())
    assert.is_equal(1, #ops)
    assert.is_equal("t", ops[1].tab)   -- the change on u was ignored
    ses:delete()
    db:close()
  end)

  it("supports a table filter callback on attach", function()
    local db = sqlite3.open_memory()
    db:exec("CREATE TABLE keep(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("CREATE TABLE dropme(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("INSERT INTO keep VALUES(1,'k'); INSERT INTO dropme VALUES(1,'d')")
    local ses = db:create_session()
    local seen = {}
    ses:attach(function(tab, udata)
      table.insert(seen, tab)
      return tab == "keep" and 1 or 0     -- 1 allow, 0 skip
    end)
    db:exec("UPDATE keep SET a='k2'; UPDATE dropme SET a='d2'")
    local ops = M.iter_ops(db, ses:changeset())
    assert.is_equal(1, #ops)
    assert.is_equal("keep", ops[1].tab)
    assert.is_equal("keep,dropme", table.concat(seen, ","))
    ses:delete()
    db:close()
  end)

  it("can be enabled / disabled at runtime", function()
    local db = M.new_db({ {1, "a", "P"} })
    local ses = db:create_session()
    ses:attach()
    -- enable/indirect set the flag when given a value and report it back
    assert.is_false(ses:enable(false))
    db:exec("UPDATE t SET a='x' WHERE id=1")
    assert.is_true(ses:isempty())             -- disabled: nothing recorded
    assert.is_equal(0, #ses:changeset())
    assert.is_true(ses:enable(true))
    db:exec("UPDATE t SET a='y' WHERE id=1")
    assert.is_false(ses:isempty())
    assert.is_true(#ses:changeset() > 0)
    ses:delete()
    db:close()
  end)

  it("marks changes recorded under indirect mode", function()
    local db = M.new_db({ {1, "a", "P"} })
    local ses = db:create_session()
    ses:attach()
    assert.is_true(ses:indirect(true))
    db:exec("UPDATE t SET a='ind' WHERE id=1")
    local ops = M.iter_ops(db, ses:changeset())
    assert.is_equal(1, #ops)
    assert.is_true(ops[1].indirect)
    ses:delete()
    db:close()
  end)

  it("can diff two attached databases into the session", function()
    local db = sqlite3.open_memory()
    db:exec("CREATE TABLE t(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("INSERT INTO t VALUES(1,'A0')")        -- row also on aux (differs)
    db:exec("INSERT INTO t VALUES(2,'only-main')") -- absent on aux  => INSERT
    local aux = "/tmp/lsqlite3_sess_diff_" .. tostring(math.random(1e9)) .. ".db"
    db:exec("ATTACH DATABASE '" .. aux .. "' AS aux")
    db:exec("CREATE TABLE aux.t(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("INSERT INTO aux.t VALUES(1,'B0')")        -- differs      => UPDATE
    db:exec("INSERT INTO aux.t VALUES(3,'only-aux')")  -- absent on main => DELETE
    local ses = db:create_session()
    ses:attach("t")
    assert.is_true(ses:diff("aux", "t"))
    local ops = M.iter_ops(db, ses:changeset())
    local by = {}
    for _, o in ipairs(ops) do by[o.op] = o end
    assert.is_equal(3, #ops)
    assert.is_equal("1,B0", by[UPDATE].old)
    assert.is_equal("?,A0", by[UPDATE].new)
    assert.is_equal("2,only-main", by[INSERT].new)
    assert.is_equal("3,only-aux", by[DELETE].old)
    db:exec("DETACH DATABASE aux")
    ses:delete()
    db:close()
    os.remove(aux)
  end)
end)

-- ------------------------------------------------------------------
-- 3. changeset / patchset transport as binary blobs
-- ------------------------------------------------------------------
describe("lsqlite3 session: changeset & patchset blobs", function()
  it("returns binary string blobs", function()
    local db = M.new_db()
    local ses = db:create_session()
    ses:attach()
    db:exec("DELETE FROM t WHERE id=1")
    assert.is_equal("string", type(ses:changeset()))
    assert.is_equal("string", type(ses:patchset()))
    assert.is_true(#ses:changeset() > 0)
    assert.is_true(#ses:patchset() > 0)
    ses:delete()
    db:close()
  end)

  it("returns an empty blob when nothing changed", function()
    local db = M.new_db()
    local ses = db:create_session()
    ses:attach()
    assert.is_true(ses:isempty())
    assert.is_equal(0, #ses:changeset())
    assert.is_equal(0, #ses:patchset())
    ses:delete()
    db:close()
  end)

  it("patchset stores only the columns that actually changed", function()
    local db = M.new_db({ {1, "a", "old-b"} })
    local cs, ps
    do
      local ses = db:create_session()
      ses:attach("t")
      db:exec("UPDATE t SET a='a2' WHERE id=1")
      cs = ses:changeset()
      ps = ses:patchset()
      ses:delete()
    end
    local cs_ops = M.iter_ops(db, cs)
    local ps_ops = M.iter_ops(db, ps)
    -- changeset UPDATE: old/new with "?" for the unchanged b column
    assert.is_equal(UPDATE, cs_ops[1].op)
    assert.is_equal("1,a,?", cs_ops[1].old)
    assert.is_equal("?,a2,?", cs_ops[1].new)
    -- patchset UPDATE: old only the PK, new only the changed column
    assert.is_equal(UPDATE, ps_ops[1].op)
    assert.is_equal("1,?,?", ps_ops[1].old)
    assert.is_equal("?,a2,?", ps_ops[1].new)
    db:close()
  end)

  it("changeset can be applied to another database with the same schema", function()
    local src = M.new_db()
    local cs = M.record(src, function(d)
      d:exec("INSERT INTO t VALUES(3,'z0','R')")
      d:exec("UPDATE t SET a='x1' WHERE id=1")
    end)
    local dst = M.new_db()
    local ok, err = dst:apply_changeset(cs)
    assert.is_true(ok, err)
    assert.is_equal("1=x1 2=y0 3=z0", M.dump(dst))
    src:close()
    dst:close()
  end)

  it("applying an empty changeset is a no-op success", function()
    local src = M.new_db()
    local empty = M.record(src, function() end)
    assert.is_equal(0, #empty)
    local dst = M.new_db()
    assert.is_true(dst:apply_changeset(empty))
    assert.is_equal("1=x0 2=y0", M.dump(dst))
    src:close()
    dst:close()
  end)
end)

-- ------------------------------------------------------------------
-- 4. iterate_changeset
-- ------------------------------------------------------------------
describe("lsqlite3 session: iterate_changeset", function()
  it("walks every recorded change until DONE", function()
    local db = M.new_db({ {1, "a", "P"}, {2, "b", "Q"}, {3, "c", "R"} })
    local cs = M.record(db, function(d)
      d:exec("UPDATE t SET a='A' WHERE id=1")
      d:exec("DELETE FROM t WHERE id=2")
      d:exec("INSERT INTO t VALUES(4,'D','S')")
    end)
    local ops, rc = M.iter_ops(db, cs)
    assert.is_equal(DONE, rc)
    assert.is_equal(3, #ops)
    local by = {}
    for _, o in ipairs(ops) do by[o.op] = o end
    assert.is_equal("1,a,?", by[UPDATE].old)
    assert.is_equal("?,A,?", by[UPDATE].new)
    assert.is_equal("2,b,Q", by[DELETE].old)
    assert.is_equal("4,D,S", by[INSERT].new)
    assert.is_equal("t", by[INSERT].tab)
    db:close()
  end)

  it("finalize is idempotent and reusable", function()
    local db = M.new_db()
    local cs = M.record(db, function(d) d:exec("UPDATE t SET a='z' WHERE id=1") end)
    local it = db:iterate_changeset(cs)
    assert.is_equal(ROW, it:next())
    assert.is_true(it:finalize())
    assert.is_true(it:finalize())
    db:close()
  end)

  it("fk_conflicts counts referencing rows on a real FK conflict", function()
    -- Deleting a parent row that still has a child under PRAGMA foreign_keys
    -- raises CHANGESET_FOREIGN_KEY; fk_conflicts reports how many rows block
    -- the delete. Resolving with OMIT skips the delete and apply succeeds.
    local function schema(db)
      db:exec("CREATE TABLE parent(id INTEGER PRIMARY KEY, v TEXT)")
      db:exec("CREATE TABLE child(id INTEGER PRIMARY KEY, pid"
              .. " INTEGER REFERENCES parent(id))")
      db:exec("INSERT INTO parent VALUES(1,'p')")
      db:exec("INSERT INTO child VALUES(10,1)")
    end
    local src = sqlite3.open_memory(); schema(src)
    local cs = M.record(src, function(d) d:exec("DELETE FROM parent WHERE id=1") end)
    local dst = sqlite3.open_memory(); schema(dst)
    dst:exec("PRAGMA foreign_keys=ON")
    local eC, fkct
    local ok, err = dst:apply_changeset(cs, function(ud, eEv, iter)
      eC, fkct = eEv, iter:fk_conflicts()
      return CHANGESET_OMIT
    end)
    assert.is_true(ok, err)
    assert.is_equal(CHANGESET_FOREIGN_KEY, eC)
    assert.is_equal(1, fkct)                -- the one referencing child row
    src:close()
    dst:close()
  end)

  it("rejects corrupt changeset blobs on iteration", function()
    local db = M.new_db()
    local it = db:iterate_changeset("this is not a changeset")
    assert.is_not_nil(it)                 -- validation happens on next()
    local rc = it:next()
    assert.is_not_equal(ROW, rc)
    assert.is_not_equal(DONE, rc)         -- rc is SQLITE_CORRUPT (11)
    it:finalize()
    db:close()
  end)
end)

-- ------------------------------------------------------------------
-- 5. invert / concat
-- ------------------------------------------------------------------
describe("lsqlite3 session: invert & concat", function()
  it("invert_changeset produces an undo set", function()
    local src = M.new_db()
    local cs = M.record(src, function(d)
      d:exec("INSERT INTO t VALUES(3,'z0','R')")
      d:exec("UPDATE t SET a='x1' WHERE id=1")
      d:exec("DELETE FROM t WHERE id=2")
    end)
    local db = M.new_db()
    assert.is_true(db:apply_changeset(cs))
    assert.is_equal("1=x1 3=z0", M.dump(db))
    local inv = db:invert_changeset(cs)
    assert.is_equal("string", type(inv))
    assert.is_true(#inv > 0)
    assert.is_true(db:apply_changeset(inv))
    assert.is_equal("1=x0 2=y0", M.dump(db))  -- back to the original state
    src:close()
    db:close()
  end)

  it("concat_changeset merges several changesets in order", function()
    local src = M.new_db()
    local cs1 = M.record(src, function(d) d:exec("INSERT INTO t VALUES(10,'a','P')") end)
    local cs2 = M.record(src, function(d) d:exec("INSERT INTO t VALUES(20,'b','Q')") end)
    local both = src:concat_changeset({ cs1, cs2 })
    assert.is_equal("string", type(both))
    local db = M.new_db()
    assert.is_true(db:apply_changeset(both))
    assert.is_equal("1=x0 2=y0 10=a 20=b", M.dump(db))
    src:close()
    db:close()
  end)

  it("concat of an empty changeset list yields an empty blob", function()
    local db = M.new_db()
    assert.is_equal("", db:concat_changeset({}))
    db:close()
  end)
end)

-- ------------------------------------------------------------------
-- 6. apply_changeset & conflict handling
-- ------------------------------------------------------------------
describe("lsqlite3 session: apply_changeset", function()
  it("applies cleanly when the target matches the changeset baseline", function()
    local src = M.new_db({ {1, "x0", "P"} })
    local cs = M.record(src, function(d) d:exec("UPDATE t SET a='x1' WHERE id=1") end)
    local dst = M.new_db({ {1, "x0", "P"} })
    assert.is_true(dst:apply_changeset(cs))
    assert.is_equal("1=x1", M.dump(dst))
    src:close()
    dst:close()
  end)

  it("reports CHANGESET_DATA when the row to update differs", function()
    local src = M.new_db({ {1, "x0", "P"} })
    local cs = M.record(src, function(d) d:exec("UPDATE t SET a='x1' WHERE id=1") end)
    local dst = M.new_db({ {1, "OTHER", "P"} })   -- baseline mismatch
    local seen = {}
    local ok, err = dst:apply_changeset(cs, function(ud, eC, iter, zTab, op)
      seen = { eC, zTab, op }
      return CHANGESET_OMIT
    end)
    assert.is_true(ok, err)
    assert.is_equal(CHANGESET_DATA, seen[1])
    assert.is_equal("t", seen[2])
    assert.is_equal(UPDATE, seen[3])
    src:close()
    dst:close()
  end)

  it("reports CHANGESET_NOTFOUND when the target row is missing", function()
    local src = M.new_db({ {1, "x0", "P"}, {2, "y0", "Q"} })
    local cs = M.record(src, function(d) d:exec("UPDATE t SET a='y1' WHERE id=2") end)
    local dst = M.new_db({ {1, "x0", "P"} })      -- row 2 absent
    local seen = {}
    local ok = dst:apply_changeset(cs, function(ud, eC) seen = eC; return CHANGESET_OMIT end)
    assert.is_true(ok)
    assert.is_equal(CHANGESET_NOTFOUND, seen)
    src:close()
    dst:close()
  end)

  it("reports CHANGESET_CONFLICT when inserting an existing PK", function()
    local src = M.new_db({ {1, "x0", "P"} })
    local cs = M.record(src, function(d) d:exec("INSERT INTO t VALUES(9,'nine','N')") end)
    local dst = M.new_db({ {1, "x0", "P"}, {9, "existing", "E"} })
    local seen = {}
    local ok = dst:apply_changeset(cs, function(ud, eC) seen = eC; return CHANGESET_OMIT end)
    assert.is_true(ok)
    assert.is_equal(CHANGESET_CONFLICT, seen)
    src:close()
    dst:close()
  end)

  it("CHANGESET_OMIT skips only the conflicting change", function()
    local src = M.new_db({ {1, "a0", "P"}, {2, "b0", "Q"} })
    local cs = M.record(src, function(d)
      d:exec("UPDATE t SET a='a1' WHERE id=1")    -- applies fine on dst
      d:exec("UPDATE t SET a='b1' WHERE id=2")    -- conflicts on dst
    end)
    local dst = M.new_db({ {1, "a0", "P"}, {2, "zz", "Z"} })
    local ok, err = dst:apply_changeset(cs, function() return CHANGESET_OMIT end)
    assert.is_true(ok, err)
    assert.is_equal("1=a1 2=zz", M.dump(dst))     -- first applied, second omitted
    src:close()
    dst:close()
  end)

  it("CHANGESET_REPLACE overwrites the conflicting row", function()
    local src = M.new_db({ {1, "a0", "P"} })
    local cs = M.record(src, function(d)
      d:exec("INSERT INTO t VALUES(9,'nine','N')")
      d:exec("UPDATE t SET a='a1' WHERE id=1")
    end)
    local dst = M.new_db({ {1, "a0", "P"}, {9, "old", "O"} })
    local ok = dst:apply_changeset(cs, function(ud, eC)
      return eC == CHANGESET_CONFLICT and CHANGESET_REPLACE or CHANGESET_OMIT
    end)
    assert.is_true(ok)
    assert.is_equal("1=a1 9=nine", M.dump(dst))   -- old PK row replaced
    src:close()
    dst:close()
  end)

  it("CHANGESET_ABORT aborts atomically and rolls back earlier changes", function()
    local src = M.new_db({ {1, "a0", "P"}, {2, "b0", "Q"} })
    local cs = M.record(src, function(d)
      d:exec("UPDATE t SET a='a1' WHERE id=1")    -- would apply fine
      d:exec("UPDATE t SET a='b1' WHERE id=2")    -- conflicts => ABORT
    end)
    local dst = M.new_db({ {1, "a0", "P"}, {2, "zz", "Z"} })
    local n = 0
    local ok, err = dst:apply_changeset(cs, function(ud, eC)
      n = n + 1
      return CHANGESET_ABORT
    end)
    assert.is_nil(ok)
    assert.is_number(err)                   -- rc returned as the second value
    assert.is_equal(1, n)
    -- the whole apply was rolled back to its pre-apply state
    assert.is_equal("1=a0 2=zz", M.dump(dst))
    src:close()
    dst:close()
  end)

  it("conflict callback can introspect the offending change", function()
    local src = M.new_db({ {1, "a0", "P"} })
    local cs = M.record(src, function(d) d:exec("UPDATE t SET a='a1' WHERE id=1") end)
    local dst = M.new_db({ {1, "OTHER", "P"} })
    local cap
    local ok = dst:apply_changeset(cs, function(ud, eC, iter, zTab, op, bInd)
      cap = { pk = iter:pk(), old = iter:old(), new = iter:new() }
      return CHANGESET_OMIT
    end)
    assert.is_true(ok)
    assert.is_not_nil(cap)
    -- inside a conflict the iterator exposes PK + the recorded old/new
    assert.is_equal("true,?,?", M.vdump(cap.pk))
    assert.is_equal("1,a0,?", M.vdump(cap.old))
    assert.is_equal("?,a1,?", M.vdump(cap.new))
    src:close()
    dst:close()
  end)

  it("supports a table filter callback during apply", function()
    local src = sqlite3.open_memory()
    src:exec("CREATE TABLE a(id INTEGER PRIMARY KEY, v TEXT)")
    src:exec("CREATE TABLE b(id INTEGER PRIMARY KEY, v TEXT)")
    src:exec("INSERT INTO a VALUES(1,'a'); INSERT INTO b VALUES(1,'b')")
    local cs = M.record(src, function(d)
      d:exec("UPDATE a SET v='a1'; UPDATE b SET v='b1'")
    end)
    local dst = sqlite3.open_memory()
    dst:exec("CREATE TABLE a(id INTEGER PRIMARY KEY, v TEXT)")
    dst:exec("CREATE TABLE b(id INTEGER PRIMARY KEY, v TEXT)")
    dst:exec("INSERT INTO a VALUES(1,'a'); INSERT INTO b VALUES(1,'b')")
    local calls = {}
    local ok, err = dst:apply_changeset(cs,
      function(zTab)                       -- 1) table filter callback
        table.insert(calls, zTab)
        return zTab == "a" and 1 or 0      -- only table a is accepted
      end,
      function() return CHANGESET_OMIT end)  -- 2) conflict callback
    assert.is_true(ok, err)
    assert.is_equal("a,b", table.concat(calls, ","))
    assert.is_equal("1=a1", M.dump(dst, "a", "id", "v"))
    assert.is_equal("1=b", M.dump(dst, "b", "id", "v"))  -- b skipped
    src:close()
    dst:close()
  end)

  it("apply with a rebaser returns a rebase blob", function()
    -- A rebaser lets an offline node apply somebody else's changes without
    -- discarding its own concurrent edits to the same rows.
    local master = M.new_db({ {1, "a0", "P"} })
    local master_cs = M.record(master, function(d)
      d:exec("UPDATE t SET a='from-master' WHERE id=1")
    end)
    local slave = M.new_db({ {1, "a0", "P"} })
    M.record(slave, function(d)           -- slave's own concurrent edit
      d:exec("UPDATE t SET a='from-slave' WHERE id=1")
    end)
    local reb = slave:create_rebaser()
    local rebased, rc = slave:apply_changeset(
      master_cs,
      function(zTab) return 1 end,        -- filter: allow all tables
      function() return CHANGESET_OMIT end, -- conflict policy
      nil,                                -- udata
      reb)                                -- rebaser
    assert.is_not_nil(rebased, "expected a rebase blob, rc=" .. tostring(rc))
    assert.is_equal("string", type(rebased))
    reb:delete()
    master:close()
    slave:close()
  end)
end)

-- ------------------------------------------------------------------
-- 7. rebaser object
-- ------------------------------------------------------------------
describe("lsqlite3 session: rebaser", function()
  it("rebases a changeset into a new valid changeset blob", function()
    local db = M.new_db({ {1, "a0", "P"} })
    local cs = M.record(db, function(d) d:exec("UPDATE t SET a='a1' WHERE id=1") end)
    local reb = db:create_rebaser()
    local out = reb:rebase(cs)
    assert.is_equal("string", type(out))
    assert.is_true(#out > 0)
    -- the rebased blob is still a well-formed changeset we can walk
    local ops, rc = M.iter_ops(db, out)
    assert.is_equal(DONE, rc)
    assert.is_equal(1, #ops)
    assert.is_equal(UPDATE, ops[1].op)
    reb:delete()
    db:close()
  end)
end)

-- ------------------------------------------------------------------
-- 8. error handling
-- ------------------------------------------------------------------
describe("lsqlite3 session: error handling", function()
  it("returns nil + error code for corrupt changesets on invert", function()
    local db = M.new_db()
    local out, rc = db:invert_changeset("garbage-not-a-changeset")
    assert.is_nil(out)
    assert.is_number(rc)
    assert.is_true(rc ~= 0)
    db:close()
  end)

  it("apply silently succeeds when the target table is absent", function()
    -- SQLite session apply does not fail on a missing table (verified);
    -- record that behaviour explicitly so future changes are noticed.
    local src = M.new_db()
    local cs = M.record(src, function(d) d:exec("INSERT INTO t VALUES(5,'x','P')") end)
    local dst = sqlite3.open_memory()
    dst:exec("CREATE TABLE other(id INTEGER PRIMARY KEY)")  -- no table t
    assert.is_true(dst:apply_changeset(cs))
    src:close()
    dst:close()
  end)

  it("invalid conflict-handler results abort apply with an error code", function()
    local src = M.new_db({ {1, "a0", "P"} })
    local cs = M.record(src, function(d) d:exec("UPDATE t SET a='a1' WHERE id=1") end)
    local dst = M.new_db({ {1, "zz", "Z"} })
    local ok, rc = dst:apply_changeset(cs, function() return 42 end)
    assert.is_nil(ok)
    assert.is_number(rc)
    assert.is_true(rc ~= 0)             -- SQLITE_MISUSE is reported
    src:close()
    dst:close()
  end)

  it("lua errors surface from callbacks", function()
    local src = M.new_db({ {1, "a0", "P"} })
    local cs = M.record(src, function(d) d:exec("UPDATE t SET a='a1' WHERE id=1") end)
    local dst = M.new_db({ {1, "zz", "Z"} })
    assert.has.errors(function()
      dst:apply_changeset(cs, function() error("boom from conflict cb") end)
    end)
    src:close()
    dst:close()
  end)

  it("using a deleted session raises an error", function()
    local db = M.new_db()
    local ses = db:create_session()
    ses:attach()
    ses:delete()
    assert.has.errors(function() ses:changeset() end)
    db:close()
  end)

  it("using a deleted rebaser raises an error", function()
    local db = sqlite3.open_memory()
    local reb = db:create_rebaser()
    reb:delete()
    assert.has.errors(function() reb:rebase("x") end)
    db:close()
  end)
end)

-- ------------------------------------------------------------------
-- 9. concurrency model: many connections / many sessions / interleaved
--
-- Plain Lua is single-threaded, so "concurrency" here models the topology
-- used in real deployments: each worker owns its own connection and session;
-- the binary changeset is the only object that crosses boundaries.
-- ------------------------------------------------------------------
describe("lsqlite3 session: multi-connection / multi-session model", function()
  it("two sessions on one db track different tables independently", function()
    local db = sqlite3.open_memory()
    db:exec("CREATE TABLE t(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("CREATE TABLE u(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("INSERT INTO t VALUES(1,'t0'); INSERT INTO u VALUES(1,'u0')")
    local st = db:create_session(); st:attach("t")
    local su = db:create_session(); su:attach("u")
    db:exec("UPDATE t SET a='t1'; UPDATE u SET a='u1'")
    assert.is_equal(1, #M.iter_ops(db, st:changeset()))
    assert.is_equal(1, #M.iter_ops(db, su:changeset()))
    assert.is_equal("t", M.iter_ops(db, st:changeset())[1].tab)
    assert.is_equal("u", M.iter_ops(db, su:changeset())[1].tab)
    st:delete(); su:delete()
    db:close()
  end)

  it("interleaved writers on disjoint keys converge without conflict", function()
    -- N independent replicas each edit their own key, then fan the changesets
    -- out to every other replica. Applied rows are not re-recorded because no
    -- session is active while applying.
    local function replica()
      local db = sqlite3.open_memory()
      db:exec("CREATE TABLE kv(k INTEGER PRIMARY KEY, v TEXT)")
      for i = 1, 4 do
        db:exec(string.format("INSERT INTO kv VALUES(%d,'r0')", i))
      end
      return db
    end
    local n = 4
    local nodes = {}
    for i = 1, n do nodes[i] = replica() end

    local csets = {}
    for i = 1, n do
      csets[i] = M.record(nodes[i], function(db)
        db:exec(string.format("UPDATE kv SET v='n%d' WHERE k=%d", i, i))
      end)
    end

    for i = 1, n do                    -- full mesh of changeset applications
      for j = 1, n do
        if i ~= j then
          local ok, err = nodes[i]:apply_changeset(csets[j])
          assert.is_true(ok, err)
        end
      end
    end

    local expect = "1=n1 2=n2 3=n3 4=n4"
    for i = 1, n do
      assert.is_equal(expect, M.dump(nodes[i], "kv", "k", "v"), "node " .. i)
    end
    for i = 1, n do nodes[i]:close() end
  end)

  it("handles a concurrent same-row edit via a conflict policy", function()
    -- Both nodes edit key 1 concurrently. Exchanging changesets creates a
    -- conflict; resolving it with OMIT keeps each node's local value, which
    -- is deterministic and safe (the next round can still be retried).
    local function mk()
      local db = sqlite3.open_memory()
      db:exec("CREATE TABLE kv(k INTEGER PRIMARY KEY, v TEXT)")
      db:exec("INSERT INTO kv VALUES(1,'base')")
      return db
    end
    local A, B = mk(), mk()
    local csA = M.record(A, function(d) d:exec("UPDATE kv SET v='A-wins' WHERE k=1") end)
    local csB = M.record(B, function(d) d:exec("UPDATE kv SET v='B-wins' WHERE k=1") end)

    local function apply_local_win(db, cs)
      local ok, err = db:apply_changeset(cs, function() return CHANGESET_OMIT end)
      assert.is_true(ok, err)
    end
    apply_local_win(A, csB)
    apply_local_win(B, csA)
    assert.is_equal("1=A-wins", M.dump(A, "kv", "k", "v"))
    assert.is_equal("1=B-wins", M.dump(B, "kv", "k", "v"))
    A:close(); B:close()
  end)
end)

-- ------------------------------------------------------------------
-- 10. two-way synchronization between two nodes (round-trip model)
--
-- Mirrors the design in doc/lsqlite3-sync.md: each node records local edits
-- in a short-lived session, snapshots the changeset at sync time and then
-- rebuilds its session for the next edit window. Remote changes are applied
-- while no session is active, so they are never re-broadcast (no echo-back).
-- ------------------------------------------------------------------
describe("lsqlite3 session: two-way node sync", function()
  local function node()
    return M.new_db({ {1, "x0", "P"}, {2, "y0", "Q"} })
  end

  it("converges after two rounds of local edits + full exchange", function()
    local A, B = node(), node()

    -- round 1: independent local edits -------------------------------
    local csA1 = M.record(A, function(d) d:exec("UPDATE t SET a='x1' WHERE id=1") end)
    local csB1 = M.record(B, function(d) d:exec("UPDATE t SET a='y1' WHERE id=2") end)

    assert.is_true(A:apply_changeset(csB1))
    assert.is_true(B:apply_changeset(csA1))
    assert.is_equal("1=x1 2=y1", M.dump(A))
    assert.is_equal("1=x1 2=y1", M.dump(B))

    -- round 2: new local edits + echo-back check ---------------------
    local csA2 = M.record(A, function(d) d:exec("UPDATE t SET a='x2' WHERE id=1") end)
    local csB2 = M.record(B, function(d) d:exec("INSERT INTO t VALUES(3,'z0','R')") end)

    -- B's round-2 changeset must NOT echo A's round-1 row-1 edit back
    local opsB = M.iter_ops(B, csB2)
    assert.is_equal(1, #opsB)
    assert.is_equal(INSERT, opsB[1].op)
    assert.is_equal("3,z0,R", opsB[1].new)   -- only B's own insert

    assert.is_true(B:apply_changeset(csA2))
    assert.is_true(A:apply_changeset(csB2))
    assert.is_equal("1=x2 2=y1 3=z0", M.dump(A))
    assert.is_equal("1=x2 2=y1 3=z0", M.dump(B))

    A:close(); B:close()
  end)

  it("undo of a sync round restores both nodes", function()
    local A, B = node(), node()
    local csA = M.record(A, function(d)
      d:exec("INSERT INTO t VALUES(5,'five','F')")
      d:exec("DELETE FROM t WHERE id=2")
    end)
    assert.is_true(B:apply_changeset(csA))
    assert.is_equal("1=x0 5=five", M.dump(B))

    -- invert the round on B, and on A too (A holds its own copy of the edits)
    local undo = A:invert_changeset(csA)
    assert.is_true(B:apply_changeset(undo))
    assert.is_equal("1=x0 2=y0", M.dump(B))
    assert.is_true(A:apply_changeset(undo))
    assert.is_equal("1=x0 2=y0", M.dump(A))

    A:close(); B:close()
  end)
end)

-- ------------------------------------------------------------------
-- 11. multi-process nodes
--
-- Real process isolation: a child luajit process opens its own in-memory
-- sqlite db, records edits into a session and writes the binary changeset to
-- a file. The parent reads that file and applies it to its own database.
-- Skipped (pending) where io.popen / OS tools are unavailable.
-- ------------------------------------------------------------------
describe("lsqlite3 session: multi-process nodes", function()
  local ROOT = os.getenv("PWD") or "."
  local script_path
  local CHILD = [[
local out, id, tag = arg[1], tonumber(arg[2]), arg[3]
package.cpath = __CPATH__ .. package.cpath
local s = require("lsqlite3")
local db = s.open_memory()
db:exec("CREATE TABLE t(id INTEGER PRIMARY KEY, a TEXT)")
db:exec("INSERT INTO t VALUES(1,'x0')")
local ses = db:create_session()
ses:attach()
db:exec(string.format("INSERT INTO t VALUES(%d,'%s')", id, tag))
local f = assert(io.open(out, "wb"))
f:write(ses:changeset())
f:close()
print("child-done")
]]

  setup(function()
    local q = string.format("%q", ROOT .. "/.?.so;")
    local src = CHILD:gsub("__CPATH__", q)  -- cache: gsub() returns 2 values
    script_path = os.tmpname() .. ".lua"
    local f = assert(io.open(script_path, "w"))
    f:write(src)
    f:close()
  end)

  teardown(function()
    if script_path then os.remove(script_path) end
  end)

  local function base_node()
    local db = sqlite3.open_memory()
    db:exec("CREATE TABLE t(id INTEGER PRIMARY KEY, a TEXT)")
    db:exec("INSERT INTO t VALUES(1,'x0')")
    return db
  end

  local function run_child(cmd)
    local pipe = io.popen(cmd .. " 2>&1")
    if not pipe then return nil, "io.popen unavailable" end
    local out = pipe:read("*a")
    pipe:close()
    return out
  end

  it("applies a changeset produced by a separate OS process", function()
    local out = os.tmpname()
    local cmd = string.format("luajit %q %q 5 child", script_path, out)
    local res = run_child(cmd)
    if not res then pending("io.popen unavailable"); return end
    assert.is_true(string.find(res, "child-done", 1, true) ~= nil, res)
    local f = io.open(out, "rb")
    if not f then pending("child wrote no changeset: " .. res); return end
    local cs = f:read("*a"); f:close()
    assert.is_true(#cs > 0)
    local db = base_node()
    local ok, err = db:apply_changeset(cs)
    assert.is_true(ok, err)
    assert.is_equal("1=x0 5=child", M.dump(db))
    db:close(); os.remove(out)
  end)

  it("merges concurrent changesets from parallel OS processes", function()
    local outA, outB = os.tmpname(), os.tmpname()
    local q = string.format("%q", script_path)
    local cmd = string.format(
      "luajit %s %q 10 A & luajit %s %q 20 B & wait",
      q, outA, q, outB)
    local res = run_child(cmd)
    if not res then pending("io.popen unavailable"); return end
    assert.is_true(string.find(res, "child-done", 1, true) ~= nil, res)
    local function read_cs(p)
      local f = io.open(p, "rb")
      if not f then return nil end
      local c = f:read("*a"); f:close()
      return c
    end
    local csA, csB = read_cs(outA), read_cs(outB)
    assert.is_not_nil(csA, "child A wrote no changeset")
    assert.is_not_nil(csB, "child B wrote no changeset")
    assert.is_true(#csA > 0 and #csB > 0)
    local db = base_node()
    local both = db:concat_changeset({ csA, csB })
    assert.is_true(db:apply_changeset(both))
    assert.is_equal("1=x0 10=A 20=B", M.dump(db))
    db:close(); os.remove(outA); os.remove(outB)
  end)
end)
