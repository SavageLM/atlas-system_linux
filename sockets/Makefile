CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
0 = $(0-todo_api.c)
1 = $(1-todo_api.c)
2 = $(2-todo_api.c)
3 = $(3-todo_api.c)
4 = $(4-todo_api.c)
5 = $(5-todo_api.c)

.PHONY: todo_api_0 todo_api_1 todo_api_2 todo_api_3 todo_api_4 todo_api_5 clean

todo_api_0: $(0)
	$(CC) $(CFLAGS) 0-todo_api.c -o todo_api_1

todo_api_1: $(1)
	$(CC) $(CFLAGS) $(1) -o todo_api_1

todo_api_2: $(2)
	$(CC) $(CFLAGS) $(2) -o todo_api_2

todo_api_3: $(3)
	$(CC) $(CFLAGS) $(3) -o todo_api_3

todo_api_4: $(4)
	$(CC) $(CFLAGS) $(4) -o todo_api_4

todo_api_5: $(5)
	$(CC) $(CFLAGS) $(5) -o todo_api_5

clean:
	rm -f *todo_api_*
	rm -f *.o