#include "signals.h"

/**
 * main - Describes the signal given
 * @argc: Number of arguements
 * @argv: Array of arguements
 * Return: Success or Failure
*/

int main(int argc, char **argv)
{
	int flag;

	if (argc != 2)
	{
		printf("Usage: %s <PID>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	flag = kill(atoi(argv[1]), 2);
	if (flag != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
