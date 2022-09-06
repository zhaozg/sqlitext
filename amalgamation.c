#include "src/sqlite3.c"
#if defined(SQLITE_EXT_CEVFS) || defined(SQLITE_ENABLE_CEROD)
#include "ext/cevfs/cevfs.c"
#endif
#if defined(SQLITE_ENABLE_CEROD)
#include "ext/cevfs/cevfs_mod.c"
#endif
