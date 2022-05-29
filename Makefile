CC=gcc
CFLAGS=-g -Wall -lcriterion
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
TEST2=unit_tests

TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/%, $(TESTS))

$(TEST)/bin:
	mkdir -p $@

$(TESTBINS)/bin: $(TEST)/%.c
	echo $(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion
	# @$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion

test: $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS);do ./$$test ;done

tests_run:
	@mkdir -p bin
	@$(CC) -c test/*.c
	@echo $(CC) *.o -lcriterion -lgcov -o bin/$(TEST2)
	@$(CC) *.o -lcriterion -lgcov -o bin/$(TEST2)
	@echo 'msg'
	@rm -f *.o
	@./bin/$(TEST2)

# release
release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean
release: $(BIN)
