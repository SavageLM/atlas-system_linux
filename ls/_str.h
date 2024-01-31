#ifndef _STR_H
#define _STR_H

#include <stdio.h>
#include <stdlib.h>
#include "_ls.h"

/** Prototypes */
int _strlen(const char *s);
char *_strdup(const char *str);
char *_strcat(char *dest, char *src);
void free_list(file_list **files);

#endif