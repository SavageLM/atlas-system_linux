#include "_str.h"

/**
 * _strdup- entry to function
 * @str: str to copy
 * Return: returns pointer to new string memory or NULL on failure.
 */

char *_strdup(const char *str)
{
	char *copy;
	int i, j;

	if (str == NULL)
		return (NULL);

	j = _strlen(str);

	copy = malloc(sizeof(char) * j + 1);

	if (copy == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		copy[i] = str[i];

	return (copy);
}

/**
 * _strlen - entry to function
 * @s: string to be counted
 * Return: returns string length
 */

int _strlen(const char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}

	return (len);
}
