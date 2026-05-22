BUILD_DIR = build
BUILD_PARSER_DIR = $(BUILD_DIR)/parser
BUILD_GENERATED_DIR = $(BUILD_DIR)/generated
BUILD_TRANSFORM_DIR = $(BUILD_DIR)/transform
BUILD_EXECUTOR_DIR = $(BUILD_DIR)/executor
BUILD_TEST_DIR = $(BUILD_DIR)/tests
COVERAGE_DIR = $(BUILD_DIR)/coverage


SRC_DIR = ext/graph
BACKEND_DIR = $(SRC_DIR)/backend
PARSER_DIR = $(BACKEND_DIR)/parser
GENERATED_DIR = $(SRC_DIR)/generated

# Parser sources (C files)
PARSER_SRCS = \
	$(PARSER_DIR)/cypher_keywords.c \
	$(PARSER_DIR)/cypher_scanner_api.c \
	$(PARSER_DIR)/cypher_ast.c \
	$(PARSER_DIR)/cypher_parser.c

# Generated sources
GENERATED_SRCS = \
	$(GENERATED_DIR)/cypher_scanner.c \
	$(GENERATED_DIR)/cypher_gram.tab.c

# All parser sources including generated
ALL_PARSER_SRCS = $(PARSER_SRCS) $(GENERATED_SRCS)

GENERATED_OBJS = $(GENERATED_SRCS:$(GENERATED_DIR)/%.c=$(BUILD_GENERATED_DIR)/%.o)
GENERATED_OBJS_COV = $(GENERATED_SRCS:$(GENERATED_DIR)/%.c=$(BUILD_GENERATED_DIR)/%.cov.o)
GENERATED_OBJS_PIC = $(GENERATED_SRCS:$(GENERATED_DIR)/%.c=$(BUILD_GENERATED_DIR)/%.pic.o)

PARSER_OBJS = $(PARSER_SRCS:$(PARSER_DIR)/%.c=$(BUILD_PARSER_DIR)/%.o)
PARSER_OBJS_COV = $(PARSER_SRCS:$(PARSER_DIR)/%.c=$(BUILD_PARSER_DIR)/%.cov.o)
PARSER_OBJS_PIC = $(PARSER_SRCS:$(PARSER_DIR)/%.c=$(BUILD_PARSER_DIR)/%.pic.o)

# Transform sources
TRANSFORM_DIR = $(SRC_DIR)/backend/transform
TRANSFORM_SRCS = \
	$(TRANSFORM_DIR)/cypher_transform.c \
	$(TRANSFORM_DIR)/transform_match.c \
	$(TRANSFORM_DIR)/transform_create.c \
	$(TRANSFORM_DIR)/transform_set.c \
	$(TRANSFORM_DIR)/transform_delete.c \
	$(TRANSFORM_DIR)/transform_remove.c \
	$(TRANSFORM_DIR)/transform_foreach.c \
	$(TRANSFORM_DIR)/transform_load_csv.c \
	$(TRANSFORM_DIR)/transform_return.c \
	$(TRANSFORM_DIR)/transform_func_string.c \
	$(TRANSFORM_DIR)/transform_func_math.c \
	$(TRANSFORM_DIR)/transform_func_entity.c \
	$(TRANSFORM_DIR)/transform_func_path.c \
	$(TRANSFORM_DIR)/transform_func_list.c \
	$(TRANSFORM_DIR)/transform_func_graph.c \
	$(TRANSFORM_DIR)/transform_func_aggregate.c \
	$(TRANSFORM_DIR)/transform_func_dispatch.c \
	$(TRANSFORM_DIR)/transform_helpers.c \
	$(TRANSFORM_DIR)/transform_variables.c \
	$(TRANSFORM_DIR)/transform_expr_predicate.c \
	$(TRANSFORM_DIR)/transform_with.c \
	$(TRANSFORM_DIR)/transform_unwind.c \
	$(TRANSFORM_DIR)/transform_expr_ops.c \
	$(TRANSFORM_DIR)/sql_builder.c

# Executor sources
EXECUTOR_DIR = $(SRC_DIR)/backend/executor
EXECUTOR_SRCS = \
	$(EXECUTOR_DIR)/cypher_schema.c \
	$(EXECUTOR_DIR)/cypher_executor.c \
	$(EXECUTOR_DIR)/executor_variable_map.c \
	$(EXECUTOR_DIR)/executor_foreach_ctx.c \
	$(EXECUTOR_DIR)/executor_result.c \
	$(EXECUTOR_DIR)/executor_helpers.c \
	$(EXECUTOR_DIR)/executor_delete.c \
	$(EXECUTOR_DIR)/executor_set.c \
	$(EXECUTOR_DIR)/executor_remove.c \
	$(EXECUTOR_DIR)/executor_create.c \
	$(EXECUTOR_DIR)/executor_foreach.c \
	$(EXECUTOR_DIR)/executor_merge.c \
	$(EXECUTOR_DIR)/executor_match.c \
	$(EXECUTOR_DIR)/query_dispatch.c \
	$(EXECUTOR_DIR)/agtype.c \
	$(EXECUTOR_DIR)/json_builder.c \
	$(EXECUTOR_DIR)/graph_algorithms.c \
	$(EXECUTOR_DIR)/graph_algo_pagerank.c \
	$(EXECUTOR_DIR)/graph_algo_community.c \
	$(EXECUTOR_DIR)/graph_algo_paths.c \
	$(EXECUTOR_DIR)/graph_algo_centrality.c \
	$(EXECUTOR_DIR)/graph_algo_components.c \
	$(EXECUTOR_DIR)/graph_algo_betweenness.c \
	$(EXECUTOR_DIR)/graph_algo_closeness.c \
	$(EXECUTOR_DIR)/graph_algo_louvain.c \
	$(EXECUTOR_DIR)/graph_algo_triangle.c \
	$(EXECUTOR_DIR)/graph_algo_astar.c \
	$(EXECUTOR_DIR)/graph_algo_traversal.c \
	$(EXECUTOR_DIR)/graph_algo_similarity.c \
	$(EXECUTOR_DIR)/graph_algo_knn.c \
	$(EXECUTOR_DIR)/graph_algo_eigenvector.c \
	$(EXECUTOR_DIR)/graph_algo_apsp.c

TRANSFORM_OBJS = $(TRANSFORM_SRCS:$(TRANSFORM_DIR)/%.c=$(BUILD_TRANSFORM_DIR)/%.o)
TRANSFORM_OBJS_COV = $(TRANSFORM_SRCS:$(TRANSFORM_DIR)/%.c=$(BUILD_TRANSFORM_DIR)/%.cov.o)
TRANSFORM_OBJS_PIC = $(TRANSFORM_SRCS:$(TRANSFORM_DIR)/%.c=$(BUILD_TRANSFORM_DIR)/%.pic.o)

EXECUTOR_OBJS = $(EXECUTOR_SRCS:$(EXECUTOR_DIR)/%.c=$(BUILD_EXECUTOR_DIR)/%.o)
EXECUTOR_OBJS_COV = $(EXECUTOR_SRCS:$(EXECUTOR_DIR)/%.c=$(BUILD_EXECUTOR_DIR)/%.cov.o)
EXECUTOR_OBJS_PIC = $(EXECUTOR_SRCS:$(EXECUTOR_DIR)/%.c=$(BUILD_EXECUTOR_DIR)/%.pic.o)

# SQLite extension - use .dylib on macOS, .dll on Windows, .so on Linux
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_S),Darwin)
    EXTENSION_LIB = $(BUILD_DIR)/graphqlite.dylib
else ifneq (,$(findstring MINGW,$(UNAME_S)))
    EXTENSION_LIB = $(BUILD_DIR)/graphqlite.dll
else ifneq (,$(findstring MSYS,$(UNAME_S)))
    EXTENSION_LIB = $(BUILD_DIR)/graphqlite.dll
else
    EXTENSION_LIB = $(BUILD_DIR)/graphqlite.so
endif
EXTENSION_OBJ = $(BUILD_DIR)/extension.o

VENDOR_SQLITE_DIR=src
CFLAGS = -Wall -Wextra -O2 -I$(VENDOR_SQLITE_DIR) -Iext/graph/include $(EXTRA_INCLUDES)
EXTENSION_CFLAGS_BASE = -Wall -Wextra -O2 -I$(VENDOR_SQLITE_DIR) -Iext/graph/include
LDFLAGS = $(EXTRA_LIBS) -lsqlite3 -lm

# Extension-specific flags: enable sqlite3ext.h API pointer redirection
EXTENSION_CFLAGS = -DGRAPHQLITE_EXTENSION

GRAPH_ALL_OBJS = $(EXTENSION_OBJ) $(GENERATED_OBJS_PIC) $(PARSER_OBJS_PIC) $(TRANSFORM_OBJS_PIC) $(EXECUTOR_OBJS_PIC)

# SQLite extension shared library (with full parser, transform, and executor)
$(EXTENSION_LIB): $(EXTENSION_OBJ) $(GENERATED_OBJS_PIC) $(PARSER_OBJS_PIC) $(TRANSFORM_OBJS_PIC) $(EXECUTOR_OBJS_PIC) | dirs $(GRAMMAR_HDR)
ifeq ($(UNAME_S),Darwin)
	$(CC) -g -fPIC -dynamiclib $(EXTENSION_OBJ) $(GENERATED_OBJS_PIC) $(PARSER_OBJS_PIC) $(TRANSFORM_OBJS_PIC) $(EXECUTOR_OBJS_PIC) -o $@ -undefined dynamic_lookup
else ifneq (,$(findstring MINGW,$(UNAME_S)))
	$(CC) -shared -static $(EXTENSION_OBJ) $(GENERATED_OBJS_PIC) $(PARSER_OBJS_PIC) $(TRANSFORM_OBJS_PIC) $(EXECUTOR_OBJS_PIC) -o $@ -lsqlite3 -lsystre -ltre -lintl -liconv
else ifneq (,$(findstring MSYS,$(UNAME_S)))
	$(CC) -shared -static $(EXTENSION_OBJ) $(GENERATED_OBJS_PIC) $(PARSER_OBJS_PIC) $(TRANSFORM_OBJS_PIC) $(EXECUTOR_OBJS_PIC) -o $@ -lsqlite3 -lsystre -ltre -lintl -liconv
else
	$(CC) -shared -fPIC $(EXTENSION_OBJ) $(GENERATED_OBJS_PIC) $(PARSER_OBJS_PIC) $(TRANSFORM_OBJS_PIC) $(EXECUTOR_OBJS_PIC) -o $@
endif

# Main application object
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

# Extension object (uses vendored SQLite headers for ABI consistency - no EXTRA_INCLUDES)
$(BUILD_DIR)/extension.o: $(SRC_DIR)/extension.c | dirs
	$(CC) $(EXTENSION_CFLAGS_BASE) $(EXTENSION_CFLAGS) -fPIC -c $< -o $@

# Parser objects (regular build) - need build dir for generated headers
$(BUILD_PARSER_DIR)/%.o: $(PARSER_DIR)/%.c $(GRAMMAR_HDR) | dirs
	$(CC) $(CFLAGS) -I$(GENERATED_DIR) -c $< -o $@

$(BUILD_GENERATED_DIR)/%.o: $(GENERATED_DIR)/%.c $(GRAMMAR_HDR) | dirs
	$(CC) $(CFLAGS) -I$(GENERATED_DIR) -c $< -o $@

# Parser objects (coverage build) - need build dir for generated headers
$(BUILD_PARSER_DIR)/%.cov.o: $(PARSER_DIR)/%.c $(GRAMMAR_HDR) | dirs
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -I$(GENERATED_DIR) -c $< -o $@

$(BUILD_GENERATED_DIR)/%.cov.o: $(GENERATED_DIR)/%.c $(GRAMMAR_HDR) | dirs
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -I$(GENERATED_DIR) -c $< -o $@

$(BUILD_TRANSFORM_DIR)/%.o: $(TRANSFORM_DIR)/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

# Transform objects (coverage build)
$(BUILD_TRANSFORM_DIR)/%.cov.o: $(TRANSFORM_DIR)/%.c | dirs
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

# Executor objects
$(BUILD_EXECUTOR_DIR)/%.o: $(EXECUTOR_DIR)/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

# Executor objects (coverage build)
$(BUILD_EXECUTOR_DIR)/%.cov.o: $(EXECUTOR_DIR)/%.c | dirs
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

# PIC object builds for shared library (uses vendored SQLite headers only - no EXTRA_INCLUDES)
$(BUILD_PARSER_DIR)/%.pic.o: $(PARSER_DIR)/%.c $(GRAMMAR_HDR) | dirs
	$(CC) $(EXTENSION_CFLAGS_BASE) $(EXTENSION_CFLAGS) -fPIC -I$(GENERATED_DIR) -c $< -o $@

$(BUILD_GENERATED_DIR)/%.pic.o: $(GENERATED_DIR)/%.c $(GRAMMAR_HDR) | dirs
	$(CC) $(EXTENSION_CFLAGS_BASE) $(EXTENSION_CFLAGS) -fPIC -I$(GENERATED_DIR) -c $< -o $@

$(BUILD_TRANSFORM_DIR)/%.pic.o: $(TRANSFORM_DIR)/%.c | dirs
	$(CC) $(EXTENSION_CFLAGS_BASE) $(EXTENSION_CFLAGS) -fPIC -c $< -o $@

$(BUILD_EXECUTOR_DIR)/%.pic.o: $(EXECUTOR_DIR)/%.c | dirs
	$(CC) $(EXTENSION_CFLAGS_BASE) $(EXTENSION_CFLAGS) -fPIC -c $< -o $@

dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_PARSER_DIR)
	@mkdir -p $(BUILD_GENERATED_DIR)
	@mkdir -p $(BUILD_TRANSFORM_DIR)
	@mkdir -p $(BUILD_EXECUTOR_DIR)
