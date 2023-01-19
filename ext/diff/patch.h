#pragma once

#include "diff.h"
#include "sqlite3.h"

int sqlitediff_apply(sqlite3 *db, const char *buf, size_t size);
int sqlitediff_apply_file(sqlite3 *db, FILE *diff);

int sqlitediff_patch(const char *dbFile, FILE *diff);
int sqlitediff_patch_file(const char *dbFile, const char *diffFile);
