#include "_str.h"

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

/**
 * free_list - Function to free a list of files
 * @files: list to free
*/
void free_list(file_list **files)
{
	file_list *tmp = *files;

	if (!*files)
		return;

	while (*files)
	{
		tmp = (*files)->next;
		free((*files)->name);
		free(*files);
		*files = tmp;
	}
	free(*files);
	*files = NULL;
}

/**
 * *_strncpy - entry to function
 * @dest: copied string
 * @src: string to be copied
 * @n: length of src
 * Return: destination of copied string
 */

char *_strncpy(char *dest, const char *src, int n)
{
	int i = 0;

	while (src[i] != '\0')
	{
		if (i < n)
		dest[i] = src[i];

		else
			break;
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
