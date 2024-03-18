#include "signals.h"

/**
 * sigint_handler - determines how SIGINT is handled
 * @sig: Signal Received
*/

void sigint_handler(int sig)
{
	printf("Gotcha! [%d]\n", sig);
}

/**
 * handle_signal - function for handling SIGINT
 * Return: 0 on success, -1 on failure
*/

int handle_signal(void)
{
	return (signal(SIGINT, sigint_handler) == SIG_ERR ? -1 : 0);
}
