-- ========================================================================
-- Test 02: Relationship Operations (CREATE, MATCH, Properties)
-- ========================================================================
-- PURPOSE: Comprehensive testing of relationship creation, direction handling,
--          relationship properties, and relationship pattern matching
-- COVERS:  Directed/undirected relationships, relationship types,
--          edge properties, relationship variables, complex patterns
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("Relationship Operations", function()
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
  -- SECTION 1: Basic Relationship Creation Patterns
  -- =======================================================================
  describe("Basic Relationship Creation", function()
    it("should create a simple directed relationship", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})')
      assert.is_true(ok, "Directed relationship: " .. tostring(err))
    end)

    it("should create a reverse directed relationship", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (c:Person {name: "Charlie"})<-[:FOLLOWS]-(d:Person {name: "David"})')
      assert.is_true(ok, "Reverse directed relationship: " .. tostring(err))
    end)

    it("should create an undirected relationship", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (e:Person {name: "Eve"})-[:FRIENDS]-(f:Person {name: "Frank"})')
      assert.is_true(ok, "Undirected relationship: " .. tostring(err))
    end)

    it("should create a relationship without type", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (g:Person {name: "Grace"})-[]->(h:Person {name: "Henry"})')
      assert.is_true(ok, "Relationship without type: " .. tostring(err))
    end)

    it("should create a relationship with variable", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (i:Person {name: "Iris"})-[rel:MENTORS]->(j:Person {name: "Jack"})')
      assert.is_true(ok, "Relationship with variable: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 2: Relationship Types and Properties
  -- =======================================================================
  describe("Relationship Types and Properties", function()
    it("should create multiple relationship types", function()
      local ok1 = helper.cypher_exec(db, 'CREATE (k:Person {name: "Kelly"})-[:WORKS_FOR]->(l:Company {name: "TechCorp"})')
      local ok2 = helper.cypher_exec(db, 'CREATE (k:Person {name: "Kelly"})-[:LIVES_IN]->(m:City {name: "NYC"})')
      assert.is_true(ok1, "WORKS_FOR: " .. tostring(ok1))
      assert.is_true(ok2, "LIVES_IN: " .. tostring(ok2))
    end)

    it("should create relationship with integer property", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n:Person {name: "Nina"})-[:KNOWS {since: 2020}]->(o:Person {name: "Oscar"})')
      assert.is_true(ok, "Relationship with integer property: " .. tostring(err))
    end)

    it("should create relationship with multiple property types", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (p:Person {name: "Paul"})-[:WORKS_WITH {years: 5, salary: 75000.50, verified: true, department: "Engineering"}]->(q:Person {name: "Quinn"})')
      assert.is_true(ok, "Multiple property types: " .. tostring(err))
    end)

    it("should create relationship with string properties", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (r:Person {name: "Rachel"})-[:COLLABORATES {project: "GraphDB", role: "lead"}]->(s:Person {name: "Sam"})')
      assert.is_true(ok, "String properties: " .. tostring(err))
    end)

    it("should create relationship with empty properties", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (t:Person {name: "Tom"})-[:KNOWS {}]->(u:Person {name: "Uma"})')
      assert.is_true(ok, "Empty properties: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 3: Different Relationship Directions (易错)
  -- =======================================================================
  describe("Relationship Directions (易错)", function()
    it("should create left-directed relationship with properties", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (v:Person {name: "Victor"})<-[:MENTORS {skill: "programming"}]-(w:Person {name: "Wendy"})')
      assert.is_true(ok, "Left-directed: " .. tostring(err))
    end)

    it("should create bidirectional relationship", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (x:Person {name: "Xavier"})-[:FRIENDS {duration: "lifelong"}]-(y:Person {name: "Yuki"})')
      assert.is_true(ok, "Bidirectional: " .. tostring(err))
    end)

    it("should create multiple outgoing relationships from same node", function()
      local ok1 = helper.cypher_exec(db, 'CREATE (z:Person {name: "Zoe"})-[:MANAGES]->(aa:Person {name: "Alex"})')
      local ok2 = helper.cypher_exec(db, 'CREATE (z:Person {name: "Zoe"})-[:LEADS]->(bb:Person {name: "Blake"})')
      assert.is_true(ok1, "MANAGES: " .. tostring(ok1))
      assert.is_true(ok2, "LEADS: " .. tostring(ok2))
    end)
  end)

  -- =======================================================================
  -- SECTION 4: Complex Relationship Patterns (重要)
  -- =======================================================================
  describe("Complex Relationship Patterns (重要)", function()
    it("should create a relationship chain", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (cc:Person {name: "Cameron"})-[:MANAGES]->(dd:Person {name: "Dana"})-[:REPORTS_TO]->(ee:Company {name: "MegaCorp"})')
      assert.is_true(ok, "Relationship chain: " .. tostring(err))
    end)

    it("should create multiple relationships in single CREATE", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (ff:Person {name: "Felix"})-[:KNOWS]->(gg:Person {name: "Gina"}), (ff)-[:WORKS_WITH]->(gg)')
      assert.is_true(ok, "Multiple relationships: " .. tostring(err))
    end)

    it("should create self-referencing relationship", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (hh:Person {name: "Harper"})-[:MANAGES]->(hh)')
      assert.is_true(ok, "Self-referencing: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 5: Relationship Matching and Querying
  -- =======================================================================
  describe("Relationship Matching", function()
    it("should match by relationship type", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})')
      local results = helper.cypher_query(db, "MATCH (a)-[:KNOWS]->(b) RETURN a.name, b.name")
      assert.is_not_nil(results)
    end)

    it("should match any relationship type", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})')
      local results = helper.cypher_query(db, "MATCH (a)-[r]->(b) RETURN a.name, b.name")
      assert.is_not_nil(results)
    end)

    it("should match undirected (both directions)", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:FRIENDS]-(b:Person {name: "Bob"})')
      local results = helper.cypher_query(db, "MATCH (a)-[:FRIENDS]-(b) RETURN a.name, b.name")
      assert.is_not_nil(results)
    end)

    it("should match reverse direction", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})<-[:FOLLOWS]-(b:Person {name: "Bob"})')
      local results = helper.cypher_query(db, "MATCH (a)<-[:FOLLOWS]-(b) RETURN a.name, b.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 6: Relationship Property Access (易错)
  -- =======================================================================
  describe("Relationship Property Access (易错)", function()
    it("should return relationship with properties", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS {since: 2020}]->(b:Person {name: "Bob"})')
      local results = helper.cypher_query(db, "MATCH ()-[r:KNOWS]->() RETURN r")
      assert.is_not_nil(results)
    end)

    it("should filter by relationship property", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS {since: 2020}]->(b:Person {name: "Bob"})')
      helper.cypher_exec(db, 'CREATE (c:Person {name: "Carol"})-[:KNOWS {since: 2021}]->(d:Person {name: "Dave"})')
      local results = helper.cypher_query(db, "MATCH (a)-[r:KNOWS]->(b) WHERE r.since = 2020 RETURN a.name, b.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 7: Edge Cases (易错)
  -- =======================================================================
  describe("Edge Cases (易错)", function()
    it("should handle non-existent relationship type (empty result)", function()
      local results = helper.cypher_query(db, "MATCH (a)-[:NONEXISTENT]->(b) RETURN a, b")
      assert.is_not_nil(results)
    end)

    it("should handle empty relationship pattern", function()
      local results = helper.cypher_query(db, "MATCH ()-[]->() RETURN 1 LIMIT 1")
      assert.is_not_nil(results)
    end)

    it("should match relationship chains", function()
      helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice"})-[:KNOWS]->(b:Person {name: "Bob"})-[:KNOWS]->(c:Person {name: "Carol"})')
      local results = helper.cypher_query(db, "MATCH (a)-[:KNOWS]->(b)-[:KNOWS]->(c) RETURN a.name, b.name, c.name")
      assert.is_not_nil(results)
    end)
  end)
end)
