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

/**
 * proute_header - Function for routing prints for ELF header
 * @fptr: Pointer to File stream
 * @prog: program name
 * Return: 1 on success, 0 on fail
*/

int proute_header(FILE *fptr, char *prog)
{
	elf_hdr header;
	int flag_OP = 0, flag_SIG = 0;

	fread(&header.Ehdr64, sizeof(header.Ehdr64), 1, fptr);
	rewind(fptr);
	fread(&header.Ehdr32, sizeof(header.Ehdr32), 1, fptr);
	if (memcmp(header.Ehdr64.e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: Error Not an ELF file\n", prog);
		return (0);
	}
	print_magnum(header);
	flag_OP = print_class(prog, header);
	if (!flag_OP)
		return (0);
	flag_SIG = print_data(prog, header);
	if (!flag_SIG)
		return (0);
	if (!print_ver(prog, header))
		return (0);
	print_osabi(header);
	print_type(header);
	print_machine(header);
	print_fver(header);
	print_entry(header, flag_OP);
	print_phoff_shoff(header, flag_OP);
	print_flags(header, flag_OP);
	print_phehsize(header, flag_OP);
	print_phnum(header, flag_OP);
	print_shentsize_num(header, flag_OP);
	print_shstrndx(header, flag_OP);
	fclose(fptr);
	return (1);
}

/**
 * print_magnum - Checks if file is an ELF file, and prints the magic number
 * @header: struct with ELF Header data
*/

void print_magnum(elf_hdr header)
{
	size_t i = 0;

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (; i < EI_NIDENT; i++)
		printf("%02x ", header.Ehdr64.e_ident[i]);
	putchar('\n');
}

/**
 * print_class - Function to print the class of the ELF file
 * @prog: Program name
 * @header: Struct with ELF header data
 * Return: value based on if file is 32 or 64 bit
*/

int print_class(char *prog, elf_hdr header)
{
	if (header.Ehdr64.e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		fprintf(stderr, "%s: Error: This Class is invalid\n", prog);
		return (0);
	}
	else if (header.Ehdr64.e_ident[EI_CLASS] == ELFCLASS32)
	{
		printf("  Class:                             ELF32\n");
		return (32);
	}
	else if (header.Ehdr64.e_ident[EI_CLASS] == ELFCLASS64)
	{
		printf("  Class:                             ELF32\n");
		return (64);
	}
	return (1);
}

/**
 * print_data - Prints the data from the ELF Header
 * @prog: Program name
 * @header: Struct with ELF Header data
 * Return: value based on if file is lsb or msb
*/

int print_data(char *prog, elf_hdr header)
{
	if (header.Ehdr64.e_ident[EI_DATA] == ELFDATANONE)
	{
		fprintf(stderr, "%s: Error: Unknown data format\n", prog);
		return (0);
	}
	else if (header.Ehdr64.e_ident[EI_DATA] == ELFDATA2LSB)
	{
		printf("  Data:                              2's complement, little endian\n");
		return (2);
	}
	else
	{
		printf("  Data:                              2's complement, big endian\n");
		return (1);
	}
	return (3);
}
