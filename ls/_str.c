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

/**
 * *_strcat - entry to function
 * @dest: string to be appended
 * @src: string to append
 * Return: Returns pointer to resulting string, dest
 */

char *_strcat(char *dest, char *src)
{
	int c = 0, i = 0;

	while (dest[c] != '\0')
	{
		c++;
	}

	while (src[i] != '\0')
	{
		dest[c] = src[i];
		c++;
		i++;
	}

	dest[c] = '\0';

	return (dest);
}
