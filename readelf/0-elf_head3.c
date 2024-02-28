#include "readelf.h"

/**
 * print_entry - Function that prints virtual address where control is passed
 * @header: Struct Containing the ELF header data
*/

void print_entry(elf_hdr header)
{
	printf("  Entry point address:               ");
	printf("0x%x\n", header.Ehdr.e_entry);
}

/**
 * print_phoff_shoff - Function that prints Section/program header offset
 * @header: Struct that contains the ELF header data
*/

void print_phoff_shoff(elf_hdr header)
{
	printf("  Start of program headers:          ");
	printf("%i (bytes into file)\n", header.Ehdr.e_phoff);

	printf("  Start of section headers:          ");
	printf("%i (bytes into file)\n", header.Ehdr.e_shoff);
}

/**
 * print_flags - Function to print the flags
 * @header: Struct Containing the ELF header data
*/

void print_flags(elf_hdr header)
{
	printf("  Flags:                             ");
	printf("0x%x\n", header.Ehdr.e_flags);
}

/**
 * print_phehsize - Function to print size of header and program header
 * @header: Struct holding ELF header data
*/

void print_phehsize(elf_hdr header)
{
	printf("  Size of this header:               ");
	printf("%i (bytes)\n", header.Ehdr.e_ehsize);

	printf("  Size of program headers:           ");
	printf("%i (bytes)\n", header.Ehdr.e_phentsize);
}

/**
 * print_phnum - function to print number of items in program header
 * @header: Struct holding ELF header data
*/

void print_phnum(elf_hdr header)
{
	printf("  Number of program headers:         ");
	printf("%i\n", header.Ehdr.e_phnum);
}
