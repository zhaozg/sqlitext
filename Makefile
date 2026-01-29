CFLAGS		:=
BIN_PATH	:= bin

SECURE_NAME	:= secure
TARGET_NAME	:= sqlite3
CONVERT_NAME	:= cevfs
VECTOR_NAME	:= vector

ifeq ($(OS),Windows_NT)
	CONVERT_NAME := $(addsuffix .exe,$(CONVERT_NAME))
	SECURE_NAME := $(addsuffix .exe,$(SECURE_NAME))
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
	VECTOR_NAME := $(addsuffix .exe,$(VECTOR_NAME))
endif

SOURCE		:= amalgamation.c

SECURE		:= $(BIN_PATH)/$(SECURE_NAME)
TARGET		:= $(BIN_PATH)/$(TARGET_NAME)
CONVERT		:= $(BIN_PATH)/$(CONVERT_NAME)
VECTOR		:= $(BIN_PATH)/$(VECTOR_NAME)

#LuaJIT auto detect
LUA_VERSION	:= 5.1 #$(shell luajit -e "_,_,v=string.find(_VERSION,'Lua (.+)');print(v)")
LUA_CFLAGS	?= -I/usr/local/include/luajit-2.1 #$(shell $(PKG_CONFIG) luajit --cflags)
LUA_LIBS	?= -L/usr/local/lib -lluajit-5.1 #$(shell $(PKG_CONFIG) luajit --libs)
LUA_LIBDIR	?= /usr/local/lib/lua/5.1 #$(PREFIX)/lib/lua/$(LUA_VERSION)
LUA		:= luajit

default: makedir all

# non-phony targets
$(TARGET):
	$(CC) $(CFLAGS) -DHAVE_READLINE=1 -o $@ $(SOURCE) src/shell.c -lreadline

$(CONVERT):
	$(CC) $(CFLAGS) -DSQLITE_EXT_CEVFS -o $@ $(SOURCE) ext/cevfs/cevfs_build.c -lz

$(SECURE):
	$(CC) $(CFLAGS) -DSQLITE_ENABLE_CEROD=1 -DHAVE_READLINE=1 \
	-o $@ $(SOURCE) src/shell.c -lz -lreadline

$(VECTOR):
	$(CC) $(FLAGS) -DSQLITE_VEC_STATIC -DSQLITE_CORE -DSQLITE_VEC_ENABLE_AVX \
	-mavx -o $@ $(SOURCE) src/shell.c ext/vector/sqlite-vec.c -lz -lreadline

lsqlite3.so:
	$(CC) $(FLAGS) -DSQLITE_VEC_STATIC -DSQLITE_CORE -DSQLITE_VEC_ENABLE_AVX \
	-Isrc $(LUA_CFLAGS) $(LUA_LIBS) \
	-mavx -shared -o lsqlite3.so $(SOURCE) ext/vector/sqlite-vec.c binding/lua/lsqlite3.c

install: lsqlite3.so
	cp -a lsqlite3.so $(LUA_LIBDIR)

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH)

.PHONY: all cevfs

all: $(TARGET) $(CONVERT) $(SECURE) $(VECTOR)

clean:
	@rm -rf bin *.so
