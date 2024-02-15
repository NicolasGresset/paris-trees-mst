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


arbres: arbres.o $(OBJDIR)/options.o $(OBJDIR)/fonctions.o $(OBJDIR)/parse.o $(OBJDIR)/algo.o $(OBJDIR)/restrictiveOptions.o $(OBJDIR)/manageSIGINT.o $(OBJDIR)/display.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

arbres.o: $(SRCDIR)/arbres.c $(SRCDIR)/options.c $(SRCDIR)/fonctions.c $(SRCDIR)/parse.c $(SRCDIR)/algo.c $(SRCDIR)/restrictiveOptions.c $(SRCDIR)/manageSIGINT.c $(SRCDIR)/display.c 
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)


testBinary.o: testBinary.c $(SRCDIR)/options.c $(SRCDIR)/fonctions.c $(SRCDIR)/parse.c $(SRCDIR)/algo.c $(SRCDIR)/restrictiveOptions.c $(SRCDIR)/manageSIGINT.c $(SRCDIR)/display.c 
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

testBinary: testBinary.o $(OBJDIR)/options.o $(OBJDIR)/fonctions.o $(OBJDIR)/parse.o $(OBJDIR)/algo.o $(OBJDIR)/restrictiveOptions.o $(OBJDIR)/manageSIGINT.o $(OBJDIR)/display.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)


.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o
	rm -f ../../bin/arbres
