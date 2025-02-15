CC=gcc
CFLAGS=-Wall -Wextra
TMPEXE=shly.tmp

build: main.c
	$(CC) $(CFLAGS) -o shly main.c

run: main.c
	$(CC) $(CFLAGS) -o $(TMPEXE) main.c
	./$(TMPEXE)
	rm -f $(TMPEXE)

clean:
	rm -f shly $(TMPEXE)

.PHONY: run clean-temp
