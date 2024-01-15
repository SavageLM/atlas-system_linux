#ifndef _GETLINE_H_
#define _GETLINE_H_

#define READ_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * struct fbuf- node for holding buffer info
 * @fd: file descriptor
 * @buffer: holds text that has been read
 * @buff_bytes: Size of buffer
 * @pos: position of cursor in buffer
 * @flag: flag for newline character
 * @next: points to next nore or NULL
*/

typedef struct fbuf
{
	int fd;
	char *buffer;
	ssize_t buff_bytes;
	size_t pos;
	size_t flag;
	struct fbuf *next;
}file_buf;

/*Prototypes*/
char *_getline(const int fd);
file_buf *node_find(file_buf **list, int fd);
file_buf *add_node(file_buf **list, int fd);
char *reader(int fd);
char *next_line(file_buf *file);
#endif
