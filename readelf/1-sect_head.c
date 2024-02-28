#include "readelf.h"

/**
 * main - Start of program to print ELF header
 * @argc: Number of argumenets
 * @argv: Array of arguments
 * Return: 0 on success, -1 on fail
*/

int main(int argc, char **argv)
{
	struct stat info;
	FILE *fptr;

	if (argc != 2)
	{
		fprintf(stderr, "Unsupported number of Arguments\n");
		return (-1);
	}
	stat(argv[1], &info);
	if (!S_ISREG(info.st_mode))
	{
		fprintf(stderr, "%s: Error: '%s': is not an ordinary file\n",
				argv[0], argv[1]);
		return (-1);
	}
	fptr = fopen(argv[1], "rb");
	if (!fptr)
	{
		fprintf(stderr, "%s: Error: '%s': is not an ordinary file\n",
				argv[0], argv[1]);
		return (-1);
	}
	if (!proute_header(fptr, *argv))
		return (-1);
	else
		return (0);
}
