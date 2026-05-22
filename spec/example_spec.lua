local sqlite3 = require("lsqlite3")

describe("SQLite3 Basic Tests", function()
  local db

  setup(function()
    -- 在所有测试之前运行
    db = sqlite3.open_memory()
  end)

  teardown(function()
    -- 在所有测试之后运行
    if db then
      db:close()
    end
  end)

  before_each(function()
    -- 在每个测试之前运行
    db:exec("CREATE TABLE test (id INTEGER, name TEXT)")
    db:exec("INSERT INTO test VALUES (1, 'Hello World')")
  end)

  after_each(function()
    -- 在每个测试之后运行
    db:exec("DROP TABLE IF EXISTS test")
  end)

  it("should create a table and insert data", function()
    local count = 0
    for row in db:nrows("SELECT COUNT(*) as cnt FROM test") do
      count = row.cnt
    end
    assert.are.equal(1, count)
  end)

  it("should retrieve inserted data", function()
    local name
    for row in db:nrows("SELECT name FROM test WHERE id = 1") do
      name = row.name
    end
    assert.are.equal("Hello World", name)
  end)

  it("should update data correctly", function()
    db:exec("UPDATE test SET name = 'Updated' WHERE id = 1")
    
    local name
    for row in db:nrows("SELECT name FROM test WHERE id = 1") do
      name = row.name
    end
    assert.are.equal("Updated", name)
  end)
end)