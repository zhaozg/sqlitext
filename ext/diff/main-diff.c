#if defined(__linux__) && defined(__GNUC__)
#define _XOPEN_SOURCE 500
#endif
#include "diff.h"
#include "sqlite3.h"

#include <stdio.h>
#include <string.h>

#define SQLOK(X)                                                               \
  do {                                                                         \
    rc = X;                                                                    \
    if (rc != 0) {                                                             \
      fprintf(stderr, "Error: %s returned %d\n", #X, rc);                      \
      fprintf(stderr, "%s", sqlite3_errstr(rc));                               \
      return rc;                                                               \
    }                                                                          \
  } while (0)

#ifdef SQLITE_TRACE_STMT
int trace_callback(unsigned trace, void *db, void *p, void *x) {
  (void)trace;
  (void)db;
  (void)p;

  if (trace == SQLITE_TRACE_STMT) {
    fprintf(stderr, "{SQL} [%s]\n", (const char *)x);
  }
  return 0;
}
#endif

const char *usage = "Usage: sqlite-diff [db1] [db2]";

int main(int argc, char const *argv[]) {
  const char *db1File;
  const char *db2File;
  char sql[1024];
  int verbose = 0;

  int rc;
  sqlite3 *db;

  if (argc < 3) {
    fprintf(stderr, "Wrong number of arguments\n%s\n", usage);
    return 1;
  }

  db1File = argv[1];
  db2File = argv[2];
  if (argc == 4)
    verbose = 1;

  rc = sqlite3_open_v2(db1File, &db, SQLITE_OPEN_READWRITE, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Could not open sqlite DB: %s\n", db1File);
    return 2;
  }

  if (verbose) {
#ifdef SQLITE_TRACE_STMT
    sqlite3_trace_v2(db, SQLITE_TRACE_STMT, trace_callback, db);
#endif
  }

  snprintf(sql, sizeof(sql), "ATTACH '%s' AS 'aux';", db2File);
  SQLOK(sqlite3_exec(db, sql, 0, 0, 0));

  sqlitediff_diff_prepared(db, NULL, stdout);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Could not create changeset.\n");
    sqlite3_close(db);
    return 2;
  }

  sqlite3_close(db);

  return 0;
}
