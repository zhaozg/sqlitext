#pragma once

#include "diff.h"
#include "sqlite3.h"

int applyInstruction(const struct Instruction *instr, struct sqlite3 *db);

int sqlitediff_apply(const char *buf, size_t size, InstrCallback instr_callback,
                     void *context);
int sqlitediff_apply_file(const char *filename, InstrCallback instr_callback,
                          void *context);

int sqlitediff_patch(struct sqlite3 *db, const char *buf, size_t size);
int sqlitediff_patch_file(struct sqlite3 *db, const char *filename);
