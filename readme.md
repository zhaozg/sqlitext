# sqlitext:  sqlite with extend feature

sqlite is good, and I like it.
SEE(Sqlite Encryption Extension) not free. and [sqlcipher](https://github.com/sqlcipher/sqlcipher)
not amalgamation, so I cut some essential to do some updated.

But after sqlite3 version up, some api changed, so I search another solution,
now change to [CEVFS](sqlite3-compression-encryption-vfs).

## Building

`make`.

## Using

`cerod` is encrypt vfs name.

### create plain db

```shell
bin/sqlite plain.db
SQLite version 3.39.3 2022-09-05 11:02:23
Enter ".help" for usage hints.
sqlite> create table people (name text primary key);
sqlite> insert into people (name) values ('charlie'), ('huey');
sqlite> select * from people;
charlie
huey
sqlite> .quit
```

### convert to cipher db

```shell
bin/cevfs plain.db cipher.db cerod "x'2F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA2'"
```

### read cipher db

```shell
bin/secure
sqlite> PRAGMA activate_extensions("cerod-x'2F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA2'");
sqlite> .open cipher.db
sqlite> select * from people;
Parse error: file is not a database (26)
sqlite> .quit
```

```shell
bin/secure
sqlite> PRAGMA activate_extensions("cerod-x'2F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA2'");
sqlite> .open test.db
sqlite> create table people (name text primary key);
sqlite> insert into people (name) values ('charlie'), ('huey');
sqlite> select * from people;
charlie
huey
sqlite> .quit

bin/secure
sqlite> PRAGMA activate_extensions("cerod-x''2F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA2'");
sqlite> .open test.db
sqlite> select * from people;
charlie
huey
sqlite> .quit
```
