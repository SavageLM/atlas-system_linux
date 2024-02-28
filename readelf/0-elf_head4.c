#include "readelf.h"

/**
 * print_shentsize_num - FUnction to print section header size
 * @header:Struct holding ELF header data
 * @flag_OP: Flag for 32 or 64 bit OP
 * @flag_SIG: flag for lsb or msb
*/

void print_shentsize_num(elf_hdr header, int flag_OP, int flag_SIG)
{
	Elf64_Half sect_size64 = header.Ehdr64.e_shentsize;
	Elf64_Half sect_num64 = header.Ehdr64.e_shnum;
	Elf32_Half sect_size32 = header.Ehdr32.e_shentsize;
	Elf64_Half sect_num32 = header.Ehdr32.e_shnum;

	if (flag_OP == 64)
	{
		if (flag_SIG == 1)
		{
			convert_bits((char *) &sect_size64, sizeof(sect_size64));
			convert_bits((char *) &sect_num64, sizeof(sect_num64));
		}
		printf("  Size of section headers:           ");
		printf("%i (bytes)\n", sect_size64);
		printf("  Number of section headers:         ");
		printf("%i\n", sect_num64);
	}
	else
	{
		if (flag_SIG == 1)
		{
			convert_bits((char *) &sect_size32, sizeof(sect_size32));
			convert_bits((char *) &sect_num32, sizeof(sect_num32));
		}
		printf("  Size of section headers:           ");
		printf("%i (bytes)\n", sect_size32);
		printf("  Number of section headers:         ");
		printf("%i\n", sect_num32);
	}
}

/**
 * print_shstrndx - Function that prints header table string index
 * @header: Struct holding ELF header data
 * @flag_OP: Flag for 32 or 64 bit OP
 * @flag_SIG: flag for lsb or msb
*/

void print_shstrndx(elf_hdr header, int flag_OP, int flag_SIG)
{
	Elf64_Half shstrndx64 = header.Ehdr64.e_shstrndx;
	Elf32_Half shstrndx32 = header.Ehdr32.e_shstrndx;

	if (flag_OP == 64)
	{
		if (flag_SIG == 1)
			convert_bits((char *) &shstrndx64, sizeof(shstrndx64));
		printf("  Section header string table index: ");
		printf("%i\n", shstrndx64);
	}
	else
	{
		if (flag_SIG == 1)
			convert_bits((char *) &shstrndx32, sizeof(shstrndx32));
		printf("  Section header string table index: ");
		printf("%i\n", shstrndx32);
	}
}

/**
 * convert_bits - Function to convert from lsb to msb
 * @ptr: pointer to first octet of word
 * @size: size of ptr
*/

void convert_bits(char *ptr, size_t size)
{
	size_t tmp, start, end;

	for (start = 0, end = size - 1; start < end; ++start, --end)
	{
		tmp = ptr[start];
		ptr[start] = ptr[end];
		ptr[end] = tmp;
	}
}
