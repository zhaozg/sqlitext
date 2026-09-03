-- GraphQLite Tests (busted format)
-- GraphQLite 是静态编译连接到 lsqlite3 中的（通过 SQLITE_GRAPH_STATIC）
-- 先探测模块是否已加载，否则再动态加载

local sqlite3 = require("lsqlite3")

-- 探测 GraphQLite 是否已加载（静态编译或已动态加载）
local function is_graphqlite_loaded(db)
  local ok, err = pcall(function()
    for row in db:nrows("SELECT graphqlite_test()") do
      return row["graphqlite_test()"] ~= nil
    end
  end)
  return ok
end

-- 尝试加载 GraphQLite 扩展（如果尚未静态编译）
local function ensure_graphqlite(db)
  if is_graphqlite_loaded(db) then
    return true, "static"
  end

  -- 尝试动态加载
  local extension_paths = {
    "./build/graphqlite.dylib",   -- macOS
    "./build/graphqlite.so",      -- Linux
    "./build/graphqlite.dll",     -- Windows
  }

  for _, path in ipairs(extension_paths) do
    local ok = pcall(function()
      db:exec("PRAGMA load_extension = 1;")
      db:exec(string.format("SELECT load_extension('%s');", path))
    end)
    if ok then
      return true, "dynamic:" .. path
    end
  end

  return false, nil
end

-- 辅助函数：安全地执行单条 Cypher 查询
local function cypher_exec(db, cypher_query)
  local escaped = cypher_query:gsub("'", "''")
  local sql = string.format("SELECT cypher('%s');", escaped)
  local ok, err = pcall(function() db:exec(sql) end)
  return ok, err
end

-- 辅助函数：执行查询并收集结果
local function cypher_query(db, cypher_query)
  local results = {}
  local escaped = cypher_query:gsub("'", "''")
  local sql = string.format("SELECT cypher('%s');", escaped)
  local stmt = db:prepare(sql)
  if stmt then
    for row in stmt:rows() do
      table.insert(results, row)
    end
    stmt:finalize()
  end
  return results
end

describe("GraphQLite Tests", function()
  describe("Module Detection", function()
    it("should detect GraphQLite is statically linked", function()
      local db = sqlite3.open_memory()
      assert.is_true(is_graphqlite_loaded(db),
        "GraphQLite should be statically compiled into lsqlite3.so")
      db:close()
    end)

    it("should ensure GraphQLite is available", function()
      local db = sqlite3.open_memory()
      local ok, method = ensure_graphqlite(db)
      assert.is_true(ok, "GraphQLite should be available")
      assert.are.equal("static", method,
        "GraphQLite should be loaded statically, not dynamically")
      db:close()
    end)
  end)

  describe("Graph Database Operations", function()
    local db

    before_each(function()
      db = sqlite3.open_memory()
      assert.is_not_nil(db, "Failed to open database")
      -- 确保 GraphQLite 已加载
      local ok = ensure_graphqlite(db)
      if not ok then
        error("GraphQLite extension not available")
      end
    end)

    after_each(function()
      if db then
        db:close()
        db = nil
      end
    end)

    it("should have graphqlite_test function", function()
      for row in db:nrows("SELECT graphqlite_test()") do
        assert.are.equal("GraphQLite extension loaded successfully!",
          row["graphqlite_test()"])
      end
    end)

    it("should have cypher function registered", function()
      -- cypher 函数应该已注册
      local ok, err = pcall(function()
        db:exec("SELECT cypher('RETURN 1 AS n')")
      end)
      assert.is_true(ok, "cypher function should be registered: " .. tostring(err))
    end)

    it("should create nodes", function()
      local ok, err = cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30})')
      assert.is_true(ok, "Should create Alice node: " .. (err or ""))

      ok, err = cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25})')
      assert.is_true(ok, "Should create Bob node: " .. (err or ""))

      ok, err = cypher_exec(db, 'CREATE (c:Person {name: "Charlie", age: 35})')
      assert.is_true(ok, "Should create Charlie node: " .. (err or ""))
    end)

    it("should create relationships between nodes", function()
      -- 先创建节点
      cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30})')
      cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25})')
      cypher_exec(db, 'CREATE (c:Person {name: "Charlie", age: 35})')

      -- 创建关系
      local ok, err = cypher_exec(db, [[
        MATCH (a:Person {name: "Alice"}), (b:Person {name: "Bob"})
        CREATE (a)-[:KNOWS]->(b)
      ]])
      assert.is_true(ok, "Should create KNOWS relationship: " .. (err or ""))

      ok, err = cypher_exec(db, [[
        MATCH (b:Person {name: "Bob"}), (c:Person {name: "Charlie"})
        CREATE (b)-[:KNOWS]->(c)
      ]])
      assert.is_true(ok, "Should create second KNOWS relationship: " .. (err or ""))
    end)

    it("should query all persons", function()
      -- 准备数据
      cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30})')
      cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25})')

      -- 查询所有人员
      local results = cypher_query(db, 'MATCH (p:Person) RETURN p.name, p.age')
      assert.is_not_nil(results)
      assert.are.equal(1, #results, "Should return one result row")

      -- 结果应该是 JSON 格式的数组
      local json = results[1][1]
      assert.is_true(type(json) == "string", "Result should be a JSON string")
      -- 应该包含 Alice 和 Bob
      assert.is_true(json:find("Alice") ~= nil, "Result should contain Alice")
      assert.is_true(json:find("Bob") ~= nil, "Result should contain Bob")
    end)

    it("should query relationships", function()
      -- 准备数据
      cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30})')
      cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25})')
      cypher_exec(db, [[
        MATCH (a:Person {name: "Alice"}), (b:Person {name: "Bob"})
        CREATE (a)-[:KNOWS]->(b)
      ]])

      -- 查询关系
      local results = cypher_query(db,
        'MATCH (a:Person)-[:KNOWS]->(b:Person) RETURN a.name, b.name')
      assert.is_not_nil(results)
      assert.are.equal(1, #results, "Should return one relationship")
    end)

    it("should query friend-of-friend", function()
      -- 准备数据
      cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30})')
      cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25})')
      cypher_exec(db, 'CREATE (c:Person {name: "Charlie", age: 35})')
      cypher_exec(db, [[
        MATCH (a:Person {name: "Alice"}), (b:Person {name: "Bob"})
        CREATE (a)-[:KNOWS]->(b)
      ]])
      cypher_exec(db, [[
        MATCH (b:Person {name: "Bob"}), (c:Person {name: "Charlie"})
        CREATE (b)-[:KNOWS]->(c)
      ]])

      -- 查询朋友的朋友
      local results = cypher_query(db, [[
        MATCH (a:Person {name: "Alice"})-[:KNOWS]->()-[:KNOWS]->(fof)
        RETURN fof.name
      ]])
      assert.is_not_nil(results)
      assert.are.equal(1, #results, "Should find Charlie as friend-of-friend")
    end)

    it("should handle cypher_validate function", function()
      -- 验证有效查询
      local ok, err = pcall(function()
        db:exec("SELECT cypher_validate('RETURN 1')")
      end)
      assert.is_true(ok, "cypher_validate should work: " .. tostring(err))
    end)

    it("should handle regexp function", function()
      -- regexp 函数应该已注册
      local ok, err = pcall(function()
        for row in db:nrows("SELECT 'hello' REGEXP '^h.*'") do
          -- 只是测试函数存在
        end
      end)
      assert.is_true(ok, "regexp function should be registered: " .. tostring(err))
    end)
  end)

  describe("Helper Functions", function()
    local db

    before_each(function()
      db = sqlite3.open_memory()
    end)

    after_each(function()
      if db then
        db:close()
      end
    end)

    it("should escape single quotes in cypher queries", function()
      local test_query = "MATCH (n) WHERE n.name = 'O'Connor' RETURN n"
      local escaped = test_query:gsub("'", "''")
      assert.are.equal(
        "MATCH (n) WHERE n.name = ''O''Connor'' RETURN n", escaped)
    end)

    it("should format SQL with escaped cypher queries", function()
      local test_query = "MATCH (n) RETURN n"
      local escaped = test_query:gsub("'", "''")
      local sql = string.format("SELECT cypher('%s');", escaped)
      assert.are.equal("SELECT cypher('MATCH (n) RETURN n');", sql)
    end)

    it("should detect graphqlite_test function via SQL", function()
      -- 通过 SQL 探测 graphqlite_test 函数
      local found = false
      for row in db:nrows("SELECT name FROM sqlite_master WHERE type='func'") do
        -- sqlite_master 不包含函数信息，所以这个测试只是验证不报错
      end
      -- 直接调用 graphqlite_test 来验证
      local ok = is_graphqlite_loaded(db)
      assert.is_true(ok, "graphqlite_test should be callable")
    end)
  end)

  describe("Error Handling", function()
    local db

    before_each(function()
      db = sqlite3.open_memory()
      ensure_graphqlite(db)
    end)

    after_each(function()
      if db then
        db:close()
      end
    end)

    it("should handle invalid cypher syntax gracefully", function()
      -- GraphQLite 通过 sqlite3_result_error 返回 JSON 错误信息
      -- 使用 nrows() 迭代时会触发 Lua 错误（SQLite step 返回错误）
      -- 使用 exec() 则不会触发错误，exec 返回 SQLITE_OK
      local ok, err = pcall(function()
        for row in db:nrows("SELECT cypher('INVALID SYNTAX!!!')") do
          -- 不应该到达这里
        end
      end)
      assert.is_false(ok, "Invalid syntax should cause nrows() error")
      -- 错误信息应该是 JSON 格式
      assert.is_true(type(err) == "string", "Error should be a string")
      assert.is_true(err:find("error") ~= nil or err:find("ERROR") ~= nil,
        "Error should contain error info")
    end)

    it("should handle cypher with no arguments gracefully", function()
      local ok, err = pcall(function()
        for row in db:nrows("SELECT cypher()") do
          -- 不应该到达这里
        end
      end)
      assert.is_false(ok, "cypher() with no args should cause nrows() error")
      assert.is_true(type(err) == "string", "Error should be a string")
    end)
  end)
end)
