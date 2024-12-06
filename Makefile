CC := gcc
CFLAGS := -Wall -g -Wextra -O3
LDLIBS := -lm
INCLUDE_PATH = ./include
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TEST_DIR = test
TEST_SRC = $(TEST_DIR)/test.c
TEST_BIN = $(TEST_DIR)/test

program   := main
test-program := test-main

test-sources := $(wildcard TEST_DIR/*.c) 
test-objects := $(test-sources:.c=.o)


SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)




$(BINDIR)/$(program): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

doc:
	doxygen Doxyfile

test: $(TEST_BIN)

$(TEST_BIN): $(OBJECTS) $(TEST_SRC)
	@ $(CC) $(CFLAGS) $(LDLIBS) $(OBJECTS) -o $(TEST_BIN) $(TEST_SRC)


.PHONY: clean
clean:
	rm -rf obj/*.o
	rm -f bin/arbres
	rm -f test/test
