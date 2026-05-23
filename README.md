# sqlitext: SQLite with Extended Features

This project enhances SQLite with several useful extensions including encryption, compression, graph database capabilities, vector search, and more. It provides a comprehensive set of tools for working with SQLite databases in various scenarios.

## Extensions Included

This repository includes the following SQLite extensions in the `ext/` directory:

1. **CEVFS** - Compression & Encryption VFS for SQLite 3
   - Provides transparent compression and encryption at the pager level
   - Allows creating encrypted databases that can only be accessed with the correct key
   - See `ext/cevfs/` directory for implementation

2. **Diff/Patch** - SQLite database diff and patch tool
   - Generates differences between two SQLite databases
   - Applies patches to synchronize databases
   - Useful for database versioning and synchronization
   - See `ext/diff/` directory for implementation

3. **Graph** - Graph database extension with Cypher query support
   - Implements graph database functionality on top of SQLite
   - Supports Cypher query language for graph operations
   - Includes interactive shell for graph database operations
   - See `ext/graph/` directory for implementation

4. **Sequence** - Sequence functions for SQLite
   - Provides `nextval()` and `curval()` functions similar to PostgreSQL sequences
   - Enables generating unique identifiers for database records
   - See `ext/sequence/` directory for implementation

5. **Vector** - Vector search extension
   - Implements vector similarity search capabilities
   - Supports storing and querying float, int8, and binary vectors
   - Useful for AI applications and similarity searches
   - See `ext/vector/` directory for implementation

## Building

To build all components, simply run:

```bash
make
```

This will compile all extensions and create executables in the `bin/` directory.

## Usage

After building, you'll find several executables in the `bin/` directory:

- `bin/sqlite3` - Standard SQLite shell with extensions loaded
- `bin/secure` - SQLite shell configured for encrypted databases
- `bin/cevfs` - Tool for creating and managing encrypted databases
- `bin/vector` - Vector search enabled SQLite shell

### CEVFS (Encryption/Compression)

The `cerod` VFS provides encryption capabilities for SQLite databases.

#### Creating an Encrypted Database

```shell
bin/cevfs plain.db cipher.db cerod "x'2F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA2'"
```

This command converts a plain SQLite database (`plain.db`) to an encrypted one (`cipher.db`) using the `cerod` VFS with the specified encryption key.

#### Reading an Encrypted Database

To access an encrypted database, you need to activate the encryption extension with the correct key:

```shell
bin/secure
sqlite> PRAGMA activate_extensions("cerod-x'2F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA22F3A995FCE317EA2'");
sqlite> .open cipher.db
sqlite> select * from people;
charlie
huey
sqlite> .quit
```

Note: Make sure to use the correct encryption key, or you won't be able to access the database contents.

### Diff/Patch Tool

Generate differences between two databases:

```shell
./bin/sqlite-diff db1.db db2.db > db.diff
```

Apply patches to synchronize databases:

```shell
./bin/sqlite-patch db1.db db.diff
```

### Graph Database

Use the interactive Cypher shell for graph database operations:

```shell
./bin/graph
graphqlite> CREATE (n:Person {name: 'Alice'});
graphqlite> MATCH (n:Person) RETURN n;
```

### Vector Search

Perform vector similarity searches:

```shell
.load ./vec0

CREATE VIRTUAL TABLE vec_examples USING vec0(
  sample_embedding float[8]
);

INSERT INTO vec_examples(rowid, sample_embedding)
  VALUES
    (1, '[-0.200, 0.250, 0.341, -0.211, 0.645, 0.935, -0.316, -0.924]'),
    (2, '[0.443, -0.501, 0.355, -0.771, 0.707, -0.708, -0.185, 0.362]');

SELECT rowid, distance FROM vec_examples
WHERE sample_embedding MATCH '[0.890, 0.544, 0.825, 0.961, 0.358, 0.0196, 0.521, 0.175]'
ORDER BY distance LIMIT 2;
```

### Sequence Functions

Generate unique sequence values:

```sql
SELECT nextval('my_sequence');
SELECT curval('my_sequence');
```

## Directory Structure

- `bin/` - Compiled executables
- `ext/` - SQLite extensions (cevfs, diff, graph, sequence, vector)
- `src/` - SQLite source code
- `build/` - Build artifacts
- `doc/` - Documentation
- `examples/` - Example scripts
- `spec/` - Test specifications
