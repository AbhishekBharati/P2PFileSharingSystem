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
									 $(SRC_DIR)/file_transfer.c

# Header files for Dependency Tracking
DEPS = $(INCLUDE_DIR)/peer.h \
       $(INCLUDE_DIR)/network.h \
       $(INCLUDE_DIR)/file_transfer.h \
       $(INCLUDE_DIR)/encryption.h \
       $(INCLUDE_DIR)/auth.h \
       $(INCLUDE_DIR)/utils.h \
       $(INCLUDE_DIR)/file_utils.h

# Object files (Generated from source files)
COMMON_OBJ_FILES = $(COMMON_SRC_FILES:.c=.o)

# Output Executable
EXEC = $(BUILD_DIR)/P2PFileSharing

# Additional Executables for server and client
SERVER_SRC = $(SRC_DIR)/server.c
CLIENT_SRC = $(SRC_DIR)/client.c

SERVER_EXEC = $(BUILD_DIR)/P2PFileServer
CLIENT_EXEC = $(BUILD_DIR)/P2PFileClient

# Default target to build the executables
all: $(SERVER_EXEC) $(CLIENT_EXEC)

# Rule to create the server executable (server only gets its main function)
$(SERVER_EXEC): $(SRC_DIR)/server.o $(COMMON_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(SERVER_EXEC) $(SRC_DIR)/server.o $(COMMON_OBJ_FILES)

# Rule to create the client executable (client gets main from main.c)
$(CLIENT_EXEC): $(SRC_DIR)/client.o $(COMMON_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(CLIENT_EXEC) $(SRC_DIR)/client.o $(COMMON_OBJ_FILES)

# Rule to compile .c files to .o files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean object files and executable
clean:
	rm -rf $(COMMON_OBJ_FILES) $(EXEC) $(SERVER_EXEC) $(CLIENT_EXEC)

# Rule to remove all build files (including the build directory)
distclean: clean
	rm -rf $(BUILD_DIR)

# Create the build Directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean distclean

