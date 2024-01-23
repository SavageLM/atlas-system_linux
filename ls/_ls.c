#include "_ls.h"

/**
 * main- Entry into the function
 * @argc: count of arguments
 * @argv: array of arguments
 * Returns: Always 0
*/

int main(int argc, const char *argv[])
{
	int flag_1 = 0, flag_a = 0, flag_l = 0; flag_A = 0, i = 0;
	char file_name;

	if (argc == 1)
	{
		new_ls(".", 0, 0, 0, 0);
	}

	else if (argc > 1)
	{
		if (argv[1][0] == '-')
		{
			for (i; argv[1][i] != NULL, i++)
			{
				if (argv[1][i] == 1)
					flag_1 = 1;
				else if (argv[1][i] == 'l')
					flag_l = 1;
				else if (argv[1][i] == 'a')
					flag_a = 1;
				else if (argv[1][i] == 'A')
					flag_A = 1;
				else
				{
					/** Error Code goes here*/
				}
			}
			file_name = argv[argc - 1];
		}
		else
			file_name = argv[1];
		new_ls(file_name, flag_1, flag_A, flag_a, flag_l);
	}
	return (0);
}

/**
 * new_ls - Function for printing out directory
 * @dir: directory to print
 * @flag_a: optional flag for hidden files
 * @flag_l: optional flag for long listing format
 * @flag_1: optional flag for one file per line
 * @flag_A: optional flag for amlmost all files
*/

void new_ls(const char *dir, int flag_a, int flag_l, int flag_1, int flag_A)
{
	struct dirent *res = readdir(dh);
	DIR *dh = opendir(dir);

	if (!dh)
	{
		if (errno = ENOENT)
			perror("Directory Doesn't Exist");
		else
			perror("Unable to read directory");
		exit(EXIT_FAILURE);
	}

	while (res)
	{
		if (flag_l)
		{
			continue;
			/** Added in code for -l later*/
		}
		else if (!flag_a && res->d_name[0] == '.')
			continue;
		printf("%s ", res->d_name);
		if (flag_1)
			printf("\n");
	}
}