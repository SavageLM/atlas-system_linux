#include "readelf.h"

/**
 * print_entry - Function that prints virtual address where control is passed
 * @header: Struct Containing the ELF header data
 * @flag_OP: Flag for 32 or 64 bit OP
*/

void print_entry(elf_hdr header, int flag_OP)
{
	Elf64_Addr enter_64 = header.Ehdr64.e_entry;
	Elf32_Addr enter_32 = header.Ehdr32.e_entry;

	printf("  Entry point address:               ");
	if (flag_OP == 64)
		printf("0x%lx\n", enter_64);
	else
		printf("0x%x\n", enter_32);
}

/**
 * print_phoff_shoff - Function that prints Section/program header offset
 * @header: Struct that contains the ELF header data
 * @flag_OP: Flag for 32 or 64 bit OP
*/

void print_phoff_shoff(elf_hdr header, int flag_OP)
{
	Elf64_Off phoff64 = header.Ehdr64.e_phoff;
	Elf64_Off shoff64 = header.Ehdr64.e_shoff;
	Elf32_Off phoff32 = header.Ehdr32.e_phoff;
	Elf32_Off shoff32 = header.Ehdr32.e_shoff;

	if (flag_OP == 64)
	{
		printf("  Start of program headers:          ");
		printf("%li (bytes into file)\n", phoff64);
		printf("  Start of section headers:          ");
		printf("%li (bytes into file)\n", shoff64);
	}
	else
		{
			printf("  Start of program headers:          ");
			printf("%i (bytes into file)\n", phoff32);
			printf("  Start of section headers:          ");
			printf("%i (bytes into file)\n", shoff32);
		}
}

/**
 * print_flags - Function to print the flags
 * @header: Struct Containing the ELF header data
 * @flag_OP: Flag for 32 or 64 bit OP
*/

void print_flags(elf_hdr header, int flag_OP)
{
	Elf64_Word flags64 = header.Ehdr64.e_flags;
	Elf32_Word flags32 = header.Ehdr32.e_flags;

	printf("  Flags:                             ");
	if (flag_OP == 64)
		printf("0x%x\n", flags64);
	else
	printf("0x%x\n", flags32);
}

/**
 * print_phehsize - Function to print size of header and program header
 * @header: Struct holding ELF header data
 * @flag_OP: Flag for 32 or 64 bit OP
*/

void print_phehsize(elf_hdr header, int flag_OP)
{
	Elf64_Half headsize64 = header.Ehdr64.e_ehsize;
	Elf64_Half progsize64 = header.Ehdr64.e_phentsize;
	Elf32_Half headsize32 = header.Ehdr32.e_ehsize;
	Elf32_Half progsize32 = header.Ehdr32.e_phentsize;

	if (flag_OP == 64)
	{
		printf("  Size of this header:               ");
		printf("%i (bytes)\n", headsize64);
		printf("  Size of program headers:           ");
		printf("%i (bytes)\n", progsize64);
	}
	else
	{
		printf("  Size of this header:               ");
		printf("%i (bytes)\n", headsize32);
		printf("  Size of program headers:           ");
		printf("%i (bytes)\n", progsize32);
	}
}

/**
 * print_phnum - function to print number of items in program header
 * @header: Struct holding ELF header data
 * @flag_OP: Flag for 32 or 64 bit OP
*/

void print_phnum(elf_hdr header, int flag_OP)
{
	Elf64_Half prog_num64 = header.Ehdr64.e_phnum;
	Elf32_Half prog_num32 = header.Ehdr32.e_phnum;

	printf("  Number of program headers:         ");
	if (flag_OP == 64)
		printf("%i\n", prog_num64);
	else
		printf("%i\n", prog_num32);
}
