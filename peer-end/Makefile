# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source Files (Common files for both server and client)
COMMON_SRC_FILES = $(SRC_DIR)/network.c \
                   $(SRC_DIR)/utils.c \
                   $(SRC_DIR)/file_transfer.c \
									 $(SRC_DIR)/tracker_client.c \
                   $(SRC_DIR)/main.c  # Include main.c

# Header files for Dependency Tracking
DEPS = $(INCLUDE_DIR)/peer.h \
       $(INCLUDE_DIR)/network.h \
       $(INCLUDE_DIR)/file_transfer.h \
       $(INCLUDE_DIR)/encryption.h \
       $(INCLUDE_DIR)/auth.h \
       $(INCLUDE_DIR)/utils.h \
			 $(INCLUDE_DIR)/tracker_client.h \
       $(INCLUDE_DIR)/file_utils.h 

# Object files (Generated from source files)
COMMON_OBJ_FILES = $(COMMON_SRC_FILES:.c=.o)

# Output Executable
EXEC = $(BUILD_DIR)/P2PFileSharing  # Single executable for both client & server

# Default target to build the executable
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(COMMON_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(COMMON_OBJ_FILES)

# Rule to compile .c files to .o files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean object files and executable
clean:
	rm -rf $(COMMON_OBJ_FILES) $(EXEC)

# Rule to remove all build files (including the build directory)
distclean: clean
	rm -rf $(BUILD_DIR)

# Create the build Directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean distclean

