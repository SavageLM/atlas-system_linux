/* Description: `asm_strlen("Holberton School")` */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1	"Holberton School"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	assert(strlen(S1) == asm_strlen(S1));

	printf("All good!\n");
	return (EXIT_SUCCESS);
}