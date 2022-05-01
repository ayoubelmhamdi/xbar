CC=gcc
CFLAGS=-g -Wall
SRC=src
OBJ=build
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main

all:$(BIN)

$(BIN): $(OBJS)
	@mkdir -p build
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r build/*

release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean
release: $(BIN)
