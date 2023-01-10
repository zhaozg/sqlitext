#include "diff.h"
#include "patch.h"
#include <sqlite3.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

#define F(X)                                                                   \
  do {                                                                         \
    rc = X;                                                                    \
    if (rc != 0) {                                                             \
      fprintf(stderr, "Error: %s returned %d\n", #X, rc);                      \
      return rc;                                                               \
    }                                                                          \
  } while (0)

#define T(X) F(!(X))

static int checkB(struct sqlite3 *db, const char *dbName) {
  int rc;
  sqlite3_stmt *stmt;
  char sql[256];
  sprintf(sql, "SELECT ID, Name, Farbe FROM %s.Entries;", dbName);
  F(sqlite3_prepare(db, sql, -1, &stmt, NULL));

  T(sqlite3_step(stmt) == SQLITE_ROW);
  T(sqlite3_column_int(stmt, 0) == 0);
  F(strcmp((const char *)sqlite3_column_text(stmt, 1), "Apfel"));
  F(strcmp((const char *)sqlite3_column_text(stmt, 2), "Grün"));

  T(sqlite3_step(stmt) == SQLITE_ROW);
  T(sqlite3_column_int(stmt, 0) == 1);
  F(strcmp((const char *)sqlite3_column_text(stmt, 1), "Banane"));
  F(strcmp((const char *)sqlite3_column_text(stmt, 2), "Gelb"));

  T(sqlite3_step(stmt) == SQLITE_ROW);
  T(sqlite3_column_int(stmt, 0) == 2);
  F(strcmp((const char *)sqlite3_column_text(stmt, 1), "Clementine"));
  F(strcmp((const char *)sqlite3_column_text(stmt, 2), "Orange"));

  F(sqlite3_finalize(stmt));

  return 0;
};

int main(int argc, char const *argv[]) {
  int rc;

  const char *aF = "a.sqlite";
  const char *bF = "b.sqlite";
  struct sqlite3 *db;

  rc = remove(aF);
  if (rc) {
    T(errno == ENOENT);
  }
  rc = remove(bF);
  if (rc) {
    T(errno == ENOENT);
  }

  F(sqlite3_open_v2(aF, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL));

  F(sqlite3_exec(db, "ATTACH 'b.sqlite' AS 'aux'", NULL, NULL, NULL));

  F(sqlite3_exec(db, "CREATE TABLE main.Entries (ID PRIMARY KEY, Name, Farbe)",
                 NULL, NULL, NULL));
  F(sqlite3_exec(db, "CREATE TABLE aux.Entries (ID PRIMARY KEY, Name, Farbe)",
                 NULL, NULL, NULL));

  F(sqlite3_exec(db, "INSERT INTO main.Entries VALUES (0, 'Apfel', 'Grün')",
                 NULL, NULL, NULL));
  F(sqlite3_exec(db, "INSERT INTO main.Entries VALUES (1, 'Banane', 'Gälb')",
                 NULL, NULL, NULL));
  F(sqlite3_exec(db, "INSERT INTO main.Entries VALUES (3, 'Dattel', 'Rot')",
                 NULL, NULL, NULL));

  F(sqlite3_exec(db, "INSERT INTO aux.Entries VALUES (0, 'Apfel', 'Grün')",
                 NULL, NULL, NULL));
  F(sqlite3_exec(db, "INSERT INTO aux.Entries VALUES (1, 'Banane', 'Gelb')",
                 NULL, NULL, NULL));
  F(sqlite3_exec(db,
                 "INSERT INTO aux.Entries VALUES (2, 'Clementine', 'Orange')",
                 NULL, NULL, NULL));

  F(checkB(db, "aux"));

  // Diff
  FILE *out = fopen("out.diff", "wb");
  F(sqlitediff_diff_prepared(db, NULL, out /* Output stream */
                             ));
  fclose(out);

  F(sqlitediff_patch_file(db, "out.diff"));

  F(checkB(db, "main"));

  F(sqlite3_close(db));

  return 0;
}
