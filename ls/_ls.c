#include "_ls.h"

/**
 * main- Entry into the function
 * @argc: count of arguments
 * @argv: array of arguments
 * Returns: Always 0
*/

int main(int argc, const char *argv[])
{
	int flag_1 = 0, flag_a = 0, flag_l = 0, flag_A = 0, i = 1, j = 1;
	const char *file_name;

	if (argc == 1)
	{
		new_ls(".", 0, 0, 0, 0);
	}

	else if (argc > 1)
	{
		for (; j <= argc; j++)
		{
			if (argv[j][0] == '-')
			{
				for (; argv[j][i] != '\0'; i++)
				{
					if (argv[j][i] == 1)
						flag_1 = 1;
					else if (argv[j][i] == 'l')
						flag_l = 1;
					else if (argv[j][i] == 'a')
						flag_a = 1;
					else if (argv[j][i] == 'A')
						flag_A = 1;
					else if (argv[j][i] == '1')
						flag_1 = 1;
					else
					{
						perror("./hls: Option not supported");
					}
				}
			}
			else
				file_name = argv[j];
		}
		new_ls(file_name, flag_a, flag_l, flag_1, flag_A);
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
	struct dirent *res;
	DIR *dh = opendir(dir);

	if (!dh)
	{
		if (errno == ENOENT)
			perror("./hls: ");
		else
			perror("Unable to read directory");
		exit(EXIT_FAILURE);
	}

	while ((res = readdir(dh)))
	{
		if (flag_l)
		{
			continue;
			/** Added in code for -l later*/
		}
		else if (flag_A)
		{
			if (res->d_name[0] == '.' && res->d_name[1] == '\0')
				continue;
			else if (res->d_name[1] == '.' && res->d_name[2] == '\0')
				continue;
			printf("%s ", res->d_name);
		}
		else if (!flag_a)
		{
			if (res->d_name[0] == '.')
				continue;
			printf("%s ", res->d_name);
		}
		else
			printf("%s ", res->d_name);
		if (flag_1)
			printf("\n");
	}
	closedir(dh);
}
