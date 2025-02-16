CC=gcc
CFLAGS=-Wall -Wextra
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
BUILDDIR=build
BUILDEXE=$(BUILDDIR)/shly
TMPDIR=tmp
TMPEXE=$(TMPDIR)/shly

build: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BUILDEXE) cmd/shly.c $(OBJECTS)
	rm -f $(TMPDIR)/* $(OBJECTS)

run: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TMPEXE) cmd/shly.c $(OBJECTS)
	./$(TMPEXE)
	rm -f $(TMPDIR)/* $(OBJECTS)

clean:
	rm -f $(TMPDIR)/* $(OBJECTS)

.PHONY: build run clean
