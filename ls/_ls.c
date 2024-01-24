#include "_ls.h"
#include "_str.h"

/**
 * main- Entry into the function
 * @argc: count of arguments
 * @argv: array of arguments
 * Return: Always 0
*/

int main(int argc, const char *argv[])
{
	static file_list *flist;
	int flag_1 = 0, flag_a = 0, flag_l = 0, flag_A = 0, i = 1, j = 1;

	if (argc == 1)
	{
		new_ls(".", 0, 0, 0, 0);
	}

	else if (argc > 1)
	{
		for (; j < argc; j++)
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
				addnode(argv[j], &flist);
		}
		file_list *tmp = flist;
		while (tmp)
		{
			new_ls(tmp->name, flag_a, flag_l, flag_1, flag_A);
			tmp = tmp->next;
		}
	}
	if (!flag_1 && !flag_l)
		printf("\n");
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
	struct stat info;
	DIR *dh = opendir(dir);

	if (!dh)
	{
		if (lstat(dir, &info) == 0)
		{
			printf("%s ", dir);
			return;
		}
		else
		{
			perror("./hls");
			exit(EXIT_FAILURE);
		}
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
			if (IS_CURRENT_DIR(res->d_name))
				continue;
			else if (IS_PARENT_DIR(res->d_name))
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

/**
 * addnode - file for adding a node to a list
 * @filename: Name of file or directory
 * @flist: list of files
*/

void addnode(const char *filename, file_list **flist)
{
	file_list *newf = NULL, *tmp = *flist;
	char *fn_copy;

	fn_copy = _strdup(filename);

	newf = malloc(sizeof(file_list));
	if (!newf)
		return;
	newf->name = fn_copy;
	newf->next = NULL;
	if (!*flist)
		*flist = newf;
	else
	{
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = newf;
				return;
			}
			tmp = tmp->next;
		}
	}
}
