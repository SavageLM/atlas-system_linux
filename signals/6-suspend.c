#include "signals.h"

/**
 * find_pid - finds pid of process that sent SIGQUIT
 * @sig: signal received
*/

void sig_catch(int sig)
{
	printf("Caught %d\n", sig);
	fflush(stdout);
}

/**
 * main - entry to program
 * Return: 0 on success, -1 on fail
*/

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	set_handler();
	pause();
	printf("Signal received\n");
	return (EXIT_SUCCESS);
}

/**
 * set_handler - sets SIGINT handler, waits for s
 * Return: 0 on success, -1 on fail
*/

int set_handler(void)
{
	struct sigaction handle;

	handle.sa_handler = sig_catch;
	return (sigaction(SIGINT, &handle, NULL));
}
