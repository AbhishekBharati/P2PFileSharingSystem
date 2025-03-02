# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Iinclude -pthread

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source Files for Tracker Server
TRACKER_SRC_FILES = $(SRC_DIR)/tracker_handler.c \
                    $(SRC_DIR)/tracker_network.c \
                    $(SRC_DIR)/tracker_main.c

# Object files
TRACKER_OBJ_FILES = $(TRACKER_SRC_FILES:.c=.o)

# Output Executable
TRACKER_EXEC = $(BUILD_DIR)/TrackerServer

# Default target to build the tracker server
all: $(TRACKER_EXEC)

$(TRACKER_EXEC): $(TRACKER_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TRACKER_EXEC) $(TRACKER_OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TRACKER_OBJ_FILES) $(TRACKER_EXEC)

.PHONY: all clean

