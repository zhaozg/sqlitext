
local function showdata(db)
	for r in db:nrows("select * from foo") do print("select: ", r.k,
			r.a, r.b, r.c)
	end
end


local sqlite3 = require("lsqlite3")
local db = sqlite3.open_memory()
local ses = db:create_session()

print("create", db:exec("create table foo(k primary key, a, b, c)"))
print("insert", db:exec("insert into foo(k, a, b, c) values (1, 'v1', 'v1', 'v1')"))

ses:attach()
print("update/1", db:exec("update foo set a = 'v2', b = 'v2' where k = 1"))
showdata(db)
local cs2 = ses:changeset()

print("update/2", db:exec("update foo set a = 'v3', b = 'v1' where k = 1"))
showdata(db)
local cs3 = ses:changeset()

print("apply1/abort", db:apply_changeset(cs2,
	function(...) print("filter", ...) return 1 end,
	function(...) print("conflict", ...) return sqlite3.CHANGESET_ABORT end))
showdata(db)

local cs4 = db:concat_changeset { db:invert_changeset(cs3), cs2, cs3 }
print("apply2/no-conflict", db:apply_changeset(cs4,
	function(...) print("filter", ...) return 1 end,
	function(...) print("conflict", ...) return sqlite3.CHANGESET_REPLACE end))
showdata(db)

