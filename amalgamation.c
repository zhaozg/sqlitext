#ifndef SQLITE_HAS_CODEC
#define SQLITE_HAS_CODEC 1
#endif
#ifndef SQLITE_TEMP_STORE
#define SQLITE_TEMP_STORE 2
#endif

#include "src/sqlite3.c"
#include "ext/cipher/crypto.c"
#include "ext/cipher/crypto_impl.c"
#include "ext/cipher/crypto_openssl.c"
