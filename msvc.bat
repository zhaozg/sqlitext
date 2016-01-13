setlocal
SET OPENSSL_DIR=e:\work\product\openssl\win32\
cl -DSQLITE_HAS_CODEC=1 -DSQLITE_TEMP_STORE=2 /Fesqlite.exe amalgamation.c src/shell.c -I%OPENSSL_DIR%\include %OPENSSL_DIR%\lib\libeay32.lib kernel32.lib advapi32.lib gdi32.lib user32.lib
copy sqlite.exe build
del sqlite.exe *.obj

