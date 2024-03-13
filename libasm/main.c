#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1	"Holberton"
#define S2	"Holberton School"
#define S3 ""

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    printf(" real :%d mine: %d\n", strcmp(S1, S2), asm_strcmp(S1, S2));
    printf(" real :%d mine: %d\n", strcmp(S3, S1), asm_strcmp(S3, S1));
	assert(strcmp(S1, S2) == asm_strcmp(S1, S2));
    assert(strcmp(S3, S1) == asm_strcmp(S3, S1));

	printf("All good!\n");
	return (EXIT_SUCCESS);
}