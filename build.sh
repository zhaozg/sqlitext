OPENSSL_DIR=/mnt/hgfs/luvit/luvi/build/openssl

gcc -DSQLITE_HAS_CODEC=1 -DSQLITE_TEMP_STORE=2 -o sqlite3 amalgamation.c src/shell.c -lrt -ldl -pthread -I${OPENSSL_DIR}\include /mnt/hgfs/luvit/luvi/build/libopenssl.a

