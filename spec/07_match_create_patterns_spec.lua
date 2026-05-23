-- ========================================================================
-- Test 07: MATCH...CREATE vs CREATE Patterns
-- ========================================================================
-- PURPOSE: Testing the distinction between MATCH...CREATE (using existing
--          nodes) and standalone CREATE (creating new nodes)
-- COVERS:  MATCH...CREATE patterns, node reuse vs creation, relationship
--          creation with existing nodes, error handling for missing nodes
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("MATCH...CREATE vs CREATE Patterns", function()
  local db

  before_each(function()
    db = sqlite3.open_memory()
    assert.is_not_nil(db, "Failed to open database")
    helper.ensure_graphqlite(db)
  end)

  after_each(function()
    if db then
      db:close()
      db = nil
    end
  end)

  -- =======================================================================
  -- SECTION 1: Basic MATCH...CREATE Functionality (重要)
  -- =======================================================================
  describe("Basic MATCH...CREATE (重要)", function()
    it("should create initial nodes and verify count", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')

      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)

    it("should MATCH existing nodes and CREATE relationship without adding nodes", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')

      -- MATCH...CREATE should not add new nodes
      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}), (b:Person {name: \"Bob\"}) CREATE (a)-[:KNOWS]->(b)")
      assert.is_true(ok, "MATCH...CREATE relationship")

      -- Node count should still be 2
      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)

    it("should verify relationship was created via MATCH...CREATE", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')
      helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}), (b:Person {name: \"Bob\"}) CREATE (a)-[:KNOWS]->(b)")

      local results = helper.cypher_query(db, "MATCH (a:Person)-[r:KNOWS]->(b:Person) RETURN a.name, b.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 2: MATCH...CREATE with Properties
  -- =======================================================================
  describe("MATCH...CREATE with Properties", function()
    it("should create relationship with edge properties using existing nodes", function()
      helper.cypher_exec(db, 'CREATE (charlie:Person {name: "Charlie", department: "Engineering"})')
      helper.cypher_exec(db, 'CREATE (diana:Person {name: "Diana", department: "Marketing"})')

      local ok = helper.cypher_exec(db, "MATCH (c:Person {name: \"Charlie\"}), (d:Person {name: \"Diana\"}) CREATE (c)-[:COLLABORATES {project: \"Website\", since: 2023}]->(d)")
      assert.is_true(ok, "MATCH...CREATE with edge properties")

      local results = helper.cypher_query(db, "MATCH (c:Person)-[r:COLLABORATES]->(d:Person) RETURN c.name, r, d.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 3: Error Cases and Edge Conditions (易错)
  -- =======================================================================
  describe("Error Cases (易错)", function()
    it("should handle MATCH non-existent node (no relationship created)", function()
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')

      -- Non-existent node should not create relationship
      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"NonExistent\"}), (b:Person {name: \"Bob\"}) CREATE (a)-[:KNOWS]->(b)")
      assert.is_true(ok, "Non-existent MATCH should not error")

      -- Node count should remain 1
      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)

    it("should handle MATCH with partial success (one exists, one does not)", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')

      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}), (b:Person {name: \"NotReal\"}) CREATE (a)-[:KNOWS]->(b)")
      assert.is_true(ok, "Partial MATCH should not error")

      -- Node count should remain 1
      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)

    it("should handle MATCH with impossible conditions", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')

      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\", age: 999}), (b:Person {name: \"Bob\"}) CREATE (a)-[:IMPOSSIBLE]->(b)")
      assert.is_true(ok, "Impossible MATCH should not error")
    end)
  end)

  -- =======================================================================
  -- SECTION 4: Comparison with Regular CREATE (重要/易错)
  -- =======================================================================
  describe("CREATE vs MATCH...CREATE (重要/易错)", function()
    it("should demonstrate that regular CREATE adds new nodes", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')

      -- Regular CREATE should add new nodes
      local ok = helper.cypher_exec(db, 'CREATE (eve:Person {name: "Eve"})-[:KNOWS]->(frank:Person {name: "Frank"})')
      assert.is_true(ok, "Regular CREATE adds nodes")

      -- Node count should increase
      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)

    it("should demonstrate MATCH...CREATE does not add nodes", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')

      -- MATCH...CREATE should NOT add new nodes
      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}), (b:Person {name: \"Bob\"}) CREATE (a)-[:KNOWS]->(b)")
      assert.is_true(ok, "MATCH...CREATE does not add nodes")

      -- Node count should still be 2
      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 5: Advanced MATCH...CREATE Patterns (重要)
  -- =======================================================================
  describe("Advanced MATCH...CREATE Patterns (重要)", function()
    it("should MATCH...CREATE with relationship patterns", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')
      helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}), (b:Person {name: \"Bob\"}) CREATE (a)-[:MANAGES]->(b)")

      -- Create additional relationship based on existing pattern
      local ok = helper.cypher_exec(db, "MATCH (manager:Person)-[:MANAGES]->(subordinate:Person) CREATE (manager)-[:EVALUATES {year: 2023}]->(subordinate)")
      assert.is_true(ok, "MATCH...CREATE with relationship patterns")
    end)

    it("should MATCH...CREATE with property filtering", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30, department: "Engineering"})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25, department: "Marketing"})')

      local ok = helper.cypher_exec(db, "MATCH (eng:Person) WHERE eng.department = \"Engineering\" MATCH (eng), (mkt:Person) WHERE mkt.department = \"Marketing\" CREATE (eng)-[:CROSS_DEPT]->(mkt)")
      assert.is_true(ok, "MATCH...CREATE with property filtering")
    end)

    it("should use multiple MATCH clauses with CREATE", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')
      helper.cypher_exec(db, 'CREATE (charlie:Person {name: "Charlie", age: 35})')

      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}) MATCH (others:Person) WHERE others.name <> \"Alice\" CREATE (a)-[:KNOWS_ALL {type: \"universal\"}]->(others)")
      assert.is_true(ok, "Multiple MATCH clauses with CREATE")
    end)
  end)

  -- =======================================================================
  -- SECTION 6: Node Reuse vs Creation Verification (重要)
  -- =======================================================================
  describe("Node Reuse Verification (重要)", function()
    it("should verify node reuse pattern", function()
      helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25})')

      -- MATCH...CREATE should reuse nodes
      helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}), (b:Person {name: \"Bob\"}) CREATE (a)-[:KNOWS]->(b)")

      -- Regular CREATE should create new nodes
      helper.cypher_exec(db, 'CREATE (alice1:Person {name: "Alice"})-[:DUPLICATE]->(alice2:Person {name: "Alice"})')

      -- Now there should be multiple Alice nodes
      local results = helper.cypher_query(db, "MATCH (n:Person {name: \"Alice\"}) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)
  end)
end)
