#ifndef _PRINT_H
#define _PRINT_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/** Prototypes */
void print_flag(const char* file, int p_flag, int flag_1);
void dirprint_flag(const char* file, int d_flag);
void print_error(const char* prog, const char* file, int error);

#endif