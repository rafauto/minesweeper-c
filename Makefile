# Build and run the game with: make && ./minesweeper
CC      ?= gcc
CFLAGS  ?= -std=c99 -Wall -Wextra -O2
TARGET  := minesweeper
SRC     := src/campo_minado.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
