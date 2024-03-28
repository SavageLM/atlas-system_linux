CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
nm = $(patsubst %.c, %.o, $(wildcard nm*.c)) $(LIBS)
objdump = $(patsubst %.c, %.o, $(wildcard objdump*.c)) $(LIBS)

.PHONY: hnm hobjdump clean

hnm: $(nm)
	$(CC) $(CFLAGS) $(0) -o hnm

clean:
	rm -f hnm
	rm -f *.o