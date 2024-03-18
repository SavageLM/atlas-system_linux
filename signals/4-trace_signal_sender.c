#include "signals.h"

/**
 * find_pid - finds pid of process that sent SIGQUIT
 * @sig: signal received
 * @handle: struct holding handler info
 * @context: IDK what it does, but I need it to compile
*/

void find_pid(int sig, siginfo_t *handle, void *context)
{
	printf("SIGQUIT sent by %d\n", handle->si_pid);
	fflush(stdout);
	(void)sig;
	(void)context;
}

/**
 * trace_signal_sender - sets a handler for SIGQUIT
 * Return: 0 on success, or -1
*/

int trace_signal_sender(void)
{
	struct sigaction handle;

	handle.sa_flags = SA_SIGINFO;
	handle.sa_sigaction = find_pid;
	return (sigaction(SIGQUIT, &handle, NULL));
}
