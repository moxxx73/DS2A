CC = $(shell which gcc)
LD = $(shell which ld)
CFLAGS = -Wall -Wextra -fstack-protector
LDFLAGS = -lc -shared -z relro -z now

CWD = $(shell pwd)
SRC_PATH = $(CWD)/src
INCL_PATH = $(CWD)/include
BUILD_PATH = $(CWD)/build

SRC_FILES = $(wildcard $(SRC_PATH)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

.PHONY: clean all

all: $(OBJ_FILES)
	$(LD) $(LDFLAGS) $(OBJ_FILES) -o $(BUILD_PATH)/libds2a.so

$(OBJ_FILES): $(BUILD_PATH)/%.o : $(SRC_PATH)/%.c $(BUILD_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCL_PATH)

$(BUILD_PATH):
	mkdir -p $@

clean:
	rm -rf $(BUILD_PATH)
