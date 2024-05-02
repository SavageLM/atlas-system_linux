#include "multithreading.h"

/**
 * tprintf - Function to print thread ID and a str
 * @format: String to print
 * Return: Always 0
*/

int tprintf(char const *format, ...)
{
	pthread_t tid = pthread_self();

	printf("[%ld] %s", tid, (char *)format);
	return (0);
}
