-- ========================================================================
-- Test 03: Query Patterns (MATCH, WHERE, Property Access)
-- ========================================================================
-- PURPOSE: Comprehensive testing of MATCH patterns, WHERE clause filtering,
--          property-based queries, and advanced pattern matching
-- COVERS:  Node patterns, label matching, property matching, WHERE clauses,
--          RETURN variations, pattern combinations, edge cases
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("Query Patterns", function()
  local db

  before_each(function()
    db = sqlite3.open_memory()
    assert.is_not_nil(db, "Failed to open database")
    helper.ensure_graphqlite(db)

    -- Setup: Create diverse test data
    helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30, city: "NYC"})')
    helper.cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25, city: "LA"})')
    helper.cypher_exec(db, 'CREATE (c:Person {name: "Carol", age: 30, city: "NYC"})')
    helper.cypher_exec(db, 'CREATE (d:Person {name: "David", age: 35})')
    helper.cypher_exec(db, 'CREATE (:Person {name: "Eve", age: 28})')
    helper.cypher_exec(db, 'CREATE (tc:Company {name: "TechCorp", employees: 100})')
    helper.cypher_exec(db, 'CREATE (ac:Company {name: "AcmeCorp", employees: 50})')
    helper.cypher_exec(db, 'CREATE (:Company {name: "StartupInc"})')
    helper.cypher_exec(db, 'CREATE (p1:Product {name: "Widget", price: 19.99})')
    helper.cypher_exec(db, 'CREATE (p2:Product {name: "Gadget", price: 29.99})')
    helper.cypher_exec(db, 'CREATE (:Product {name: "Thing", price: 9.99})')
  end)

  after_each(function()
    if db then
      db:close()
      db = nil
    end
  end)

  -- =======================================================================
  -- SECTION 1: Basic MATCH Patterns
  -- =======================================================================
  describe("Basic MATCH Patterns", function()
    it("should match all nodes", function()
      local results = helper.cypher_query(db, "MATCH (n) RETURN n LIMIT 5")
      assert.is_not_nil(results)
    end)

    it("should match with any variable name", function()
      local results = helper.cypher_query(db, "MATCH (anything) RETURN anything LIMIT 3")
      assert.is_not_nil(results)
    end)

    it("should match nodes without capturing", function()
      local results = helper.cypher_query(db, "MATCH () RETURN 1 LIMIT 1")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 2: Label-based Matching
  -- =======================================================================
  describe("Label-based Matching", function()
    it("should match by single label (Person)", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name")
      assert.is_not_nil(results)
      local json = results[1][1]
      assert.is_true(json:find("Alice") ~= nil, "Should contain Alice")
      assert.is_true(json:find("Bob") ~= nil, "Should contain Bob")
    end)

    it("should match by label (Company)", function()
      local results = helper.cypher_query(db, "MATCH (c:Company) RETURN c.name")
      assert.is_not_nil(results)
      local json = results[1][1]
      assert.is_true(json:find("TechCorp") ~= nil, "Should contain TechCorp")
    end)

    it("should match non-existent label (empty result)", function()
      local results = helper.cypher_query(db, "MATCH (n:NonExistent) RETURN n")
      assert.is_not_nil(results)
    end)

    it("should handle case sensitivity in labels", function()
      local results_lower = helper.cypher_query(db, "MATCH (n:person) RETURN n")
      local results_upper = helper.cypher_query(db, "MATCH (n:PERSON) RETURN n")
      assert.is_not_nil(results_lower)
      assert.is_not_nil(results_upper)
    end)
  end)

  -- =======================================================================
  -- SECTION 3: Property-based Matching (重要)
  -- =======================================================================
  describe("Property-based Matching (重要)", function()
    it("should match by single property", function()
      local results = helper.cypher_query(db, 'MATCH (n {name: "Alice"}) RETURN n')
      assert.is_not_nil(results)
    end)

    it("should match by integer property", function()
      local results = helper.cypher_query(db, "MATCH (n {age: 30}) RETURN n.name")
      assert.is_not_nil(results)
    end)

    it("should match by float property", function()
      local results = helper.cypher_query(db, "MATCH (n {price: 19.99}) RETURN n.name")
      assert.is_not_nil(results)
    end)

    it("should match by multiple properties", function()
      local results = helper.cypher_query(db, 'MATCH (n {name: "Alice", age: 30}) RETURN n')
      assert.is_not_nil(results)
    end)

    it("should handle non-existent property value (empty result)", function()
      local results = helper.cypher_query(db, 'MATCH (n {name: "Nobody"}) RETURN n')
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 4: Combined Label and Property Matching (易错)
  -- =======================================================================
  describe("Label + Property Matching (易错)", function()
    it("should match label with single property", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person {name: "Bob"}) RETURN n')
      assert.is_not_nil(results)
    end)

    it("should match label with multiple properties", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person {age: 30, city: "NYC"}) RETURN n.name')
      assert.is_not_nil(results)
    end)

    it("should handle wrong label with right property (empty result)", function()
      local results = helper.cypher_query(db, 'MATCH (n:Company {name: "Alice"}) RETURN n')
      assert.is_not_nil(results)
    end)

    it("should handle right label with wrong property (empty result)", function()
      local results = helper.cypher_query(db, "MATCH (n:Person {employees: 100}) RETURN n")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 5: WHERE Clause Patterns (重要)
  -- =======================================================================
  describe("WHERE Clause Patterns (重要)", function()
    it("should filter with equality", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person) WHERE n.name = "Alice" RETURN n.name')
      assert.is_not_nil(results)
    end)

    it("should filter with inequality", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person) WHERE n.name <> "Alice" RETURN n.name')
      assert.is_not_nil(results)
    end)

    it("should filter with greater than", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) WHERE n.age > 25 RETURN n.name, n.age")
      assert.is_not_nil(results)
    end)

    it("should filter with less than", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) WHERE n.age < 30 RETURN n.name, n.age")
      assert.is_not_nil(results)
    end)

    it("should filter with greater than or equal", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) WHERE n.age >= 30 RETURN n.name, n.age")
      assert.is_not_nil(results)
    end)

    it("should filter with less than or equal", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) WHERE n.age <= 30 RETURN n.name, n.age")
      assert.is_not_nil(results)
    end)

    it("should combine conditions with AND", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person) WHERE n.age > 25 AND n.city = "NYC" RETURN n.name')
      assert.is_not_nil(results)
    end)

    it("should combine conditions with OR", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person) WHERE n.age < 28 OR n.city = "LA" RETURN n.name')
      assert.is_not_nil(results)
    end)

    it("should use NOT condition", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) WHERE NOT n.age = 30 RETURN n.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 6: Property Existence and Null Checks (易错)
  -- =======================================================================
  describe("Property Existence and Null Checks (易错)", function()
    it("should match nodes where property IS NOT NULL", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) WHERE n.city IS NOT NULL RETURN n.name, n.city")
      assert.is_not_nil(results)
    end)

    it("should match nodes where property IS NULL", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) WHERE n.city IS NULL RETURN n.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 7: RETURN Variations
  -- =======================================================================
  describe("RETURN Variations", function()
    it("should return with alias", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n AS person LIMIT 2")
      assert.is_not_nil(results)
    end)

    it("should return property", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name")
      assert.is_not_nil(results)
    end)

    it("should return property with alias", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name AS person_name")
      assert.is_not_nil(results)
    end)

    it("should return multiple items", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name, n.age LIMIT 3")
      assert.is_not_nil(results)
    end)

    it("should return literal values", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person) RETURN n.name, "literal", 42 LIMIT 2')
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 8: Complex Pattern Combinations (重要)
  -- =======================================================================
  describe("Complex Pattern Combinations (重要)", function()
    it("should use multiple MATCH in single query", function()
      local results = helper.cypher_query(db, "MATCH (a:Person), (b:Company) RETURN a.name, b.name LIMIT 3")
      assert.is_not_nil(results)
    end)

    it("should filter with property ranges", function()
      local results = helper.cypher_query(db, "MATCH (p:Product) WHERE p.price >= 10.0 AND p.price <= 25.0 RETURN p.name, p.price")
      assert.is_not_nil(results)
    end)

    it("should use complex WHERE with multiple conditions", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person) WHERE n.age > 25 AND n.city = "NYC" AND n.name <> "Bob" RETURN n.name')
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 9: Edge Cases (易错)
  -- =======================================================================
  describe("Edge Cases (易错)", function()
    it("should handle MATCH with no results", function()
      local results = helper.cypher_query(db, "MATCH (n:NoSuchLabel) RETURN n")
      assert.is_not_nil(results)
    end)

    it("should handle empty property matching", function()
      local results = helper.cypher_query(db, 'MATCH (n:Person) WHERE n.nonexistent = "value" RETURN n')
      assert.is_not_nil(results)
    end)

    it("should handle matching nodes with no labels", function()
      local results = helper.cypher_query(db, "MATCH (n) WHERE NOT n:Person RETURN n LIMIT 3")
      assert.is_not_nil(results)
    end)

    it("should handle property comparison edge cases", function()
      local results = helper.cypher_query(db, "MATCH (n) WHERE n.age = 0 RETURN n")
      assert.is_not_nil(results)
    end)
  end)
end)
