#include "patch.h"
#include "sqlite3.h"

const char *usage = "Usage: sqlite-patch [db] [patchfile]";

int main(int argc, char const *argv[]) {
  const char *dbFile;
  const char *patchFile;

  int rc;

  if (argc < 3) {
    fprintf(stderr, "Wrong number of arguments\n%s\n", usage);
    return 1;
  }

  dbFile = argv[1];
  patchFile = argv[2];

  rc = sqlitediff_patch_file(dbFile, patchFile);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Could not apply changeset %s\n", patchFile);
    return 2;
  }

  return 0;
}
