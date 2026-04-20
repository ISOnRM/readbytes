CC ?= cc
CFLAGS ?= -std=c99 -Wall -Werror -Wpedantic -Wextra -O2

.PHONY: install clean

readbytes: readbytes.c
	$(CC) $(CFLAGS) $^ -o $@

install: readbytes
	install -d -m 700 ~/.local/bin
	install -m 700 $^ ~/.local/bin/$^

clean:
	rm readbytes