CC=gcc
CFLAGS=-g -Wall
OBJS=build/a.o build/b.o
BIN=build/bin/main

all:$(BIN)

build/bin/main: $(OBJS)
	mkdir -p build/bin
	$(CC) $(CFLAGS) $(OBJS) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r build/*
