#include "signals.h"

/**
 * main - Describes the signal given
 * @argc: Number of arguements
 * @argv: Array of arguements
 * Return: Success or Failure
*/

int main(int argc, char **argv)
{
	int flag, pid = atoi(argv[1]);

	if (argc != 2)
	{
		printf("Usage: %s <PID>", argv[0]);
		return (EXIT_FAILURE);
	}
	flag = kill(pid, 2);
	if (flag != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
