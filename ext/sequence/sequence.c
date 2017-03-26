#include "sqlite3ext.h"
#include <string.h>
/*
** This header file defines the interface for the sequence functions
** nextval and curval
**
** sequence.h developed by Stephen Lombardo (ZETETIC LLC) 
** stephen dot lombardo at zetetic dot net
** 
** These functions provide similar functionality to the sequences
** found in systems like postgresql and oracle, allow
** applications to pre-fetch a unique identifier for use later.
** This functionality aleviates the need to use sqlite3_last_insert_rowid() 
** to build complex relationships. It also works well in cases where 
** primary key uniqueness is desirable across multiple tables.
**
** these functions can be called in one of four ways:
** nextval/curval('name')
** nextval/curval('name, 'db')
** 
** 'name'
**   is the name of the sequence to match
**   against the first column of the sequence table
**
** 'db'
**   is the name of the optional attached database to use  
**
**
** Note that these functions can be used with the following caveats:
** 1. Despite the fact that you can call nextval() from a select statement, it
**    does modify the database. Therefore, if another process has the database
**    in an active transaction or otherwise locked you cannot obtain new 
**    sequence numbers.  
** 2. You can't use the function as a default value when you create tables. 
*/

#ifndef SQLITE_OMIT_SEQUENCE_FUNCTIONS

/* nextval is a user defined function used to obtain a unique number from a
 * sequence. the sequence data is stored in a table (either sqlite_sequence
 * or sqlite3_sequence). The function must be passed a squence name like this:
 * 
 * SELECT nextval('name');
 * 
 */
void sqlite3_nextval(
  sqlite3_context *context,
  int arg,
  sqlite3_value **argv
);

/* curval() is a very simple convenience function that simply executes
 * the appropriate select statment to retrieve the current value of the 
 * named sequence. the functon takes identical parameters to nextval().
 */
void sqlite3_curval(
  sqlite3_context *context,
  int arg,
  sqlite3_value **argv
);
#endif

SQLITE_EXTENSION_INIT1;

 /*
 ** Return the collating function associated with a function.
 */
 /*
+#ifndef SQLITE_OMIT_SEQUENCE_FUNCTIONS
+	{ "nextval",				-1, 1, SQLITE_UTF8, 0, sqlite3_nextval },
+	{ "curval",					-1, 1, SQLITE_UTF8, 0, sqlite3_curval }
+#endif
*/

/*
** This file contains the C functions that implement the nextval and
** curval sequence manipulation functions
** 
** sequence.c developed by Stephen Lombardo (ZETETIC LLC) 
** stephen dot lombardo at zetetic dot net
**
** See sequence.h for description of functionality
*/

#ifndef SEQUENCE_H
#define SEQUENCE_H

#ifndef SQLITE_OMIT_SEQUENCE_FUNCTIONS

#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define SQLITE_SEQUENCE_MEMSLOTS 7

/* In order for the nextval function to work properly, the update of the sequence 
 * and the read should happen at the same time, while the database is in a locked
 * state. Also, the function will need to take into account certain advanced 
 * functionality to support increments of arbitrary values and min/max constraint
 * enforcement. Also, the code should be *mostly* the same beteween advanced
 * and classic sequence modes. Therefore the nextval function uses using the 
 * Vdbe API directly . Here is the basic logic that it uses:
 * 1. Create a new Vdbe for the database based on the context.
 * 2. Try to obtain an exclusive lock (OP_Transaction, P2=3). 
 *    The exclusive lock will fail if there are other transactions in a
 *    pending state;
 * 3. Open the sequence table for writes (OP_OpenWrite)
 * 4. Search the table and obtain the current value from the sequence table
 *    associate with that name. If one isn't found, start a new sequence off at 0.
 * 5. Increment the value
 * 6. Write the new value into the table
 * 7. Callback the new value
 * 9. Halt
 *
 */
void sqlite3_nextval(
  sqlite3_context *context,
  int arg,
  sqlite3_value **argv
){

	int rc = 0;

	sqlite3_int64 result = 0;	/*	result that will be returned on success */
	sqlite3 *db;

	sqlite3_stmt *stmt;	
	const char *db_nm = 0;  /* name of the attached database to use */
	const char *seq_nm = 0;	/*	name of the sequence instance, corresponding 
						        to the name column of the sequence table */
	const char* out;
	char *sql = 0;
	char *zErrMsg = 0;
	int seq_cols = 2; /* number of total columns used for the sequence calculations:
						 name(sequence name),seq(current value),*/

	/* nextval can be called in one of four ways:
	 * nextval('name')
	 * nextval('name, 'db')
	 * 
	 * 'name' - is the name of the sequence to match
	 *          against the first column of the sequence table
	 * 'db' - is the name of the optional attached 
	 *        database to use 
	 */
	if(!(arg >=1 && arg <= 2)) {
			sqlite3_result_error(context, 
			"invalid number of parameters", -1);
		return;
	}

	if(sqlite3_value_type(argv[0]) != SQLITE_TEXT) {
		sqlite3_result_error(context, 
			"invalid parameter(s)", -1);
		return;
	}

	/* obtain the name of the sequence to use */
	seq_nm = sqlite3_value_text(argv[0]);
		
	/* two argument form of nextval
	 * nextval('name', 'db') or
	 */
	if ( arg == 2 ) {
		if (sqlite3_value_type(argv[1]) == SQLITE_TEXT) {
			db_nm = sqlite3_value_text(argv[1]);
		} else {
			sqlite3_result_error(context, 
				"invalid parameter(s)", -1);
			return;
		}
	/* one argument form of nextval
	 * nextval('name')
	 */
	} else {
		db_nm = "main";
	}	

	/* obtain a handle to the executing DB context */
	db = sqlite3_context_db_handle(context);

	/* obtain the name of the sequence to use */
	seq_nm = sqlite3_value_text(argv[0]);

	/* query next val */
	sql = sqlite3_mprintf(
		"SELECT seq + 1 FROM %s.sqlite_sequence  WHERE name = '%q';",  db_nm, seq_nm);

	rc = sqlite3_prepare(db, sql, strlen(sql), &stmt, &out);
    if(rc==SQLITE_OK)
    {
        rc = sqlite3_step(stmt);
        /* if sqlite3_step returns a row, then we have found the proper sequence and can 
         * initialize result to the curretn value */
        if(rc == SQLITE_ROW) {
            result = sqlite3_column_int64(stmt, 0);
            rc = SQLITE_OK;
            /* If no result is returned, then this sequence doesnt exist. The result will be 0. This
             * is a save value to return, as the first call to nextval('name') will always return 1 */
        } else if (rc == SQLITE_DONE) {
		    result = 0;
        } 
    }

	sqlite3_finalize(stmt);
	sqlite3_free(sql);
    
	sql = sqlite3_mprintf(
		"UPDATE  %s.sqlite_sequence SET seq = seq+1 WHERE name = '%q';",  db_nm, seq_nm);
  
	if(rc == SQLITE_OK)
	{		
        char* err=NULL;
        int i = 0;
        while((rc = sqlite3_exec(db,sql,0,0,&err))==SQLITE_BUSY && i<10)
        {
            if(err!=NULL)
                sqlite3_free(err);
            i++;
            sqlite3_sleep(100);
        }
	}
	

	sqlite3_free(sql);
	/* if we detected an error, anywhere in the process return without 
	 * passing a result. */
	if(rc) {
         sqlite3_result_error_code(context,rc);
		 return;
	}
	
	sqlite3_result_int64(context, result);
}

/* 
 * NOTE: if the sequence called doesn't exist in the table, curval will
 * still return a value of 0. This is for consistency, as the first call
 * to nextval() for a given sequence will always return 1
 */
void sqlite3_curval(
  sqlite3_context *context,
  int arg,
  sqlite3_value **argv
){
	int rc;
	sqlite3_int64 result = 0;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char *select;
	const char *out;
	const char *seq_nm;
	const char *db_nm;

	/* curval can be called in one of four ways:
	 * curval('name')
	 * curval('name, 'db')
	 * 
	 * 'name' - is the name of the sequence to match
	 *          against the first column of the sequence table
	 * 'db' - is the name of the optional attached 
	 *        database to use 
	 */
	if(!(arg >=1 && arg <= 2)) {
			sqlite3_result_error(context, 
			"invalid number of parameters", -1);
		return;
	}

	if(sqlite3_value_type(argv[0]) != SQLITE_TEXT) {
		sqlite3_result_error(context, 
			"invalid parameter(s)", -1);
		return;
	}

	/* obtain the name of the sequence to use */
	seq_nm = sqlite3_value_text(argv[0]);
		
	/* two argument form of curval
	 * curval('name', 'db') or
	 */
	if ( arg == 2 ) {
		if (sqlite3_value_type(argv[1]) == SQLITE_TEXT) {
			db_nm = sqlite3_value_text(argv[1]);
		} else {
			sqlite3_result_error(context, 
				"invalid parameter(s)", -1);
			return;
		}
	/* one argument form of nextval
	 * curval('name')
	 */
	} else {
		db_nm = "main";
	}

	/* obtain a handle to the executing DB context */
	db = sqlite3_context_db_handle(context);

	/* obtain the name of the sequence to use */
	seq_nm = sqlite3_value_text(argv[0]);

	select = sqlite3_mprintf(
		"SELECT seq FROM %s.sqlite_sequence WHERE name = '%q';",  db_nm, seq_nm);
	
	rc = sqlite3_prepare(db, select, strlen(select), &stmt, &out);

	if(rc==SQLITE_OK) {
		rc = sqlite3_step(stmt);

		/* if sqlite3_step returns a row, then we have found the proper sequence and can 
		 * initialize result to the curretn value */
		if(rc == SQLITE_ROW) {
			result = sqlite3_column_int64(stmt, 0);
            rc = SQLITE_OK;
		/* If no result is returned, then this sequence doesnt exist. The result will be 0. This
		 * is a save value to return, as the first call to nextval('name') will always return 1 */
		} else if (rc == SQLITE_DONE) {
			result = 0;
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_free(select);

	/* if we detected an error, anywhere in the process return without 
	 * passing a result. */
	if(rc) {
		sqlite3_result_error_code(context,rc);
        return;
	}

	sqlite3_result_int64(context, result);
}
#ifdef WIN32
__declspec( dllexport ) 
#endif
int sqlite3_extension_init(
  sqlite3 *db,          /* The database connection */
  char **pzErrMsg,      /* Write error messages here */
  const sqlite3_api_routines *api  /* API methods */
){
	int ret;
	SQLITE_EXTENSION_INIT2(api);

	ret = sqlite3_create_function(
	  db,
	  "nextval",
	  -1,
	  SQLITE_ANY,
	  NULL,
	  sqlite3_nextval,
	  NULL,
	  NULL
	);

	if(ret!=0)
	{
		*pzErrMsg = sqlite3_mprintf("sequence support init(nextval) error:%d,%s",ret,sqlite3_errmsg(db));
		return ret;
	}

	ret = sqlite3_create_function(
	  db,
	  "curval",
	  -1,
	  SQLITE_ANY,
	  NULL,
	  sqlite3_curval,
	  NULL,
	  NULL
	);
	if(ret!=0)
	{
		*pzErrMsg = sqlite3_mprintf("sequence support init(curval) error:%d",ret,sqlite3_errmsg(db));
		return ret;
	}
	return 0;
}

#endif
#endif
