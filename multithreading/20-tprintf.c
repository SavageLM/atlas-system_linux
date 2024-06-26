#include "multithreading.h"

void make_lock(void) __attribute__((constructor));
void break_lock(void) __attribute__((destructor));

pthread_mutex_t lock;

/**
 * tprintf - Function to print a str using mutex
 * @format: Str to be printed
 * Return: Always 0
*/

int tprintf(char const *format, ...)
{
	pthread_t tid = pthread_self();
	va_list arg;

	va_start(arg, format);

	pthread_mutex_lock(&lock);
	printf("[%ld] ", tid);
	vprintf(format, arg);
	va_end(arg);
	pthread_mutex_unlock(&lock);
	return (0);
}

/**
 * make_lock - Constructor for mutex lock
*/
void make_lock(void)
{
	pthread_mutex_init(&lock, NULL);
}

/**
 * break_lock - Destructor for mutex lock
*/
void break_lock(void)
{
	pthread_mutex_destroy(&lock);
}
