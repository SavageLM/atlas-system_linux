#ifndef _LS_H
#define _LS_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

#define IS_CURRENT_DIR(s) \
		((s)[0] == '.' && !(s)[1])

#define IS_PARENT_DIR(s) \
		((s)[0] == '.' && (s)[1] == '.' && !(s)[2])

/**
 * flist - list to hold file names
 * @name: file name
 * @next: points to next node
*/

typedef struct flist
{
	char *name;
	struct flist *next;
} file_list;


/** Prototypes */
int main(int argc, const char *argv[]);
void new_ls(const char *dir, int flag_a, int flag_l, int flag_1, int flag_A);
void addnode(const char *filename, file_list **flist);

#endif
