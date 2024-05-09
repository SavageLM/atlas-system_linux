#include "multithreading.h"

/**
 * prime_factors - factors a number into a list of prime factors
 * @s: string representation of the number to factor
 * Return: list_t of prime factors
 **/
list_t *prime_factors(char const *s)
{
	unsigned long num;
	unsigned long *tmp, factor = 2;
	list_t *list;

	list = malloc(sizeof(list_t));
	if (!list || !s)
		return (NULL);
	num = strtoul(s, NULL, 10);
	list_init(list);
	while (factor * factor <= num)
	{
		while (num % factor == 0)
		{
			tmp = malloc(sizeof(unsigned long));
			*tmp = factor;
			list_add(list, (void *)tmp);
			num /= factor;
		}

		factor += 1 + (factor != 2);
	}

	if (num >= 2)
	{
		tmp = malloc(sizeof(unsigned long));
		*tmp = num;
		list_add(list, (void *)tmp);
	}
	return (list);
}
