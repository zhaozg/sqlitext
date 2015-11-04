## sqlitext:  sqlite with extend feature

sqlite is good, and I like it.
SEE(Sqlite Encryption Extension) not free, and [sqlcipher](https://github.com/sqlcipher/sqlcipher) 
not amalgamation, so I cut some essential to do some updated.

Building 

 1. You *must* define SQLITE_HAS_CODEC and SQLITE_TEMP_STORE=2 when building sqlcipher. 
 2. You need to link against a OpenSSL's libcrypto 
 
 Useing
 
 ```
E:\work\sqlitext>sqlite.exe safe.db
SQLite version 3.9.2 2015-11-02 18:31:45
Enter ".help" for usage hints.
sqlite> pragma key='abcdefghicj';
sqlite> create table people (name text primary key);
sqlite> insert into people (name) values ('charlie'), ('huey');
sqlite> select * from people;
charlie
huey
sqlite> .quit

E:\work\sqlitext>sqlite.exe safe.db
SQLite version 3.9.2 2015-11-02 18:31:45
Enter ".help" for usage hints.
sqlite> pragma key='abcdefghicj';
sqlite> pragma rekey='12345678';
sqlite> select * from people;
charlie
huey
sqlite> .quit

E:\work\sqlitext>sqlite.exe safe.db
SQLite version 3.9.2 2015-11-02 18:31:45
Enter ".help" for usage hints.
sqlite>  pragma key='abcdefghicj';
sqlite> select * from people;
Error: file is encrypted or is not a database
sqlite> pragma key='12345678';
sqlite> select * from people;
Error: file is encrypted or is not a database
sqlite> .quit

E:\work\sqlitext>sqlite.exe safe.db
SQLite version 3.9.2 2015-11-02 18:31:45
Enter ".help" for usage hints.
sqlite> pragma key='12345678';
sqlite> select * from people;
charlie
huey
sqlite> .quit

E:\work\sqlitext>
```
