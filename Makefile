# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -std=c11

# Source directory
SRC_DIR = Simple-BlackJack/src

# Source files
SRCS = $(SRC_DIR)/deck.c $(SRC_DIR)/functions.c $(SRC_DIR)/main.c $(SRC_DIR)/score.c

# Output executable
TARGET = SimpleBJ

# Build target
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Run target with UTF-8 encoding for Windows
run: $(TARGET)
	.\$(TARGET)

# Clean target
.PHONY: clean
clean:
	rm -f $(TARGET)