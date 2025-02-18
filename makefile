CC=gcc
CFLAGS=-Wall -Wextra -I./src
BUILDDIR=build
BUILDEXE=$(BUILDDIR)/shly
TMPDIR=tmp
TMPEXE=$(TMPDIR)/shly
SRCS=$(wildcard src/*.c)
TESTSRCS=tests/test_input.c tests/test_builtins.c

build: $(BUILDDIR)-dir
	$(CC) $(CFLAGS) -o $(BUILDEXE) cmd/shly.c $(SRCS)
	rm -f $(TMPDIR)/*

run: $(TMPDIR)-dir
	$(CC) $(CFLAGS) -o $(TMPEXE) cmd/shly.c $(SRCS)
	./$(TMPEXE)
	rm -f $(TMPDIR)/*

test: $(TMPDIR)-dir
	@for test in $(TESTSRCS); do \
		$(CC) $(CFLAGS) -o $(TMPEXE) $$test $(SRCS); \
		./$(TMPEXE); \
	done

format:
	clang-format -i src/*.c src/*.h cmd/*.c tests/*.c

$(BUILDDIR)-dir:
	mkdir -p $(BUILDDIR)

$(TMPDIR)-dir:
	mkdir -p $(TMPDIR)

clean:
	rm -f $(TMPDIR)/*
 
.PHONY: build run clean
