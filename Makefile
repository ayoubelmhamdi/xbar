CC=gcc
CFLAGS=-g -Wall -lcriterion

OBJ=build
OBJ2=build

SRC=src
SRC2=lib

SRCS=$(wildcard $(SRC)/*.c)
SRCS2=$(wildcard $(SRC2)/*.c)

OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
OBJS2=$(patsubst $(SRC2)/%.c, $(OBJ2)/%.o, $(SRCS2))


# main
BINDIR=bin
BIN=bin/main
all:$(BIN)


$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -pv build
	@mkdir -pv bin
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ2)/%.o: $(SRC2)/%.c
	@mkdir -pv build
	@mkdir -pv bin
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS) $(OBJS2)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS2) -o $@

clean:
	@$(RM) -rv build/*

purge:
	@$(RM) -rv bin build


# TEST
TEST=test
TEST2=unit_tests

TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/%, $(TESTS))

$(TEST)/bin:
	mkdir -p $@

$(TESTBINS)/bin: $(TEST)/%.c
	@# echo $(CC) $(CFLAGS) $< $(OBJS) -o $@
	@$(CC) $(CFLAGS) $< $(OBJS) -o $@ 

test: $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS);do ./$$test ;done

tests_run:
	@mkdir -p bin
	@$(CC) -c test/*.c
	@echo $(CC) *.o -lcriterion -lgcov -o bin/$(TEST2)
	@$(CC) *.o -lcriterion -lgcov -o bin/$(TEST2)
	@echo 'msg'
	@rm -f *.o
	@echo 'sleep' && sleep 3 && clear
	@./bin/$(TEST2) || sleep 4

# release
release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean
release: $(BIN)
