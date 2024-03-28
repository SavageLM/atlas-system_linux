#include "nm.h"
#include "nm_macros.h"

/**
 * print_symbol - Prints out the relevent symbol info
 * @header: pointer to elf_ehdr struct
 * @sym64: pointer to index in symbol table for 64 bit systems
 * @sym32: pointer to index in symbol table for 32 bit systems
*/

void print_symbol(elf_hdr *header, Elf64_Sym *sym64, Elf32_Sym *sym32)
{
	if (header->Flag_OP)
	{
		(void)sym32;
		printf("%lx ", sym64->st_value);
		get_type64(header, sym64);
		printf("%s\n", header->str_table + sym64->st_name);
	}
	else
	{
		(void)sym64;
		printf("%x ", sym32->st_value);
		get_type32(header, sym32);
		printf("%s\n", header->str_table + sym32->st_name);
	}
}

/**
 * get_type64 - gets type of symbol in one char
 * @header: POinter to struct
 * @sym64: pointer to index in symbol table
 * Return: the char type
 */

char get_type64(elf_hdr *header, Elf64_Sym *sym64)
{
	char c;

	if (ELF64_ST_BIND(sym64->st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(sym64->st_info) == STB_WEAK &&
		ELF64_ST_TYPE(sym64->st_info) == STT_OBJECT)
		c = sym64->st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF64_ST_BIND(sym64->st_info) == STB_WEAK)
		c = sym64->st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym64->st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym64->st_shndx == SHN_ABS)
		c = 'A';
	else if (sym64->st_shndx == SHN_COMMON)
		c = 'C';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_NOBITS
			&& header->Shdr64[sym64->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr64[sym64->st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr64[sym64->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr64[sym64->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (header->Shdr64[sym64->st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	if (ELF64_ST_BIND(sym64->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}

/**
 * get_nm_type32 - gets type of symbol in one char
 * @header: Pointer to struct
 * @sym32: pointer to index of symbol table in 32 bit system
 * Return: the char type
 */

char get_type32(elf_hdr *header, Elf32_Sym *sym32)
{
	char  c;

	if (ELF32_ST_BIND(sym32->st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF32_ST_BIND(sym32->st_info) == STB_WEAK &&
		ELF32_ST_TYPE(sym32->st_info) == STT_OBJECT)
		c = sym32->st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF32_ST_BIND(sym32->st_info) == STB_WEAK)
		c = sym32->st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym32->st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym32->st_shndx == SHN_ABS)
		c = 'A';
	else if (sym32->st_shndx == SHN_COMMON)
		c = 'C';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_NOBITS
			&& header->Shdr32[sym32->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr32[sym32->st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr32[sym32->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_PROGBITS
			&& header->Shdr32[sym32->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (header->Shdr32[sym32->st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	if (ELF32_ST_BIND(sym32->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}

/**
 * convert_bits - Function to convert from lsb to msb
 * @ptr: pointer to first octet of word
 * @size: size of ptr


void convert_bits(char *ptr, size_t size)
{
	size_t tmp, start, end;

	for (start = 0, end = size - 1; start < end; ++start, --end)
	{
		tmp = ptr[start];
		ptr[start] = ptr[end];
		ptr[end] = tmp;
	}
}*/
