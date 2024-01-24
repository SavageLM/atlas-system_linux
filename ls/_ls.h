#ifndef _LS_H
#define _LS_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

/** Prototypes */
int main(int argc, const char *argv[]);
void new_ls(const char *dir, int flag_a, int flag_l, int flag_1, int flag_A);

#endif
