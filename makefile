CC=gcc
CFLAGS=-Wall -Wextra -I./src
BUILDDIR=build
BUILDEXE=$(BUILDDIR)/shly
TMPDIR=tmp
TMPEXE=$(TMPDIR)/shly
SRCS=$(wildcard src/*.c)

build: $(BUILDDIR)-dir
	$(CC) $(CFLAGS) -o $(BUILDEXE) cmd/shly.c $(SRCS)
	rm -f $(TMPDIR)/*

run: $(TMPDIR)-dir
	$(CC) $(CFLAGS) -o $(TMPEXE) cmd/shly.c $(SRCS)
	./$(TMPEXE)
	rm -f $(TMPDIR)/*

$(BUILDDIR)-dir:
	mkdir -p $(BUILDDIR)

$(TMPDIR)-dir:
	mkdir -p $(TMPDIR)

clean:
	rm -f $(TMPDIR)/*

.PHONY: build run clean
