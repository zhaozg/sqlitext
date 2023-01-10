#include "patch.h"
#include "sqlite3.h"

void trace_callback(void *udp, const char *sql) { printf("{SQL} [%s]\n", sql); }

const char *usage = "Usage: sqlite-patch [db] [patchfile]";

int main(int argc, char const *argv[]) {
  const char *dbFile;
  const char *patchFile;

  int rc;
  sqlite3 *db;

  if (argc != 3) {
    fprintf(stderr, "Wrong number of arguments\n%s\n", usage);
    return 1;
  }

  dbFile = argv[1];
  patchFile = argv[2];

  rc = sqlite3_open_v2(dbFile, &db, SQLITE_OPEN_READWRITE, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Could not open sqlite DB %s:%s", dbFile,
            sqlite3_errstr(rc));
    sqlite3_close(db);
    return 2;
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
