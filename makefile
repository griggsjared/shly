CC=gcc
CFLAGS=-Wall -Wextra
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
TMPEXE=shly.tmp

build: $(OBJECTS)
	$(CC) $(CFLAGS) -o shly $(OBJECTS)

run: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TMPEXE) $(OBJECTS)
	./$(TMPEXE)
	rm -f $(TMPEXE)

clean:
	rm -f shly $(TMPEXE)

.PHONY: run clean-temp
