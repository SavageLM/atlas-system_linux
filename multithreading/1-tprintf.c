#include "multithreading.h"

/**
 * tprintf - Function to print thread ID and a str
 * @format: String to print
 * Return: NULL pointer
*/

int tprintf(char const *format, ...)
{
	pid_t tid = gettid();

	printf("[%d] %s", tid, (char *)format);
	pthread_exit(NULL);
}
