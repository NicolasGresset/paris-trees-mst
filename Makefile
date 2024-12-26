# Project Settings
debug ?= 0
test ?= 0
NAME := main
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
LIB_DIR := lib
TESTS_DIR := tests
BIN_DIR := bin
DOXYGEN := doxygen
DOXYFILE := Doxyfile
DOC_DIR := docs

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_LIB_FILES = $(wildcard $(LIB_DIR)/**/*.c)
HEADER_FILES = $(wildcard $(INCLUDE_DIR)/*.h)

# Generate paths for all object files
# transforms src/src1.c into src/src1.o
OBJS := $(patsubst %.c,%.o, $(SRC_FILES) $(SRC_LIB_FILES))

# remove main.o from the previous variable
TEST_OBJS := $(filter-out $(SRC_DIR)/$(NAME).o, $(OBJS))

# transforms tests/main_test.c into tests/main_test.o
CUNIT_OBJS := $(patsubst %.c,%.o, $(wildcard $(TESTS_DIR)/*.c))

# Compiler settings
CC := clang
LINTER := clang-tidy
FORMATTER := clang-format

# Compiler and Linker flags Settings:
# 	-std=gnu17: Use the GNU17 standard
# 	-D _GNU_SOURCE: Use GNU extensions
# 	-D __STDC_WANT_LIB_EXT1__: Use C11 extensions
# 	-Wall: Enable all warnings
# 	-Wextra: Enable extra warnings
# 	-pedantic: Enable pedantic warnings
# 	-lm: Link to libm
CFLAGS := -Wall -Wextra #-pedantic -std=gnu17 -D _GNU_SOURCE -D __STDC_WANT_LIB_EXT1__
LDFLAGS := -lm

ifeq ($(debug), 1)
	CFLAGS := $(CFLAGS) -g -O0
else
	CFLAGS := $(CFLAGS) -Oz
endif

ifeq ($(test), 1)
	CFLAGS := $(CFLAGS) -DTEST_BUILD
	LDFLAGS := $(LDFLAGS) -lcunit
endif

# Targets

# Build executable
# todo add lint as build dependency
$(NAME): format dir $(OBJS)
	@echo "Generating main executable"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $(patsubst %, build/%, $(OBJS))

# Build object files and third-party libraries
$(OBJS): dir $(HEADER_FILES) $(SRC_FILES)
	@mkdir -p $(BUILD_DIR)/$(@D)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ -c $*.c

$(CUNIT_OBJS): dir
	@mkdir -p $(BUILD_DIR)/$(@D)
	@$(CC) $(CFLAGS) -DTEST_BUILD -o $(BUILD_DIR)/$@ -c $*.c

# Run CUnit tests
test: dir $(TEST_OBJS) $(CUNIT_OBJS)
	@echo "Generating cunit test program"
	@$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN_DIR)/$(NAME)_test $(patsubst %, build/%, $(TEST_OBJS)) $(patsubst %, build/%, $(CUNIT_OBJS))
	@valgrind -s --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$(NAME)_test

# Run linter on source directories
lint:
	@$(LINTER) --config-file=.clang-tidy $(SRC_DIR)/* $(INCLUDE_DIR)/*  -- $(CFLAGS)
# $(TESTS_DIR)/*

# Run formatter on source directories
format:
	@$(FORMATTER) -style=file -i $(SRC_DIR)/* $(INCLUDE_DIR)/* 
# $(TESTS_DIR)/*

doc: $(DOXYFILE)
	@echo "Generating documentation"
	$(DOXYGEN) $(DOXYFILE)

# Run valgrind memory checker on executable
check: $(NAME)
	@sudo valgrind -s --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$< --help
	@sudo valgrind -s --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$< --version
	@sudo valgrind -s --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$< -v

# Setup build and bin directories
dir:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Clean build and bin directories
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run bear to generate compile_commands.json
bear:
	@bear -- make $(NAME)

.PHONY: lint format check setup dir clean bear




# il faudrait trouver une meilleure manière pour tester les fonctions internes aux fichiers