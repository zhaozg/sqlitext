/************************************************************************
* lsqlite3                                                              *
* Copyright (C) 2002-2016 Tiago Dionizio, Doug Currie                   *
* All rights reserved.                                                  *
* Author    : Tiago Dionizio <tiago.dionizio@ist.utl.pt>                *
* Author    : Doug Currie <doug.currie@alum.mit.edu>                    *
* Library   : lsqlite3 - an SQLite 3 database binding for Lua 5         *
*                                                                       *
* Permission is hereby granted, free of charge, to any person obtaining *
* a copy of this software and associated documentation files (the       *
* "Software"), to deal in the Software without restriction, including   *
* without limitation the rights to use, copy, modify, merge, publish,   *
* distribute, sublicense, and/or sell copies of the Software, and to    *
* permit persons to whom the Software is furnished to do so, subject to *
* the following conditions:                                             *
*                                                                       *
* The above copyright notice and this permission notice shall be        *
* included in all copies or substantial portions of the Software.       *
*                                                                       *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  *
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  *
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     *
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                *
************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define LUA_LIB
#include "lua.h"
#include "lauxlib.h"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#if LUA_VERSION_NUM < 502
/*
** Lua 5.1 (or LuaJIT)
*/

#ifndef LUA_OK
#define LUA_OK 0
#endif

#ifndef luaL_len
#define luaL_len lua_objlen
#endif

#endif

#if LUA_VERSION_NUM > 501
/*
** Lua 5.2
*/
#ifndef lua_strlen
#define lua_strlen lua_rawlen
#endif
/* luaL_typerror always used with arg at ndx == NULL */
#define luaL_typerror(L,ndx,str) luaL_error(L,"bad argument %d (%s expected, got nil)",ndx,str)
/* luaL_register used once, so below expansion is OK for this case */
#define luaL_register(L,name,reg) lua_newtable(L);luaL_setfuncs(L,reg,0)
/* luaL_openlib always used with name == NULL */
#define luaL_openlib(L,name,reg,nup) luaL_setfuncs(L,reg,nup)

#if LUA_VERSION_NUM > 502
/*
** Lua 5.3
*/
#define luaL_checkint(L,n)  ((int)luaL_checkinteger(L, (n)))
#endif
#endif

#include "sqlite3.h"

/* compile time features */
#if !defined(SQLITE_OMIT_PROGRESS_CALLBACK)
    #define SQLITE_OMIT_PROGRESS_CALLBACK 0
#endif
#if !defined(LSQLITE_OMIT_UPDATE_HOOK)
    #define LSQLITE_OMIT_UPDATE_HOOK 0
#endif
#if defined(LSQLITE_OMIT_OPEN_V2)
    #define SQLITE3_OPEN(L,filename,flags) sqlite3_open(L,filename)
#else
    #define SQLITE3_OPEN(L,filename,flags) sqlite3_open_v2(L,filename,flags,NULL)
#endif

typedef struct sdb sdb;
typedef struct sdb_vm sdb_vm;
typedef struct sdb_bu sdb_bu;
typedef struct sdb_func sdb_func;

/* to use as C user data so i know what function sqlite is calling */
struct sdb_func {
    /* references to associated lua values */
    int fn_step;
    int fn_finalize;
    int udata;

    sdb *db;
    char aggregate;

    sdb_func *next;
};

/* information about database */
struct sdb {
    /* associated lua state */
    lua_State *L;
    /* registry ref that pins the lua_State owning db->L, so that sqlite->Lua
       callbacks (busy handler, progress, update/commit/rollback hooks, ...)
       never run against a collected coroutine. LuaJIT coroutines are plain
       lua_State objects: if the db handle outlives the coroutine that opened
       it (e.g. it was handed out and the coroutine was then collected), db->L
       would dangle and the next callback would crash inside lua_rawgeti().
       Holding this ref keeps the opening thread alive until the handle is
       closed/collected. */
    int state_ref;
    /* sqlite database handle */
    sqlite3 *db;

    /* sql functions stack usage */
    sdb_func *func;         /* top SQL function being called */

    /* references */
    int busy_cb;        /* busy callback */
    int busy_udata;

    int progress_cb;    /* progress handler */
    int progress_udata;

    int trace_cb;       /* trace callback */
    int trace_udata;

#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK

    int wal_hook_cb;    /* wal_hook callback */
    int wal_hook_udata;

    int update_hook_cb; /* update_hook callback */
    int update_hook_udata;

    int commit_hook_cb; /* commit_hook callback */
    int commit_hook_udata;

    int rollback_hook_cb; /* rollback_hook callback */
    int rollback_hook_udata;

#endif
};

static const char *sqlite_meta      = ":sqlite3";
static const char *sqlite_vm_meta   = ":sqlite3:vm";
static const char *sqlite_bu_meta   = ":sqlite3:bu";
static const char *sqlite_ctx_meta  = ":sqlite3:ctx";
static int sqlite_ctx_meta_ref;
#ifdef SQLITE_ENABLE_SESSION
static const char *const sqlite_ses_meta  = ":sqlite3:ses";
static const char *const sqlite_reb_meta  = ":sqlite3:reb";
static const char *const sqlite_itr_meta  = ":sqlite3:itr";
static int sqlite_ses_meta_ref;
static int sqlite_reb_meta_ref;
static int sqlite_itr_meta_ref;
#endif
/* global config configuration */
static int log_cb = LUA_NOREF; /* log callback */
static int log_udata;

/* Lua 5.3 introduced an integer type, but depending on the implementation, it could be 32
** or 64 bits (or something else?). This helper macro tries to do "the right thing."
*/

#if LUA_VERSION_NUM > 502
#define PUSH_INT64(L,i64in,fallback) \
    do { \
        sqlite_int64 i64 = i64in; \
        lua_Integer i = (lua_Integer )i64; \
        if (i == i64) lua_pushinteger(L, i);\
        else { \
            lua_Number n = (lua_Number)i64; \
            if (n == i64) lua_pushnumber(L, n); \
            else fallback; \
        } \
    } while (0)
#else
#define PUSH_INT64(L,i64in,fallback) \
    do { \
        sqlite_int64 i64 = i64in; \
        lua_Number n = (lua_Number)i64; \
        if (n == i64) lua_pushnumber(L, n); \
        else fallback; \
    } while (0)
#endif

/*
** =======================================================
** Database Virtual Machine Operations
** =======================================================
*/

static void vm_push_column(lua_State *L, sqlite3_stmt *vm, int idx) {
    switch (sqlite3_column_type(vm, idx)) {
        case SQLITE_INTEGER:
            PUSH_INT64(L, sqlite3_column_int64(vm, idx)
                     , lua_pushlstring(L, (const char*)sqlite3_column_text(vm, idx)
                                        , sqlite3_column_bytes(vm, idx)));
            break;
        case SQLITE_FLOAT:
            lua_pushnumber(L, sqlite3_column_double(vm, idx));
            break;
        case SQLITE_TEXT:
            lua_pushlstring(L, (const char*)sqlite3_column_text(vm, idx), sqlite3_column_bytes(vm, idx));
            break;
        case SQLITE_BLOB:
            lua_pushlstring(L, sqlite3_column_blob(vm, idx), sqlite3_column_bytes(vm, idx));
            break;
        case SQLITE_NULL:
            lua_pushnil(L);
            break;
        default:
            lua_pushnil(L);
            break;
    }
}

/* virtual machine information */
struct sdb_vm {
    sdb *db;                /* associated database handle */
    sqlite3_stmt *vm;       /* virtual machine */

    /* sqlite3_step info */
    int columns;            /* number of columns in result */
    char has_values;        /* true when step succeeds */

    char temp;              /* temporary vm used in db:rows */
};

/* called with db,sql text on the lua stack */
static sdb_vm *newvm(lua_State *L, sdb *db) {
    sdb_vm *svm = (sdb_vm*)lua_newuserdata(L, sizeof(sdb_vm)); /* db sql svm_ud -- */

    luaL_getmetatable(L, sqlite_vm_meta);
    lua_setmetatable(L, -2);        /* set metatable */

    svm->db = db;
    svm->columns = 0;
    svm->has_values = 0;
    svm->vm = NULL;
    svm->temp = 0;

    /* add an entry on the database table: svm -> db to keep db live while svm is live */
    lua_pushlightuserdata(L, db);     /* db sql svm_ud db_lud -- */
    lua_rawget(L, LUA_REGISTRYINDEX); /* db sql svm_ud reg[db_lud] -- */
    lua_pushvalue(L, -2);             /* db sql svm_ud reg[db_lud] svm_ud -- */
    lua_pushvalue(L, -5);             /* db sql svm_ud reg[db_lud] svm_ud db -- */
    lua_rawset(L, -3);                /* (reg[db_lud])[svm_ud] = db ; set the db for this vm */
    lua_pop(L, 1);                    /* db sql svm_ud -- */

    return svm;
}

static int cleanupvm(lua_State *L, sdb_vm *svm) {
    svm->columns = 0;
    svm->has_values = 0;

    if (!svm->vm) return 0;
    lua_pushinteger(L, sqlite3_finalize(svm->vm));
    svm->vm = NULL;
    return 1;
}

static int stepvm(lua_State *L, sdb_vm *svm) {
	(void)L;
    return sqlite3_step(svm->vm);
}

static sdb_vm *lsqlite_getvm(lua_State *L, int index) {
    sdb_vm *svm = (sdb_vm*)luaL_checkudata(L, index, sqlite_vm_meta);
    if (svm == NULL) luaL_argerror(L, index, "bad sqlite virtual machine");
    return svm;
}

static sdb_vm *lsqlite_checkvm(lua_State *L, int index) {
    sdb_vm *svm = lsqlite_getvm(L, index);
    if (svm->vm == NULL) luaL_argerror(L, index, "attempt to use closed sqlite virtual machine");
    return svm;
}

static int dbvm_isopen(lua_State *L) {
    sdb_vm *svm = lsqlite_getvm(L, 1);
    lua_pushboolean(L, svm->vm != NULL ? 1 : 0);
    return 1;
}

static int dbvm_tostring(lua_State *L) {
    char buff[40];
    sdb_vm *svm = lsqlite_getvm(L, 1);
    if (svm->vm == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", svm);
    lua_pushfstring(L, "sqlite virtual machine (%s)", buff);
    return 1;
}

static int dbvm_gc(lua_State *L) {
    cleanupvm(L, lsqlite_getvm(L, 1));
    return 0;
}

static int dbvm_step(lua_State *L) {
    int result;
    sdb_vm *svm = lsqlite_checkvm(L, 1);

    result = stepvm(L, svm);
    svm->has_values = result == SQLITE_ROW ? 1 : 0;
    svm->columns = sqlite3_data_count(svm->vm);

    lua_pushinteger(L, result);
    return 1;
}

static int dbvm_finalize(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    return cleanupvm(L, svm);
}

static int dbvm_reset(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_reset(svm->vm);
    lua_pushinteger(L, sqlite3_errcode(svm->db->db));
    return 1;
}

static void dbvm_check_contents(lua_State *L, sdb_vm *svm) {
    if (!svm->has_values) {
        luaL_error(L, "misuse of function");
    }
}

static void dbvm_check_index(lua_State *L, sdb_vm *svm, int index) {
    if (index < 0 || index >= svm->columns) {
        luaL_error(L, "index out of range [0..%d]", svm->columns - 1);
    }
}

static void dbvm_check_bind_index(lua_State *L, sdb_vm *svm, int index) {
    if (index < 1 || index > sqlite3_bind_parameter_count(svm->vm)) {
        luaL_error(L, "bind index out of range [1..%d]", sqlite3_bind_parameter_count(svm->vm));
    }
}

static int dbvm_last_insert_rowid(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    /* conversion warning: int64 -> luaNumber */
    sqlite_int64 rowid = sqlite3_last_insert_rowid(svm->db->db);
    PUSH_INT64(L, rowid, lua_pushfstring(L, "%ll", rowid));
    return 1;
}

/*
** =======================================================
** Virtual Machine - generic info
** =======================================================
*/
static int dbvm_columns(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    lua_pushinteger(L, sqlite3_column_count(svm->vm));
    return 1;
}

/*
** =======================================================
** Virtual Machine - getters
** =======================================================
*/

static int dbvm_get_value(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checkint(L, 2);
    dbvm_check_contents(L, svm);
    dbvm_check_index(L, svm, index);
    vm_push_column(L, svm->vm, index);
    return 1;
}

static int dbvm_get_name(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checknumber(L, 2);
    dbvm_check_index(L, svm, index);
    lua_pushstring(L, sqlite3_column_name(svm->vm, index));
    return 1;
}

static int dbvm_get_type(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checknumber(L, 2);
    dbvm_check_index(L, svm, index);
    lua_pushstring(L, sqlite3_column_decltype(svm->vm, index));
    return 1;
}

static int dbvm_get_values(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = svm->columns;
    int n;
    dbvm_check_contents(L, svm);

    lua_createtable(L, columns, 0);
    for (n = 0; n < columns;) {
        vm_push_column(L, vm, n++);
        lua_rawseti(L, -2, n);
    }
    return 1;
}

static int dbvm_get_names(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_createtable(L, columns, 0);
    for (n = 0; n < columns;) {
        lua_pushstring(L, sqlite3_column_name(vm, n++));
        lua_rawseti(L, -2, n);
    }
    return 1;
}

static int dbvm_get_types(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_createtable(L, columns, 0);
    for (n = 0; n < columns;) {
        lua_pushstring(L, sqlite3_column_decltype(vm, n++));
        lua_rawseti(L, -2, n);
    }
    return 1;
}

static int dbvm_get_uvalues(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = svm->columns;
    int n;
    dbvm_check_contents(L, svm);

    lua_checkstack(L, columns);
    for (n = 0; n < columns; ++n)
        vm_push_column(L, vm, n);
    return columns;
}

static int dbvm_get_unames(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_checkstack(L, columns);
    for (n = 0; n < columns; ++n)
        lua_pushstring(L, sqlite3_column_name(vm, n));
    return columns;
}

static int dbvm_get_utypes(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_checkstack(L, columns);
    for (n = 0; n < columns; ++n)
        lua_pushstring(L, sqlite3_column_decltype(vm, n));
    return columns;
}

static int dbvm_get_named_values(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = svm->columns;
    int n;
    dbvm_check_contents(L, svm);

    lua_createtable(L, 0, columns);
    for (n = 0; n < columns; ++n) {
        lua_pushstring(L, sqlite3_column_name(vm, n));
        vm_push_column(L, vm, n);
        lua_rawset(L, -3);
    }
    return 1;
}

static int dbvm_get_named_types(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm);
    int n;

    lua_createtable(L, 0, columns);
    for (n = 0; n < columns; ++n) {
        lua_pushstring(L, sqlite3_column_name(vm, n));
        lua_pushstring(L, sqlite3_column_decltype(vm, n));
        lua_rawset(L, -3);
    }
    return 1;
}

/*
** =======================================================
** Virtual Machine - Bind
** =======================================================
*/

static int dbvm_bind_index(lua_State *L, sqlite3_stmt *vm, int index, int lindex) {
    switch (lua_type(L, lindex)) {
        case LUA_TSTRING:
            return sqlite3_bind_text(vm, index, lua_tostring(L, lindex), lua_strlen(L, lindex), SQLITE_TRANSIENT);
        case LUA_TNUMBER:
#if LUA_VERSION_NUM > 502
            if (lua_isinteger(L, lindex))
                return sqlite3_bind_int64(vm, index, lua_tointeger(L, lindex));
#endif
            return sqlite3_bind_double(vm, index, lua_tonumber(L, lindex));
        case LUA_TBOOLEAN:
            return sqlite3_bind_int(vm, index, lua_toboolean(L, lindex) ? 1 : 0);
        case LUA_TNONE:
        case LUA_TNIL:
            return sqlite3_bind_null(vm, index);
        default:
            luaL_error(L, "index (%d) - invalid data type for bind (%s)", index, lua_typename(L, lua_type(L, lindex)));
            return SQLITE_MISUSE; /*!*/
    }
}


static int dbvm_bind_parameter_count(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    lua_pushinteger(L, sqlite3_bind_parameter_count(svm->vm));
    return 1;
}

static int dbvm_bind_parameter_name(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checknumber(L, 2);
    dbvm_check_bind_index(L, svm, index);
    lua_pushstring(L, sqlite3_bind_parameter_name(svm->vm, index));
    return 1;
}

static int dbvm_bind(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int index = luaL_checkint(L, 2);
    int result;

    dbvm_check_bind_index(L, svm, index);
    result = dbvm_bind_index(L, vm, index, 3);

    lua_pushinteger(L, result);
    return 1;
}

static int dbvm_bind_blob(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checkint(L, 2);
    const char *value = luaL_checkstring(L, 3);
    int len = lua_strlen(L, 3);

    lua_pushinteger(L, sqlite3_bind_blob(svm->vm, index, value, len, SQLITE_TRANSIENT));
    return 1;
}

static int dbvm_bind_values(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int top = lua_gettop(L);
    int result, n;

    if (top - 1 != sqlite3_bind_parameter_count(vm))
        luaL_error(L,
            "incorrect number of parameters to bind (%d given, %d to bind)",
            top - 1,
            sqlite3_bind_parameter_count(vm)
        );

    for (n = 2; n <= top; ++n) {
        if ((result = dbvm_bind_index(L, vm, n - 1, n)) != SQLITE_OK) {
            lua_pushinteger(L, result);
            return 1;
        }
    }

    lua_pushinteger(L, SQLITE_OK);
    return 1;
}

static int dbvm_bind_table_fields (lua_State *L, int idx, int n, sqlite3_stmt *vm) {
    const char *name;
    int result, i;

    for ( i = 1; i <= n; ++i ) {
        name = sqlite3_bind_parameter_name(vm, i );
        if (name && (name[0] == ':' || name[0] == '$')) {
            lua_pushstring(L, ++name);
            lua_gettable(L, idx);
            result = dbvm_bind_index(L, vm, i, -1);
            lua_pop(L, 1);
        }
        else {
            lua_pushinteger(L, i );
            lua_gettable(L, idx);
            result = dbvm_bind_index(L, vm, i, -1);
            lua_pop(L, 1);
        }

        if (result != SQLITE_OK) {
            return result;
        }
    }
    return SQLITE_OK;
}

static int dbvm_bind_names(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int count = sqlite3_bind_parameter_count(vm);
    int result;
    luaL_checktype(L, 2, LUA_TTABLE);

    result = dbvm_bind_table_fields (L, 2, count, vm);
    lua_pushinteger(L, result);
    return 1;
}

/*
** =======================================================
** Database (internal management)
** =======================================================
*/

/*
** When creating database handles, always creates a `closed' database handle
** before opening the actual database; so, if there is a memory error, the
** database is not left opened.
**
** Creates a new 'table' and leaves it in the stack
*/
static sdb *newdb (lua_State *L) {
    sdb *db = (sdb*)lua_newuserdata(L, sizeof(sdb));
    db->L = L;
    db->db = NULL;  /* database handle is currently `closed' */
    db->func = NULL;

    db->state_ref =
    db->busy_cb =
    db->busy_udata =
    db->wal_hook_cb =
    db->wal_hook_udata =
    db->progress_cb =
    db->progress_udata =
    db->trace_cb =
    db->trace_udata =
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    db->update_hook_cb =
    db->update_hook_udata =
    db->commit_hook_cb =
    db->commit_hook_udata =
    db->rollback_hook_cb =
    db->rollback_hook_udata =
#endif
        LUA_NOREF;

    /* Keep the lua_State that created this handle alive for as long as the
       handle lives.  If the db is opened inside a LuaJIT coroutine and that
       coroutine is later garbage-collected while the connection is still in
       use, db->L would point at a freed thread and the very first sqlite ->
       Lua callback (busy handler, ...) would crash.  Pinning the thread here
       (and releasing it in cleanupdb) closes that hole. */
    lua_pushthread(L);
    db->state_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    luaL_getmetatable(L, sqlite_meta);

    lua_setmetatable(L, -2);        /* set metatable */

    /* to keep track of 'open' virtual machines; make keys week */
    lua_pushlightuserdata(L, db);
    lua_newtable(L);                    // t
    lua_newtable(L);                    // t mt
    lua_pushstring(L, "k");             // t mt v
    lua_setfield(L, -2, "__mode");      // t mt
    lua_setmetatable(L, -2);            // t
    lua_rawset(L, LUA_REGISTRYINDEX);

    return db;
}

/* cleanup all vms or just temporary ones */
static void closevms(lua_State *L, sdb *db, int temp) {
    /* free associated virtual machines */
    lua_pushlightuserdata(L, db);
    lua_rawget(L, LUA_REGISTRYINDEX);

    /* close all used handles */
    lua_pushnil(L);
    while (lua_next(L, -2)) {
        sdb_vm *svm = lua_touserdata(L, -2); /* key: vm; val: sql text */
        if ((!temp || svm->temp)) lua_pop(L, cleanupvm(L, svm));
        lua_pop(L, 1); /* pop value; leave key in the stack */
    }
}

static int cleanupdb(lua_State *L, sdb *db) {
    sdb_func *func;
    sdb_func *func_next;
    int top = lua_gettop(L);
    int result;

    if (!db->db) return SQLITE_MISUSE;

    closevms(L, db, 0);

    /* remove entry in lua registry table */
    lua_pushlightuserdata(L, db);
    lua_pushnil(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    /* 'free' all references; release the pinned owner thread last so no
       callback can fire on a half-dismantled state while we unref. */
    luaL_unref(L, LUA_REGISTRYINDEX, db->state_ref);
    db->state_ref = LUA_NOREF;
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->wal_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->wal_hook_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->progress_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->progress_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->trace_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->trace_udata);
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_udata);
#endif

    /* close database; _v2 is intended for use with garbage collected languages
       and where the order in which destructors are called is arbitrary. */
    result = sqlite3_close_v2(db->db);
    db->db = NULL;

    /* free associated memory with created functions */
    func = db->func;
    while (func) {
        func_next = func->next;
        luaL_unref(L, LUA_REGISTRYINDEX, func->fn_step);
        luaL_unref(L, LUA_REGISTRYINDEX, func->fn_finalize);
        luaL_unref(L, LUA_REGISTRYINDEX, func->udata);
        free(func);
        func = func_next;
    }
    db->func = NULL;

    lua_settop(L, top);
    return result;
}

static sdb *lsqlite_getdb(lua_State *L, int index) {
    sdb *db = (sdb*)luaL_checkudata(L, index, sqlite_meta);
    if (db == NULL) luaL_typerror(L, index, "sqlite database");
    return db;
}

static sdb *lsqlite_checkdb(lua_State *L, int index) {
    sdb *db = lsqlite_getdb(L, index);
    if (db->db == NULL) luaL_argerror(L, index, "attempt to use closed sqlite database");
    return db;
}


/*
** =======================================================
** User Defined Functions - Context Methods
** =======================================================
*/
typedef struct {
    sqlite3_context *ctx;
    int ud;
} lcontext;

static lcontext *lsqlite_make_context(lua_State *L) {
    lcontext *ctx = (lcontext*)lua_newuserdata(L, sizeof(lcontext));
    lua_rawgeti(L, LUA_REGISTRYINDEX, sqlite_ctx_meta_ref);
    lua_setmetatable(L, -2);
    ctx->ctx = NULL;
    ctx->ud = LUA_NOREF;
    return ctx;
}

static lcontext *lsqlite_getcontext(lua_State *L, int index) {
    lcontext *ctx = (lcontext*)luaL_checkudata(L, index, sqlite_ctx_meta);
    if (ctx == NULL) luaL_typerror(L, index, "sqlite context");
    return ctx;
}

static lcontext *lsqlite_checkcontext(lua_State *L, int index) {
    lcontext *ctx = lsqlite_getcontext(L, index);
    if (ctx->ctx == NULL) luaL_argerror(L, index, "invalid sqlite context");
    return ctx;
}

static int lcontext_tostring(lua_State *L) {
    char buff[41];
    lcontext *ctx = lsqlite_getcontext(L, 1);
    if (ctx->ctx == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", ctx->ctx);
    lua_pushfstring(L, "sqlite function context (%s)", buff);
    return 1;
}

static void lcontext_check_aggregate(lua_State *L, lcontext *ctx) {
    sdb_func *func = (sdb_func*)sqlite3_user_data(ctx->ctx);
    if (!func->aggregate) {
        luaL_error(L, "attempt to call aggregate method from scalar function");
    }
}

static int lcontext_user_data(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    sdb_func *func = (sdb_func*)sqlite3_user_data(ctx->ctx);
    lua_rawgeti(L, LUA_REGISTRYINDEX, func->udata);
    return 1;
}

static int lcontext_get_aggregate_context(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    lcontext_check_aggregate(L, ctx);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->ud);
    return 1;
}

static int lcontext_set_aggregate_context(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    lcontext_check_aggregate(L, ctx);
    lua_settop(L, 2);
    luaL_unref(L, LUA_REGISTRYINDEX, ctx->ud);
    ctx->ud = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}

static int lcontext_aggregate_count(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    lcontext_check_aggregate(L, ctx);
    lua_pushinteger(L, sqlite3_aggregate_count(ctx->ctx));
    return 1;
}

#if 0
void *sqlite3_get_auxdata(sqlite3_context*, int);
void sqlite3_set_auxdata(sqlite3_context*, int, void*, void (*)(void*));
#endif

static int lcontext_result(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    switch (lua_type(L, 2)) {
        case LUA_TNUMBER:
#if LUA_VERSION_NUM > 502
            if (lua_isinteger(L, 2))
                sqlite3_result_int64(ctx->ctx, luaL_checkinteger(L, 2));
            else
#endif
            sqlite3_result_double(ctx->ctx, luaL_checknumber(L, 2));
            break;
        case LUA_TSTRING:
            sqlite3_result_text(ctx->ctx, luaL_checkstring(L, 2), lua_strlen(L, 2), SQLITE_TRANSIENT);
            break;
        case LUA_TNIL:
        case LUA_TNONE:
            sqlite3_result_null(ctx->ctx);
            break;
        default:
            luaL_error(L, "invalid result type %s", lua_typename(L, 2));
            break;
    }

    return 0;
}

static int lcontext_result_blob(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    const char *blob = luaL_checkstring(L, 2);
    int size = lua_strlen(L, 2);
    sqlite3_result_blob(ctx->ctx, (const void*)blob, size, SQLITE_TRANSIENT);
    return 0;
}

static int lcontext_result_double(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    double d = luaL_checknumber(L, 2);
    sqlite3_result_double(ctx->ctx, d);
    return 0;
}

static int lcontext_result_error(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    const char *err = luaL_checkstring(L, 2);
    int size = lua_strlen(L, 2);
    sqlite3_result_error(ctx->ctx, err, size);
    return 0;
}

static int lcontext_result_int(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    int i = luaL_checkint(L, 2);
    sqlite3_result_int(ctx->ctx, i);
    return 0;
}

static int lcontext_result_null(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    sqlite3_result_null(ctx->ctx);
    return 0;
}

static int lcontext_result_text(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    const char *text = luaL_checkstring(L, 2);
    int size = lua_strlen(L, 2);
    sqlite3_result_text(ctx->ctx, text, size, SQLITE_TRANSIENT);
    return 0;
}

/*
** =======================================================
** Database Methods
** =======================================================
*/

static int db_isopen(lua_State *L) {
    sdb *db = lsqlite_getdb(L, 1);
    lua_pushboolean(L, db->db != NULL ? 1 : 0);
    return 1;
}

static int db_last_insert_rowid(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    /* conversion warning: int64 -> luaNumber */
    sqlite_int64 rowid = sqlite3_last_insert_rowid(db->db);
    PUSH_INT64(L, rowid, lua_pushfstring(L, "%ll", rowid));
    return 1;
}

static int db_changes(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushinteger(L, sqlite3_changes(db->db));
    return 1;
}

static int db_total_changes(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushinteger(L, sqlite3_total_changes(db->db));
    return 1;
}

static int db_errcode(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushinteger(L, sqlite3_errcode(db->db));
    return 1;
}

static int db_errmsg(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushstring(L, sqlite3_errmsg(db->db));
    return 1;
}

static int db_interrupt(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    sqlite3_interrupt(db->db);
    return 0;
}

static int db_db_filename(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *db_name = luaL_checkstring(L, 2);
    /* sqlite3_db_filename may return NULL, in that case Lua pushes nil... */
    lua_pushstring(L, sqlite3_db_filename(db->db, db_name));
    return 1;
}

static int pusherr(lua_State *L, int rc) {
    lua_pushnil(L);
    lua_pushinteger(L, rc);
    return 2;
}

static int pusherrstr(lua_State *L, char *str) {
    lua_pushnil(L);
    lua_pushstring(L, str);
    return 2;
}

static int db_wal_checkpoint(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    int eMode = luaL_optinteger(L, 2, SQLITE_CHECKPOINT_PASSIVE);
    const char *db_name = luaL_optstring(L, 3, NULL);
    int nLog, nCkpt;
    if (sqlite3_wal_checkpoint_v2(db->db, db_name, eMode, &nLog, &nCkpt) != SQLITE_OK) {
        return pusherr(L, sqlite3_errcode(db->db));
    }
    lua_pushinteger(L, nLog);
    lua_pushinteger(L, nCkpt);
    return 2;
}

/*
** Registering SQL functions:
*/

static void db_push_value(lua_State *L, sqlite3_value *value) {
    switch (sqlite3_value_type(value)) {
        case SQLITE_TEXT:
            lua_pushlstring(L, (const char*)sqlite3_value_text(value), sqlite3_value_bytes(value));
            break;

        case SQLITE_INTEGER:
            PUSH_INT64(L, sqlite3_value_int64(value)
                        , lua_pushlstring(L, (const char*)sqlite3_value_text(value)
                                            , sqlite3_value_bytes(value)));
            break;

        case SQLITE_FLOAT:
            lua_pushnumber(L, sqlite3_value_double(value));
            break;

        case SQLITE_BLOB:
            lua_pushlstring(L, sqlite3_value_blob(value), sqlite3_value_bytes(value));
            break;

        case SQLITE_NULL:
            lua_pushnil(L);
            break;

        default:
            /* things done properly (SQLite + Lua SQLite)
            ** this should never happen */
            lua_pushnil(L);
            break;
    }
}

/*
** callback functions used when calling registered sql functions
*/

/* scalar function to be called
** callback params: context, values... */
static void db_sql_normal_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    sdb_func *func = (sdb_func*)sqlite3_user_data(context);
    lua_State *L = func->db->L;
    int n;
    lcontext *ctx;

    int top = lua_gettop(L);

    /* ensure there is enough space in the stack */
    lua_checkstack(L, argc + 3);

    lua_rawgeti(L, LUA_REGISTRYINDEX, func->fn_step);   /* function to call */

    if (!func->aggregate) {
        ctx = lsqlite_make_context(L); /* push context - used to set results */
    }
    else {
        /* reuse context userdata value */
        void *p = sqlite3_aggregate_context(context, 1);
        /* i think it is OK to use assume that using a light user data
        ** as an entry on LUA REGISTRY table will be unique */
        lua_pushlightuserdata(L, p);
        lua_rawget(L, LUA_REGISTRYINDEX);       /* context table */

        if (lua_isnil(L, -1)) { /* not yet created? */
            lua_pop(L, 1);
            ctx = lsqlite_make_context(L);
            lua_pushlightuserdata(L, p);
            lua_pushvalue(L, -2);
            lua_rawset(L, LUA_REGISTRYINDEX);
        }
        else
            ctx = lsqlite_getcontext(L, -1);
    }

    /* push params */
    for (n = 0; n < argc; ++n) {
        db_push_value(L, argv[n]);
    }

    /* set context */
    ctx->ctx = context;

    if (lua_pcall(L, argc + 1, 0, 0)) {
        const char *errmsg = lua_tostring(L, -1);
        int size = lua_strlen(L, -1);
        sqlite3_result_error(context, errmsg, size);
    }

    /* invalidate context */
    ctx->ctx = NULL;

    if (!func->aggregate) {
        luaL_unref(L, LUA_REGISTRYINDEX, ctx->ud);
    }

    lua_settop(L, top);
}

static void db_sql_finalize_function(sqlite3_context *context) {
    sdb_func *func = (sdb_func*)sqlite3_user_data(context);
    lua_State *L = func->db->L;
    void *p = sqlite3_aggregate_context(context, 1); /* minimal mem usage */
    lcontext *ctx;
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, func->fn_finalize);   /* function to call */

    /* i think it is OK to use assume that using a light user data
    ** as an entry on LUA REGISTRY table will be unique */
    lua_pushlightuserdata(L, p);
    lua_rawget(L, LUA_REGISTRYINDEX);       /* context table */

    if (lua_isnil(L, -1)) { /* not yet created? - shouldn't happen in finalize function */
        lua_pop(L, 1);
        ctx = lsqlite_make_context(L);
        lua_pushlightuserdata(L, p);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }
    else
        ctx = lsqlite_getcontext(L, -1);

    /* set context */
    ctx->ctx = context;

    if (lua_pcall(L, 1, 0, 0)) {
        sqlite3_result_error(context, lua_tostring(L, -1), -1);
    }

    /* invalidate context */
    ctx->ctx = NULL;

    /* cleanup context */
    luaL_unref(L, LUA_REGISTRYINDEX, ctx->ud);
    /* remove it from registry */
    lua_pushlightuserdata(L, p);
    lua_pushnil(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    lua_settop(L, top);
}

/*
** Register a normal function
** Params: db, function name, number arguments, [ callback | step, finalize], user data
** Returns: true on sucess
**
** Normal function:
** Params: context, params
**
** Aggregate function:
** Params of step: context, params
** Params of finalize: context
*/
static int db_register_function(lua_State *L, int aggregate) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *name;
    int args;
    int result;
    sdb_func *func;

    /* safety measure */
    if (aggregate) aggregate = 1;

    name = luaL_checkstring(L, 2);
    args = luaL_checkint(L, 3);
    luaL_checktype(L, 4, LUA_TFUNCTION);
    if (aggregate) luaL_checktype(L, 5, LUA_TFUNCTION);

    /* maybe an alternative way to allocate memory should be used/avoided */
    func = (sdb_func*)malloc(sizeof(sdb_func));
    if (func == NULL) {
        luaL_error(L, "out of memory");
    }

    result = sqlite3_create_function(
        db->db, name, args, SQLITE_UTF8, func,
        aggregate ? NULL : db_sql_normal_function,
        aggregate ? db_sql_normal_function : NULL,
        aggregate ? db_sql_finalize_function : NULL
    );

    if (result == SQLITE_OK) {
        /* safety measures for userdata field to be present in the stack */
        lua_settop(L, 5 + aggregate);

        /* save registered function in db function list */
        func->db = db;
        func->aggregate = aggregate;
        func->next = db->func;
        db->func = func;

        /* save the setp/normal function callback */
        lua_pushvalue(L, 4);
        func->fn_step = luaL_ref(L, LUA_REGISTRYINDEX);
        /* save user data */
        lua_pushvalue(L, 5+aggregate);
        func->udata = luaL_ref(L, LUA_REGISTRYINDEX);

        if (aggregate) {
            lua_pushvalue(L, 5);
            func->fn_finalize = luaL_ref(L, LUA_REGISTRYINDEX);
        }
        else
            func->fn_finalize = LUA_NOREF;
    }
    else {
        /* free allocated memory */
        free(func);
    }

    lua_pushboolean(L, result == SQLITE_OK ? 1 : 0);
    return 1;
}

static int db_create_function(lua_State *L) {
    return db_register_function(L, 0);
}

static int db_create_aggregate(lua_State *L) {
    return db_register_function(L, 1);
}

/* create_collation; contributed by Thomas Lauer
*/

typedef struct {
    lua_State *L;
    int ref;
} scc;

static int collwrapper(scc *co,int l1,const void *p1,
                        int l2,const void *p2) {
    int res=0;
    lua_State *L=co->L;
    lua_rawgeti(L,LUA_REGISTRYINDEX,co->ref);
    lua_pushlstring(L,p1,l1);
    lua_pushlstring(L,p2,l2);
    if (lua_pcall(L,2,1,0)==0) res=(int)lua_tonumber(L,-1);
    lua_pop(L,1);
    return res;
}

static void collfree(scc *co) {
    if (co) {
        luaL_unref(co->L,LUA_REGISTRYINDEX,co->ref);
        free(co);
    }
}

static int db_create_collation(lua_State *L) {
    sdb *db=lsqlite_checkdb(L,1);
    const char *collname=luaL_checkstring(L,2);
    scc *co=NULL;
    int (*collfunc)(scc *,int,const void *,int,const void *)=NULL;
    lua_settop(L,3); /* default args to nil, and exclude extras */
    if (lua_isfunction(L,3)) collfunc=collwrapper;
    else if (!lua_isnil(L,3))
        luaL_error(L,"create_collation: function or nil expected");
    if (collfunc != NULL) {
        co=(scc *)malloc(sizeof(scc)); /* userdata is a no-no as it
                                          will be garbage-collected */
        if (co) {
            co->L=L;
            /* lua_settop(L,3) above means we don't need: lua_pushvalue(L,3); */
            co->ref=luaL_ref(L,LUA_REGISTRYINDEX);
        }
        else luaL_error(L,"create_collation: could not allocate callback");
    }
    sqlite3_create_collation_v2(db->db, collname, SQLITE_UTF8,
        (void *)co,
        (int(*)(void*,int,const void*,int,const void*))collfunc,
        (void(*)(void*))collfree);
    return 0;
}

/* Thanks to Wolfgang Oertl...
*/
static int db_load_extension(lua_State *L) {
    sdb *db=lsqlite_checkdb(L,1);
    const char *extname=luaL_optstring(L,2,NULL);
    const char *entrypoint=luaL_optstring(L,3,NULL);
    int result;
    char *errmsg = NULL;

    if (extname == NULL) {
        result = sqlite3_enable_load_extension(db->db,0); /* disable extension loading */
    }
    else {
        sqlite3_enable_load_extension(db->db,1); /* enable extension loading */
        result = sqlite3_load_extension(db->db,extname,entrypoint,&errmsg);
    }

    if (result == SQLITE_OK) {
        lua_pushboolean(L,1);
        return 1;
    }

    lua_pushboolean(L,0); /* so, assert(load_extension(...)) works */
    lua_pushstring(L,errmsg);
    sqlite3_free(errmsg);
    return 2;
}

/*
** wal_hook callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata, db handle, database name, number of wal file pages
*/
static int db_wal_hook_callback(void *user, sqlite3 *dbh, char const *dbname, int pnum) {
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->wal_hook_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->wal_hook_udata); /* get callback user data */
    lua_pushstring(L, dbname); /* hook database name */
    lua_pushinteger(L, pnum);

    if (lua_pcall(L, 3, 0, 0) != LUA_OK) return lua_error(L);

    lua_settop(L, top);
    return SQLITE_OK;
}

static int db_wal_hook(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    luaL_unref(L, LUA_REGISTRYINDEX, db->wal_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->wal_hook_udata);
    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        db->wal_hook_cb =
        db->wal_hook_udata = LUA_NOREF;

        /* clear hook handler */
        sqlite3_wal_hook(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        db->wal_hook_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->wal_hook_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set hook handler */
        sqlite3_wal_hook(db->db, db_wal_hook_callback, db);
    }

    return 0;
}

/*
** trace callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata, sql
*/
static void db_trace_callback(void *user, const char *sql) {
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->trace_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->trace_udata); /* get callback user data */
    lua_pushstring(L, sql); /* traced sql statement */

    /* call lua function */
    lua_pcall(L, 2, 0, 0);
    /* ignore any error generated by this function */

    lua_settop(L, top);
}

static int db_trace(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->trace_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->trace_udata);

        db->trace_cb =
        db->trace_udata = LUA_NOREF;

        /* clear trace handler */
        sqlite3_trace(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        luaL_unref(L, LUA_REGISTRYINDEX, db->trace_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->trace_udata);

        db->trace_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->trace_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set trace handler */
        sqlite3_trace(db->db, db_trace_callback, db);
    }

    return 0;
}

#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK

#ifndef LUA_MAINTHREAD
#define LUA_MAINTHREAD 1
#endif

static lua_State* db_mainthread(lua_State *L) {
  lua_State *ML = L;
  lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_MAINTHREAD);
  ML = lua_tothread(L, -1);
  lua_pop(L, 1);
  return ML ? ML : L;
}

/*
** update_hook callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata, {one of SQLITE_INSERT, SQLITE_DELETE, or SQLITE_UPDATE},
**          database name, table name (containing the affected row), rowid of the row
*/
static void db_update_hook_callback(void *user, int op, char const *dbname, char const *tblname, sqlite3_int64 rowid) {
    sdb *db = (sdb*)user;
    lua_State *L = db_mainthread(db->L);
    int top = lua_gettop(L);

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->update_hook_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->update_hook_udata); /* get callback user data */
    lua_pushinteger(L, op);
    lua_pushstring(L, dbname); /* update_hook database name */
    lua_pushstring(L, tblname); /* update_hook database name */

    PUSH_INT64(L, rowid, lua_pushfstring(L, "%ll", rowid));

    /* call lua function */
    lua_pcall(L, 5, 0, 0);
    /* ignore any error generated by this function */

    lua_settop(L, top);
}

static int db_update_hook(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_udata);
    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {

        db->update_hook_cb =
        db->update_hook_udata = LUA_NOREF;

        /* clear update_hook handler */
        sqlite3_update_hook(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        db->update_hook_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->update_hook_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set update_hook handler */
        sqlite3_update_hook(db->db, db_update_hook_callback, db);
    }

    return 0;
}

/*
** commit_hook callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata
** Returned value: Return false or nil to continue the COMMIT operation normally.
**  return true (non false, non nil), then the COMMIT is converted into a ROLLBACK.
*/
static int db_commit_hook_callback(void *user) {
    sdb *db = (sdb*)user;
    lua_State *L = db_mainthread(db->L);
    int top = lua_gettop(L);
    int rollback = 0;

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->commit_hook_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->commit_hook_udata); /* get callback user data */

    /* call lua function */
    if (!lua_pcall(L, 1, 1, 0))
        rollback = lua_toboolean(L, -1); /* use result if there was no error */

    lua_settop(L, top);
    return rollback;
}

static int db_commit_hook(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_udata);
    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {

        db->commit_hook_cb =
        db->commit_hook_udata = LUA_NOREF;

        /* clear commit_hook handler */
        sqlite3_commit_hook(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        db->commit_hook_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->commit_hook_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set commit_hook handler */
        sqlite3_commit_hook(db->db, db_commit_hook_callback, db);
    }

    return 0;
}

/*
** rollback hook callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata
*/
static void db_rollback_hook_callback(void *user) {
    sdb *db = (sdb*)user;
    lua_State *L = db_mainthread(db->L);
    int top = lua_gettop(L);

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->rollback_hook_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->rollback_hook_udata); /* get callback user data */

    /* call lua function */
    lua_pcall(L, 1, 0, 0);
    /* ignore any error generated by this function */

    lua_settop(L, top);
}

static int db_rollback_hook(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_udata);
    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {

        db->rollback_hook_cb =
        db->rollback_hook_udata = LUA_NOREF;

        /* clear rollback_hook handler */
        sqlite3_rollback_hook(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        db->rollback_hook_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->rollback_hook_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set rollback_hook handler */
        sqlite3_rollback_hook(db->db, db_rollback_hook_callback, db);
    }

    return 0;
}

#endif /* #if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK */

#if !defined(SQLITE_OMIT_PROGRESS_CALLBACK) || !SQLITE_OMIT_PROGRESS_CALLBACK

/*
** progress handler:
** Params: database, number of opcodes, callback function, userdata
**
** callback function:
** Params: userdata
** returns: 0 to return immediatly and return SQLITE_ABORT, non-zero to continue
*/
static int db_progress_callback(void *user) {
    int result = 1; /* abort by default */
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, db->progress_cb);
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->progress_udata);

    /* call lua function */
    if (!lua_pcall(L, 1, 1, 0))
        result = lua_toboolean(L, -1);

    lua_settop(L, top);
    return result;
}

static int db_progress_handler(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->progress_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->progress_udata);

        db->progress_cb =
        db->progress_udata = LUA_NOREF;

        /* clear busy handler */
        sqlite3_progress_handler(db->db, 0, NULL, NULL);
    }
    else {
        int nop = luaL_checkint(L, 2);  /* number of opcodes */
        luaL_checktype(L, 3, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 4);

        luaL_unref(L, LUA_REGISTRYINDEX, db->progress_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->progress_udata);

        db->progress_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->progress_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set progress callback */
        sqlite3_progress_handler(db->db, nop, db_progress_callback, db);
    }

    return 0;
}

#else /* #if !defined(SQLITE_OMIT_PROGRESS_CALLBACK) || !SQLITE_OMIT_PROGRESS_CALLBACK */

static int db_progress_handler(lua_State *L) {
    lua_pushliteral(L, "progress callback support disabled at compile time");
    lua_error(L);
    return 0;
}

#endif /* #if !defined(SQLITE_OMIT_PROGRESS_CALLBACK) || !SQLITE_OMIT_PROGRESS_CALLBACK */

/* Online Backup API */
#if 0
sqlite3_backup *sqlite3_backup_init(
  sqlite3 *pDest,                        /* Destination database handle */
  const char *zDestName,                 /* Destination database name */
  sqlite3 *pSource,                      /* Source database handle */
  const char *zSourceName                /* Source database name */
);
int sqlite3_backup_step(sqlite3_backup *p, int nPage);
int sqlite3_backup_finish(sqlite3_backup *p);
int sqlite3_backup_remaining(sqlite3_backup *p);
int sqlite3_backup_pagecount(sqlite3_backup *p);
#endif

struct sdb_bu {
    sqlite3_backup *bu;     /* backup structure */
};

static int cleanupbu(lua_State *L, sdb_bu *sbu) {

    if (!sbu->bu) return 0; /* already finished */

    /* remove table from registry */
    lua_pushlightuserdata(L, sbu->bu);
    lua_pushnil(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    lua_pushinteger(L, sqlite3_backup_finish(sbu->bu));
    sbu->bu = NULL;

    return 1;
}

static int lsqlite_backup_init(lua_State *L) {

    sdb *target_db = lsqlite_checkdb(L, 1);
    const char *target_nm = luaL_checkstring(L, 2);
    sdb *source_db = lsqlite_checkdb(L, 3);
    const char *source_nm = luaL_checkstring(L, 4);

    sqlite3_backup *bu = sqlite3_backup_init(target_db->db, target_nm, source_db->db, source_nm);

    if (NULL != bu) {
        sdb_bu *sbu = (sdb_bu*)lua_newuserdata(L, sizeof(sdb_bu));

        luaL_getmetatable(L, sqlite_bu_meta);
        lua_setmetatable(L, -2);        /* set metatable */
        sbu->bu = bu;

        /* create table from registry */
        /* to prevent referenced databases from being garbage collected while bu is live */
        lua_pushlightuserdata(L, bu);
        lua_createtable(L, 2, 0);
        /* add source and target dbs to table at indices 1 and 2 */
        lua_pushvalue(L, 1); /* target db */
        lua_rawseti(L, -2, 1);
        lua_pushvalue(L, 3); /* source db */
        lua_rawseti(L, -2, 2);
        /* put table in registry with key lightuserdata bu */
        lua_rawset(L, LUA_REGISTRYINDEX);

        return 1;
    }
    else {
        return 0;
    }
}

static sdb_bu *lsqlite_getbu(lua_State *L, int index) {
    sdb_bu *sbu = (sdb_bu*)luaL_checkudata(L, index, sqlite_bu_meta);
    if (sbu == NULL) luaL_typerror(L, index, "sqlite database backup");
    return sbu;
}

static sdb_bu *lsqlite_checkbu(lua_State *L, int index) {
    sdb_bu *sbu = lsqlite_getbu(L, index);
    if (sbu->bu == NULL) luaL_argerror(L, index, "attempt to use closed sqlite database backup");
    return sbu;
}

static int dbbu_gc(lua_State *L) {
    sdb_bu *sbu = lsqlite_getbu(L, 1);
    if (sbu->bu != NULL) {
        cleanupbu(L, sbu);
        lua_pop(L, 1);
    }
    /* else ignore if already finished */
    return 0;
}

static int dbbu_step(lua_State *L) {
    sdb_bu *sbu = lsqlite_checkbu(L, 1);
    int nPage = luaL_checkint(L, 2);
    lua_pushinteger(L, sqlite3_backup_step(sbu->bu, nPage));
    return 1;
}

static int dbbu_remaining(lua_State *L) {
    sdb_bu *sbu = lsqlite_checkbu(L, 1);
    lua_pushinteger(L, sqlite3_backup_remaining(sbu->bu));
    return 1;
}

static int dbbu_pagecount(lua_State *L) {
    sdb_bu *sbu = lsqlite_checkbu(L, 1);
    lua_pushinteger(L, sqlite3_backup_pagecount(sbu->bu));
    return 1;
}

static int dbbu_finish(lua_State *L) {
    sdb_bu *sbu = lsqlite_checkbu(L, 1);
    return cleanupbu(L, sbu);
}

/* end of Online Backup API */

/*
** busy handler:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata, number of tries
** returns: 0 to return immediatly and return SQLITE_BUSY, non-zero to try again
*/
static int db_busy_callback(void *user, int tries) {
    int retry = 0; /* abort by default */
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, db->busy_cb);
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->busy_udata);
    lua_pushinteger(L, tries);

    /* call lua function */
    if (!lua_pcall(L, 2, 1, 0))
        retry = lua_toboolean(L, -1);

    lua_settop(L, top);
    return retry;
}

static int db_busy_handler(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);
    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {

        db->busy_cb =
        db->busy_udata = LUA_NOREF;

        /* clear busy handler */
        sqlite3_busy_handler(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);
        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        db->busy_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->busy_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set busy handler */
        sqlite3_busy_handler(db->db, db_busy_callback, db);
    }

    return 0;
}

static int db_busy_timeout(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    int timeout = luaL_checkint(L, 2);
    sqlite3_busy_timeout(db->db, timeout);

    /* if there was a timeout callback registered, it is now
    ** invalid/useless. free any references we may have */
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);
    db->busy_cb =
    db->busy_udata = LUA_NOREF;

    return 0;
}

/*
** Params: db, sql, callback, user
** returns: code [, errmsg]
**
** Callback:
** Params: user, number of columns, values, names
** Returns: 0 to continue, other value will cause abort
*/
static int db_exec_callback(void* user, int columns, char **data, char **names) {
    int result = SQLITE_ABORT; /* abort by default */
    lua_State *L = (lua_State*)user;
    int n;

    int top = lua_gettop(L);

    lua_pushvalue(L, 3); /* function to call */
    lua_pushvalue(L, 4); /* user data */
    lua_pushinteger(L, columns); /* total number of rows in result */

    /* column values */
    lua_pushvalue(L, 6);
    for (n = 0; n < columns;) {
        lua_pushstring(L, data[n++]);
        lua_rawseti(L, -2, n);
    }

    /* columns names */
    lua_pushvalue(L, 5);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_createtable(L, columns, 0);
        lua_pushvalue(L, -1);
        lua_replace(L, 5);
        for (n = 0; n < columns;) {
            lua_pushstring(L, names[n++]);
            lua_rawseti(L, -2, n);
        }
    }

    /* call lua function */
    if (!lua_pcall(L, 4, 1, 0)) {

#if LUA_VERSION_NUM > 502
        if (lua_isinteger(L, -1))
            result = lua_tointeger(L, -1);
        else
#endif
        if (lua_isnumber(L, -1))
            result = lua_tonumber(L, -1);
    }

    lua_settop(L, top);
    return result;
}

static int db_exec(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    int result;

    if (!lua_isnoneornil(L, 3)) {
        /* stack:
        **  3: callback function
        **  4: userdata
        **  5: column names
        **  6: reusable column values
        */
        luaL_checktype(L, 3, LUA_TFUNCTION);
        lua_settop(L, 4);   /* 'trap' userdata - nil extra parameters */
        lua_pushnil(L);     /* column names not known at this point */
        lua_newtable(L);    /* column values table */

        result = sqlite3_exec(db->db, sql, db_exec_callback, L, NULL);
    }
    else {
        /* no callbacks */
        result = sqlite3_exec(db->db, sql, NULL, NULL, NULL);
    }

    lua_pushinteger(L, result);
    return 1;
}

/*
** Params: db, sql
** returns: code, compiled length or error message
*/
static int db_prepare(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    int sql_len = lua_strlen(L, 2);
    const char *sqltail;
    sdb_vm *svm;
    lua_settop(L,2); /* db,sql is on top of stack for call to newvm */
    svm = newvm(L, db);

    if (sqlite3_prepare_v2(db->db, sql, sql_len, &svm->vm, &sqltail) != SQLITE_OK) {
        lua_pushnil(L);
        lua_pushinteger(L, sqlite3_errcode(db->db));
        if (cleanupvm(L, svm) == 1)
            lua_pop(L, 1); /* this should not happen since sqlite3_prepare_v2 will not set ->vm on error */
        return 2;
    }

    /* vm already in the stack */
    lua_pushstring(L, sqltail);
    return 2;
}

static int db_do_next_row(lua_State *L, int packed) {
    int result;
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm;
    int columns;
    int i;

    result = stepvm(L, svm);
    vm = svm->vm; /* stepvm may change svm->vm if re-prepare is needed */
    svm->has_values = result == SQLITE_ROW ? 1 : 0;
    svm->columns = columns = sqlite3_data_count(vm);

    if (result == SQLITE_ROW) {
        if (packed) {
            if (packed == 1) {
                lua_createtable(L, columns, 0);
                for (i = 0; i < columns;) {
                    vm_push_column(L, vm, i);
                    lua_rawseti(L, -2, ++i);
                }
            }
            else {
                lua_createtable(L, 0, columns);
                for (i = 0; i < columns; ++i) {
                    lua_pushstring(L, sqlite3_column_name(vm, i));
                    vm_push_column(L, vm, i);
                    lua_rawset(L, -3);
                }
            }
            return 1;
        }
        else {
            lua_checkstack(L, columns);
            for (i = 0; i < columns; ++i)
                vm_push_column(L, vm, i);
            return svm->columns;
        }
    }

    if (svm->temp) {
        /* finalize and check for errors */
        result = sqlite3_finalize(vm);
        svm->vm = NULL;
        cleanupvm(L, svm);
    }
    else if (result == SQLITE_DONE) {
        result = sqlite3_reset(vm);
    }

    if (result != SQLITE_OK) {
        lua_pushstring(L, sqlite3_errmsg(svm->db->db));
        lua_error(L);
    }
    return 0;
}

static int db_next_row(lua_State *L) {
    return db_do_next_row(L, 0);
}

static int db_next_packed_row(lua_State *L) {
    return db_do_next_row(L, 1);
}

static int db_next_named_row(lua_State *L) {
    return db_do_next_row(L, 2);
}

static int dbvm_do_rows(lua_State *L, int(*f)(lua_State *)) {
    /* sdb_vm *svm =  */
    lsqlite_checkvm(L, 1);
    lua_pushvalue(L,1);
    lua_pushcfunction(L, f);
    lua_insert(L, -2);
    return 2;
}

static int dbvm_rows(lua_State *L) {
    return dbvm_do_rows(L, db_next_packed_row);
}

static int dbvm_nrows(lua_State *L) {
    return dbvm_do_rows(L, db_next_named_row);
}

static int dbvm_urows(lua_State *L) {
    return dbvm_do_rows(L, db_next_row);
}

static int db_do_rows(lua_State *L, int(*f)(lua_State *)) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    sdb_vm *svm;

    int nargs = lua_gettop(L) - 2;
    if (nargs > 0) {
        lua_pushvalue(L, 1);
        lua_pushvalue(L, 2);    /* copy db,sql on top of the stack for newvm */
    }

    svm = newvm(L, db);
    svm->temp = 1;

    if (sqlite3_prepare_v2(db->db, sql, -1, &svm->vm, NULL) != SQLITE_OK) {
        lua_pushstring(L, sqlite3_errmsg(svm->db->db));
        if (cleanupvm(L, svm) == 1)
            lua_pop(L, 1); /* this should not happen since sqlite3_prepare_v2 will not set ->vm on error */
        lua_error(L);
    }

    if (nargs > 0) {
        lua_replace(L, 1);
        lua_remove(L, 2);  /* stack: vm, args.. */

        if (nargs == 1 && lua_istable(L, 2)) {
            int result;
            if ((result = dbvm_bind_table_fields (L, 2, nargs, svm->vm)) != SQLITE_OK) {
                lua_pushstring(L, sqlite3_errstr(result));
                cleanupvm(L, svm);
                lua_error(L);
            }
        } else if (nargs == sqlite3_bind_parameter_count(svm->vm)) {
            int result, i;
            for (i = 1; i <= nargs; i++) {
                if ((result = dbvm_bind_index(L, svm->vm, i, i + 1)) != SQLITE_OK) {
                    lua_pushstring(L, sqlite3_errstr(result));
                    cleanupvm(L, svm);
                    lua_error(L);
                }
            }
        } else {
            luaL_error(L, "Required either %d parameters or a single table, got %d.",
                sqlite3_bind_parameter_count(svm->vm), nargs);
        }
        lua_pop(L, nargs);
        lua_pushvalue(L, 1);
    }

    lua_pushcfunction(L, f);
    lua_insert(L, -2);
    return 2;
}

static int db_rows(lua_State *L) {
    return db_do_rows(L, db_next_packed_row);
}

static int db_nrows(lua_State *L) {
    return db_do_rows(L, db_next_named_row);
}

/* unpacked version of db:rows */
static int db_urows(lua_State *L) {
    return db_do_rows(L, db_next_row);
}

static int db_tostring(lua_State *L) {
    char buff[33];
    sdb *db = lsqlite_getdb(L, 1);
    if (db->db == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", lua_touserdata(L, 1));
    lua_pushfstring(L, "sqlite database (%s)", buff);
    return 1;
}

static int db_close(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushinteger(L, cleanupdb(L, db));
    return 1;
}

static int db_close_vm(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    closevms(L, db, lua_toboolean(L, 2));
    return 0;
}

/* From: Wolfgang Oertl
When using lsqlite3 in a multithreaded environment, each thread has a separate Lua
environment, but full userdata structures can't be passed from one thread to another.
This is possible with lightuserdata, however. See: lsqlite_open_ptr().
*/
static int db_get_ptr(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushlightuserdata(L, db->db);
    return 1;
}

static int db_gc(lua_State *L) {
    sdb *db = lsqlite_getdb(L, 1);
    if (db->db != NULL)  /* ignore closed databases */
        cleanupdb(L, db);
    return 0;
}

#ifdef SQLITE_ENABLE_DESERIALIZE

static int db_serialize(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    sqlite_int64 size = 0;

    char *buffer = (char *)sqlite3_serialize(db->db, "main", &size, 0);
    if (buffer == NULL)
        return pusherrstr(L, "failed to serialize");

    lua_pushlstring(L, buffer, size);
    free(buffer);
    return 1;
}

static int db_deserialize(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    size_t size = 0;

    const char *buffer = luaL_checklstring(L, 2, &size);
    if (buffer == NULL || size == 0)
        return pusherrstr(L, "failed to deserialize");

    unsigned char *sqlbuf = memcpy(sqlite3_malloc(size), buffer, size);
    sqlite3_deserialize(db->db, "main", sqlbuf, size, size,
        SQLITE_DESERIALIZE_FREEONCLOSE + SQLITE_DESERIALIZE_RESIZEABLE);
    lua_pushinteger(L, SQLITE_OK);
    return 1;
}

#endif

#ifdef SQLITE_ENABLE_SESSION

/*
** =======================================================
** Iterator functions (for session support)
** =======================================================
*/

typedef struct {
    sqlite3_changeset_iter *itr;
    bool collectable;
} liter;

static liter *lsqlite_makeiter(lua_State *L, sqlite3_changeset_iter *piter, bool collectable) {
    liter *litr = (liter*)lua_newuserdata(L, sizeof(liter));
    lua_rawgeti(L, LUA_REGISTRYINDEX, sqlite_itr_meta_ref);
    lua_setmetatable(L, -2);
    litr->itr = piter;
    litr->collectable = collectable;
    return litr;
}

static liter *lsqlite_getiter(lua_State *L, int index) {
    return (liter *)luaL_checkudata(L, index, sqlite_itr_meta);
}

static liter *lsqlite_checkiter(lua_State *L, int index) {
    liter *litr = lsqlite_getiter(L, index);
    if (litr->itr == NULL) luaL_argerror(L, index, "invalid sqlite iterator");
    return litr;
}

static int liter_finalize(lua_State *L) {
    liter *litr = lsqlite_getiter(L, 1);
    int rc;
    if (litr->itr) {
        if (!litr->collectable) {
            return pusherr(L, SQLITE_CORRUPT);
        }
        /* NOTE: sqlite3changeset_finalize() always releases the iterator and
        ** merely reports the error code accumulated during iteration, so the
        ** handle must be cleared even on failure - otherwise __gc would call
        ** sqlite3changeset_finalize() again on freed memory (double free). */
        rc = sqlite3changeset_finalize(litr->itr);
        litr->itr = NULL;
        if (rc != SQLITE_OK) {
            return pusherr(L, rc);
        }
    }
    lua_pushboolean(L, 1);
    return 1;
}

static int liter_gc(lua_State *L) {
    return liter_finalize(L);
}

static int liter_tostring(lua_State *L) {
    char buff[33];
    liter *litr = lsqlite_getiter(L, 1);
    if (litr->itr == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", litr->itr);
    lua_pushfstring(L, "sqlite iterator (%s)", buff);
    return 1;
}

static int liter_table(
        lua_State *L,
        int (*iter_func)(sqlite3_changeset_iter *pIter, int val, sqlite3_value **ppValue)
) {
    const char *zTab;
    int n, rc, nCol, Op, bIndirect;
    sqlite3_value *pVal;
    liter *litr = lsqlite_checkiter(L, 1);
    sqlite3changeset_op(litr->itr, &zTab, &nCol, &Op, &bIndirect);
    lua_createtable(L, nCol, 0);
    for (n = 0; n < nCol; n++) {
        if ((rc = (*iter_func)(litr->itr, n, &pVal)) != LUA_OK) {
            return pusherr(L, rc);
        }
        if (pVal) {
            db_push_value(L, pVal);
        } else {
            // push `false` to indicate that the value wasn't changed
            // and not included in the record and to keep table valid
            lua_pushboolean(L, 0);
        }
        lua_rawseti(L, -2, n+1);
    }
    return 1;
}

static int liter_new(lua_State *L) {
    return liter_table(L, sqlite3changeset_new);
}

static int liter_old(lua_State *L) {
    return liter_table(L, sqlite3changeset_old);
}

static int liter_conflict(lua_State *L) {
    return liter_table(L, sqlite3changeset_conflict);
}

static int liter_op(lua_State *L) {
    const char *zTab;
    int rc, nCol, Op, bIndirect;
    liter *litr = lsqlite_checkiter(L, 1);

    if ((rc = sqlite3changeset_op(litr->itr, &zTab, &nCol, &Op, &bIndirect)) != LUA_OK) {
        return pusherr(L, rc);
    }
    lua_pushstring(L, zTab);
    lua_pushinteger(L, Op);
    lua_pushboolean(L, bIndirect);
    return 3;
}

static int liter_fk_conflicts(lua_State *L) {
    int rc, nOut;
    liter *litr = lsqlite_checkiter(L, 1);
    if ((rc = sqlite3changeset_fk_conflicts(litr->itr, &nOut)) != LUA_OK) {
        return pusherr(L, rc);
    }
    lua_pushinteger(L, nOut);
    return 1;
}

static int liter_next(lua_State *L) {
    liter *litr = lsqlite_checkiter(L, 1);
    if (!litr->collectable) {
        return pusherr(L, SQLITE_CORRUPT);
    }
    lua_pushinteger(L, sqlite3changeset_next(litr->itr));
    return 1;
}

static int liter_pk(lua_State *L) {
    const char *zTab;
    int n, rc, nCol;
    unsigned char *abPK;
    liter *litr = lsqlite_checkiter(L, 1);
    if ((rc = sqlite3changeset_pk(litr->itr, &abPK, &nCol)) != LUA_OK) {
        return pusherr(L, rc);
    }
    lua_createtable(L, nCol, 0);
    for (n = 0; n < nCol; n++) {
        lua_pushboolean(L, abPK[n]);
        lua_rawseti(L, -2, n+1);
    }
    return 1;
}

/*
** =======================================================
** Rebaser functions (for session support)
** =======================================================
*/

typedef struct {
    sqlite3_rebaser *reb;
} lrebaser;

static lrebaser *lsqlite_makerebaser(lua_State *L, sqlite3_rebaser *reb) {
    lrebaser *lreb = (lrebaser*)lua_newuserdata(L, sizeof(lrebaser));
    lua_rawgeti(L, LUA_REGISTRYINDEX, sqlite_reb_meta_ref);
    lua_setmetatable(L, -2);
    lreb->reb = reb;
    return lreb;
}

static lrebaser *lsqlite_getrebaser(lua_State *L, int index) {
    return (lrebaser *)luaL_checkudata(L, index, sqlite_reb_meta);
}

static lrebaser *lsqlite_checkrebaser(lua_State *L, int index) {
    lrebaser *lreb = lsqlite_getrebaser(L, index);
    if (lreb->reb == NULL) luaL_argerror(L, index, "invalid sqlite rebaser");
    return lreb;
}

static int lrebaser_delete(lua_State *L) {
    lrebaser *lreb = lsqlite_getrebaser(L, 1);
    if (lreb->reb != NULL) {
      sqlite3rebaser_delete(lreb->reb);
      lreb->reb = NULL;
    }
    return 0;
}

static int lrebaser_gc(lua_State *L) {
    return lrebaser_delete(L);
}

static int lrebaser_tostring(lua_State *L) {
    char buff[32];
    lrebaser *lreb = lsqlite_getrebaser(L, 1);
    if (lreb->reb == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", lreb->reb);
    lua_pushfstring(L, "sqlite rebaser (%s)", buff);
    return 1;
}

static int lrebaser_rebase(lua_State *L) {
    lrebaser *lreb = lsqlite_checkrebaser(L, 1);
    const char *cset = luaL_checkstring(L, 2);
    int nset = lua_strlen(L, 2);
    int rc;
    int size;
    void *buf;

    if ((rc = sqlite3rebaser_rebase(lreb->reb, nset, cset, &size, &buf)) != SQLITE_OK) {
        return pusherr(L, rc);
    }
    lua_pushlstring(L, buf, size);
    sqlite3_free(buf);
    return 1;
}

static int db_create_rebaser(lua_State *L) {
    sqlite3_rebaser *reb;
    int rc;

    if ((rc = sqlite3rebaser_create(&reb)) != SQLITE_OK) {
        return pusherr(L, rc);
    }
    (void)lsqlite_makerebaser(L, reb);
    return 1;
}

static int lrebaser_configure(lua_State *L) {
    lrebaser *lreb = lsqlite_checkrebaser(L, 1);
    const char *rebase = luaL_checkstring(L, 2);
    int nRebase = lua_strlen(L, 2);
    int rc;

    /* Load a rebase log previously returned by db:apply_changeset() on this
    ** or (typically) another node, so that this rebaser can rebase local
    ** changesets that overlap with changes the peer has already applied. */
    if ((rc = sqlite3rebaser_configure(lreb->reb, nRebase, (const void*)rebase)) != SQLITE_OK) {
        return pusherr(L, rc);
    }
    lua_pushboolean(L, 1);
    return 1;
}

/* session/changeset callbacks */

/* Session object.  The Lua table-filter callback for ses:attach(fn) is
** owned by the session itself - NOT by module globals.  It is handed to
** SQLite as the pCtx of sqlite3session_table_filter(), so sessions created
** on different threads / different Lua states never share (and therefore
** never clobber) each other's filter callbacks. */
typedef struct lsession {
    sqlite3_session *ses; /* SQLite session handle */
    sdb *db;              /* database this session is attached to */
    int filter_cb;        /* registry ref of attach(fn); LUA_NOREF when none */
    int filter_udata;     /* registry ref of filter udata; LUA_REFNIL when none */
} lsession;

/* Per-call context for db_apply_changeset().  Handed to the
** sqlite3changeset_apply_v2() xFilter / xConflict callbacks through pCtx so
** that concurrent applies from different threads / Lua states never share
** (and therefore never clobber) each other's Lua callback references. */
typedef struct lsqlite_changeset_apply {
    lua_State *L;    /* Lua state the callbacks were registered on */
    int filter_cb;   /* registry ref; LUA_NOREF when absent */
    int conflict_cb; /* registry ref; LUA_NOREF when absent */
    int udata;       /* registry ref; LUA_REFNIL when absent */
    int failed;      /* set once a Lua callback fails */
    int err_ref;     /* registry ref of the first error object */
} lsqlite_changeset_apply;

/* Remember a Lua error raised from inside a session callback without
** unwinding (longjmp) through the SQLite session frames: while it runs,
** sqlite3changeset_apply_v2() holds the connection mutex, is inside a
** SAVEPOINT and owns the file write-lock, so jumping out here would leave
** the database "half applied" and locked forever.  Instead the error object
** is parked in the per-call ctx and re-raised by db_apply_changeset() once
** apply_v2() has cleanly returned (and released its locks). */
static void lsqlite_changeset_capture_error(
        lsqlite_changeset_apply *ctx, lua_State *L
) {
    if (!ctx->failed) {
        ctx->err_ref = luaL_ref(L, LUA_REGISTRYINDEX); /* pops error object */
        ctx->failed = 1;
    }
    else {
        lua_pop(L, 1); /* drop the extra copy, keep the first error */
    }
}

static int db_changeset_conflict_callback(
        void *pCtx,               /* lsqlite_changeset_apply* */
        int eConflict,            /* DATA, MISSING, CONFLICT, CONSTRAINT */
        sqlite3_changeset_iter *p /* Handle describing change and conflict */
) {
    lsqlite_changeset_apply *ctx = (lsqlite_changeset_apply*)pCtx;
    lua_State *L = ctx->L;
    int top, result, isint, rc;
    const char *zTab;
    int nCol, Op, bIndirect;

    /* default behaviour: OMIT the conflicting change */
    if (ctx->conflict_cb == LUA_NOREF) return SQLITE_CHANGESET_OMIT;
    /* an earlier callback already failed: abort the whole apply cleanly */
    if (ctx->failed) return SQLITE_CHANGESET_ABORT;

    top = lua_gettop(L);

    rc = sqlite3changeset_op(p, &zTab, &nCol, &Op, &bIndirect);
    if (rc != LUA_OK) {
        lua_pushliteral(L, "invalid return from changeset iterator");
        lsqlite_changeset_capture_error(ctx, L);
        lua_settop(L, top);
        return SQLITE_CHANGESET_ABORT;
    }

    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->conflict_cb); /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->udata);       /* get user data */
    lua_pushinteger(L, eConflict);
    (void)lsqlite_makeiter(L, p, 0);
    lua_pushstring(L, zTab);
    lua_pushinteger(L, Op);
    lua_pushboolean(L, bIndirect);

    if (lua_pcall(L, 6, 1, 0) != LUA_OK) {
        lsqlite_changeset_capture_error(ctx, L);
        lua_settop(L, top);
        return SQLITE_CHANGESET_ABORT;
    }

    result = lua_tointegerx(L, -1, &isint); /* use result if there was no error */
    if (!isint) {
        lua_pushliteral(L, "non-integer returned from conflict callback");
        lsqlite_changeset_capture_error(ctx, L);
        lua_settop(L, top);
        return SQLITE_CHANGESET_ABORT;
    }

    lua_settop(L, top);
    return result;
}

static int db_changeset_filter_callback(
        void *pCtx,      /* lsqlite_changeset_apply* */
        const char *zTab /* Table name */
) {
    lsqlite_changeset_apply *ctx = (lsqlite_changeset_apply*)pCtx;
    lua_State *L = ctx->L;
    int top, result, isint;

    /* allow the table if no filter callback is provided */
    if (ctx->filter_cb == LUA_NOREF || ctx->filter_cb == LUA_REFNIL) return 1;
    /* an earlier callback failed: skip the rest; error is re-raised later */
    if (ctx->failed) return 0;

    top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->filter_cb); /* get callback */
    lua_pushstring(L, zTab);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->udata);     /* get user data */

    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        lsqlite_changeset_capture_error(ctx, L);
        lua_settop(L, top);
        return 0;
    }

    /* allow 0/1 and false/true to be returned
    ** returning 0/false skips the table */
    result = lua_tointegerx(L, -1, &isint); /* use result if there was no error */
    if (!isint && !lua_isboolean(L, -1)) {
        lua_pushliteral(L, "non-integer and non-boolean returned from filter callback");
        lsqlite_changeset_capture_error(ctx, L);
        lua_settop(L, top);
        return 0;
    }
    if (!isint) result = lua_toboolean(L, -1);

    lua_settop(L, top);
    return result;
}

/* Session table-filter callback.  pCtx is the lsession* registered by
** lsession_attach() through sqlite3session_table_filter(), so each session
** uses its OWN Lua filter refs (no module-level singletons).
** Note: a Lua error inside the filter is propagated with lua_error(), the
** same convention used by every other SQLite->Lua hook in this binding
** (update/commit/rollback hooks).  It is only apply_changeset() that must
** defer its callback errors, because SQLite is holding a write-lock there. */
static int db_session_filter_callback(
        void *pCtx,      /* lsession* (pCtx of sqlite3session_table_filter) */
        const char *zTab /* Table name */
) {
    lsession *lses = (lsession*)pCtx;
    lua_State *L = lses->db->L;
    int top, result, isint;

    /* allow the table if no filter callback is provided */
    if (lses->filter_cb == LUA_NOREF || lses->filter_cb == LUA_REFNIL) return 1;

    top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, lses->filter_cb);    /* get callback */
    lua_pushstring(L, zTab);
    lua_rawgeti(L, LUA_REGISTRYINDEX, lses->filter_udata); /* get callback user data */

    if (lua_pcall(L, 2, 1, 0) != LUA_OK) return lua_error(L);

    /* allow 0/1 and false/true to be returned
    ** returning 0/false skips the table */
    result = lua_tointegerx(L, -1, &isint); /* use result if there was no error */
    if (!isint && !lua_isboolean(L, -1)) {
        lua_pushliteral(L, "non-integer and non-boolean returned from filter callback");
        return lua_error(L);
    }
    if (!isint) result = lua_toboolean(L, -1);

    lua_settop(L, top);
    return result;
}

/*
** =======================================================
** Session functions
** =======================================================
*/

static lsession *lsqlite_makesession(lua_State *L, sqlite3_session *ses, sdb *db) {
    lsession *lses = (lsession*)lua_newuserdata(L, sizeof(lsession));
    lua_rawgeti(L, LUA_REGISTRYINDEX, sqlite_ses_meta_ref);
    lua_setmetatable(L, -2);
    lses->ses = ses;
    lses->db = db;
    lses->filter_cb = LUA_NOREF;
    lses->filter_udata = LUA_REFNIL;
    return lses;
}

static lsession *lsqlite_getsession(lua_State *L, int index) {
    return (lsession *)luaL_checkudata(L, index, sqlite_ses_meta);
}

static lsession *lsqlite_checksession(lua_State *L, int index) {
    lsession *lses = lsqlite_getsession(L, index);
    if (lses->ses == NULL) luaL_argerror(L, index, "invalid sqlite session");
    return lses;
}

static int lsession_attach(lua_State *L) {
    lsession *lses = lsqlite_checksession(L, 1);
    int rc;
    // allow either a table or a callback function to filter tables
    const char *zTab = lua_type(L, 2) == LUA_TFUNCTION
        ? NULL
        : luaL_optstring(L, 2, NULL);
    if ((rc = sqlite3session_attach(lses->ses, zTab)) != SQLITE_OK) {
        return pusherr(L, rc);
    }
    // allow to pass a filter callback (owned by this session only).
    // refs live in lses and are replaced on a repeated attach(fn).
    if (lua_type(L, 2) == LUA_TFUNCTION) {
        if (lses->filter_cb != LUA_NOREF) {
            luaL_unref(L, LUA_REGISTRYINDEX, lses->filter_cb);
            luaL_unref(L, LUA_REGISTRYINDEX, lses->filter_udata);
        }
        lua_settop(L, 3);  // add udata even if it's not provided
        lses->filter_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        lses->filter_cb = luaL_ref(L, LUA_REGISTRYINDEX);
        sqlite3session_table_filter(lses->ses,
            db_session_filter_callback, lses);
    }
    lua_pushboolean(L, 1);
    return 1;
}

static int lsession_isempty(lua_State *L) {
    lsession *lses = lsqlite_checksession(L, 1);
    lua_pushboolean(L, sqlite3session_isempty(lses->ses));
    return 1;
}

static int lsession_diff(lua_State *L) {
    lsession *lses = lsqlite_checksession(L, 1);
    const char *zFromDb = luaL_checkstring(L, 2);
    const char *zTbl = luaL_checkstring(L, 3);
    int rc = sqlite3session_diff(lses->ses, zFromDb, zTbl, NULL);
    if (rc != SQLITE_OK) return pusherr(L, rc);
    lua_pushboolean(L, 1);
    return 1;
}

static int lsession_bool(
        lua_State *L,
        int (*session_func)(sqlite3_session *ses, int val)
) {
    lsession *lses = lsqlite_checksession(L, 1);
    int val = lua_isboolean(L, 2)
        ? lua_toboolean(L, 2)
        : luaL_optinteger(L, 2, -1);
    lua_pushboolean(L, (*session_func)(lses->ses, val));
    return 1;
}

static int lsession_indirect(lua_State *L) {
    return lsession_bool(L, sqlite3session_indirect);
}

static int lsession_enable(lua_State *L) {
    return lsession_bool(L, sqlite3session_enable);
}

static int lsession_getset(
        lua_State *L,
        int (*session_setfunc)(sqlite3_session *ses, int *size, void **buf)
) {
    lsession *lses = lsqlite_checksession(L, 1);
    int rc;
    int size;
    void *buf;

    if ((rc = (*session_setfunc)(lses->ses, &size, &buf)) != SQLITE_OK) {
        return pusherr(L, rc);
    }
    lua_pushlstring(L, buf, size);
    sqlite3_free(buf);
    return 1;
}

static int lsession_changeset(lua_State *L) {
    return lsession_getset(L, sqlite3session_changeset);
}

static int lsession_patchset(lua_State *L) {
    return lsession_getset(L, sqlite3session_patchset);
}

static int lsession_delete(lua_State *L) {
    lsession *lses = lsqlite_getsession(L, 1);
    if (lses->ses != NULL) {
      sqlite3session_delete(lses->ses); /* no more xFilter calls after this */
      lses->ses = NULL;
      if (lses->filter_cb != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, lses->filter_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, lses->filter_udata);
        lses->filter_cb = LUA_NOREF;
        lses->filter_udata = LUA_REFNIL;
      }
    }
    return 0;
}

static int lsession_tostring(lua_State *L) {
    char buff[32];
    lsession *lses = lsqlite_getsession(L, 1);
    if (lses->ses == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", lses->ses);
    lua_pushfstring(L, "sqlite session (%s)", buff);
    return 1;
}

static int db_create_session(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *zDb = luaL_optstring(L, 2, "main");
    sqlite3_session *ses;

    if (sqlite3session_create(db->db, zDb, &ses) != SQLITE_OK) {
        return pusherr(L, sqlite3_errcode(db->db));
    }
    (void)lsqlite_makesession(L, ses, db);
    return 1;
}

static int db_iterate_changeset(lua_State *L) {
    sqlite3_changeset_iter *p;
    sdb *db = lsqlite_checkdb(L, 1);
    const char *cset = luaL_checkstring(L, 2);
    int nset = lua_strlen(L, 2);
    int flags = luaL_optinteger(L, 3, 0);
    int rc;

    if ((rc = sqlite3changeset_start_v2(&p, nset, cset, flags)) != SQLITE_OK) {
        return pusherr(L, rc);
    }
    (void)lsqlite_makeiter(L, p, 1);
    return 1;
}

static int db_invert_changeset(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *cset = luaL_checkstring(L, 2);
    int nset = lua_strlen(L, 2);
    int rc;
    int size;
    void *buf;

    if ((rc = sqlite3changeset_invert(nset, cset, &size, &buf)) != SQLITE_OK) {
        return pusherr(L, rc);
    }
    lua_pushlstring(L, buf, size);
    sqlite3_free(buf);
    return 1;
}

static int db_concat_changeset(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    int size, nset;
    void *buf, *cset;
    sqlite3_changegroup *pGrp;

    luaL_checktype(L, 2, LUA_TTABLE);
    int n = luaL_len(L, 2);
    int rc = sqlite3changegroup_new(&pGrp);
    for (int i = 1; rc == SQLITE_OK && i <= n; i++) {
        lua_rawgeti(L, 2, i);
        cset = (void*)lua_tostring(L, -1);
        nset = lua_strlen(L, -1);
        rc = sqlite3changegroup_add(pGrp, nset, cset);
        lua_pop(L, 1);  // pop the string
    }
    if (rc == SQLITE_OK) rc = sqlite3changegroup_output(pGrp, &size, &buf);
    sqlite3changegroup_delete(pGrp);

    if (rc != SQLITE_OK) return pusherr(L, rc);
    lua_pushlstring(L, buf, size);
    sqlite3_free(buf);
    return 1;
}

static int db_apply_changeset(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *cset = luaL_checkstring(L, 2);
    int nset = lua_strlen(L, 2);
    int top = lua_gettop(L);
    int rc;
    int flags = 0;
    void *pRebase;
    int nRebase;
    lrebaser *lreb = NULL;
    lsqlite_changeset_apply ctx; /* per-call, thread-local callback state */

    // parameters: db, changeset[[, filter cb], conflict cb[, udata[, rebaser[, flags]]]]

    ctx.L = L;
    ctx.filter_cb = LUA_NOREF;
    ctx.conflict_cb = LUA_NOREF;
    ctx.udata = LUA_REFNIL;
    ctx.failed = 0;
    ctx.err_ref = LUA_NOREF;

    // check for conflict/filter callback type if provided
    if (top >= 3) {
        luaL_checktype(L, 3, LUA_TFUNCTION);
        // if no filter callback, insert a dummy one to simplify stack handling
        if (lua_type(L, 4) != LUA_TFUNCTION) {
            lua_pushnil(L);
            lua_insert(L, 3);
            top = lua_gettop(L);
        }
    }
    if (top >= 6) lreb = lsqlite_checkrebaser(L, 6);
    if (top >= 7) flags = luaL_checkinteger(L, 7);
    if (top >= 4) {  // two callback are guaranteed to be on the stack in this case
        // shorten stack or extend to set udata to `nil` if not provided
        lua_settop(L, 5);
        ctx.udata = luaL_ref(L, LUA_REGISTRYINDEX);
        ctx.conflict_cb = luaL_ref(L, LUA_REGISTRYINDEX);
        ctx.filter_cb = luaL_ref(L, LUA_REGISTRYINDEX);
    }

    // The callback references live in this per-call ctx, which is handed to
    // sqlite3changeset_apply_v2() as its pCtx.  No process-wide globals are
    // touched, so concurrent applies from other threads / Lua states cannot
    // corrupt each other's conflict/filter callbacks (previous design used
    // module-level statics, which made db_apply_changeset() deadlock under
    // multithreaded use).
    rc = sqlite3changeset_apply_v2(db->db, nset, (void*)cset,
                                   db_changeset_filter_callback,
                                   db_changeset_conflict_callback,
                                   &ctx,   // context
                                   lreb ? &pRebase : 0,
                                   lreb ? &nRebase : 0,
                                   flags);

    // release the per-call references (apply_v2() has returned, so no
    // session callback can use them any more)
    if (ctx.filter_cb != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, ctx.filter_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, ctx.conflict_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, ctx.udata);
    }

    // A Lua error raised inside a conflict/filter callback must NOT longjmp
    // through the sqlite3changeset_apply_v2() frames (that would leave the
    // connection locked / half applied).  The callbacks above let SQLite
    // abort and roll back cleanly; we re-raise the stored Lua error here,
    // where no SQLite frame is active.
    if (ctx.failed) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ctx.err_ref); // push error object
        luaL_unref(L, LUA_REGISTRYINDEX, ctx.err_ref);
        return lua_error(L);
    }

    if (rc != SQLITE_OK) return pusherr(L, sqlite3_errcode(db->db));

    if (lreb) { // if rebaser is present
        rc = sqlite3rebaser_configure(lreb->reb, nRebase, pRebase);
        if (rc == SQLITE_OK) {
            /* rebase log is binary data - never lua_pushstring (NUL truncation) */
            if (pRebase && nRebase > 0)
                lua_pushlstring(L, pRebase, nRebase);
            else
                lua_pushliteral(L, "");
        }
        sqlite3_free(pRebase);
        if (rc == SQLITE_OK) return 1;
        return pusherr(L, rc);
    }

    lua_pushboolean(L, 1);
    return 1;
}

#endif

/*
** =======================================================
** General library functions
** =======================================================
*/

static int lsqlite_version(lua_State *L) {
    lua_pushstring(L, sqlite3_libversion());
    return 1;
}

static int lsqlite_complete(lua_State *L) {
    const char *sql = luaL_checkstring(L, 1);
    lua_pushboolean(L, sqlite3_complete(sql));
    return 1;
}

#ifndef _WIN32
static int lsqlite_temp_directory(lua_State *L) {
    const char *oldtemp = sqlite3_temp_directory;

    if (!lua_isnone(L, 1)) {
        const char *temp = luaL_optstring(L, 1, NULL);
        if (sqlite3_temp_directory) {
            sqlite3_free((char*)sqlite3_temp_directory);
        }
        if (temp) {
            sqlite3_temp_directory = sqlite3_mprintf("%s", temp);
        }
        else {
            sqlite3_temp_directory = NULL;
        }
    }
    lua_pushstring(L, oldtemp);
    return 1;
}
#endif

#if defined(SQLITE_ENABLE_CEROD)
static int lsqlite_activate_cerod(lua_State *L) {
    const char *s = luaL_checkstring(L, 1);
    sqlite3_activate_cerod(s);
    lua_pushnil(L);
    return 0;
}
#endif

static int lsqlite_do_open(lua_State *L, const char *filename, int flags) {
    sqlite3_initialize(); /* initialize the engine if hasn't been done yet */
    sdb *db = newdb(L); /* create and leave in stack */

    if (SQLITE3_OPEN(filename, &db->db, flags) == SQLITE_OK) {
        /* database handle already in the stack - return it */
        return 1;
    }

    /* failed to open database */
    lua_pushnil(L);                             /* push nil */
    lua_pushinteger(L, sqlite3_errcode(db->db));
    lua_pushstring(L, sqlite3_errmsg(db->db));  /* push error message */

    /* clean things up */
    cleanupdb(L, db);

    /* return */
    return 3;
}

static int lsqlite_open(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    int flags = luaL_optinteger(L, 2, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    return lsqlite_do_open(L, filename, flags);
}

static int lsqlite_open_memory(lua_State *L) {
    return lsqlite_do_open(L, ":memory:", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
}

/* From: Wolfgang Oertl
When using lsqlite3 in a multithreaded environment, each thread has a separate Lua
environment, but full userdata structures can't be passed from one thread to another.
This is possible with lightuserdata, however. See: db_get_ptr().
*/
static int lsqlite_open_ptr(lua_State *L) {
    sqlite3 *db_ptr;
    sdb *db;
    int rc;

    luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
    db_ptr = lua_touserdata(L, 1);
    /* This is the only API function that runs sqlite3SafetyCheck regardless of
     * SQLITE_ENABLE_API_ARMOR and does almost nothing (without an SQL
     * statement) */
    rc = sqlite3_exec(db_ptr, NULL, NULL, NULL, NULL);
    if (rc != SQLITE_OK)
        luaL_argerror(L, 1, "not a valid SQLite3 pointer");

    db = newdb(L); /* create and leave in stack */
    db->db = db_ptr;
    return 1;
}

/*
** Log callback:
** Params: user, result code, log message
** Returns: none
*/
static void log_callback(void* user, int rc, const char *msg) {
    if (log_cb != LUA_NOREF) {
        lua_State *L = (lua_State*)user;

        /* setup lua callback call */
        int top = lua_gettop(L);
        lua_rawgeti(L, LUA_REGISTRYINDEX, log_cb);    /* get callback */
        lua_rawgeti(L, LUA_REGISTRYINDEX, log_udata); /* get callback user data */
        lua_pushinteger(L, rc);
        lua_pushstring(L, msg);

        if (lua_pcall(L, 3, 0, 0) != LUA_OK) lua_error(L);

        lua_settop(L, top);
    }
}

static int lsqlite_config(lua_State *L) {
    int rc = SQLITE_MISUSE;
    int option = luaL_checkint(L, 1);

    switch (option) {
        case SQLITE_CONFIG_SINGLETHREAD:
        case SQLITE_CONFIG_MULTITHREAD:
        case SQLITE_CONFIG_SERIALIZED:
            if ((rc = sqlite3_config(option)) == SQLITE_OK) {
                lua_pushinteger(L, rc);
                return 1;
            }
            break;
        case SQLITE_CONFIG_LOG:
            /* make sure we have an userdata field (even if nil) */
            lua_settop(L, 3);

            // prepate to return current (possibly nil) values
            lua_pushinteger(L, SQLITE_OK);
            lua_rawgeti(L, LUA_REGISTRYINDEX, log_cb);    /* get callback */
            lua_rawgeti(L, LUA_REGISTRYINDEX, log_udata); /* get callback user data */

            luaL_unref(L, LUA_REGISTRYINDEX, log_cb);
            luaL_unref(L, LUA_REGISTRYINDEX, log_udata);
            if (lua_isnil(L, 2)) {
                log_cb =
                log_udata = LUA_NOREF;
            }
            else {
                luaL_checktype(L, 2, LUA_TFUNCTION);
                lua_pushvalue(L, 2);
                lua_pushvalue(L, 3);
                log_udata = luaL_ref(L, LUA_REGISTRYINDEX);
                log_cb = luaL_ref(L, LUA_REGISTRYINDEX);
            }
            return 3;  // return OK and previous callback and userdata
    }
    return pusherr(L, rc);
}

static int lsqlite_newindex(lua_State *L) {
    lua_pushliteral(L, "attempt to change readonly table");
    lua_error(L);
    return 0;
}

#ifndef LSQLITE_VERSION
/* should be defined in rockspec, but just in case... */
#define LSQLITE_VERSION "0.9.7"
#endif

/* Version number of this library
*/
static int lsqlite_lversion(lua_State *L) {
    lua_pushstring(L, LSQLITE_VERSION);
    return 1;
}

/*
** =======================================================
** Register functions
** =======================================================
*/

#define SC(s)   { #s, SQLITE_ ## s },
#define LSC(s)  { #s, LSQLITE_ ## s },

static const struct {
    const char* name;
    int value;
} sqlite_constants[] = {
    /* error codes */
    SC(OK)          SC(ERROR)       SC(INTERNAL)    SC(PERM)
    SC(ABORT)       SC(BUSY)        SC(LOCKED)      SC(NOMEM)
    SC(READONLY)    SC(INTERRUPT)   SC(IOERR)       SC(CORRUPT)
    SC(NOTFOUND)    SC(FULL)        SC(CANTOPEN)    SC(PROTOCOL)
    SC(EMPTY)       SC(SCHEMA)      SC(TOOBIG)      SC(CONSTRAINT)
    SC(MISMATCH)    SC(MISUSE)      SC(NOLFS)
    SC(FORMAT)      SC(NOTADB)

    /* sqlite_step specific return values */
    SC(RANGE)       SC(ROW)         SC(DONE)

    /* column types */
    SC(INTEGER)     SC(FLOAT)       SC(TEXT)        SC(BLOB)
    SC(NULL)

    /* Authorizer Action Codes */
    SC(CREATE_INDEX       )
    SC(CREATE_TABLE       )
    SC(CREATE_TEMP_INDEX  )
    SC(CREATE_TEMP_TABLE  )
    SC(CREATE_TEMP_TRIGGER)
    SC(CREATE_TEMP_VIEW   )
    SC(CREATE_TRIGGER     )
    SC(CREATE_VIEW        )
    SC(DELETE             )
    SC(DROP_INDEX         )
    SC(DROP_TABLE         )
    SC(DROP_TEMP_INDEX    )
    SC(DROP_TEMP_TABLE    )
    SC(DROP_TEMP_TRIGGER  )
    SC(DROP_TEMP_VIEW     )
    SC(DROP_TRIGGER       )
    SC(DROP_VIEW          )
    SC(INSERT             )
    SC(PRAGMA             )
    SC(READ               )
    SC(SELECT             )
    SC(TRANSACTION        )
    SC(UPDATE             )
    SC(ATTACH             )
    SC(DETACH             )
    SC(ALTER_TABLE        )
    SC(REINDEX            )
    SC(ANALYZE            )
    SC(CREATE_VTABLE      )
    SC(DROP_VTABLE        )
    SC(FUNCTION           )
    SC(SAVEPOINT          )

    /* file open flags */
    SC(OPEN_READONLY)
    SC(OPEN_READWRITE)
    SC(OPEN_CREATE)
    SC(OPEN_URI)
    SC(OPEN_MEMORY)
    SC(OPEN_NOMUTEX)
    SC(OPEN_FULLMUTEX)
    SC(OPEN_SHAREDCACHE)
    SC(OPEN_PRIVATECACHE)

    /* config flags */
    SC(CONFIG_SINGLETHREAD)
    SC(CONFIG_MULTITHREAD)
    SC(CONFIG_SERIALIZED)
    SC(CONFIG_LOG)

    /* checkpoint flags */
    SC(CHECKPOINT_PASSIVE)
    SC(CHECKPOINT_FULL)
    SC(CHECKPOINT_RESTART)
    SC(CHECKPOINT_TRUNCATE)

#ifdef SQLITE_ENABLE_SESSION
    /* session constants */
    SC(CHANGESETAPPLY_NOSAVEPOINT)
    SC(CHANGESET_DATA)
    SC(CHANGESET_NOTFOUND)
    SC(CHANGESET_CONFLICT)
    SC(CHANGESET_CONSTRAINT)
    SC(CHANGESET_FOREIGN_KEY)
    SC(CHANGESET_OMIT)
    SC(CHANGESET_REPLACE)
    SC(CHANGESET_ABORT)
#endif

    /* terminator */
    { NULL, 0 }
};

/* ======================================================= */

static const luaL_Reg dblib[] = {
    {"isopen",              db_isopen               },
    {"last_insert_rowid",   db_last_insert_rowid    },
    {"changes",             db_changes              },
    {"total_changes",       db_total_changes        },
    {"errcode",             db_errcode              },
    {"error_code",          db_errcode              },
    {"errmsg",              db_errmsg               },
    {"error_message",       db_errmsg               },
    {"interrupt",           db_interrupt            },
    {"db_filename",         db_db_filename          },
    {"wal_checkpoint",      db_wal_checkpoint       },

    {"create_function",     db_create_function      },
    {"create_aggregate",    db_create_aggregate     },
    {"create_collation",    db_create_collation     },
    {"load_extension",      db_load_extension       },

    {"trace",               db_trace                },
    {"progress_handler",    db_progress_handler     },
    {"busy_timeout",        db_busy_timeout         },
    {"busy_handler",        db_busy_handler         },
    {"wal_hook",            db_wal_hook             },
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    {"update_hook",         db_update_hook          },
    {"commit_hook",         db_commit_hook          },
    {"rollback_hook",       db_rollback_hook        },
#endif

    {"prepare",             db_prepare              },
    {"rows",                db_rows                 },
    {"urows",               db_urows                },
    {"nrows",               db_nrows                },

    {"exec",                db_exec                 },
    {"execute",             db_exec                 },
    {"close",               db_close                },
    {"close_vm",            db_close_vm             },
    {"get_ptr",             db_get_ptr              },

#ifdef SQLITE_ENABLE_SESSION
    {"create_session",      db_create_session       },
    {"create_rebaser",      db_create_rebaser       },
    {"apply_changeset",     db_apply_changeset      },
    {"invert_changeset",    db_invert_changeset     },
    {"concat_changeset",    db_concat_changeset     },
    {"iterate_changeset",   db_iterate_changeset    },
#endif

#ifdef SQLITE_ENABLE_DESERIALIZE
    {"serialize",           db_serialize            },
    {"deserialize",         db_deserialize          },
#endif

    {"__tostring",          db_tostring             },
    {"__gc",                db_gc                   },

    {NULL, NULL}
};

static const luaL_Reg vmlib[] = {
    {"isopen",              dbvm_isopen             },

    {"step",                dbvm_step               },
    {"reset",               dbvm_reset              },
    {"finalize",            dbvm_finalize           },

    {"columns",             dbvm_columns            },

    {"bind",                dbvm_bind               },
    {"bind_values",         dbvm_bind_values        },
    {"bind_names",          dbvm_bind_names         },
    {"bind_blob",           dbvm_bind_blob          },
    {"bind_parameter_count",dbvm_bind_parameter_count},
    {"bind_parameter_name", dbvm_bind_parameter_name},

    {"get_value",           dbvm_get_value          },
    {"get_values",          dbvm_get_values         },
    {"get_name",            dbvm_get_name           },
    {"get_names",           dbvm_get_names          },
    {"get_type",            dbvm_get_type           },
    {"get_types",           dbvm_get_types          },
    {"get_uvalues",         dbvm_get_uvalues        },
    {"get_unames",          dbvm_get_unames         },
    {"get_utypes",          dbvm_get_utypes         },

    {"get_named_values",    dbvm_get_named_values   },
    {"get_named_types",     dbvm_get_named_types    },

    {"rows",                dbvm_rows               },
    {"urows",               dbvm_urows              },
    {"nrows",               dbvm_nrows              },

    {"last_insert_rowid",   dbvm_last_insert_rowid  },

    /* compatibility names (added by request) */
    {"idata",               dbvm_get_values         },
    {"inames",              dbvm_get_names          },
    {"itypes",              dbvm_get_types          },
    {"data",                dbvm_get_named_values   },
    {"type",                dbvm_get_named_types    },

    {"__tostring",          dbvm_tostring           },
    {"__gc",                dbvm_gc                 },

    { NULL, NULL }
};

static const luaL_Reg ctxlib[] = {
    {"user_data",               lcontext_user_data              },

    {"get_aggregate_data",      lcontext_get_aggregate_context  },
    {"set_aggregate_data",      lcontext_set_aggregate_context  },
    {"aggregate_count",         lcontext_aggregate_count        },

    {"result",                  lcontext_result                 },
    {"result_null",             lcontext_result_null            },
    {"result_number",           lcontext_result_double          },
    {"result_double",           lcontext_result_double          },
    {"result_int",              lcontext_result_int             },
    {"result_text",             lcontext_result_text            },
    {"result_blob",             lcontext_result_blob            },
    {"result_error",            lcontext_result_error           },

    {"__tostring",              lcontext_tostring               },
    {NULL, NULL}
};

static const luaL_Reg dbbulib[] = {

    {"step",        dbbu_step       },
    {"remaining",   dbbu_remaining  },
    {"pagecount",   dbbu_pagecount  },
    {"finish",      dbbu_finish     },

/*  {"__tostring",  dbbu_tostring   },   */
    {"__gc",        dbbu_gc         },
    {NULL, NULL}
};

#ifdef SQLITE_ENABLE_SESSION

static const luaL_Reg seslib[] = {
    {"attach",          lsession_attach         },
    {"changeset",       lsession_changeset      },
    {"patchset",        lsession_patchset       },
    {"isempty",         lsession_isempty        },
    {"indirect",        lsession_indirect       },
    {"enable",          lsession_enable         },
    {"diff",            lsession_diff           },
    {"delete",          lsession_delete         },

    {"__tostring",      lsession_tostring       },
    {"__gc",            lsession_delete         },
    {NULL, NULL}
};

static const luaL_Reg reblib[] = {
    {"rebase",          lrebaser_rebase         },
    {"configure",       lrebaser_configure      },
    {"delete",          lrebaser_delete         },

    {"__tostring",      lrebaser_tostring       },
    {"__gc",            lrebaser_gc             },
    {NULL, NULL}
};

static const luaL_Reg itrlib[] = {
    {"op",              liter_op                },
    {"pk",              liter_pk                },
    {"new",             liter_new               },
    {"old",             liter_old               },
    {"next",            liter_next              },
    {"conflict",        liter_conflict          },
    {"finalize",        liter_finalize          },
    {"fk_conflicts",    liter_fk_conflicts      },

    {"__tostring",      liter_tostring          },
    {"__gc",            liter_gc                },
    {NULL, NULL}
};

#endif

static const luaL_Reg sqlitelib[] = {
    {"lversion",        lsqlite_lversion        },
    {"version",         lsqlite_version         },
    {"complete",        lsqlite_complete        },
    {"config",          lsqlite_config          },
#ifndef _WIN32
    {"temp_directory",  lsqlite_temp_directory  },
#endif
#if defined(SQLITE_ENABLE_CEROD)
    {"activate_cerod",  lsqlite_activate_cerod  },
#endif
    {"open",            lsqlite_open            },
    {"open_memory",     lsqlite_open_memory     },
    {"open_ptr",        lsqlite_open_ptr        },

    {"backup_init",     lsqlite_backup_init     },

    {"__newindex",      lsqlite_newindex        },
    {NULL, NULL}
};

static void create_meta(lua_State *L, const char *name, const luaL_Reg *lib) {
    luaL_newmetatable(L, name);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);               /* push metatable */
    lua_rawset(L, -3);                  /* metatable.__index = metatable */

    /* register metatable functions */
    luaL_openlib(L, NULL, lib, 0);

    /* remove metatable from stack */
    lua_pop(L, 1);
}

LUALIB_API int luaopen_lsqlite3(lua_State *L) {
    /* call config before calling initialize */
    sqlite3_config(SQLITE_CONFIG_LOG, log_callback, L);

    create_meta(L, sqlite_meta, dblib);
    create_meta(L, sqlite_vm_meta, vmlib);
    create_meta(L, sqlite_bu_meta, dbbulib);
    create_meta(L, sqlite_ctx_meta, ctxlib);

    luaL_getmetatable(L, sqlite_ctx_meta);
    sqlite_ctx_meta_ref = luaL_ref(L, LUA_REGISTRYINDEX);

#ifdef SQLITE_ENABLE_SESSION
    create_meta(L, sqlite_ses_meta, seslib);
    create_meta(L, sqlite_reb_meta, reblib);
    create_meta(L, sqlite_itr_meta, itrlib);

    luaL_getmetatable(L, sqlite_ses_meta);
    sqlite_ses_meta_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    luaL_getmetatable(L, sqlite_reb_meta);
    sqlite_reb_meta_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    luaL_getmetatable(L, sqlite_itr_meta);
    sqlite_itr_meta_ref = luaL_ref(L, LUA_REGISTRYINDEX);
#endif

    /* register (local) sqlite metatable */
    luaL_register(L, "sqlite3", sqlitelib);

    {
        int i = 0;
        /* add constants to global table */
        while (sqlite_constants[i].name) {
            lua_pushstring(L, sqlite_constants[i].name);
            lua_pushinteger(L, sqlite_constants[i].value);
            lua_rawset(L, -3);
            ++i;
        }
    }

    /* set sqlite's metatable to itself - set as readonly (__newindex) */
    lua_pushvalue(L, -1);
    lua_setmetatable(L, -2);

#ifdef SQLITE_VEC_STATIC
    int sqlite3_vec_init(sqlite3*, char**, const sqlite3_api_routines*);
    sqlite3_auto_extension((void(*)(void))sqlite3_vec_init);
#endif

#ifdef SQLITE_GRAPH_STATIC
    int sqlite3_graphqlite_init(sqlite3*, char**, const sqlite3_api_routines*);
    sqlite3_auto_extension((void(*)(void))sqlite3_graphqlite_init);
#endif

    return 1;
}
