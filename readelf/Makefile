CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
0 = $(patsubst %.c, %.o, $(wildcard 0-*.c)) $(LIBS)
1 = $(patsubst %.c, %.o, $(wildcard 1-*.c)) $(LIBS)
2 = $(patsubst %.c, %.o, $(wildcard 2-*.c)) $(LIBS)

.PHONY: 0-hreadelf 1-hreadelf 2-hreadelf clean

0-hreadelf: $(0)
	$(CC) $(CFLAGS) $(0) -o 0-hreadelf

1-hreadelf: $(1)
	$(CC) $(CFLAGS) $(1) -o 1-hreadelf

2-hreadelf: $(2)
	$(CC) $(CFLAGS) $(2) -o 2-hreadelf

clean:
	rm -f *-hreadelf
	rm -f *.o