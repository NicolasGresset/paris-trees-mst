CC ?= gcc
CFLAGS ?= -Wall -g -Wextra -O3
LDLIBS ?= -lm
INCLUDE_PATH = ./include

TARGET   =main

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin


SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TEST_DIR = test
TEST_SRC = $(TEST_DIR)/test.c
TEST_BIN = $(TEST_DIR)/test


$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

doc:
	doxygen Doxyfile

test: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_SRC)

.PHONY: clean
clean:
	rm -rf obj/*.o
	rm -f bin/arbres
