#include "print.h"

/**
 * print_flag - function for controlling print format
 * @file: file to print
 * @p_flag: flag for format
 * @flag_1: flag for 1 item per line
*/

void print_flag(const char* file, int p_flag, int flag_1)
{
	if (!p_flag)
	{
		printf("%s", file);
		if (flag_1)
			printf("\n");
	}
	else if (p_flag && flag_1)
		printf("%s\n", file);
	else if (p_flag)
		printf("  %s", file);
}

/**
 * dirprint_flag - function for controlling directory print format
 * @file: directory name to print
 * @d_flag: flag for format
*/

void dirprint_flag(const char* file, int d_flag)
{
	if (!d_flag)
		printf("%s:\n", file);
	else if (d_flag)
		printf("\n\n%s:\n", file);
}

/**
 * print_error - prints a message when error occurs
 * @prog: Program that called function
 * @file: file trying to access
 * @error: errno error that occured
*/

void print_error(const char* prog, const char* file, int error)
{
	if (error == 2)
		fprintf(
			stderr,
			"%s: cannot access %s: No such file or directory\n", prog, file
		);
	else if (error == 13)
		fprintf(
			stderr,
			"%s: cannot open directory %s: Permission denied\n", prog, file
		);
}
