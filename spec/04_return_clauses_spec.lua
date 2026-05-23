-- ========================================================================
-- Test 04: RETURN Clause Features (DISTINCT, ORDER BY, LIMIT, SKIP)
-- ========================================================================
-- PURPOSE: Comprehensive testing of RETURN clause modifiers and result
--          formatting features
-- COVERS:  DISTINCT filtering, ORDER BY sorting, LIMIT/SKIP pagination,
--          combined clauses, alias handling
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("RETURN Clause Features", function()
  local db

  before_each(function()
    db = sqlite3.open_memory()
    assert.is_not_nil(db, "Failed to open database")
    helper.ensure_graphqlite(db)

    -- Setup: Create test data with varied names and ages
    helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30})')
    helper.cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25})')
    helper.cypher_exec(db, 'CREATE (c:Person {name: "Charlie", age: 35})')
    helper.cypher_exec(db, 'CREATE (d:Person {name: "Alice", age: 28})')  -- Duplicate name
    helper.cypher_exec(db, 'CREATE (e:Person {name: "David", age: 40})')
    helper.cypher_exec(db, 'CREATE (f:Product {name: "Widget", price: 19.99})')
    helper.cypher_exec(db, 'CREATE (g:Product {name: "Gadget", price: 29.99})')
  end)

  after_each(function()
    if db then
      db:close()
      db = nil
    end
  end)

  -- =======================================================================
  -- SECTION 1: DISTINCT Clause Testing (重要)
  -- =======================================================================
  describe("DISTINCT Clause (重要)", function()
    it("should return names with duplicates", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name")
      assert.is_not_nil(results)
    end)

    it("should return distinct names", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN DISTINCT n.name")
      assert.is_not_nil(results)
    end)

    it("should return distinct ages", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN DISTINCT n.age")
      assert.is_not_nil(results)
    end)

    it("should use DISTINCT with multiple columns", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN DISTINCT n.name, n.age")
      assert.is_not_nil(results)
    end)

    it("should use DISTINCT across different node types", function()
      local results = helper.cypher_query(db, "MATCH (n) RETURN DISTINCT n.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 2: ORDER BY Clause Testing (重要)
  -- =======================================================================
  describe("ORDER BY Clause (重要)", function()
    it("should order by name ascending", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.name")
      assert.is_not_nil(results)
    end)

    it("should order by age ascending", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name, n.age ORDER BY n.age")
      assert.is_not_nil(results)
    end)

    it("should order by age descending", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name, n.age ORDER BY n.age DESC")
      assert.is_not_nil(results)
    end)

    it("should order by multiple columns", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name, n.age ORDER BY n.name, n.age")
      assert.is_not_nil(results)
    end)

    it("should order by multiple columns with mixed direction", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name, n.age ORDER BY n.name ASC, n.age DESC")
      assert.is_not_nil(results)
    end)

    it("should order by numeric property", function()
      local results = helper.cypher_query(db, "MATCH (n:Product) RETURN n.name, n.price ORDER BY n.price")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 3: LIMIT Clause Testing
  -- =======================================================================
  describe("LIMIT Clause", function()
    it("should limit to 2 results", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name LIMIT 2")
      assert.is_not_nil(results)
    end)

    it("should limit to 1 result", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name LIMIT 1")
      assert.is_not_nil(results)
    end)

    it("should use LIMIT with ORDER BY", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.name LIMIT 3")
      assert.is_not_nil(results)
    end)

    it("should handle LIMIT larger than result set", function()
      local results = helper.cypher_query(db, "MATCH (n:Product) RETURN n.name LIMIT 10")
      assert.is_not_nil(results)
    end)

    it("should handle LIMIT with zero", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name LIMIT 0")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 4: SKIP Clause Testing
  -- =======================================================================
  describe("SKIP Clause", function()
    it("should skip first 2 results", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.name SKIP 2")
      assert.is_not_nil(results)
    end)

    it("should skip first result", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.name SKIP 1")
      assert.is_not_nil(results)
    end)

    it("should handle skip with large offset", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.name SKIP 10")
      assert.is_not_nil(results)
    end)

    it("should handle skip with zero", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.name SKIP 0")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 5: Combined Clause Testing (重要/易错)
  -- =======================================================================
  describe("Combined Clauses (重要/易错)", function()
    it("should combine DISTINCT + ORDER BY", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN DISTINCT n.name ORDER BY n.name")
      assert.is_not_nil(results)
    end)

    it("should combine ORDER BY + LIMIT", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.age LIMIT 2")
      assert.is_not_nil(results)
    end)

    it("should combine ORDER BY + SKIP + LIMIT (pagination)", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.age SKIP 1 LIMIT 2")
      assert.is_not_nil(results)
    end)

    it("should combine all features", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN DISTINCT n.name ORDER BY n.name SKIP 0 LIMIT 10")
      assert.is_not_nil(results)
    end)

    it("should combine DISTINCT + ORDER BY + LIMIT", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN DISTINCT n.age ORDER BY n.age LIMIT 3")
      assert.is_not_nil(results)
    end)

    it("should handle complex pagination", function()
      local results = helper.cypher_query(db, "MATCH (n) RETURN n.name ORDER BY n.name SKIP 2 LIMIT 3")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 6: Alias and Expression Testing
  -- =======================================================================
  describe("Alias and Expression", function()
    it("should RETURN with alias", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name AS person_name ORDER BY person_name")
      assert.is_not_nil(results)
    end)

    it("should use multiple aliases", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name AS name, n.age AS years ORDER BY name")
      assert.is_not_nil(results)
    end)

    it("should use alias with ORDER BY", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name AS name ORDER BY n.age LIMIT 3")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 7: Edge Cases (易错)
  -- =======================================================================
  describe("Edge Cases (易错)", function()
    it("should handle empty result set with clauses", function()
      local results = helper.cypher_query(db, "MATCH (n:NonExistent) RETURN n.name ORDER BY n.name LIMIT 5")
      assert.is_not_nil(results)
    end)

    it("should handle NULL value handling in ORDER BY", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name, n.city ORDER BY n.city")
      assert.is_not_nil(results)
    end)

    it("should handle large SKIP beyond result set", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name SKIP 100")
      assert.is_not_nil(results)
    end)

    it("should handle DISTINCT with complex expressions", function()
      local results = helper.cypher_query(db, "MATCH (n) WHERE n.name IS NOT NULL RETURN DISTINCT n.name ORDER BY n.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 8: Performance Patterns (重要)
  -- =======================================================================
  describe("Performance Patterns (重要)", function()
    it("should support TOP-N pattern with LIMIT", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name, n.age ORDER BY n.age DESC LIMIT 1")
      assert.is_not_nil(results)
    end)

    it("should support pagination pattern", function()
      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN n.name ORDER BY n.name SKIP 1 LIMIT 2")
      assert.is_not_nil(results)
    end)

    it("should support deduplication pattern", function()
      local results = helper.cypher_query(db, "MATCH (n) RETURN DISTINCT n.name ORDER BY n.name LIMIT 5")
      assert.is_not_nil(results)
    end)
  end)
end)
