CC = /usr/local/opt/llvm/bin/clang
INCLUDES = -Iinclude
LIBS = -Llib -lhex -ltesting-logger
CFLAGS = -g -Wall -Wextra -pedantic -std=c17 -Wno-unused-command-line-argument -std=c17 $(INCLUDES) $(LIBS)

SRC_FILES = sha256 big-uint
OBJ_FILES = $(addprefix obj/,$(SRC_FILES:=.o))

CYAN =\x1b[36m
WHITE=\x1b[0m

MAIN = main benchmark sha2
MAIN_BINS = $(addprefix bin/,$(MAIN))
TEST_BINS = $(addprefix bin/test-, $(SRC_FILES))

all: $(MAIN_BINS) $(TEST_BINS)

# Directory targets
obj:
	mkdir obj
bin:
	mkdir bin

# Binary targets
bin/%: main/%.c $(OBJ_FILES) | bin
	$(CC) $(CFLAGS) $^ -o $@

bin/test-%: tests/test-%.c $(OBJ_FILES) | bin
	$(CC) $(CFLAGS) $^ -o $@

# Object targets
obj/%.o: src/%.c | obj
	$(CC) -c $(CFLAGS) $^ -o $@

obj/%.o: main/%.c | obj
	$(CC) -c $(CFLAGS) $^ -o $@

obj/%.o: tests/%.c | obj
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf bin
	rm -rf obj

test: $(TEST_BINS)
	@echo && for f in $(TEST_BINS); do echo "$(CYAN)$$f$(WHITE)"; ASAN_OPTIONS=detect_leaks=1 $$f; echo; done

memcheck:
	ASAN_OPTIONS=detect_leaks=1 ./bin/main

.SECONDARY: 
