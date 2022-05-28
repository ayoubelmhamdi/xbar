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
# not tested yet for main.c and test.c
LIBDIR=lib
LIB=$(LIBDIR)/afile.a

$(LIBDIR):
	@mkdir -pv $@


$(OBJ)/bin:
	mkdir -pv $@

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -pv build
	@mkdir -pv bin
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rv build/*


# TEST
TEST=test
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/%, $(TESTS))

$(TEST)/bin/%: $(TEST)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion

$(TEST)/bin:
	mkdir -p $@

test: $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS);do ./$$test ;done

# release
release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean
release: $(BIN)
