CC=gcc
CFLAGS=-g -Wall
SRC=src
OBJ=build
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))


# main
BINDIR=bin
BIN=$(BINDIR)/main
all:$(BIN)


# lib
LIBDIR=lib
LIB=$(LIBDIR)/afile.a

$(LIBDIR):
	mkdir -p $@


$(OBJ)/bin:
	mkdir -p $@

$(BIN): $(OBJS)
	@mkdir -p build
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r build/*


# TEST
TEST=test
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/%, $(TESTS))

$(TEST)/bin/%: $(TEST)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion

$(TEST)/bin:
	mkdir -p $@

test: $(LIB) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS);do ./$$test ;done

# release
release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean
release: $(BIN)
