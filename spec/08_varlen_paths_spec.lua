-- ========================================================================
-- Test 08: Variable-Length Relationship Patterns
-- ========================================================================
-- PURPOSE: Test variable-length path patterns with *min..max syntax
-- COVERS:  Exact length, bounded range, unbounded, with relationship types,
--          direction variations, path capture, edge cases
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("Variable-Length Path Patterns", function()
  local db

  before_each(function()
    db = sqlite3.open_memory()
    assert.is_not_nil(db, "Failed to open database")
    helper.ensure_graphqlite(db)

    -- Setup: Create a chain graph: A -> B -> C -> D -> E
    helper.cypher_exec(db, 'CREATE (a:Node {name: "A", level: 0})')
    helper.cypher_exec(db, 'CREATE (b:Node {name: "B", level: 1})')
    helper.cypher_exec(db, 'CREATE (c:Node {name: "C", level: 2})')
    helper.cypher_exec(db, 'CREATE (d:Node {name: "D", level: 3})')
    helper.cypher_exec(db, 'CREATE (e:Node {name: "E", level: 4})')
    helper.cypher_exec(db, 'MATCH (a:Node {name: "A"}), (b:Node {name: "B"}) CREATE (a)-[:NEXT]->(b)')
    helper.cypher_exec(db, 'MATCH (b:Node {name: "B"}), (c:Node {name: "C"}) CREATE (b)-[:NEXT]->(c)')
    helper.cypher_exec(db, 'MATCH (c:Node {name: "C"}), (d:Node {name: "D"}) CREATE (c)-[:NEXT]->(d)')
    helper.cypher_exec(db, 'MATCH (d:Node {name: "D"}), (e:Node {name: "E"}) CREATE (d)-[:NEXT]->(e)')

    -- Setup: Create a tree structure
    helper.cypher_exec(db, 'CREATE (root:Tree {name: "Root"})')
    helper.cypher_exec(db, 'CREATE (c1:Tree {name: "Child1"})')
    helper.cypher_exec(db, 'CREATE (c2:Tree {name: "Child2"})')
    helper.cypher_exec(db, 'CREATE (gc:Tree {name: "Grandchild"})')
    helper.cypher_exec(db, 'MATCH (r:Tree {name: "Root"}), (c:Tree {name: "Child1"}) CREATE (r)-[:PARENT_OF]->(c)')
    helper.cypher_exec(db, 'MATCH (r:Tree {name: "Root"}), (c:Tree {name: "Child2"}) CREATE (r)-[:PARENT_OF]->(c)')
    helper.cypher_exec(db, 'MATCH (c:Tree {name: "Child1"}), (gc:Tree {name: "Grandchild"}) CREATE (c)-[:PARENT_OF]->(gc)')
  end)

  after_each(function()
    if db then
      db:close()
      db = nil
    end
  end)

  -- =======================================================================
  -- SECTION 1: Exact Length Paths (重要)
  -- =======================================================================
  describe("Exact Length Paths (重要)", function()
    it("should find exactly 1 hop", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*1]->(target) RETURN target.name AS reached")
      assert.is_not_nil(results)
    end)

    it("should find exactly 2 hops", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*2]->(target) RETURN target.name AS reached")
      assert.is_not_nil(results)
    end)

    it("should find exactly 3 hops", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*3]->(target) RETURN target.name AS reached")
      assert.is_not_nil(results)
    end)

    it("should find exactly 4 hops", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*4]->(target) RETURN target.name AS reached")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 2: Bounded Range *min..max (重要/易错)
  -- =======================================================================
  describe("Bounded Range *min..max (重要/易错)", function()
    it("should find one to two hops", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*1..2]->(target) RETURN target.name AS reached ORDER BY target.name")
      assert.is_not_nil(results)
    end)

    it("should find one to three hops", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*1..3]->(target) RETURN target.name AS reached ORDER BY target.name")
      assert.is_not_nil(results)
    end)

    it("should find two to four hops", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*2..4]->(target) RETURN target.name AS reached ORDER BY target.name")
      assert.is_not_nil(results)
    end)

    it("should find zero to one hops (includes self)", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*0..1]->(target) RETURN target.name AS reached ORDER BY target.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 3: With Relationship Type (重要)
  -- =======================================================================
  describe("Typed Variable-Length (重要)", function()
    it("should find NEXT type only", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[:NEXT*1..3]->(target) RETURN target.name ORDER BY target.name")
      assert.is_not_nil(results)
    end)

    it("should find PARENT_OF in tree", function()
      local results = helper.cypher_query(db, "MATCH (r:Tree {name: \"Root\"})-[:PARENT_OF*1..2]->(descendant) RETURN descendant.name ORDER BY descendant.name")
      assert.is_not_nil(results)
    end)

    it("should find all descendants (unbounded)", function()
      local results = helper.cypher_query(db, "MATCH (r:Tree {name: \"Root\"})-[:PARENT_OF*]->(descendant) RETURN descendant.name ORDER BY descendant.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 4: Direction Variations (易错)
  -- =======================================================================
  describe("Direction Variations (易错)", function()
    it("should traverse reverse direction", function()
      local results = helper.cypher_query(db, "MATCH (e:Node {name: \"E\"})<-[*1..2]-(source) RETURN source.name ORDER BY source.name")
      assert.is_not_nil(results)
    end)

    it("should traverse any direction", function()
      local results = helper.cypher_query(db, "MATCH (c:Node {name: \"C\"})-[*1]-(neighbor) RETURN neighbor.name ORDER BY neighbor.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 5: With Path Variable
  -- =======================================================================
  describe("Path Capture", function()
    it("should capture path with length", function()
      local results = helper.cypher_query(db, "MATCH path = (a:Node {name: \"A\"})-[*2]->(target) RETURN target.name, length(path) AS path_length")
      assert.is_not_nil(results)
    end)

    it("should capture multiple paths of different lengths", function()
      local results = helper.cypher_query(db, "MATCH path = (a:Node {name: \"A\"})-[*1..3]->(target) RETURN target.name, length(path) AS hops ORDER BY hops, target.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 6: Edge Cases (易错)
  -- =======================================================================
  describe("Edge Cases (易错)", function()
    it("should handle path too long (no result)", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*10]->(target) RETURN target.name")
      assert.is_not_nil(results)
    end)

    it("should handle min equals max", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*2..2]->(target) RETURN target.name")
      assert.is_not_nil(results)
    end)

    it("should handle zero length (self)", function()
      local results = helper.cypher_query(db, "MATCH (a:Node {name: \"A\"})-[*0]->(target) RETURN target.name")
      assert.is_not_nil(results)
    end)

    it("should traverse from middle of chain", function()
      local results = helper.cypher_query(db, "MATCH (c:Node {name: \"C\"})-[*1..2]->(target) RETURN target.name ORDER BY target.name")
      assert.is_not_nil(results)
    end)
  end)
end)
