-- ========================================================================
-- Test 01: Node Operations (CREATE, MATCH, Properties)
-- ========================================================================
-- PURPOSE: Comprehensive testing of node creation, property handling,
--          and basic node matching operations
-- COVERS:  Node creation patterns, property types, label variations,
--          variable naming, multiple nodes, complex properties
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("Node Operations", function()
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
  -- SECTION 1: Basic Node Creation Patterns
  -- =======================================================================
  describe("Basic Node Creation", function()
    it("should create an empty node", function()
      local ok, err = helper.cypher_exec(db, "CREATE ()")
      assert.is_true(ok, "Empty node creation: " .. tostring(err))
    end)

    it("should create a node with variable only", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n)")
      assert.is_true(ok, "Node with variable: " .. tostring(err))
    end)

    it("should create a node with label only", function()
      local ok, err = helper.cypher_exec(db, "CREATE (:Person)")
      assert.is_true(ok, "Node with label: " .. tostring(err))
    end)

    it("should create a node with variable and label", function()
      local ok, err = helper.cypher_exec(db, "CREATE (p:Person)")
      assert.is_true(ok, "Node with variable and label: " .. tostring(err))
    end)

    it("should create a node with empty properties", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {})")
      assert.is_true(ok, "Node with empty properties: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 2: Property Types and Values
  -- =======================================================================
  describe("Property Types", function()
    it("should handle string properties", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {name: "Alice"})')
      assert.is_true(ok, "String property: " .. tostring(err))
    end)

    it("should handle integer properties", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {age: 30})")
      assert.is_true(ok, "Integer property: " .. tostring(err))
    end)

    it("should handle float properties", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {score: 95.5})")
      assert.is_true(ok, "Float property: " .. tostring(err))
    end)

    it("should handle boolean properties", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {active: true, verified: false})")
      assert.is_true(ok, "Boolean properties: " .. tostring(err))
    end)

    it("should handle null property", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {value: null})")
      assert.is_true(ok, "Null property: " .. tostring(err))
    end)

    it("should handle mixed property types", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {name: "Bob", age: 25, score: 88.5, active: true})')
      assert.is_true(ok, "Mixed property types: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 3: Special Property Values (易错)
  -- =======================================================================
  describe("Special Property Values (易错)", function()
    it("should handle empty string property", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {name: ""})')
      assert.is_true(ok, "Empty string: " .. tostring(err))
    end)

    it("should handle string with special characters", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {data: "Special: @#$%"})')
      assert.is_true(ok, "Special chars: " .. tostring(err))
    end)

    it("should handle large integer", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {big: 1000000})")
      assert.is_true(ok, "Large integer: " .. tostring(err))
    end)

    it("should handle negative integer", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {neg: -42})")
      assert.is_true(ok, "Negative integer: " .. tostring(err))
    end)

    it("should handle zero", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {zero: 0})")
      assert.is_true(ok, "Zero: " .. tostring(err))
    end)

    it("should handle decimal variations", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {pi: 3.14159, small: 0.001, neg: -2.5})")
      assert.is_true(ok, "Decimal variations: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 4: Label and Variable Variations
  -- =======================================================================
  describe("Label and Variable Variations", function()
    it("should handle uppercase label", function()
      local ok, err = helper.cypher_exec(db, "CREATE (:PERSON)")
      assert.is_true(ok, "Uppercase label: " .. tostring(err))
    end)

    it("should handle mixed case label", function()
      local ok, err = helper.cypher_exec(db, "CREATE (:PersonEntity)")
      assert.is_true(ok, "Mixed case label: " .. tostring(err))
    end)

    it("should handle label with underscore", function()
      local ok, err = helper.cypher_exec(db, "CREATE (:person_type)")
      assert.is_true(ok, "Label with underscore: " .. tostring(err))
    end)

    it("should handle label with number", function()
      local ok, err = helper.cypher_exec(db, "CREATE (:Person2)")
      assert.is_true(ok, "Label with number: " .. tostring(err))
    end)

    it("should handle long variable name", function()
      local ok, err = helper.cypher_exec(db, "CREATE (thisIsAVeryLongVariableName)")
      assert.is_true(ok, "Long variable name: " .. tostring(err))
    end)

    it("should handle variable with underscore", function()
      local ok, err = helper.cypher_exec(db, "CREATE (my_node)")
      assert.is_true(ok, "Variable with underscore: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 5: Multiple Node Creation
  -- =======================================================================
  describe("Multiple Node Creation", function()
    it("should create two empty nodes", function()
      local ok, err = helper.cypher_exec(db, "CREATE (), ()")
      assert.is_true(ok, "Two empty nodes: " .. tostring(err))
    end)

    it("should create two nodes with labels", function()
      local ok, err = helper.cypher_exec(db, "CREATE (:Person), (:Company)")
      assert.is_true(ok, "Two nodes with labels: " .. tostring(err))
    end)

    it("should create mixed node types", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (p:Person {name: "Alice"}), (:Company {name: "TechCorp"}), (c)')
      assert.is_true(ok, "Mixed node types: " .. tostring(err))
    end)

    it("should create five nodes at once", function()
      local ok, err = helper.cypher_exec(db, "CREATE (a), (b), (c), (d), (e)")
      assert.is_true(ok, "Five nodes: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 6: Property Key Variations (易错)
  -- =======================================================================
  describe("Property Key Variations (易错)", function()
    it("should handle uppercase property key", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {NAME: "Alice"})')
      assert.is_true(ok, "Uppercase property key: " .. tostring(err))
    end)

    it("should handle mixed case property key", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {firstName: "Bob"})')
      assert.is_true(ok, "Mixed case property key: " .. tostring(err))
    end)

    it("should handle property key with underscore", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {first_name: "Carol"})')
      assert.is_true(ok, "Property key with underscore: " .. tostring(err))
    end)

    it("should handle property key starting with underscore", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {_id: 123})")
      assert.is_true(ok, "Property key starting with underscore: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 7: Advanced Property Patterns (易错)
  -- =======================================================================
  describe("Advanced Property Patterns (易错)", function()
    it("should handle multiple properties", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {first: "Alice", last: "Smith"})')
      assert.is_true(ok, "Multiple properties: " .. tostring(err))
    end)

    it("should handle many properties", function()
      local ok, err = helper.cypher_exec(db, "CREATE (n {a: 1, b: 2, c: 3, d: 4, e: 5})")
      assert.is_true(ok, "Many properties: " .. tostring(err))
    end)

    it("should handle same label with different properties", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (:Person {name: "Alice"}), (:Person {name: "Bob"})')
      assert.is_true(ok, "Same label, different properties: " .. tostring(err))
    end)

    it("should handle different labels with same property", function()
      local ok, err = helper.cypher_exec(db, "CREATE (:Person {id: 1}), (:Company {id: 2})")
      assert.is_true(ok, "Different labels, same property: " .. tostring(err))
    end)

    it("should handle complex combination", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (p1:Person {name: "Alice", age: 30}), (p2:Person {name: "Bob"}), (:Company {name: "Tech"})')
      assert.is_true(ok, "Complex combination: " .. tostring(err))
    end)

    it("should handle duplicate property key (last value wins)", function()
      local ok, err = helper.cypher_exec(db, 'CREATE (n {name: "First", name: "Last"})')
      assert.is_true(ok, "Duplicate property key: " .. tostring(err))
    end)
  end)

  -- =======================================================================
  -- SECTION 8: Verification - Database State
  -- =======================================================================
  describe("Database State Verification", function()
    it("should have correct node count after creation", function()
      helper.cypher_exec(db, "CREATE (:Person {name: 'Alice'})")
      helper.cypher_exec(db, "CREATE (:Person {name: 'Bob'})")
      helper.cypher_exec(db, "CREATE (:Company {name: 'TechCorp'})")

      local results = helper.cypher_query(db, "MATCH (n) RETURN count(n) as cnt")
      assert.is_not_nil(results)
      local json = results[1][1]
      assert.is_true(json:find("3") ~= nil, "Should have 3 nodes, got: " .. json)
    end)

    it("should have correct label distribution", function()
      helper.cypher_exec(db, "CREATE (:Person {name: 'Alice'})")
      helper.cypher_exec(db, "CREATE (:Person {name: 'Bob'})")
      helper.cypher_exec(db, "CREATE (:Company {name: 'TechCorp'})")

      local results = helper.cypher_query(db, "MATCH (n:Person) RETURN count(n) as cnt")
      assert.is_not_nil(results)
      local json = results[1][1]
      assert.is_true(json:find("2") ~= nil, "Should have 2 Person nodes, got: " .. json)
    end)
  end)
end)
