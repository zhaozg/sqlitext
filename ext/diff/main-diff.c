#if defined(__linux__) && defined(__GNUC__)
#define _XOPEN_SOURCE 500
#endif
#include "diff.h"
#include "sqlite3.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *usage =
    "Usage: sqlite-diff [source file] [target file] [diff file]\n"
    " source file:  source file to diff\n"
    " target file:  target file to diff\n"
    " diff file:    generate diff file, default will output to stdout\n";

int main(int argc, char const *argv[]) {
  const char *db1File;
  const char *db2File;
  const char *diffFile = NULL;
  FILE *out = NULL;

  int rc;

  if (argc < 3 || argc > 4) {
    fprintf(stderr, "need more paramaters\n\n%s\n", usage);
    return 1;
  }

  db1File = argv[1];
  db2File = argv[2];
  if (argc == 4)
    diffFile = argv[3];

  if (diffFile) {
    out = fopen(diffFile, "wb");
    if (out == NULL) {
      fprintf(stderr, "Could create sqlite3 diff file: %s, fail with %s\n",
              db1File, strerror(errno));
      return 1;
    }
  } else
    out = stdout;

  rc = sqlitediff_diff(db1File, db2File, NULL, out);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Could generate sqlite3 diff file %d(%s)\n", rc,
            sqlite3_errstr(rc));
    return 2;
  }

  return 0;
}
