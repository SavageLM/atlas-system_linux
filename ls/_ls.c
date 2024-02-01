#include "_ls.h"
#include "_str.h"
#include "perms.h"
#include "print.h"

int flag_1 = 0, flag_a = 0, flag_l = 0, flag_A = 0;

/**
 * main- Entry into the function
 * @argc: count of arguments
 * @argv: array of arguments
 * Return: Always 0
*/

int main(int argc, const char *argv[])
{
	static file_list *flist, *tmp;
	int i = 1, err_catch = 0, count = 0;

	if (argc == 1)
		new_ls(".", 0, 0, 0, 0, 0);
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			flag_checker(argc, argv);
			err_catch = new_ls(".", flag_a, flag_l, flag_1, flag_A, count);
			if (err_catch)
				print_error(argv[0], ".", err_catch);
		}
		else
		{
			err_catch = new_ls(argv[1], 0, 0, 0, 0, 0);
			if (err_catch)
				print_error(argv[0], argv[1], err_catch);
		}
	}
	else if (argc > 2)
	{
		for (; i < argc; i++)
		{
			if (argv[i][0] == '-')
				flag_checker(argc, argv);
			else
			{
				addnode(argv[i], &flist);
				count++;
			}
		}
		tmp = flist;
		while (tmp)
		{
			err_catch = new_ls(tmp->name, flag_a, flag_l, flag_1, flag_A, count);
			if (err_catch)
				print_error(argv[0], tmp->name, err_catch);
			tmp = tmp->next;
		}
		free_list(&flist);
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
 * Return: 0 on success, errno on error
*/

int new_ls(const char *dir, int flag_a, int flag_l, int flag_1, int flag_A, int count)
{
	int p_flag = 0, d_flag = 0;
	struct dirent *res;
	struct stat info;
	DIR *dh = opendir(dir);

	if (!dh)
	{
		if (lstat(dir, &info) != -1)
		{
			printf("%s", dir);
			return (0);
		}
		else
			return (2);
	}
	if (count > 1)
	{
		dirprint_flag(dir, d_flag);
		d_flag = 1;
	}
	while ((res = readdir(dh)))
	{
		if (flag_A)
		{
			if (IS_CURRENT_DIR(res->d_name))
				continue;
			else if (IS_PARENT_DIR(res->d_name))
				continue;
			if (flag_l)
				l_option(dir, res->d_name);
			else
			{
				print_flag(res->d_name, p_flag, flag_1);
				p_flag = 1;
			}
		}
		else if (!flag_a)
		{
			if (res->d_name[0] == '.')
				continue;
			if (flag_l)
				l_option(dir, res->d_name);
			else
			{
				print_flag(res->d_name, p_flag, flag_1);
				p_flag = 1;
			}
		}
		else
			{
				if (flag_l)
					l_option(dir, res->d_name);
				else
				{
					print_flag(res->d_name, p_flag, flag_1);
					p_flag = 1;
				}
			}
	}
	closedir(dh);
	return (0);
}

/**
 * addnode - file for adding a node to a list
 * @filename: Name of file or directory
 * @flist: list of files
*/

void addnode(const char *filename, file_list **flist)
{
	file_list *newf = NULL, *tmp = *flist;

	newf = malloc(sizeof(file_list));
	newf->name = malloc(_strlen(filename) + 1);
	if (!newf)
		return;
	_strncpy(newf->name, filename, _strlen(filename) + 1);
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

/**
 * flag_checker - Function to parse argv for flags
 * @argc: number of arguments
 * @argv: array of arguments
*/

void flag_checker(int argc, const char *argv[])
{
	int j = 1, i = 1;

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
	}
}

/**
 * l_option -  Function for handling the -l option
 * @dir: Directory handed in
 * @filename: file name passed in by dirent object
*/

void l_option(const char *dir, char *filename)
{
	struct stat info;
	struct passwd *user_id;
	struct group *group_id;
	char *time, *path = NULL;

	path = make_path(dir, filename);

	if (!lstat(path, &info))
	{
		usr_perms(info.st_mode);
		grp_perms(info.st_mode);
		other_perms(info.st_mode);
		printf("%ld ", info.st_nlink);
		user_id = getpwuid(info.st_uid);
		if (user_id)
			printf("%s ", user_id->pw_name);
		else
			printf("%d ", info.st_uid);
		group_id = getgrgid(info.st_gid);
		if (group_id)
			printf("%s ", group_id->gr_name);
		else
			printf("%d ", info.st_gid);
		printf("%ld ", info.st_size);
		time = ctime(&(info.st_mtime));
		printf("%.12s %s\n", &time[4], filename);
	}
	free(path);
	path = NULL;
}
