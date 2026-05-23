-- ========================================================================
-- GraphQLite Test Helper Module
-- ========================================================================
-- Shared utility functions for all spec test files
-- ========================================================================

local sqlite3 = require("lsqlite3")

local helper = {}

-- 探测 GraphQLite 是否已加载（静态编译或已动态加载）
function helper.is_graphqlite_loaded(db)
  local ok, err = pcall(function()
    for row in db:nrows("SELECT graphqlite_test()") do
      return row["graphqlite_test()"] ~= nil
    end
  end)
  return ok
end

-- 尝试加载 GraphQLite 扩展
function helper.ensure_graphqlite(db)
  if helper.is_graphqlite_loaded(db) then
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

-- 安全地执行单条 Cypher 查询（不收集结果）
function helper.cypher_exec(db, cypher_query)
  local escaped = cypher_query:gsub("'", "''")
  local sql = string.format("SELECT cypher('%s');", escaped)
  local ok, err = pcall(function() db:exec(sql) end)
  return ok, err
end

-- 执行查询并收集结果
function helper.cypher_query(db, cypher_query)
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

return helper
