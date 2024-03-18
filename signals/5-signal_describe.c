#include "signals.h"

/**
 * main - Describes the signal given
 * @argc: Number of arguements
 * @argv: Array of arguements
 * Return: Success or Failure
*/

int main(int argc, char **argv)
{
	int arg = atoi(argv[1]);

	if (argc != 2)
	{
		printf("Usage %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (strsignal(arg))
		printf("%d: %s\n", arg, strsignal(arg));
	else
		printf("%d: %s %d\n", arg, strsignal(arg), arg);
	return (EXIT_SUCCESS);
}
