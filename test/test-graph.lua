-- test_graphqlite.lua
-- Lua 移植版本: https://colliery-io.github.io/graphqlite/latest/examples/01_getting_started.sql
-- 需要: lsqlite3, graphqlite 扩展 (路径请按实际修改)

local sqlite3 = require("lsqlite3")

-- 配置
local extension_path = "./build/graphqlite.dylib"  -- 根据你的实际路径修改

-- 辅助函数：安全地执行单条 Cypher 查询并忽略返回值（用于 CREATE）
local function cypher_exec(db, cypher_query)
    -- 转义 Cypher 字符串内的单引号：将 ' 替换为 ''
    local escaped = cypher_query:gsub("'", "''")
    local sql = string.format("SELECT cypher('%s');", escaped)
    local ok, err = pcall(function() db:exec(sql) end)
    if not ok then
        print("Error executing Cypher: " .. err)
        print("Query was: " .. cypher_query)
        return false
    end
    return true
end

-- 辅助函数：执行查询并打印结果（对应原示例中的 SELECT cypher(...)）
local function cypher_query(db, cypher_query, label)
    if label then
        print(label)
    end
    local escaped = cypher_query:gsub("'", "''")
    local sql = string.format("SELECT cypher('%s');", escaped)
    local stmt = db:prepare(sql)
    if not stmt then
        print("Prepare failed: " .. db:errmsg())
        return
    end
    -- 遍历结果行（cypher 返回的结果通常是 JSON 字符串，直接打印）
    for row in stmt:rows() do
        -- row 是一个 table，第一个字段是 cypher() 的返回值
        for i, col in ipairs(row) do
            print(tostring(col))
        end
    end
    stmt:finalize()
end

-- 主流程
local function main()
    -- 1. 打开内存数据库（也可以改为文件数据库 "test.db"）
    local db = sqlite3.open_memory()
    if not db then
        print("Failed to open database")
        return
    end
    print("Database opened (in-memory).")

    -- 2. 启用扩展加载
    db:exec("PRAGMA load_extension = 1;")
    print("Extension loading enabled.")

    -- 3. 加载 GraphQLite 扩展
    local load_sql = string.format("SELECT load_extension('%s');", extension_path)
    local ok, err = pcall(function() db:exec(load_sql) end)
    if not ok then
        print("Failed to load GraphQLite extension: " .. err)
        db:close()
        return
    end
    print("GraphQLite extension loaded.\n")

    -- 4. 创建节点（对应 CREATE）
    cypher_exec(db, 'CREATE (a:Person {name: "Alice", age: 30})')
    cypher_exec(db, 'CREATE (b:Person {name: "Bob", age: 25})')
    cypher_exec(db, 'CREATE (c:Person {name: "Charlie", age: 35})')
    print("Nodes created.")

    -- 5. 创建关系
    cypher_exec(db, [[
        MATCH (a:Person {name: "Alice"}), (b:Person {name: "Bob"})
        CREATE (a)-[:KNOWS]->(b)
    ]])
    cypher_exec(db, [[
        MATCH (b:Person {name: "Bob"}), (c:Person {name: "Charlie"})
        CREATE (b)-[:KNOWS]->(c)
    ]])
    print("Relationships created.\n")

    -- 6. 查询所有人员
    cypher_query(db, 'MATCH (p:Person) RETURN p.name, p.age', 'All people:')

    -- 7. 查询谁认识谁
    cypher_query(db, 'MATCH (a:Person)-[:KNOWS]->(b:Person) RETURN a.name, b.name', '\nWho knows who:')

    -- 8. 查询朋友的朋友（Alice 的 2 度人脉）
    cypher_query(db, [[
        MATCH (a:Person {name: "Alice"})-[:KNOWS]->()-[:KNOWS]->(fof)
        RETURN fof.name
    ]], '\nFriends of friends:')

    -- 9. 关闭数据库
    db:close()
    print("\nTest completed.")
end

-- 执行
main()
