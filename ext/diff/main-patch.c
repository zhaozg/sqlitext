#include "patch.h"
#include "sqlite3.h"

#if defined(SQLITE_TRACE_STMT)
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

const char *usage = "Usage: sqlite-patch [db] [patchfile]";

int main(int argc, char const *argv[]) {
  const char *dbFile;
  const char *patchFile;

  int verbose = 0;
  int rc;
  sqlite3 *db;

  if (argc < 3) {
    fprintf(stderr, "Wrong number of arguments\n%s\n", usage);
    return 1;
  }

  dbFile = argv[1];
  patchFile = argv[2];
  if (argc == 4)
    verbose = 1;

  rc = sqlite3_open_v2(dbFile, &db, SQLITE_OPEN_READWRITE, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Could not open sqlite DB %s:%s", dbFile,
            sqlite3_errstr(rc));
    sqlite3_close(db);
    return 2;
  }

  if (verbose) {
#if defined(SQLITE_TRACE_STMT)
    sqlite3_trace_v2(db, SQLITE_TRACE_STMT, trace_callback, db);
#endif
  }

  rc = sqlitediff_patch_file(db, patchFile);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Could not apply changeset %s\n", patchFile);
    sqlite3_close(db);
    return 2;
  }

  sqlite3_close(db);

  return 0;
}
