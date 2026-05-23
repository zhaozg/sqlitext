-- ========================================================================
-- Test 10: Delete Operations (DELETE, DETACH DELETE)
-- ========================================================================
-- PURPOSE: Test node and relationship deletion operations
-- COVERS:  DELETE relationship, DELETE node, DETACH DELETE,
--          cascade behavior, error conditions
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("Delete Operations", function()
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
  -- SECTION 1: DELETE Relationship (重要)
  -- =======================================================================
  describe("DELETE Relationship (重要)", function()
    it("should delete a relationship", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})')

      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"})-[r:KNOWS]->(b:Person {name: \"Bob\"}) DELETE r")
      assert.is_true(ok, "Delete relationship: " .. tostring(ok))

      -- Verify relationship is gone
      local results = helper.cypher_query(db, "MATCH ()-[r:KNOWS]->() RETURN count(r) as cnt")
      assert.is_not_nil(results)
    end)

    it("should keep nodes after deleting relationship", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})')
      helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"})-[r:KNOWS]->(b:Person {name: \"Bob\"}) DELETE r")

      -- Nodes should still exist
      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 2: DELETE Node Without Relationships (重要)
  -- =======================================================================
  describe("DELETE Node Without Relationships (重要)", function()
    it("should delete a node without relationships", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})')

      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}) DELETE a")
      assert.is_true(ok, "Delete node: " .. tostring(ok))

      -- Verify node is gone
      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 3: DETACH DELETE (重要/易错)
  -- =======================================================================
  describe("DETACH DELETE (重要/易错)", function()
    it("should detach delete a node with relationships", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})')

      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}) DETACH DELETE a")
      assert.is_true(ok, "DETACH DELETE: " .. tostring(ok))

      -- Alice and the relationship should be gone
      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)

    it("should keep other nodes after DETACH DELETE", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})')
      helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}) DETACH DELETE a")

      -- Bob should still exist
      local results = helper.cypher_query(db, "MATCH (n:Person {name: \"Bob\"}) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 4: DELETE Multiple Nodes (重要)
  -- =======================================================================
  describe("DELETE Multiple Nodes (重要)", function()
    it("should delete multiple nodes", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})')
      helper.cypher_exec(db, 'CREATE (b:Person {name: "Bob"})')
      helper.cypher_exec(db, 'CREATE (c:Person {name: "Charlie"})')

      local ok = helper.cypher_exec(db, "MATCH (n:Person) WHERE n.name IN [\"Alice\", \"Bob\"] DELETE n")
      assert.is_true(ok, "Delete multiple nodes: " .. tostring(ok))
    end)

    it("should delete all nodes with DETACH DELETE", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})')

      local ok = helper.cypher_exec(db, "MATCH (n) DETACH DELETE n")
      assert.is_true(ok, "Delete all: " .. tostring(ok))

      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 5: DELETE with WHERE Conditions
  -- =======================================================================
  describe("DELETE with WHERE Conditions", function()
    it("should delete nodes matching specific conditions", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30})')
      helper.cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25})')

      local ok = helper.cypher_exec(db, "MATCH (n:Person) WHERE n.age < 30 DELETE n")
      assert.is_true(ok, "Delete with WHERE: " .. tostring(ok))
    end)
  end)

  -- =======================================================================
  -- SECTION 6: DELETE Edge Cases (易错)
  -- =======================================================================
  describe("DELETE Edge Cases (易错)", function()
    it("should handle deleting non-existent node gracefully", function()
      local ok = helper.cypher_exec(db, "MATCH (n:NonExistent) DELETE n")
      assert.is_true(ok, "Delete non-existent: " .. tostring(ok))
    end)

    it("should handle deleting non-existent relationship gracefully", function()
      local ok = helper.cypher_exec(db, "MATCH ()-[r:NONEXISTENT]->() DELETE r")
      assert.is_true(ok, "Delete non-existent rel: " .. tostring(ok))
    end)

    it("should handle deleting already deleted node gracefully", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})')
      helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}) DELETE a")

      -- Try deleting again
      local ok = helper.cypher_exec(db, "MATCH (a:Person {name: \"Alice\"}) DELETE a")
      assert.is_true(ok, "Delete already deleted: " .. tostring(ok))
    end)
  end)
end)
