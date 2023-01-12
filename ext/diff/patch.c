#if defined(__linux__) && defined(__GNUC__)
#define _XOPEN_SOURCE 500
#endif

#include "diff.h"

#include "sqliteint.h"

#include <assert.h>
#include <errno.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "patch.h"

#define CHANGESET_CORRUPT 1
#define CHANGESET_INSTRUCTION_CORRUPT 3
#define CHANGESET_CALLBACK_ERROR 4

/**

FORMAT of binary changeset (pseudo-grammar):

->:
        <TableInstructions>[1+]

TableInstructions:
        'T'
        varint	=> nCols
        byte[nCols] (PK flag)
        <string>	name of table
        <Instruction>[1+]

string:
        varInt	length
        …		data

Instruction:
        <InstrInsert> | <InstrDelete> | <InstrUpdate>

InstrInsert:
        SQLITE_INSERT
        0x0
        <Value>[nCols]

InstrDelete:
        SQLITE_DELETE
        0x0
        <Value>[nCols]

InstrUpdate:
        SQLITE_DELETE
        0x0
        <ZeroOrValue>[nCols]		# Old Values (zero if not changed)
        <ZeroOrValue>[nCols]		# New Values (zero if not changed)

ZeroOrValue:
        0x0 | <Value>

Value:
        byte iDType data type, (if NULL that's it)
        …data

*/

/*
** Dynamic string object
*/
typedef struct Str Str;
struct Str {
  char *z;    /* Text of the string */
  int nAlloc; /* Bytes allocated in z[] */
  int nUsed;  /* Bytes actually used in z[] */
};

/*
** Initialize a Str object
*/
static void strInit(Str *p) {
  p->z = 0;
  p->nAlloc = 0;
  p->nUsed = 0;
}

static void strFinal(Str *p) {
  free(p->z);
  p->z = NULL;
  p->nAlloc = 0;
  p->nUsed = 0;
}

/*
** Print an error message for an error that occurs at runtime, then
** abort the program.
*/
static int runtimeError(const char *zFormat, ...) {
  va_list ap;
  fprintf(stderr, "sqlpatch: ");
  va_start(ap, zFormat);
  vfprintf(stderr, zFormat, ap);
  va_end(ap);
  fprintf(stderr, "\n");
  return 1;
}

/*
** Add formatted text to the end of a Str object
*/
static void strPrintf(Str *p, const char *zFormat, ...) {
  int nNew;
  for (;;) {
    if (p->z) {
      va_list ap;
      va_start(ap, zFormat);
      sqlite3_vsnprintf(p->nAlloc - p->nUsed, p->z + p->nUsed, zFormat, ap);
      va_end(ap);
      nNew = (int)strlen(p->z + p->nUsed);
    } else {
      nNew = p->nAlloc;
    }
    if (p->nUsed + nNew < p->nAlloc - 1) {
      p->nUsed += nNew;
      break;
    }
    p->nAlloc = p->nAlloc * 2 + 1000;
    p->z = realloc(p->z, p->nAlloc);
    if (p->z == 0)
      runtimeError("out of memory");
  }
}

/*
** Dynamic string array
*/
typedef struct StrArray StrArray;
struct StrArray {
  const char **s; /* Text of the string */
  int nAlloc;     /* Bytes allocated in s[] */
  int nUsed;      /* Bytes actually used in s[] */
};

static void strArrayInit(StrArray *ary, size_t items) {
  ary->s = items == 0 ? 0 : malloc(items * sizeof(char *));
  ary->nAlloc = items;
  ary->nUsed = 0;
}

static void strArrayFinal(StrArray *ary) {
  while (ary->nUsed >= 0)
    free((void *)(ary->s[ary->nUsed--]));
  if (ary->nUsed)
    free(ary->s);
  ary->nAlloc = 0;
  ary->nAlloc = 0;
  ary->nUsed = 0;
}

static void strArrayAppend(StrArray *ary, const char *str) {
  if (ary->nUsed == ary->nAlloc) {
    ary->nAlloc += 16;
    ary->s = realloc(ary->s, ary->nAlloc * sizeof(char *));
    if (ary->s == NULL)
      runtimeError("out of memory");
  }
  ary->s[ary->nUsed] = strdup(str);
  if (ary->s[ary->nUsed] == NULL)
    runtimeError("out of memory");
  ary->nUsed += 1;
}

size_t readValue(const char *buf, struct sqlite_value *val) {
  u8 type = buf[0];
  val->type = type;
  buf++;
  void *data = (void *)(buf);

  size_t read = 1;

  switch (type) {
  case SQLITE_INTEGER: {
    val->data1.iVal = sessionGetI64((u8 *)data);
    read += 8;
    break;
  }
  case SQLITE_FLOAT: {
    int64_t iVal = sessionGetI64((u8 *)data);
    val->data1.dVal = *(double *)(&iVal);
    read += 8;
    break;
  }

  case SQLITE_TEXT: {
    u32 textLen;
    u8 varIntLen = getVarint32((u8 *)data, textLen);

    val->data1.iVal = textLen;
    val->data2 = (char *)data + varIntLen;

    read += textLen + varIntLen;
    break;
  }
  case SQLITE_BLOB: {
    u32 blobLen;
    u8 varIntLen = getVarint32((u8 *)data, blobLen);

    val->data1.iVal = blobLen;
    val->data2 = (char *)data + varIntLen;

    read += blobLen + varIntLen;
    break;
  }
  case SQLITE_NULL:
    break;
  case 0:
    val->type = 0;
    break;
  default:
    val->type = -1;
    return 0;
  }

  return read;
}

int bindValue(sqlite3_stmt *stmt, int col, const struct sqlite_value *val) {
  int rv = SQLITE_INTERNAL;
  switch (val->type) {
  case SQLITE_INTEGER:
    rv = sqlite3_bind_int64(stmt, col, val->data1.iVal);
    break;
  case SQLITE_FLOAT:
    rv = sqlite3_bind_double(stmt, col, val->data1.dVal);
    break;
  case SQLITE_TEXT:
    rv = sqlite3_bind_text(stmt, col, val->data2, val->data1.iVal, NULL);
    break;
  case SQLITE_BLOB:
#if SQLITE_VERSION_NUMBER > 3020000
    rv = sqlite3_bind_blob64(stmt, col, val->data2, val->data1.iVal, NULL);
#else
    rv = sqlite3_bind_blob(stmt, col, val->data2, val->data1.iVal, NULL);
#endif
    break;
  case SQLITE_NULL:
    rv = sqlite3_bind_null(stmt, col);
    break;
  default:;
  }
  if (rv != SQLITE_OK) {
    runtimeError("bindValue fail %s with returned %d\n", sqlite3_errstr(rv),
                 rv);
  }
  return rv;
}

int bindValues_ncolumns(sqlite3_stmt *stmt, struct sqlite_value *values,
                        uint8_t nCol, int skipNull) {
  int i, n, rc;
  for (i = 0, n = 1; i < nCol; i++) {
    int isNull = values[i].type == SQLITE_NULL;
    if (isNull && skipNull)
      continue;

    rc = bindValue(stmt, n, &values[i]);
    if (rc != SQLITE_OK) {
      return rc;
    }
    n++;
  }
  return SQLITE_OK;
}

int applyInsert(sqlite3 *db, const struct Instruction *instr) {
  int rc;
  Str sql; /* SQL for the patch SQL query */
  int i;

  int nCol = instr->table->nCol;
  const char *tableName = instr->table->tableName;

  strInit(&sql);

  strPrintf(&sql, "INSERT INTO %s VALUES (", tableName);

  for (i = 0; i < nCol; i++) {
    if (i < nCol - 1)
      strPrintf(&sql, "?,");
    else
      strPrintf(&sql, "?");
  }
  strPrintf(&sql, ");");

  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, sql.z, sql.nUsed, &stmt, NULL);
  strFinal(&sql);
  if (rc != SQLITE_OK) {
    return rc;
  }

  rc = bindValues_ncolumns(stmt, instr->values, nCol, 0);
  if (rc != SQLITE_OK) {
    return rc;
  }

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) {
    runtimeError("Error applying insert: %s", sqlite3_errmsg(db));
    return rc;
  }

  return SQLITE_OK;
}

static int getColumnNames(sqlite3 *db, const char *tableName, StrArray *ary) {
  int rc;
  Str sql;

  sqlite3_stmt *stmt;

  strInit(&sql);
  strPrintf(&sql, "pragma table_info(%s);", tableName);

  rc = sqlite3_prepare_v2(db, sql.z, sql.nUsed, &stmt, NULL);
  strFinal(&sql);
  if (rc != SQLITE_OK) {
    return rc;
  }

  while (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
    strArrayAppend(ary, (const char *)sqlite3_column_text(stmt, 1));
  }

  sqlite3_finalize(stmt);
  return rc;
}

int applyDelete(sqlite3 *db, const struct Instruction *instr) {
  int rc;
  Str sql; /* SQL for the patch SQL query */
  int i;
  StrArray columnNames;
  uint8_t nCol = instr->table->nCol;

  sqlite3_stmt *stmt;

  strArrayInit(&columnNames, 0);

  rc = getColumnNames(db, instr->table->tableName, &columnNames);

  strInit(&sql);

  strPrintf(&sql, "DELETE FROM %s WHERE", instr->table->tableName);

  for (i = 0; i < nCol; i++) {
    int isNull = instr->values[i].type == SQLITE_NULL;
    if (i == 0)
      strPrintf(&sql, isNull ? " %s IS NULL" : " %s = ?", columnNames.s[i]);
    else
      strPrintf(&sql, isNull ? " AND %s IS NULL" : " AND %s = ?",
                columnNames.s[i]);
  }

  rc = sqlite3_prepare_v2(db, sql.z, sql.nUsed, &stmt, NULL);
  strFinal(&sql);
  if (rc != SQLITE_OK) {
    runtimeError("Failed preparing DELETE statement: %s", sql);
    strArrayFinal(&columnNames);
    return rc;
  }

  rc = bindValues_ncolumns(stmt, instr->values, nCol, 1);
  if (rc != SQLITE_OK) {
    runtimeError("Failed binding to DELETE statement: %s", sql);
    strArrayFinal(&columnNames);
    return rc;
  }

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  strArrayFinal(&columnNames);
  if (rc != SQLITE_DONE) {
    return rc;
  }

  return SQLITE_OK;
}

int applyUpdate(sqlite3 *db, const struct Instruction *instr) {
  int nCol = instr->table->nCol;
  Str sql; /* SQL for the patch SQL query */
  StrArray columnNames;
  sqlite3_stmt *stmt;
  int rc;
  int i;
  int n;

  struct sqlite_value *valsBefore = instr->values;
  struct sqlite_value *valsAfter = instr->values + nCol;

  strInit(&sql);
  strArrayInit(&columnNames, 0);

  rc = getColumnNames(db, instr->table->tableName, &columnNames);
  strPrintf(&sql, "UPDATE %s SET ", instr->table->tableName);

  /* sets */
  for (n = 0, i = 0; i < nCol; i++) {
    const struct sqlite_value val = valsAfter[i];
    if (val.type) {
      if (n == 0)
        strPrintf(&sql, "%s = ?", columnNames.s[i]);
      else
        strPrintf(&sql, ", %s = ?", columnNames.s[i]);
      n++;
    }
  }

  /* wheres */
  strPrintf(&sql, " WHERE ");
  for (n = 0, i = 0; i < nCol; i++) {
    const struct sqlite_value val = valsBefore[i];
    int is_null = val.type == SQLITE_NULL;
    if (val.type) {
      if (n == 0)
        strPrintf(&sql, is_null ? "%s IS NULL" : "%s = ?", columnNames.s[i]);
      else
        strPrintf(&sql, is_null ? " AND %s IS NULL" : " AND %s = ?",
                  columnNames.s[i]);
      n++;
    }
  }

  rc = sqlite3_prepare_v2(db, sql.z, sql.nUsed, &stmt, NULL);
  strFinal(&sql);
  if (rc != SQLITE_OK) {
    runtimeError("applyUpdate: Failed preparing sql: %s", sql);
    strArrayFinal(&columnNames);
    return 1;
  }

  for (i = 0, n = 1; i < nCol; i++) {
    struct sqlite_value *val = &valsAfter[i];
    if (val->type) {
      if (bindValue(stmt, n, val)) {
        strArrayFinal(&columnNames);
        return 1;
      }
      n++;
    }
  }

  for (i = 0; i < nCol; i++) {
    struct sqlite_value *val = &valsBefore[i];
    int is_null = val->type == SQLITE_NULL;
    if (val->type && !is_null) {
      if (bindValue(stmt, n, val)) {
        strArrayFinal(&columnNames);
        return 1;
      }
      n++;
    }
  }

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  strArrayFinal(&columnNames);

  if (rc != SQLITE_DONE) {
    return rc;
  }
  return SQLITE_OK;
}

int applyInstruction(const struct Instruction *instr, sqlite3 *db) {
  switch (instr->iType) {
  case SQLITE_INSERT:
    return applyInsert(db, instr);
  case SQLITE_UPDATE:
    return applyUpdate(db, instr);
  case SQLITE_DELETE:
    return applyDelete(db, instr);
  default:
    return CHANGESET_CORRUPT;
  }
}

int applyInstructionCallback(const struct Instruction *instr, void *context) {
  return applyInstruction(instr, (sqlite3 *)context);
}

size_t readInstructionFromBuffer(const char *buf, struct Instruction *instr) {
  int i;
  size_t nRead = 0;

  instr->iType = *buf;
  buf += 2;
  nRead += 2;

  int nCol = instr->table->nCol;
  if (instr->iType == SQLITE_UPDATE) {
    nCol *= 2;
  }

  for (i = 0; i < nCol; i++) {
    struct sqlite_value *val_p = instr->values + i;
    size_t read = readValue(buf, val_p);
    if (read == 0) {
      return 0;
    }
    buf += read;
    nRead += read;
  }

  return nRead;
}

int sqlitediff_patch(sqlite3 *db, const char *buf, size_t size) {
  int rc;

  rc = sqlite3_exec(db, "SAVEPOINT changeset_apply", 0, 0, 0);
  if (rc == SQLITE_OK) {
    rc = sqlite3_exec(db, "PRAGMA defer_foreign_keys = 1", 0, 0, 0);
  }

  rc = sqlitediff_apply(buf, size, applyInstructionCallback, db);

  if (rc) {
    runtimeError("Error occured.");
    rc = sqlite3_exec(db, "PRAGMA defer_foreign_keys = 0", 0, 0, 0);
    rc = sqlite3_exec(db, "ROLLBACK TO SAVEPOINT changeset_apply", 0, 0, 0);
  } else {
    rc = sqlite3_exec(db, "PRAGMA defer_foreign_keys = 0", 0, 0, 0);
    rc = sqlite3_exec(db, "RELEASE changeset_apply", 0, 0, 0);
  }

  return rc;
}

static int file_read(const char *filename, void *buffer, size_t *len) {
  FILE *file = fopen(filename, "rb");
  size_t size;

  if (file == NULL) {
    runtimeError("fopen file(%s) error: %s", filename, strerror(errno));
    return 1;
  }

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  if (buffer == NULL && len != NULL) {
    *len = size;
    fclose(file);
    return 0;
  }

  if (*len < size) {
    runtimeError("file_read need %zd bytes buffer, but %zd", size, *len);
    fclose(file);
    *len = size;
    return 1;
  }

  if (fread(buffer, 1, size, file) != size) {
    runtimeError("fread file(%s) error: %s", filename, strerror(ferror(file)));
    fclose(file);
    return 1;
  }
  fclose(file);
  *len = size;
  return 0;
}

int sqlitediff_patch_file(sqlite3 *db, const char *filename) {
  size_t size;

  int rc = file_read(filename, NULL, &size);
  if (rc == 0) {
    char *buffer = malloc(size);
    if (buffer == NULL) {
      runtimeError("Out of memory");
      return 1;
    }
    rc = file_read(filename, buffer, &size);
    if (rc == 0)
      rc = sqlitediff_patch(db, buffer, size);
    free(buffer);
  }
  return rc;
}

int sqlitediff_apply(const char *buf, size_t size, InstrCallback instr_callback,
                     void *context) {
  const char *const bufEnd = buf + size;

  while (buf < bufEnd) {
    u32 nCol;
    u32 varintLen;
    int *PKs;
    const char *tableName;
    size_t tableNameLen;
    size_t instrRead = 0;
    u32 i;

    struct TableInfo table;
    struct Instruction instr;

    char op = buf[0];
    buf++;

    /* Read OP */
    if (op != 'T') {
      return CHANGESET_CORRUPT;
    }

    /* Read number of columns */
    varintLen = getVarint32((u8 *)buf, nCol);
    buf += varintLen;

    /* Read Primary Key flags */
    PKs = malloc(nCol * sizeof(*PKs));
    for (i = 0; i < nCol; i++) {
      PKs[i] = buf[i];
    }
    buf += nCol;

    /* Read table name */
    tableName = buf;
    tableNameLen = strlen(tableName);
    buf += tableNameLen + 1;

    instrRead = 0;

    table.PKs = PKs;
    table.nCol = (uint8_t)nCol;
    table.tableName = tableName;

    instr.table = &table;
    instr.values = malloc((nCol * 2) * sizeof(struct sqlite_value));

    while (buf < bufEnd && buf[0] != 'T') {
      int rc;

      instrRead = readInstructionFromBuffer(buf, &instr);
      if (instrRead == 0) {
        runtimeError("Error reading instruction from buffer.");
        free(instr.values);
        free(PKs);
        return CHANGESET_INSTRUCTION_CORRUPT;
      }

      if (instr_callback && (rc = instr_callback(&instr, context))) {
        runtimeError("Error applying instruction. Callback returned %d", rc);
        free(instr.values);
        free(PKs);
        return CHANGESET_CALLBACK_ERROR;
      }

      buf += instrRead;
    }

    free(instr.values);
    free(PKs);
  }

  return 0;
}

int sqlitediff_apply_file(const char *filename, InstrCallback instr_callback,
                          void *context) {
  size_t size;
  int rc = file_read(filename, NULL, &size);
  if (rc == 0) {
    char *buffer = malloc(size);
    if (buffer == NULL) {
      runtimeError("Out of memory");
      return 1;
    }
    rc = file_read(filename, buffer, &size);
    if (rc == 0)
      rc = sqlitediff_apply(buffer, size, instr_callback, context);
    free(buffer);
  }
  return rc;
}
