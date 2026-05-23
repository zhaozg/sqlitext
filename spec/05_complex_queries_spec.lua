-- ========================================================================
-- Test 05: Complex Query Operations
-- ========================================================================
-- PURPOSE: Advanced graph query patterns including multi-hop relationships,
--          complex patterns, and sophisticated graph traversals
-- COVERS:  Multi-hop paths, complex patterns, relationship chains,
--          advanced WHERE clauses, nested patterns, aggregation
-- ========================================================================

local sqlite3 = require("lsqlite3")
local helper = require("spec.helper")

describe("Complex Query Operations", function()
  local db

  before_each(function()
    db = sqlite3.open_memory()
    assert.is_not_nil(db, "Failed to open database")
    helper.ensure_graphqlite(db)

    -- Setup: Create a complex graph structure
    helper.cypher_exec(db, 'CREATE (alice:Person {name: "Alice", age: 30, department: "Engineering"})')
    helper.cypher_exec(db, 'CREATE (bob:Person {name: "Bob", age: 25, department: "Sales"})')
    helper.cypher_exec(db, 'CREATE (charlie:Person {name: "Charlie", age: 35, department: "Engineering"})')
    helper.cypher_exec(db, 'CREATE (diana:Person {name: "Diana", age: 28, department: "Marketing"})')
    helper.cypher_exec(db, 'CREATE (eve:Person {name: "Eve", age: 32, department: "Engineering"})')
    helper.cypher_exec(db, 'CREATE (techcorp:Company {name: "TechCorp", founded: 2010, employees: 500})')
    helper.cypher_exec(db, 'CREATE (startup:Company {name: "StartupInc", founded: 2020, employees: 50})')
    helper.cypher_exec(db, 'CREATE (megacorp:Company {name: "MegaCorp", founded: 1995, employees: 10000})')
    helper.cypher_exec(db, 'CREATE (project1:Project {name: "WebApp", budget: 100000, status: "active"})')
    helper.cypher_exec(db, 'CREATE (project2:Project {name: "MobileApp", budget: 150000, status: "completed"})')
    helper.cypher_exec(db, 'CREATE (project3:Project {name: "Database", budget: 200000, status: "planning"})')
    helper.cypher_exec(db, 'CREATE (nyc:City {name: "NYC", population: 8000000})')
    helper.cypher_exec(db, 'CREATE (sf:City {name: "San Francisco", population: 900000})')
    helper.cypher_exec(db, 'CREATE (la:City {name: "Los Angeles", population: 4000000})')

    -- Create relationships
    helper.cypher_exec(db, 'MATCH (alice:Person {name: "Alice"}), (techcorp:Company {name: "TechCorp"}) CREATE (alice)-[:WORKS_FOR {since: "2022", role: "Senior Engineer"}]->(techcorp)')
    helper.cypher_exec(db, 'MATCH (bob:Person {name: "Bob"}), (startup:Company {name: "StartupInc"}) CREATE (bob)-[:WORKS_FOR {since: "2023", role: "Sales Manager"}]->(startup)')
    helper.cypher_exec(db, 'MATCH (charlie:Person {name: "Charlie"}), (techcorp:Company {name: "TechCorp"}) CREATE (charlie)-[:WORKS_FOR {since: "2020", role: "Lead Engineer"}]->(techcorp)')
    helper.cypher_exec(db, 'MATCH (alice:Person {name: "Alice"}), (charlie:Person {name: "Charlie"}) CREATE (charlie)-[:MANAGES {team: "backend"}]->(alice)')
    helper.cypher_exec(db, 'MATCH (diana:Person {name: "Diana"}), (bob:Person {name: "Bob"}) CREATE (diana)-[:MANAGES {team: "sales"}]->(bob)')
    helper.cypher_exec(db, 'MATCH (alice:Person {name: "Alice"}), (project1:Project {name: "WebApp"}) CREATE (alice)-[:WORKS_ON {role: "developer", allocation: 0.8}]->(project1)')
    helper.cypher_exec(db, 'MATCH (charlie:Person {name: "Charlie"}), (project1:Project {name: "WebApp"}) CREATE (charlie)-[:LEADS]->(project1)')
    helper.cypher_exec(db, 'MATCH (alice:Person {name: "Alice"}), (nyc:City {name: "NYC"}) CREATE (alice)-[:LIVES_IN]->(nyc)')
    helper.cypher_exec(db, 'MATCH (bob:Person {name: "Bob"}), (sf:City {name: "San Francisco"}) CREATE (bob)-[:LIVES_IN]->(sf)')
    helper.cypher_exec(db, 'MATCH (techcorp:Company {name: "TechCorp"}), (nyc:City {name: "NYC"}) CREATE (techcorp)-[:LOCATED_IN]->(nyc)')
    helper.cypher_exec(db, 'MATCH (diana:Person {name: "Diana"}), (startup:Company {name: "StartupInc"}) CREATE (diana)-[:CONSULTS_FOR {rate: 200}]->(startup)')
    helper.cypher_exec(db, 'MATCH (eve:Person {name: "Eve"}), (megacorp:Company {name: "MegaCorp"}) CREATE (eve)-[:WORKS_FOR {since: "2018", role: "Architect"}]->(megacorp)')
    helper.cypher_exec(db, 'MATCH (startup:Company {name: "StartupInc"}), (sf:City {name: "San Francisco"}) CREATE (startup)-[:LOCATED_IN]->(sf)')
  end)

  after_each(function()
    if db then
      db:close()
      db = nil
    end
  end)

  -- =======================================================================
  -- SECTION 1: Multi-hop Relationship Patterns (重要)
  -- =======================================================================
  describe("Multi-hop Relationship Patterns (重要)", function()
    it("should traverse two-hop relationship (Person -> Company -> City)", function()
      local results = helper.cypher_query(db, "MATCH (p:Person)-[:WORKS_FOR]->(c:Company)-[:LOCATED_IN]->(city:City) RETURN p.name, c.name, city.name")
      assert.is_not_nil(results)
    end)

    it("should traverse three-hop relationship", function()
      local results = helper.cypher_query(db, "MATCH (manager:Person)-[:MANAGES]->(employee:Person)-[:WORKS_FOR]->(company:Company)-[:LOCATED_IN]->(city:City) RETURN manager.name, employee.name, company.name, city.name")
      assert.is_not_nil(results)
    end)

    it("should traverse project collaboration chain", function()
      local results = helper.cypher_query(db, "MATCH (lead:Person)-[:LEADS]->(project:Project)<-[:WORKS_ON]-(dev:Person) RETURN lead.name, project.name, dev.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 2: Complex Pattern Matching (重要)
  -- =======================================================================
  describe("Complex Pattern Matching (重要)", function()
    it("should match multiple relationship types from same node", function()
      local results = helper.cypher_query(db, "MATCH (p:Person)-[:WORKS_FOR]->(company), (p)-[:LIVES_IN]->(city) RETURN p.name, company.name, city.name")
      assert.is_not_nil(results)
    end)

    it("should match fan-out pattern (one-to-many)", function()
      local results = helper.cypher_query(db, "MATCH (manager:Person)-[:MANAGES]->(employee:Person) RETURN manager.name, count(employee.name) as team_size")
      assert.is_not_nil(results)
    end)

    it("should match fan-in pattern (many-to-one)", function()
      local results = helper.cypher_query(db, "MATCH (person:Person)-[:WORKS_FOR]->(company:Company) RETURN company.name, count(person.name) as employee_count")
      assert.is_not_nil(results)
    end)

    it("should match diamond pattern (diverge and converge)", function()
      local results = helper.cypher_query(db, "MATCH (mgr:Person)-[:MANAGES]->(emp:Person)-[:WORKS_FOR]->(company:Company), (mgr)-[:WORKS_FOR]->(company) RETURN mgr.name, emp.name, company.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 3: Advanced WHERE Clause Patterns (重要)
  -- =======================================================================
  describe("Advanced WHERE Clause Patterns (重要)", function()
    it("should filter across relationships with complex conditions", function()
      local results = helper.cypher_query(db, "MATCH (p:Person)-[:WORKS_FOR]->(c:Company) WHERE p.age > 30 AND c.founded < 2015 RETURN p.name, p.age, c.name, c.founded")
      assert.is_not_nil(results)
    end)

    it("should filter by relationship property", function()
      local results = helper.cypher_query(db, 'MATCH (p:Person)-[r:WORKS_FOR]->(c:Company) WHERE r.since >= "2022" RETURN p.name, r.since, c.name')
      assert.is_not_nil(results)
    end)

    it("should filter with complex logical combinations", function()
      local results = helper.cypher_query(db, "MATCH (p:Person) WHERE (p.age > 30 AND p.department = \"Engineering\") OR (p.age < 26 AND p.department = \"Sales\") RETURN p.name, p.age, p.department")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 4: Relationship Chain Analysis (重要)
  -- =======================================================================
  describe("Relationship Chain Analysis (重要)", function()
    it("should find people in same city as their company", function()
      local results = helper.cypher_query(db, "MATCH (p:Person)-[:LIVES_IN]->(city:City)<-[:LOCATED_IN]-(c:Company)<-[:WORKS_FOR]-(p) RETURN p.name, city.name, c.name")
      assert.is_not_nil(results)
    end)

    it("should find indirect connections through intermediaries", function()
      local results = helper.cypher_query(db, "MATCH (a:Person)-[:WORKS_FOR]->(company:Company)<-[:WORKS_FOR]-(colleague:Person) WHERE a.name <> colleague.name RETURN a.name, colleague.name, company.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 5: Graph Traversal Patterns (重要)
  -- =======================================================================
  describe("Graph Traversal Patterns (重要)", function()
    it("should find all connections from a specific person", function()
      local results = helper.cypher_query(db, "MATCH (alice:Person {name: \"Alice\"})-[r]->(connected) RETURN alice.name, type(r), connected")
      assert.is_not_nil(results)
    end)

    it("should traverse bidirectional relationships", function()
      local results = helper.cypher_query(db, "MATCH (a:Person)-[:MANAGES]-(b:Person) RETURN a.name, b.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 6: Aggregation and Grouping Patterns (重要)
  -- =======================================================================
  describe("Aggregation and Grouping (重要)", function()
    it("should count relationships by type", function()
      local results = helper.cypher_query(db, "MATCH ()-[r]->() RETURN type(r) as relationship_type, count(r) as count ORDER BY count DESC")
      assert.is_not_nil(results)
    end)

    it("should aggregate by department", function()
      local results = helper.cypher_query(db, "MATCH (p:Person) RETURN p.department, count(p) as department_size, avg(p.age) as avg_age ORDER BY department_size DESC")
      assert.is_not_nil(results)
    end)

    it("should return company statistics", function()
      local results = helper.cypher_query(db, "MATCH (c:Company) RETURN c.name, c.employees, c.founded ORDER BY c.employees DESC")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 7: Complex Filtering (重要/易错)
  -- =======================================================================
  describe("Complex Filtering (重要/易错)", function()
    it("should find senior engineers in large companies", function()
      local results = helper.cypher_query(db, "MATCH (p:Person)-[r:WORKS_FOR]->(c:Company) WHERE p.department = \"Engineering\" AND p.age >= 30 AND c.employees > 100 RETURN p.name, p.age, r.role, c.name")
      assert.is_not_nil(results)
    end)

    it("should filter projects with specific budget ranges", function()
      local results = helper.cypher_query(db, "MATCH (proj:Project) WHERE proj.budget >= 100000 AND proj.budget <= 200000 RETURN proj.name, proj.budget, proj.status ORDER BY proj.budget")
      assert.is_not_nil(results)
    end)

    it("should find overlapping work relationships", function()
      local results = helper.cypher_query(db, "MATCH (p1:Person)-[:WORKS_FOR]->(c:Company)<-[:WORKS_FOR]-(p2:Person) WHERE p1.name < p2.name RETURN p1.name, p2.name, c.name")
      assert.is_not_nil(results)
    end)
  end)

  -- =======================================================================
  -- SECTION 8: Edge Cases (易错)
  -- =======================================================================
  describe("Edge Cases (易错)", function()
    it("should handle empty result complex query", function()
      local results = helper.cypher_query(db, "MATCH (p:Person)-[:WORKS_FOR]->(c:Company) WHERE c.founded > 2025 RETURN p.name, c.name")
      assert.is_not_nil(results)
    end)

    it("should handle self-referential patterns", function()
      local results = helper.cypher_query(db, "MATCH (p:Person)-[:MANAGES]->(p) RETURN p.name")
      assert.is_not_nil(results)
    end)

    it("should handle complex NULL handling", function()
      local results = helper.cypher_query(db, "MATCH (p:Person) WHERE p.nonexistent IS NULL RETURN p.name, p.nonexistent LIMIT 3")
      assert.is_not_nil(results)
    end)

    it("should handle OPTIONAL MATCH (left-outer-join)", function()
      local results = helper.cypher_query(db, "MATCH (p:Person) OPTIONAL MATCH (p)-[:MANAGES]->(subordinate:Person) RETURN p.name, subordinate.name")
      assert.is_not_nil(results)
    end)
  end)
end)
