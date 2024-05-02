#include "multithreading.h"

/**
 * thread_entry - Function that makes a thread print a str
 * @arg: Address of the string to print
*/

void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
}
