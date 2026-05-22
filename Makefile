BIN_PATH	:= bin

SECURE_NAME	:= secure
TARGET_NAME	:= sqlite3
CONVERT_NAME	:= cevfs
VECTOR_NAME	:= vector
GRAPH_NAME      := graph

OS		:= $(shell uname)
LUA		:= luajit
PKG_CONFIG	:= pkg-config

ifeq ($(OS),Windows_NT)
	SECURE_NAME := $(addsuffix .exe,$(SECURE_NAME))
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
	VECTOR_NAME := $(addsuffix .exe,$(VECTOR_NAME))
	CONVERT_NAME := $(addsuffix .exe,$(CONVERT_NAME))
	GRAPH_NAME := $(addsuffix .exe,$(GRAPH_NAME))
endif

ifeq ($(OS),Darwin)
	export PKG_CONFIG_PATH := /usr/local/lib/pkgconfig
endif

SOURCE		:= amalgamation.c

SECURE		:= $(BIN_PATH)/$(SECURE_NAME)
TARGET		:= $(BIN_PATH)/$(TARGET_NAME)
CONVERT		:= $(BIN_PATH)/$(CONVERT_NAME)
VECTOR		:= $(BIN_PATH)/$(VECTOR_NAME)
GRAPH           := $(BIN_PATH)/$(GRAPH_NAME)

#LuaJIT auto detect
LUA_VERSION	:= 5.1 #$(shell luajit -e "_,_,v=string.find(_VERSION,'Lua (.+)');print(v)")
LUA_CFLAGS	?= $(shell $(PKG_CONFIG) $(LUA) --cflags)
LUA_LIBS	?= $(shell $(PKG_CONFIG) $(LUA) --libs)
LUA_LIBDIR	?= $(shell $(PKG_CONFIG) $(LUA) --variable=INSTALL_LMOD)


default: makedir all

include graph.mk

# non-phony targets
$(TARGET):
	$(CC) $(CFLAGS) -DHAVE_READLINE=1 -o $@ $(SOURCE) src/shell.c -lreadline

$(CONVERT):
	$(CC) $(CFLAGS) -DSQLITE_EXT_CEVFS -o $@ $(SOURCE) ext/cevfs/cevfs_build.c -lz

$(SECURE):
	$(CC) $(CFLAGS) -DSQLITE_ENABLE_CEROD=1 -DHAVE_READLINE=1 \
	-o $@ $(SOURCE) src/shell.c -lz -lreadline

$(VECTOR):
	$(CC) $(CFLAGS) -DSQLITE_VEC_STATIC -DSQLITE_CORE -DSQLITE_VEC_ENABLE_AVX \
	-mavx2 -o $@ $(SOURCE) src/shell.c ext/vector/sqlite-vec.c -lz -lreadline

$(GRAPH):
	$(CC) $(CFLAGS) -DGRAPHQLITE_EXTENSION \
	-o $@ $(SOURCE) ext/graph/main.c ext/graph/extension.c -lz -lreadline

lsqlite3.so: $(GRAPH_ALL_OBJS) ext/vector/sqlite-vec.c binding/lua/lsqlite3.c
	$(CC) $(CFLAGS) -DSQLITE_VEC_STATIC -DSQLITE_CORE -DSQLITE_VEC_ENABLE_AVX \
	-Isrc $(LUA_CFLAGS) $(LUA_LIBS) -mavx2 -shared -o lsqlite3.so \
	$(SOURCE) ext/vector/sqlite-vec.c binding/lua/lsqlite3.c \
	-DSQLITE_GRAPH_STATIC $(GRAPH_ALL_OBJS)

install: lsqlite3.so
	cp -a lsqlite3.so $(LUA_LIBDIR)

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH)

.PHONY: all

all: $(TARGET) $(CONVERT) $(SECURE) $(VECTOR) lsqlite3.so

clean:
	@rm -rf bin *.so
