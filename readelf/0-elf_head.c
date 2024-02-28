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
	if (!proute_header(fptr, *argv[0], *argv[1]))
		return (-1);
	else
		return (0);
}

/**
 * proute_header - Function for routing prints for ELF header
 * @fptr: Pointer to File stream
 * @prog: program name
 * @file_name: Name of file
 * Return: 1 on success, 0 on fail
*/

int proute_header(FILE *fptr, char *prog, char *file_name)
{
	elf_hdr header;

	if (!print_magnum(fptr, prog, header))
		return (0);
	if (!print_class(prog, header))
		return (0);
	if (!print_data(prog, header))
		return (0);
	if (!print_ver(prog, header))
		return (0);
	print_osabi(header);
	print_type(header);
	print_machine(header);
	print_fver(header);
	print_entry(header);
	print_phoff_shoff(header);
	print_flags(header);
	print_phehsize(header);
	print_phnum(header);
	print_shentsize(header);
	print_shnum(header);
	print_shstrndx(header);
	fclose(fptr);
	return (1);
}

/**
 * print_magnum - Checks if file is an ELF file, and prints the magic number
 * @fptr: pointer to the file stream
 * @prog: Name of the called program
 * @header: struct with ELF Header data
 * Return: 1 on Success, 0 on failure
*/

int print_magnum(FILE *fptr, char *prog, elf_hdr header)
{
	size_t i = 0;

	fread(&header.Ehdr, sizeof(header.Ehdr), 1, fptr);
	if (memcmp(header.Ehdr.e_indent, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: Error Not an ELF file\n", prog);
		return (0);
	}
	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (; i < EI_NIDENT; i++)
		printf("%02x ", header.Ehdr.e_ident[i]);
	putchar('\n');
	return (1);
}

/**
 * print_class - Function to print the class of the ELF file
 * @prog: Program name
 * @header: Struct with ELF header data
 * Return: 1 on Success, 0 on Failure
*/

int print_class(char *prog, elf_hdr header)
{
	if (header.Ehdr.e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		fprintf(stderr, "%s: Error: This Class is invalid\n", prog);
		return (0);
	}
	else if (header.Ehdr.e_ident[EI_CLASS] == ELFCLASS32)
	{
		printf("  Class:                             ELF32\n")
		header.flag_OP = 32;
	}
	else if (header.Ehdr.e_ident[EI_CLASS] == ELFCLASS64)
	{
		printf("  Class:                             ELF32\n")
		header.flag_OP = 64;
	}
	return (1);
}

/**
 * print_data - Prints the data from the ELF Header
 * @prog: Program name
 * @header: Struct with ELF Header data
 * Return: 1 on Success, 0 on failure
*/

int print_data(char *prog, elf_hdr header)
{
	if (header.Ehdr.e_ident[EI_DATA] == ELFDATANONE)
	{
		fprintf(stderr, "%s: Error: Unknown data format\n", prog);
		return (0);
	}
	else if (header.Ehdr.e_ident[EI_DATA] == ELFDATA2LSB)
	{
		printf("  Data:                              2's complement, little endian\n");
		header.flag_SIG = 1;
	}
	else
		printf("  Data:                              2's complement, big endian\n");
		header.flag_SIG = 2;
		return (1);
}
