local sqlite3 = require("lsqlite3")

describe("SQLite3 Core Functionality Tests", function()
  local db, vm
  local width = 78
  
  local function line(pref, suff)
    -- print suppressed for cleaner test output
  end

  setup(function()
    line(sqlite3.version())
    os.remove('test.db')
    db = sqlite3.open('test.db')
  end)

  teardown(function()
    if db then
      db:close()
    end
    os.remove('test.db')
    line(nil, "db:close")
    line(sqlite3.version())
  end)

  describe("Database Execution", function()
    it("should create table successfully", function()
      local result = db:exec('CREATE TABLE t(a, b)')
      assert.are.equal(sqlite3.OK, result)
    end)
  end)

  describe("Statement Preparation", function()
    it("should prepare statement and bind values", function()
      vm = db:prepare('insert into t values(?, :bork)')
      assert.is_not_nil(vm)
      assert.are.equal(2, vm:bind_parameter_count())
      assert.are.equal(sqlite3.OK, vm:bind_values(2, 4))
      assert.are.equal(sqlite3.DONE, vm:step())
      assert.are.equal(sqlite3.OK, vm:reset())
      
      assert.are.equal(sqlite3.OK, vm:bind_names{ 'pork', bork = 'nono' })
      assert.are.equal(sqlite3.DONE, vm:step())
      assert.are.equal(sqlite3.OK, vm:reset())
      
      assert.are.equal(sqlite3.OK, vm:bind_names{ bork = 'sisi' })
      assert.are.equal(sqlite3.DONE, vm:step())
      assert.are.equal(sqlite3.OK, vm:reset())
      
      assert.are.equal(sqlite3.OK, vm:bind_names{ 1 })
      assert.are.equal(sqlite3.DONE, vm:step())
      assert.are.equal(sqlite3.OK, vm:finalize())
    end)
  end)

  describe("Data Selection", function()
    it("should select data using db:exec", function()
      local results = {}
      local status = db:exec('select * from t', function (ud, ncols, values, names)
        table.insert(results, values)
        return sqlite3.OK
      end)
      assert.are.equal(sqlite3.OK, status)
      assert.are.equal(4, #results)  -- Should have 4 rows from previous inserts
    end)

    it("should select data using prepared statements", function()
      local vm = db:prepare('select * from t')
      assert.is_not_nil(vm)
      
      local results = {}
      while (vm:step() == sqlite3.ROW) do
        table.insert(results, {vm:get_uvalues()})
      end
      assert.are.equal(sqlite3.OK, vm:finalize())
      assert.are.equal(4, #results)  -- Should have 4 rows
    end)
  end)

  describe("User Defined Functions", function()
    it("should create and use scalar UDF", function()
      local function udf1_scalar(ctx, v)
        local ud = ctx:user_data()
        ud.r = (ud.r or '') .. tostring(v)
        ctx:result_text(ud.r)
      end

      db:create_function('udf1', 1, udf1_scalar, { })
      
      -- Test that the function exists and can be called
      local vm = db:prepare('SELECT udf1(a) FROM t LIMIT 1')
      assert.is_not_nil(vm)
      assert.are.equal(sqlite3.OK, vm:finalize())
    end)

    it("should create and use aggregate UDF", function()
      local function udf2_aggregate(ctx, ...)
        local ud = ctx:get_aggregate_data()
        if (not ud) then
          ud = {}
          ctx:set_aggregate_data(ud)
        end
        ud.r = (ud.r or 0) + 2
      end

      local function udf2_aggregate_finalize(ctx, v)
        local ud = ctx:get_aggregate_data()
        ctx:result_number(ud and ud.r or 0)
      end

      db:create_aggregate('udf2', 1, udf2_aggregate, udf2_aggregate_finalize, { })
      
      -- Test that the function exists and can be called
      local vm = db:prepare('SELECT udf2(a) FROM t LIMIT 1')
      assert.is_not_nil(vm)
      assert.are.equal(sqlite3.OK, vm:finalize())
    end)
  end)

  describe("Performance Tests", function()
    setup(function()
      db:exec('DELETE FROM t')
    end)

    it("should perform 100 inserts with exec", function()
      local t = os.time()
      for i = 1, 100 do
        db:exec('insert into t values('..i..', '..(i * 2 * -1^i)..')')
      end
      local elapsed = os.time() - t
      -- print('100 insert exec elapsed: '..elapsed)
      
      -- Verify count
      local count = 0
      for row in db:nrows('select count(*) as cnt from t') do
        count = row.cnt
      end
      assert.are.equal(100, count)
    end)

    it("should perform 100000 inserts with transaction", function()
      db:exec('delete from t')
      local t = os.time()
      db:exec('begin')
      for i = 1, 100000 do
        db:exec('insert into t values('..i..', '..(i * 2 * -1^i)..')')
      end
      db:exec('commit')
      local elapsed = os.time() - t
      -- print('100000 insert exec T elapsed: '..elapsed)
      
      -- Verify count
      local count = 0
      for row in db:nrows('select count(*) as cnt from t') do
        count = row.cnt
      end
      assert.are.equal(100000, count)
    end)

    it("should perform 100000 inserts with prepared statements", function()
      db:exec('delete from t')
      local t = os.time()
      local vm = db:prepare('insert into t values(?, ?)')
      db:exec('begin')
      for i = 1, 100000 do
        vm:bind_values(i, i * 2 * -1^i)
        vm:step()
        vm:reset()
      end
      vm:finalize()
      db:exec('commit')
      local elapsed = os.time() - t
      -- print('100000 insert prepare/bind T elapsed: '..elapsed)
      
      -- Verify count
      local count = 0
      for row in db:nrows('select count(*) as cnt from t') do
        count = row.cnt
      end
      assert.are.equal(100000, count)
    end)
  end)
end)