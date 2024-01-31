#include "_ls.h"
#include "_str.h"

/**
 * usr_perms - searches stat for user permissions
 * @mode: permissions to check
*/

void usr_perms(mode_t mode)
{
	if (S_ISDIR(mode))
		printf("d");
	else
		printf("-");
	
	if (mode & S_IRUSR)
		printf("r");
	else
		printf("-");
	
	if (mode & S_IWUSR)
		printf("w");
	else
		printf("-");
	
	if (mode & S_IXUSR)
		printf("x");
	else
		printf("-");
}

/**
 * grp_perms - searches stat for user permissions
 * @mode: permissions to check
*/

void grp_perms(mode_t mode)
{
	if (mode & S_IRGRP)
		printf("r");
	else
		printf("-");
	
	if (mode & S_IWGRP)
		printf("w");
	else
		printf("-");
	
	if (mode & S_IXGRP)
		printf("x");
	else
		printf("-");
}

/**
 * other_perms - searches stat for user permissions
 * @mode: permissions to check
*/

void other_perms(mode_t mode)
{
	if (mode & S_IROTH)
		printf("r");
	else
		printf("-");
	
	if (mode & S_IWOTH)
		printf("w");
	else
		printf("-");
	
	if (mode & S_IXOTH)
		printf("x");
	else
		printf("-");
}

/**
 * make_path - Function to make a file path
 * @dir: directory name
 * @file: file name
 * Return: returns a string containing file path
*/

char *make_path(char *dir, char *filename)
{
	char *filepath = NULL;

	filepath = malloc(sizeof(char) * (_strlen(dir) + _strlen(filename) + 2));
	if (!filepath)
		return (NULL);
	filepath[0] = '\0';
	_strcat(filepath, dir);
	if (filepath[_strlen(dir) - 1] == '/')
		filepath[_strlen(dir) - 1] = '\0';
	_strcat(filepath, "/");
	_strcat(filepath, filename);
	return (filepath);
}

/**
 * print_flag - function for controlling print format
 * @file: file to print
 * @p_flag: flag for format
*/

int print_flag(const char* file, int p_flag)
{
	if (p_flag)
		printf(" %s", file);
	else
	{
		printf("%s", file);
		p_flag = 1;
		}
		return (p_flag);
}
