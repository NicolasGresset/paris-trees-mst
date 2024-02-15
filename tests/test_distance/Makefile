CC ?= gcc
CFLAGS ?= -Wall -g -ltps -lSDL2 -lSDL2_ttf
LDLIBS ?= -lm
INCLUDE_PATH = ./include

TARGET   =arbres

SRCDIR   = ../../src
OBJDIR   = ../../obj
BINDIR   = ../../bin


SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)


testDist.o: testDist.c $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

testDist: testDist.o $(OBJDIR)/%.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)


.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o
	rm -f ../../bin/arbres
