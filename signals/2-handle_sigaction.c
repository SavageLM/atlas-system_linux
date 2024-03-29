#include "signals.h"

/**
 * sigint_handler - handles SIGINT
 * @sig: signal received
*/

void sigint_handler(int sig)
{
	printf("Gotcha! [%d]\n", sig);
	fflush(stdout);
}

/**
 * handle_sigaction - sets a handler for SIGINT
 * Return: 0 on success, or -1
*/

int handle_sigaction(void)
{
	struct sigaction handle;

	handle.sa_handler = sigint_handler;
	return (sigaction(SIGINT, &handle, NULL));
}
