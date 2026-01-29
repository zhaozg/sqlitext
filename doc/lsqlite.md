# LuaSQLite3

- [NAME](#name)
- [OVERVIEW](#overview)
- [DOWNLOAD](#download)
- [INSTALLATION](#installation)
- [EXAMPLES](#examples)
- [VERIFICATION TESTS](#verification_tests)
- [REFERENCE](#reference)
- [SQLite3 functions](#sqlite3_functions)
  - [sqlite3.complete](#sqlite3_complete)
  - [sqlite3.lversion](#sqlite3_lversion)
  - [sqlite3.open](#sqlite3_open)
  - [sqlite3.open_memory](#sqlite3_open_memory)
  - [sqlite3.open_ptr](#sqlite3_open_ptr)
  - [sqlite3.backup_init](#sqlite3_backup_init)
  - [sqlite3.temp_directory](#sqlite3_temp_directory)
  - [sqlite3.version](#sqlite3_version)
- [Database methods](#database_methods)
  - [db:busy_handler](#db_busy_handler)
  - [db:busy_timeout](#db_busy_timeout)
  - [db:changes](#db_changes)
  - [db:close](#db_close)
  - [db:close_vm](#db_close_vm)
  - [db:get_ptr](#db_get_ptr)
  - [db:commit_hook](#db_commit_hook)
  - [db:create_aggregate](#db_create_aggregate)
  - [db:create_collation](#db_create_collation)
  - [db:create_function](#db_create_function)
  - [db:errcode](#db_errcode)
  - [db:errmsg](#db_errmsg)
  - [db:exec](#db_exec)
  - [db:interrupt](#db_interrupt)
  - [db:db_filename](#db_db_filename)
  - [db:isopen](#db_isopen)
  - [db:last_insert_rowid](#db_last_insert_rowid)
  - [db:load_extension](#db_load_extension)
  - [db:nrows](#db_nrows)
  - [db:prepare](#db_prepare)
  - [db:progress_handler](#db_progress_handler)
  - [db:rollback_hook](#db_rollback_hook)
  - [db:rows](#db_rows)
  - [db:total_changes](#db_total_changes)
  - [db:trace](#db_trace)
  - [db:update_hook](#db_update_hook)
  - [db:urows](#db_urows)
- [Methods for prepared statements](#methods_for_prepared_statements)
  - [stmt:bind](#stmt_bind)
  - [stmt:bind_blob](#stmt_bind_blob)
  - [stmt:bind_names](#stmt_bind_names)
  - [stmt:bind_parameter_count](#stmt_bind_parameter_count)
  - [stmt:bind_parameter_name](#stmt_bind_parameter_name)
  - [stmt:bind_values](#stmt_bind_values)
  - [stmt:columns](#stmt_columns)
  - [stmt:finalize](#stmt_finalize)
  - [stmt:get_name](#stmt_get_name)
  - [stmt:get_named_types](#stmt_get_named_types)
  - [stmt:get_named_values](#stmt_get_named_values)
  - [stmt:get_names](#stmt_get_names)
  - [stmt:get_type](#stmt_get_type)
  - [stmt:get_types](#stmt_get_types)
  - [stmt:get_unames](#stmt_get_unames)
  - [stmt:get_utypes](#stmt_get_utypes)
  - [stmt:get_uvalues](#stmt_get_uvalues)
  - [stmt:get_value](#stmt_get_value)
  - [stmt:get_values](#stmt_get_values)
  - [stmt:isopen](#stmt_isopen)
  - [stmt:last_insert_rowid](#stmt_last_insert_rowid)
  - [stmt:nrows](#stmt_nrows)
  - [stmt:reset](#stmt_reset)
  - [stmt:rows](#stmt_rows)
  - [stmt:step](#stmt_step)
  - [stmt:urows](#stmt_urows)
- [Methods for callback contexts](#methods_for_callback_contexts)
  - [context:aggregate_count](#context_aggregate_count)
  - [context:get_aggregate_data](#context_get_aggregate_data)
  - [context:set_aggregate_data](#context_set_aggregate_data)
  - [context:result](#context_result)
  - [context:result_null](#context_result_null)
  - [context:result_number](#context_result_number)
  - [context:result_int](#context_result_int)
  - [context:result_text](#context_result_text)
  - [context:result_blob](#context_result_blob)
  - [context:result_error](#context_result_error)
  - [context:user_data](#context_user_data)
- [Methods for Online Backup](#methods_for_online_backup)
  - [backup:step](#bu_step)
  - [backup:remaining](#bu_remaining)
  - [backup:pagecount](#bu_pagecount)
  - [backup:finish](#bu_finish)
- [Numerical error and result codes](#numerical_error_and_result_codes)
- [VERSION](#version)
- [CREDITS](#credits)
- [LICENSE](#license)

----------------------------------------------------------------------

----------------------------------------------------------------------

# [NAME](#name)

**LuaSQLite 3** - a Lua 5.1 to 5.3 wrapper for the SQLite3 library

----------------------------------------------------------------------

# [OVERVIEW](#overview)

**LuaSQLite 3** is a thin wrapper around the public domain SQLite3 database engine.

There are two modules, identical except that one links SQLite3 dynamically, the other statically.

The module `lsqlite3` links SQLite3 dynamically. To use this module you need the SQLite3 library (DLL or .so). You can get it from <http://www.sqlite.org/>

The module `lsqlite3complete` links SQLite3 statically. The SQLite3 amalgamation source code is included in the LuaSQLite 3 distribution. This can simplify deployment, but might result in more than one copy of the SQLite library if other parts of the code also include it. See [http://www.sqlite.org/howtocorrupt.html](http://www.sqlite.org/howtocorrupt.html#multiple_copies_of_sqlite_linked_into_the_same_application) for an explanation on why it would be a bad idea.

Both modules support the creation and manipulation of SQLite3 databases. After a `sqlite3 = require('lsqlite3')` (or `sqlite3 = require('lsqlite3complete')`) the exported functions are called with prefix `sqlite3`. However, most sqlite3 functions are called via an object-oriented interface to either database or SQL statement objects; see below for details.

This documentation does not attempt to describe how SQLite3 itself works, it just describes the Lua binding and the available functions. For more information about the SQL features supported by SQLite3 and details about the syntax of SQL statements and queries, please see the **SQLite3 documentation** <http://www.sqlite.org/>. Using some of the advanced features (how to use callbacks, for instance) will require some familiarity with the SQLite3 API.

----------------------------------------------------------------------

# [DOWNLOAD](#download)

**LuaSQLite 3** source code can be downloaded from its Fossil (<http://lua.sqlite.org/>) page.

For `lsqlite3` (but not for `lsqlite3complete`) you will also need to build or obtain an SQLite3 loadable library (DLL or .so). See <http://www.sqlite.org/> for obtaining SQLite3 source code or downloading a binary SQLite3 library.

----------------------------------------------------------------------

# [INSTALLATION](#installation)

Luarocks (<http://luarocks.org/>) is the preferred mechanism to build and install `lsqlite3` or `lsqlite3complete`; for `lsqlite3` it assumes an SQLite3 library is already installed. For `lsqlite3complete` no SQLite3 library is needed.

----------------------------------------------------------------------

# [EXAMPLES](#examples)

The distribution contains an *examples* directory. The unit tests also show some example use.

----------------------------------------------------------------------

# [VERIFICATION TESTS](#verification_tests)

The distribution contains a *tests* directory with some units tests using an enhanced version of Michael Roth's `lunit` called `lunitx`. Some of the tests were also derived from Michael's **lua-sqlite3** module, and more unit tests added by Doug Currie. Get `lunitx` using Luarocks.

The distribution also contains some functional tests by Tiago.

This version of `lsqlite3` was tested with SQLite 3.11.0 and 3.15.1.

----------------------------------------------------------------------

# [REFERENCE](#reference)

----------------------------------------------------------------------

# [SQLite3 functions](#sqlite3_functions)

## [sqlite3.complete](#sqlite3_complete)

```lua
sqlite3.complete(sql)
```

Returns true if the string `sql` comprises one or more complete SQL statements and false otherwise.

## [sqlite3.open](#sqlite3_open)

```lua
sqlite3.open(filename)
```

Opens (or creates if it does not exist) an SQLite database with name `filename` and returns its handle as userdata (the returned object should be used for all further method calls in connection with this specific database, see [Database methods](#database_methods)).

Example:

```lua
myDB = sqlite3.open('MyDatabase.sqlite3')  -- open
-- do some database calls...
myDB:close()  -- close
```

In case of an error, the function returns nil, an error code and an error message.

Since 0.9.4, there is a second optional flags argument to `sqlite3.open`.

```lua
sqlite3.open(filename, flags)
```

See [sqlite3_open_v2](https://www.sqlite.org/c3ref/open.html) for an explanation of these flags and options.

Example:

```lua
local db = sqlite3.open('foo.db', sqlite3.OPEN_READWRITE + sqlite3.OPEN_CREATE + sqlite3.OPEN_SHAREDCACHE)
```

The default value for flags is `sqlite3.OPEN_READWRITE + sqlite3.OPEN_CREATE`.

## [sqlite3.open_memory](#sqlite3_open_memory)

```lua
sqlite3.open_memory()
```

Opens an SQLite database **in memory** and returns its handle as userdata. In case of an error, the function returns nil, an error code and an error message. (In-memory databases are volatile as they are never stored on disk.)

## [sqlite3.open_ptr](#sqlite3_open_ptr)

```lua
sqlite3.open_ptr(db_ptr)
```

Opens the SQLite database corresponding to the light userdata `db_ptr` and returns its handle as userdata. Use [`db:get_ptr`](#db_get_ptr) to get a `db_ptr` for an open database.

## [sqlite3.backup_init](#sqlite3_backup_init)

```lua
sqlite3.backup_init(target_db, target_name, source_db, source_name)
```

Starts an SQLite Online Backup from `source_db` to `target_db` and returns its handle as userdata. The `source_db` and `target_db` are open databases; they may be in-memory or file-based databases. The `target_name` and `source_name` are "main" for the main database, "temp" for the temporary database, or the name specified after the AS keyword in an ATTACH statement for an attached database.

The source and target databases must be different, or else the init call will fail with an error. A call to `sqlite3.backup_init` will fail, returning NULL, if there is already a read or read-write transaction open on the target database.

If an error occurs within `sqlite3.backup_init`, then NULL is returned, and an error code and error message are stored in `target_db`. The error code and message for the failed call can be retrieved using the [`db:errcode`](#db_errcode), or [`db:errmsg`](#db_errmsg).

## [sqlite3.temp_directory](#sqlite3_temp_directory)

```lua
sqlite3.temp_directory([temp])
```

Sets or queries the directory used by SQLite for temporary files. If string `temp` is a directory name or nil, the temporary directory is set accordingly and the old value is returned. If `temp` is missing, the function simply returns the current temporary directory.

## [sqlite3.version](#sqlite3_version)

```lua
sqlite3.version()
```

Returns a string with SQLite version information, in the form 'x.y[.z[.p]]'.

## [sqlite3.lversion](#sqlite3_lversion)

```lua
sqlite3.lversion()
```

Returns a string with lsqlite3 library version information, in the form 'x.y[.z]'.

----------------------------------------------------------------------

# [Database methods](#database_methods)

After opening a database with [`sqlite3.open()`](#sqlite3_open) or [`sqlite3.open_memory()`](#sqlite3_open_memory) the returned database object should be used for all further method calls in connection with that database. An open database object supports the following methods.

## [db:busy_handler](#db_busy_handler)

```lua
db:busy_handler([func[, udata]])
```

Sets or removes a busy handler for a database. `func` is either a Lua function that implements the busy handler or nil to remove a previously set handler. This function returns nothing.

The handler function is called with two parameters: `udata` and the number of (re-)tries for a pending transaction. It should return nil, false or 0 if the transaction is to be aborted. All other values will result in another attempt to perform the transaction. (See the SQLite documentation for important hints about writing busy handlers.)

## [db:busy_timeout](#db_busy_timeout)

```lua
db:busy_timeout(t)
```

Sets a busy handler that waits for `t` milliseconds if a transaction cannot proceed. Calling this function will remove any busy handler set by [`db:busy_handler()`](#db_busy_handler); calling it with an argument less than or equal to 0 will turn off all busy handlers.

## [db:changes](#db_changes)

```lua
db:changes()
```

This function returns the number of database rows that were changed (or inserted or deleted) by the most recent SQL statement. Only changes that are directly specified by INSERT, UPDATE, or DELETE statements are counted. Auxiliary changes caused by triggers are not counted. Use [`db:total_changes()`](#db_total_changes) to find the total number of changes.

## [db:close](#db_close)

```lua
db:close()
```

Closes a database. All SQL statements prepared using [`db:prepare()`](#db_prepare) should have been finalized before this function is called. The function returns `sqlite3.OK` on success or else a numerical error code (see the list of [Numerical error and result codes](#numerical_error_and_result_codes)).

## [db:close_vm](#db_close_vm)

```lua
db:close_vm(temponly)
```

Finalizes all statements that have not been explicitly finalized. If `temponly` is true, only internal, temporary statements are finalized. This function returns nothing.

## [db:get_ptr](#db_get_ptr)

```lua
db:get_ptr()
```

Returns a lightuserdata corresponding to the open `db`. Use with [`sqlite3.open_ptr`](#sqlite3_open_ptr) to pass a database connection between threads. (When using lsqlite3 in a multithreaded environment, each thread has a separate Lua environment; full userdata structures can't be passed from one thread to another, but this is possible with lightuserdata.)

## [db:commit_hook](#db_commit_hook)

```lua
db:commit_hook(func, udata)
```

This function installs a commit_hook callback handler. `func` is a Lua function that is invoked by SQLite3 whenever a transaction is commited. This callback receives one argument: the `udata` argument used when the callback was installed. If `func` returns `false` or `nil` the COMMIT is allowed to prodeed, otherwise the COMMIT is converted to a ROLLBACK.

See: [db:rollback_hook](#db_rollback_hook) and [db:update_hook](#db_update_hook)

## [db:create_aggregate](#db_create_aggregate)

```lua
db:create_aggregate(name, nargs, step, final[, userdata])
```

This function creates an aggregate callback function. Aggregates perform an operation over all rows in a query. `name` is a string with the name of the aggregate function as given in an SQL statement; `nargs` is the number of arguments this call will provide. `step` is the actual Lua function that gets called once for every row; it should accept a function context (see [Methods for callback contexts](#methods_for_callback_contexts)) plus the same number of parameters as given in `nargs`. `final` is a function that is called once after all rows have been processed; it receives one argument, the function context. If provided, `userdata` can be any Lua value and would be returned by the `context:user_data()` method.

The function context can be used inside the two callback functions to communicate with SQLite3. Here is a simple example:

```lua
db:exec[=[
  CREATE TABLE numbers(num1, num2);
  INSERT INTO numbers VALUES(1, 11);
  INSERT INTO numbers VALUES(2, 22);
  INSERT INTO numbers VALUES(3, 33);
]=]

local num_sum = 0
local function oneRow(context, num)  -- add one column in all rows
  num_sum = num_sum + num
end

local function afterLast(context)   -- return sum after last row has been processed
  context:result_number(num_sum)
  num_sum = 0
end

db:create_aggregate("do_the_sums", 1, oneRow, afterLast)

for sum in db:urows('SELECT do_the_sums(num1) FROM numbers') do
  print("Sum of col 1:", sum)
end

for sum in db:urows('SELECT do_the_sums(num2) FROM numbers') do
  print("Sum of col 2:", sum)
end
```

This prints:

```
Sum of col 1:   6
Sum of col 2:   66
```

## [db:create_collation](#db_create_collation)

```lua
db:create_collation(name, func)
```

This creates a collation callback. A collation callback is used to establish a collation order, mostly for string comparisons and sorting purposes. `name` is a string with the name of the collation to be created; `func` is a function that accepts two string arguments, compares them and returns 0 if both strings are identical, -1 if the first argument is lower in the collation order than the second and 1 if the first argument is higher in the collation order than the second. A simple example:

```lua
local function collate(s1, s2)
  s1 = s1:lower()
  s2 = s2:lower()
  if s1 == s2 then
    return 0
  elseif s1 < s2 then
    return -1
  else
    return 1
  end
end

db:exec[=[
  CREATE TABLE test(id INTEGER PRIMARY KEY, content COLLATE CINSENS);
  INSERT INTO test VALUES(NULL, 'hello world');
  INSERT INTO test VALUES(NULL, 'Buenos dias');
  INSERT INTO test VALUES(NULL, 'HELLO WORLD');
]=]

db:create_collation('CINSENS', collate)

for row in db:nrows('SELECT * FROM test') do
  print(row.id, row.content)
end
```

## [db:create_function](#db_create_function)

```lua
db:create_function(name, nargs, func[, userdata])
```

This function creates a callback function. Callback function are called by SQLite3 once for every row in a query. `name` is a string with the name of the callback function as given in an SQL statement; `nargs` is the number of arguments this call will provide. `func` is the actual Lua function that gets called once for every row; it should accept a function context (see [Methods for callback contexts](#methods_for_callback_contexts)) plus the same number of parameters as given in nargs. If provided, `userdata` can be any Lua value and would be returned by the `context:user_data()` method. Here is an example:

```lua
db:exec'CREATE TABLE test(col1, col2, col3)'
db:exec'INSERT INTO test VALUES(1, 2, 4)'
db:exec'INSERT INTO test VALUES(2, 4, 9)'
db:exec'INSERT INTO test VALUES(3, 6, 16)'

db:create_function('sum_cols', 3, function(ctx, a, b, c)
  ctx:result_number(a + b + c)
end)

for col1, col2, col3, sum in db:urows('SELECT *, sum_cols(col1, col2, col3) FROM test') do
  util.printf('%2i+%2i+%2i=%2i\n', col1, col2, col3, sum)
end
```

## [db:load_extension](#db_load_extension)

```lua
db:load_extension([name[, entrypoint]])
```

When a `name` is provided, loads an SQLite extension library from the named file into this database connection. The optional `entrypoint` is the library initialization function name; if not supplied, SQLite tries various default entrypoint names. Returns `true` when successful, or `false` and an error string otherwise.

When called with no arguments, disables the load_extension() SQL function, which is enabled as a side effect of calling `db:load_extension` with a `name`.

## [db:errcode](#db_errcode)

```lua
db:errcode()
db:error_code()
```

Returns the numerical result code (or extended result code) for the most recent failed call associated with database db. See [Numerical error and result codes](#numerical_error_and_result_codes) for details.

## [db:errmsg](#db_errmsg)

```lua
db:errmsg()
db:error_message()
```

Returns a string that contains an error message for the most recent failed call associated with database db.

## [db:exec](#db_exec)

```lua
db:exec(sql[, func[, udata]])
db:execute(sql[, func[, udata]])
```

Compiles and executes the SQL statement(s) given in string `sql`. The statements are simply executed one after the other and not stored. The function returns `sqlite3.OK` on success or else a numerical error code (see [Numerical error and result codes](#numerical_error_and_result_codes)).

If one or more of the SQL statements are queries, then the callback function specified in `func` is invoked once for each row of the query result (if `func` is nil, no callback is invoked). The callback receives four arguments: `udata` (the third parameter of the `db:exec()` call), the number of columns in the row, a table with the column values and another table with the column names. The callback function should return 0. If the callback returns a non-zero value then the query is aborted, all subsequent SQL statements are skipped and `db:exec()` returns `sqlite3.ABORT`. Here is a simple example:

```lua
sql = [=[
  CREATE TABLE numbers(num1, num2, str);
  INSERT INTO numbers VALUES(1, 11, "ABC");
  INSERT INTO numbers VALUES(2, 22, "DEF");
  INSERT INTO numbers VALUES(3, 33, "UVW");
  INSERT INTO numbers VALUES(4, 44, "XYZ");
  SELECT * FROM numbers;
]=]

function showrow(udata, cols, values, names)
  assert(udata == 'test_udata')
  print('exec:')
  for i = 1, cols do
    print('', names[i], values[i])
  end
  return 0
end

db:exec(sql, showrow, 'test_udata')
```

## [db:interrupt](#db_interrupt)

```lua
db:interrupt()
```

This function causes any pending database operation to abort and return at the next opportunity. This function returns nothing.

## [db:db_filename](#db_db_filename)

```lua
db:db_filename(name)
```

This function returns the filename associated with database `name` of connection `db`. The `name` may be "main" for the main database file, or the name specified after the AS keyword in an ATTACH statement for an attached database. If there is no attached database `name` on the database connection `db`, then no value is returned; if database `name` is a temporary or in-memory database, then an empty string is returned.

## [db:isopen](#db_isopen)

```lua
db:isopen()
```

Returns true if database db is open, false otherwise.

## [db:last_insert_rowid](#db_last_insert_rowid)

```lua
db:last_insert_rowid()
```

This function returns the rowid of the most recent INSERT into the database. If no inserts have ever occurred, 0 is returned. (Each row in an SQLite table has a unique 64-bit signed integer key called the 'rowid'. This id is always available as an undeclared column named ROWID, OID, or _ROWID_. If the table has a column of type INTEGER PRIMARY KEY then that column is another alias for the rowid.)

If an INSERT occurs within a trigger, then the rowid of the inserted row is returned as long as the trigger is running. Once the trigger terminates, the value returned reverts to the last value inserted before the trigger fired.

## [db:nrows](#db_nrows)

```lua
db:nrows(sql)
```

Creates an iterator that returns the successive rows selected by the SQL statement given in string `sql`. Each call to the iterator returns a table in which the named fields correspond to the columns in the database. Here is an example:

```lua
db:exec[=[
  CREATE TABLE numbers(num1, num2);
  INSERT INTO numbers VALUES(1, 11);
  INSERT INTO numbers VALUES(2, 22);
  INSERT INTO numbers VALUES(3, 33);
]=]

for a in db:nrows('SELECT * FROM numbers') do
  table.print(a)
end
```

This script prints:

```
num2: 11
num1: 1
num2: 22
num1: 2
num2: 33
num1: 3
```

## [db:prepare](#db_prepare)

```lua
db:prepare(sql)
```

This function compiles the SQL statement in string `sql` into an internal representation and returns this as userdata. The returned object should be used for all further method calls in connection with this specific SQL statement (see [Methods for prepared statements](#methods_for_prepared_statements)).

## [db:progress_handler](#db_progress_handler)

```lua
db:progress_handler(n, func, udata)
```

This function installs a callback function `func` that is invoked periodically during long-running calls to [`db:exec()`](#db_exec) or [`stmt:step()`](#stmt_step). The progress callback is invoked once for every `n` internal operations, where `n` is the first argument to this function. `udata` is passed to the progress callback function each time it is invoked. If a call to `db:exec()` or `stmt:step()` results in fewer than `n` operations being executed, then the progress callback is never invoked. Only a single progress callback function may be registered for each opened database and a call to this function will overwrite any previously set callback function. To remove the progress callback altogether, pass nil as the second argument.

If the progress callback returns a result other than 0, then the current query is immediately terminated, any database changes are rolled back and the containing `db:exec()` or `stmt:step()` call returns `sqlite3.INTERRUPT`. This feature can be used to cancel long-running queries.

## [db:rollback_hook](#db_rollback_hook)

```lua
db:rollback_hook(func, udata)
```

This function installs a rollback_hook callback handler. `func` is a Lua function that is invoked by SQLite3 whenever a transaction is rolled back. This callback receives one argument: the `udata` argument used when the callback was installed.

See: [db:commit_hook](#db_commit_hook) and [db:update_hook](#db_update_hook)

## [db:rows](#db_rows)

```lua
db:rows(sql)
```

Creates an iterator that returns the successive rows selected by the SQL statement given in string `sql`. Each call to the iterator returns a table in which the numerical indices 1 to n correspond to the selected columns 1 to n in the database. Here is an example:

```lua
db:exec[=[
  CREATE TABLE numbers(num1, num2);
  INSERT INTO numbers VALUES(1, 11);
  INSERT INTO numbers VALUES(2, 22);
  INSERT INTO numbers VALUES(3, 33);
]=]

for a in db:rows('SELECT * FROM numbers') do
  table.print(a)
end
```

This script prints:

```
1: 1
2: 11
1: 2
2: 22
1: 3
2: 33
```

## [db:total_changes](#db_total_changes)

```lua
db:total_changes()
```

This function returns the number of database rows that have been modified by INSERT, UPDATE or DELETE statements since the database was opened. This includes UPDATE, INSERT and DELETE statements executed as part of trigger programs. All changes are counted as soon as the statement that produces them is completed by calling either [`stmt:reset()`](#stmt_reset) or [`stmt:finalize()`](#stmt_finalize).

## [db:trace](#db_trace)

```lua
db:trace(func, udata)
```

This function installs a trace callback handler. `func` is a Lua function that is called by SQLite3 just before the evaluation of an SQL statement. This callback receives two arguments: the first is the `udata` argument used when the callback was installed; the second is a string with the SQL statement about to be executed.

## [db:update_hook](#db_update_hook)

```lua
db:update_hook(func, udata)
```

This function installs an update_hook Data Change Notification Callback handler. `func` is a Lua function that is invoked by SQLite3 whenever a row is updated, inserted or deleted. This callback receives five arguments: the first is the `udata` argument used when the callback was installed; the second is an integer indicating the operation that caused the callback to be invoked (one of `sqlite3.UPDATE`, `sqlite3.INSERT`, or `sqlite3.DELETE`). The third and fourth arguments are the database and table name containing the affected row. The final callback parameter is the rowid of the row. In the case of an update, this is the rowid after the update takes place.

See: [db:commit_hook](#db_commit_hook) and [db:rollback_hook](#db_rollback_hook)

## [db:urows](#db_urows)

```lua
db:urows(sql)
```

Creates an iterator that returns the successive rows selected by the SQL statement given in string `sql`. Each call to the iterator returns the values that correspond to the columns in the currently selected row. Here is an example:

```lua
db:exec[=[
  CREATE TABLE numbers(num1, num2);
  INSERT INTO numbers VALUES(1, 11);
  INSERT INTO numbers VALUES(2, 22);
  INSERT INTO numbers VALUES(3, 33);
]=]

for num1, num2 in db:urows('SELECT * FROM numbers') do
  print(num1, num2)
end
```

This script prints:

```
1       11
2       22
3       33
```

----------------------------------------------------------------------

# [Methods for prepared statements](#methods_for_prepared_statements)

After creating a prepared statement with [`db:prepare()`](#db_prepare) the returned statement object should be used for all further calls in connection with that statement. Statement objects support the following methods.

## [stmt:bind](#stmt_bind)

```lua
stmt:bind(n[, value])
```

Binds value to statement parameter `n`. If the type of value is string it is bound as text. If the type of value is number, then with Lua prior to 5.3 it is bound as a double, with Lua 5.3 it is bound as an integer or double depending on its subtype using `lua_isinteger`. If `value` is a boolean then it is bound as 0 for `false` or 1 for `true`. If `value` is nil or missing, any previous binding is removed. The function returns `sqlite3.OK` on success or else a numerical error code (see [Numerical error and result codes](#numerical_error_and_result_codes)).

## [stmt:bind_blob](#stmt_bind_blob)

```lua
stmt:bind_blob(n, blob)
```

Binds string `blob` (which can be a binary string) as a blob to statement parameter `n`. The function returns `sqlite3.OK` on success or else a numerical error code (see [Numerical error and result codes](#numerical_error_and_result_codes)).

## [stmt:bind_names](#stmt_bind_names)

```lua
stmt:bind_names(nametable)
```

Binds the values in `nametable` to statement parameters. If the statement parameters are named (i.e., of the form ":AAA" or "$AAA") then this function looks for appropriately named fields in `nametable`; if the statement parameters are not named, it looks for numerical fields 1 to the number of statement parameters. The function returns `sqlite3.OK` on success or else a numerical error code (see [Numerical error and result codes](#numerical_error_and_result_codes)).

## [stmt:bind_parameter_count](#stmt_bind_parameter_count)

```lua
stmt:bind_parameter_count()
```

Returns the largest statement parameter index in prepared statement `stmt`. When the statement parameters are of the forms ":AAA" or "?", then they are assigned sequentially increasing numbers beginning with one, so the value returned is the number of parameters. However if the same statement parameter name is used multiple times, each occurrence is given the same number, so the value returned is the number of unique statement parameter names.

If statement parameters of the form "?NNN" are used (where NNN is an integer) then there might be gaps in the numbering and the value returned by this interface is the index of the statement parameter with the largest index value.

## [stmt:bind_parameter_name](#stmt_bind_parameter_name)

```lua
stmt:bind_parameter_name(n)
```

Returns the name of the `n`-th parameter in prepared statement `stmt`. Statement parameters of the form ":AAA" or "@AAA" or "$VVV" have a name which is the string ":AAA" or "@AAA" or "$VVV". In other words, the initial ":" or "$" or "@" is included as part of the name. Parameters of the form "?" or "?NNN" have no name. The first bound parameter has an index of 1. If the value `n` is out of range or if the `n`-th parameter is nameless, then nil is returned. The function returns `sqlite3.OK` on success or else a numerical error code (see [Numerical error and result codes](#numerical_error_and_result_codes))

## [stmt:bind_values](#stmt_bind_values)

```lua
stmt:bind_values(value1, value2, ..., valueN)
```

Binds the given values to statement parameters. The function returns `sqlite3.OK` on success or else a numerical error code (see [Numerical error and result codes](#numerical_error_and_result_codes)).

## [stmt:columns](#stmt_columns)

```lua
stmt:columns()
```

Returns the number of columns in the result set returned by statement stmt or 0 if the statement does not return data (for example an UPDATE).

## [stmt:finalize](#stmt_finalize)

```lua
stmt:finalize()
```

This function frees prepared statement stmt. If the statement was executed successfully, or not executed at all, then `sqlite3.OK` is returned. If execution of the statement failed then an error code is returned.

## [stmt:get_name](#stmt_get_name)

```lua
stmt:get_name(n)
```

Returns the name of column `n` in the result set of statement stmt. (The left-most column is number 0.)

## [stmt:get_named_types](#stmt_get_named_types)

```lua
stmt:get_named_types()
```

Returns a table with the names and types of all columns in the result set of statement stmt.

## [stmt:get_named_values](#stmt_get_named_values)

```lua
stmt:get_named_values()
```

This function returns a table with names and values of all columns in the current result row of a query.

## [stmt:get_names](#stmt_get_names)

```lua
stmt:get_names()
```

This function returns an array with the names of all columns in the result set returned by statement stmt.

## [stmt:get_type](#stmt_get_type)

```lua
stmt:get_type(n)
```

Returns the type of column `n` in the result set of statement stmt. (The left-most column is number 0.)

## [stmt:get_types](#stmt_get_types)

```lua
stmt:get_types()
```

This function returns an array with the types of all columns in the result set returned by statement stmt.

## [stmt:get_unames](#stmt_get_unames)

```lua
stmt:get_unames()
```

This function returns a list with the names of all columns in the result set returned by statement stmt.

## [stmt:get_utypes](#stmt_get_utypes)

```lua
stmt:get_utypes()
```

This function returns a list with the types of all columns in the result set returned by statement stmt.

## [stmt:get_uvalues](#stmt_get_uvalues)

```lua
stmt:get_uvalues()
```

This function returns a list with the values of all columns in the current result row of a query.

## [stmt:get_value](#stmt_get_value)

```lua
stmt:get_value(n)
```

Returns the value of column `n` in the result set of statement stmt. (The left-most column is number 0.)

## [stmt:get_values](#stmt_get_values)

```lua
stmt:get_values()
```

This function returns an array with the values of all columns in the result set returned by statement stmt.

## [stmt:isopen](#stmt_isopen)

```lua
stmt:isopen()
```

Returns true if stmt has not yet been finalized, false otherwise.

## [stmt:nrows](#stmt_nrows)

```lua
stmt:nrows()
```

Returns an function that iterates over the names and values of the result set of statement `stmt`. Each iteration returns a table with the names and values for the current row. This is the prepared statement equivalent of [`db:nrows()`](#db_nrows).

## [stmt:reset](#stmt_reset)

```lua
stmt:reset()
```

This function resets SQL statement `stmt`, so that it is ready to be re-executed. Any statement variables that had values bound to them using the `stmt:bind*()` functions retain their values.

## [stmt:rows](#stmt_rows)

```lua
stmt:rows()
```

Returns an function that iterates over the values of the result set of statement stmt. Each iteration returns an array with the values for the current row. This is the prepared statement equivalent of [`db:rows()`](#db_rows).

## [stmt:step](#stmt_step)

```lua
stmt:step()
```

This function must be called to evaluate the (next iteration of the) prepared statement stmt. It will return one of the following values:

- `sqlite3.BUSY`: the engine was unable to acquire the locks needed. If the statement is a COMMIT or occurs outside of an explicit transaction, then you can retry the statement. If the statement is not a COMMIT and occurs within a explicit transaction then you should rollback the transaction before continuing.

- `sqlite3.DONE`: the statement has finished executing successfully. [`stmt:step()`](#stmt_step) should not be called again on this statement without first calling [`stmt:reset()`](#stmt_reset) to reset the virtual machine back to the initial state.

- `sqlite3.ROW`: this is returned each time a new row of data is ready for processing by the caller. The values may be accessed using the column access functions. [`stmt:step()`](#stmt_step) can be called again to retrieve the next row of data.

- `sqlite3.ERROR`: a run-time error (such as a constraint violation) has occurred. [`stmt:step()`](#stmt_step) should not be called again. More information may be found by calling [`db:errmsg()`](#db_errmsg). A more specific error code (can be obtained by calling [`stmt:reset()`](#stmt_reset).

- `sqlite3.MISUSE`: the function was called inappropriately, perhaps because the statement has already been finalized or a previous call to [`stmt:step()`](#stmt_step) has returned `sqlite3.ERROR` or `sqlite3.DONE`.

## [stmt:urows](#stmt_urows)

```lua
stmt:urows()
```

Returns an function that iterates over the values of the result set of statement stmt. Each iteration returns the values for the current row. This is the prepared statement equivalent of [`db:urows()`](#db_urows).

## [stmt:last_insert_rowid](#stmt_last_insert_rowid)

```lua
stmt:last_insert_rowid()
```

This function returns the rowid of the most recent INSERT into the database corresponding to this statement. See [`db:last_insert_rowid()`](#db_last_insert_rowid).

----------------------------------------------------------------------

# [Methods for callback contexts](#methods_for_callback_contexts)

A callback context is available as a parameter inside the callback functions [`db:create_aggregate()`](#db_create_aggregate) and [`db:create_function()`](#db_create_function). It can be used to get further information about the state of a query.

## [context:aggregate_count](#context_aggregate_count)

```lua
context:aggregate_count()
```

Returns the number of calls to the aggregate step function.

## [context:get_aggregate_data](#context_get_aggregate_data)

```lua
context:get_aggregate_data()
```

Returns the user-definable data field for callback funtions.

## [context:set_aggregate_data](#context_set_aggregate_data)

```lua
context:set_aggregate_data(udata)
```

Set the user-definable data field for callback funtions to `udata`.

## [context:result](#context_result)

```lua
context:result(res)
```

This function sets the result of a callback function to res. The type of the result depends on the type of res and is either a number or a string or nil. All other values will raise an error message.

## [context:result_null](#context_result_null)

```lua
context:result_null()
```

This function sets the result of a callback function to nil. It returns nothing.

## [context:result_number](#context_result_number)

```lua
context:result_number(number)
context:result_double(number)
```

This function sets the result of a callback function to the value `number`. It returns nothing.

## [context:result_int](#context_result_int)

```lua
context:result_int(number)
```

This function sets the result of a callback function to the integer value in `number`. It returns nothing.

## [context:result_text](#context_result_text)

```lua
context:result_text(str)
```

This function sets the result of a callback function to the string in `str`. It returns nothing.

## [context:result_blob](#context_result_blob)

```lua
context:result_blob(blob)
```

This function sets the result of a callback function to the binary string in `blob`. It returns nothing.

## [context:result_error](#context_result_error)

```lua
context:result_error(err)
```

This function sets the result of a callback function to the error value in `err`. It returns nothing.

## [context:user_data](#context_user_data)

```lua
context:user_data()
```

Returns the userdata parameter given in the call to install the callback function (see [`db:create_aggregate()`](#db_create_aggregate) and [`db:create_function()`](#db_create_function) for details).

----------------------------------------------------------------------

# [Methods for Online Backup](#methods_for_online_backup)

A backup userdata is created using `backup = ` [`sqlite3.backup_init(...)`](#sqlite3_backup_init). It is then used to step the backup, or inquire about its progress.

## [backup:step](#bu_step)

```lua
backup:step(nPages)
```

Returns the status of the backup after stepping `nPages`. It is called one or more times to transfer the data between the two databases.

`backup:step(nPages)` will copy up to `nPages` pages between the source and destination databases specified by `backup` userdata. If `nPages` is negative, all remaining source pages are copied.

If `backup:step(nPages)` successfully copies `nPages` pages and there are still more pages to be copied, then the function returns `sqlite3.OK`. If `backup:step(nPages)` successfully finishes copying all pages from source to destination, then it returns `sqlite3.DONE`. If an error occurs during the step, then an error code is returned. such as `sqlite3.READONLY`, `sqlite3.NOMEM`, `sqlite3.BUSY`, `sqlite3.LOCKED`, or an `sqlite3.IOERR_XXX` extended error code.

## [backup:remaining](#bu_remaining)

```lua
backup:remaining()
```

Returns the number of pages still to be backed up at the conclusion of the most recent step.

## [backup:pagecount](#bu_pagecount)

```lua
backup:pagecount()
```

Returns the total number of pages in the source database at the conclusion of the most recent step.

## [backup:finish](#bu_finish)

```lua
backup:finish()
```

When `backup:step(nPages)` has returned `sqlite3.DONE`, or when the application wishes to abandon the backup operation, the application should destroy the backup by calling `backup:finish()`. This releases all resources associated with the backup. If `backup:step(nPages)` has not yet returned `sqlite3.DONE`, then any active write-transaction on the destination database is rolled back. After the call, the backup userdata corresponds to a completed backup, and should not be used.

The value returned by `backup:finish()` is `sqlite3.OK` if no errors occurred, regardless or whether or not the backup completed. If an out-of-memory condition or IO error occurred during any prior step on the same backup, then `backup:finish()` returns the corresponding error code.

A return of `sqlite3.BUSY` or `sqlite3.LOCKED` from `backup:step(nPages)` is not a permanent error and does not affect the return value of `backup:finish()`.

----------------------------------------------------------------------

# [Numerical error and result codes](#numerical_error_and_result_codes)

The following constants are defined by module sqlite3:

```lua
OK: 0          ERROR: 1       INTERNAL: 2    PERM: 3        ABORT: 4
BUSY: 5        LOCKED: 6      NOMEM: 7       READONLY: 8    INTERRUPT: 9
IOERR: 10      CORRUPT: 11    NOTFOUND: 12   FULL: 13       CANTOPEN: 14
PROTOCOL: 15   EMPTY: 16      SCHEMA: 17     TOOBIG: 18     CONSTRAINT: 19
MISMATCH: 20   MISUSE: 21     NOLFS: 22      FORMAT: 24     RANGE: 25
NOTADB: 26     ROW: 100       DONE: 101
```

plus the Authorizer Action Codes:

```lua
CREATE_INDEX: 1         CREATE_TABLE: 2       CREATE_TEMP_INDEX: 3  CREATE_TEMP_TABLE: 4
CREATE_TEMP_TRIGGER: 5  CREATE_TEMP_VIEW: 6   CREATE_TRIGGER: 7     CREATE_VIEW: 8
DELETE: 9               DROP_INDEX: 10        DROP_TABLE: 11        DROP_TEMP_INDEX: 12
DROP_TEMP_TABLE: 13     DROP_TEMP_TRIGGER: 14 DROP_TEMP_VIEW: 15    DROP_TRIGGER: 16
DROP_VIEW: 17           INSERT: 18            PRAGMA: 19            READ: 20
SELECT: 21              TRANSACTION: 22       UPDATE: 23            ATTACH: 24
DETACH: 25              ALTER_TABLE: 26       REINDEX: 27           ANALYZE: 28
CREATE_VTABLE: 29       DROP_VTABLE: 30       FUNCTION: 31          SAVEPOINT: 32
```

and the Open Flags:

```lua
OPEN_READONLY           OPEN_READWRITE        OPEN_CREATE           OPEN_URI
OPEN_MEMORY             OPEN_NOMUTEX          OPEN_FULLMUTEX        OPEN_SHAREDCACHE
OPEN_PRIVATECACHE
```

For details about their exact meaning please see the **SQLite3 documentation** <http://www.sqlite.org/>.

----------------------------------------------------------------------

# [VERSION](#version)

This is `lsqlite3` version "0.9.4", also tagged as `fsl_9x`.

----------------------------------------------------------------------

# [CREDITS](#credits)

`lsqlite3` was developed by Tiago Dionizio and Doug Currie with contributions from Thomas Lauer, Michael Roth, and Wolfgang Oertl.

This documentation is based on the "(very) preliminary" documents for the Idle-SQLite3 database module. Thanks to Thomas Lauer for making it available.
