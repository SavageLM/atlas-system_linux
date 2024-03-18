#include "signals.h"

/**
 * current_handler_sigaction - Finds current handler
 * Return: pointer to handler, or NULL
*/

void (*current_handler_sigaction(void))(int)
{
	struct sigaction old_handle;

	if (sigaction(SIGINT, NULL, &old_handle) == -1)
		return (NULL);
	return (old_handle.sa_handler);
}
