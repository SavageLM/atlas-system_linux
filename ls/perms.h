#ifndef _PERMS_H
#define _PERMS_H

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

/** Prototypes */
void usr_perms(mode_t mode);
void grp_perms(mode_t mode);
void other_perms(mode_t mode);
char *make_path(const char *dir, char *filename);
int print_flag(const char* file, int p_flag);

#endif