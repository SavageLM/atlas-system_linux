#ifndef _LS_H
#define _LS_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>


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
int new_ls(const char *dir, int flag_a, int flag_l, int flag_1, int flag_A, int count);
void addnode(const char *filename, file_list **flist);
void flag_checker(int argc, const char *argv[]);
void l_option(const char *dir, char *filename);

#endif
