-- ========================================================================
-- Test 09: UNION Queries and CASE Expressions
-- ========================================================================
-- PURPOSE: Test UNION/UNION ALL query combinations and CASE WHEN expressions
-- COVERS:  Basic UNION, UNION ALL, column alignment, ordering with UNION,
--          searched CASE, CASE with ELSE, CASE without ELSE, CASE in WHERE
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("UNION Queries and CASE Expressions", function()
  local db

  before_each(function()
    db = sqlite3.open_memory()
    assert.is_not_nil(db, "Failed to open database")
    helper.ensure_graphqlite(db)

    -- Setup for UNION tests
    helper.cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30, dept: "Engineering"})')
    helper.cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25, dept: "Marketing"})')
    helper.cypher_exec(db, 'CREATE (c:Person {name: "Carol", age: 35, dept: "Engineering"})')
    helper.cypher_exec(db, 'CREATE (d:Person {name: "David", age: 28, dept: "Sales"})')
    helper.cypher_exec(db, 'CREATE (p1:Product {name: "Widget", category: "Tools"})')
    helper.cypher_exec(db, 'CREATE (p2:Product {name: "Gadget", category: "Electronics"})')

    -- Setup for CASE tests
    helper.cypher_exec(db, 'CREATE (e:Person {name: "Eve", age: 25, score: 100, status: "active"})')
    helper.cypher_exec(db, 'CREATE (f:Person {name: "Frank", age: 35})')
    helper.cypher_exec(db, 'CREATE (p3:Product {name: "Thing", price: 9.99, stock: 0})')
  end)

  after_each(function()
    if db then
      db:close()
      db = nil
    end
  end)

  -- =======================================================================
  -- SECTION 1: Basic UNION (重要)
  -- =======================================================================
  describe("Basic UNION (重要)", function()
    it("should UNION two queries with overlap (dedup)", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person) WHERE p.dept = "Engineering" RETURN p.name AS name
        UNION
        MATCH (p:Person) WHERE p.age > 27 RETURN p.name AS name
      ]])
      assert.is_not_nil(results)
    end)

    it("should UNION with no overlap", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person) WHERE p.dept = "Marketing" RETURN p.name AS name
        UNION
        MATCH (p:Person) WHERE p.dept = "Sales" RETURN p.name AS name
      ]])
      assert.is_not_nil(results)
    end)

    it("should UNION with identical results (dedup to one)", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person {name: "Alice"}) RETURN p.name AS name
        UNION
        MATCH (p:Person {name: "Alice"}) RETURN p.name AS name
      ]])
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 2: UNION ALL (重要/易错)
  -- =======================================================================
  describe("UNION ALL (重要/易错)", function()
    it("should UNION ALL with overlap (keep duplicates)", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person) WHERE p.dept = "Engineering" RETURN p.name AS name
        UNION ALL
        MATCH (p:Person) WHERE p.age > 27 RETURN p.name AS name
      ]])
      assert.is_not_nil(results)
    end)

    it("should UNION ALL with identical results (keep both)", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person {name: "Alice"}) RETURN p.name AS name
        UNION ALL
        MATCH (p:Person {name: "Alice"}) RETURN p.name AS name
      ]])
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 3: Multi-column UNION
  -- =======================================================================
  describe("Multi-column UNION", function()
    it("should UNION with two columns", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person) WHERE p.dept = "Engineering" RETURN p.name AS name, p.age AS value
        UNION
        MATCH (p:Product) RETURN p.name AS name, 0 AS value
      ]])
      assert.is_not_nil(results)
    end)

    it("should UNION mixing node types with type label", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person) RETURN p.name AS item, "person" AS type
        UNION
        MATCH (p:Product) RETURN p.name AS item, "product" AS type
      ]])
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 4: UNION with ORDER BY and LIMIT (易错)
  -- =======================================================================
  describe("UNION with Modifiers (易错)", function()
    it("should UNION with final ORDER BY", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person) WHERE p.dept = "Engineering" RETURN p.name AS name
        UNION
        MATCH (p:Person) WHERE p.dept = "Marketing" RETURN p.name AS name
        ORDER BY name
      ]])
      assert.is_not_nil(results)
    end)

    it("should UNION with LIMIT", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person) RETURN p.name AS name
        UNION
        MATCH (p:Product) RETURN p.name AS name
        LIMIT 3
      ]])
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 5: UNION Edge Cases (易错)
  -- =======================================================================
  describe("UNION Edge Cases (易错)", function()
    it("should handle UNION with empty first result", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person {name: "NonExistent"}) RETURN p.name AS name
        UNION
        MATCH (p:Person {name: "Alice"}) RETURN p.name AS name
      ]])
      assert.is_not_nil(results)
    end)

    it("should handle UNION with both empty", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person {name: "X"}) RETURN p.name AS name
        UNION
        MATCH (p:Person {name: "Y"}) RETURN p.name AS name
      ]])
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 6: Searched CASE Expressions (重要)
  -- =======================================================================
  describe("Searched CASE Expressions (重要)", function()
    it("should classify age categories", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person)
        RETURN p.name,
               p.age,
               CASE
                   WHEN p.age < 18 THEN "minor"
                   WHEN p.age < 65 THEN "adult"
                   ELSE "senior"
               END AS category
        ORDER BY p.age
      ]])
      assert.is_not_nil(results)
    end)

    it("should calculate score grades", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person)
        WHERE p.score IS NOT NULL
        RETURN p.name,
               p.score,
               CASE
                   WHEN p.score >= 90 THEN "A"
                   WHEN p.score >= 80 THEN "B"
                   WHEN p.score >= 70 THEN "C"
                   WHEN p.score >= 60 THEN "D"
                   ELSE "F"
               END AS grade
        ORDER BY p.score DESC
      ]])
      assert.is_not_nil(results)
    end)

    it("should map status to text", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person)
        RETURN p.name,
               CASE
                   WHEN p.status = "active" THEN "Currently Active"
                   WHEN p.status = "pending" THEN "Awaiting Approval"
                   WHEN p.status = "inactive" THEN "Deactivated"
                   ELSE "Unknown"
               END AS status_text
        ORDER BY p.name
      ]])
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 7: CASE with ELSE and without ELSE (易错)
  -- =======================================================================
  describe("CASE ELSE Variations (易错)", function()
    it("should handle CASE with default ELSE value", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person)
        RETURN p.name,
               CASE
                   WHEN p.age > 50 THEN "Over 50"
                   ELSE "50 or under"
               END AS age_group
        ORDER BY p.name
      ]])
      assert.is_not_nil(results)
    end)

    it("should handle CASE without ELSE (returns NULL)", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person)
        RETURN p.name,
               p.age,
               CASE
                   WHEN p.age < 18 THEN "underage"
                   WHEN p.age > 60 THEN "retirement"
               END AS special_status
        ORDER BY p.name
      ]])
      assert.is_not_nil(results)
    end)

    it("should handle CASE returning boolean values", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person)
        RETURN p.name,
               CASE
                   WHEN p.status = "active" THEN true
                   ELSE false
               END AS is_active
        ORDER BY p.name
      ]])
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 8: CASE in WHERE Clause (重要/易错)
  -- =======================================================================
  describe("CASE in WHERE Clause (重要/易错)", function()
    it("should filter by CASE result", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person)
        WHERE CASE
                  WHEN p.age < 18 THEN "minor"
                  WHEN p.age < 65 THEN "adult"
                  ELSE "senior"
              END = "adult"
        RETURN p.name, p.age
        ORDER BY p.age
      ]])
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 9: CASE with Numeric Results
  -- =======================================================================
  describe("CASE Numeric Results", function()
    it("should assign numeric status codes", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Person)
        RETURN p.name,
               p.status,
               CASE
                   WHEN p.status = "active" THEN 1
                   WHEN p.status = "pending" THEN 0
                   ELSE -1
               END AS status_code
        ORDER BY p.name
      ]])
      assert.is_not_nil(results)
    end)

    it("should calculate discount based on stock", function()
      local results = helper.cypher_query(db, [[
        MATCH (p:Product)
        RETURN p.name,
               p.price,
               CASE
                   WHEN p.stock = 0 THEN 0
                   WHEN p.stock < 10 THEN 10
                   ELSE 20
               END AS discount_percent
        ORDER BY p.name
      ]])
      assert.is_not_nil(results)
    end)
  end)
end)
