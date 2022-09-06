CFLAGS		:=
BIN_PATH	:= bin

SECURE_NAME	:= secure
TARGET_NAME	:= sqlite3
CONVERT_NAME	:= cevfs

ifeq ($(OS),Windows_NT)
	CONVERT_NAME := $(addsuffix .exe,$(CONVERT_NAME))
	SECURE_NAME := $(addsuffix .exe,$(SECURE_NAME))
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif

SOURCE		:= amalgamation.c

SECURE		:= $(BIN_PATH)/$(SECURE_NAME)
TARGET		:= $(BIN_PATH)/$(TARGET_NAME)
CONVERT		:= $(BIN_PATH)/$(CONVERT_NAME)

default: makedir all

# non-phony targets
$(TARGET):
	$(CC) $(CFLAGS) -DHAVE_READLINE=1 -o $@ $(SOURCE) src/shell.c -lreadline

$(CONVERT):
	$(CC) $(CFLAGS) -DSQLITE_EXT_CEVFS -o $@ $(SOURCE) ext/cevfs/cevfs_build.c -lz

$(SECURE):
	$(CC) $(CFLAGS) -DSQLITE_ENABLE_CEROD=1 -DHAVE_READLINE=1 \
	-o $@ $(SOURCE) src/shell.c -lz -lreadline

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH)

.PHONY: all cevfs

all: $(TARGET) $(CONVERT) $(SECURE)

clean:
	@rm -rf bin
