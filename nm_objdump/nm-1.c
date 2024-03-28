#include "nm.h"
#include "nm_macros.h"

/**
 * main - entry to function
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 on success, else -1
*/

int main(int argc, char **argv)
{
	struct stat info;
	elf_hdr header;
	int fd;

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
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		fprintf(stderr, "%s: Error: '%s': is not an ordinary file\n",
				argv[0], argv[1]);
		return (-1);
	}
	if (map_header(&header, fd, *argv) == -1)
	{
		close(fd);
		return (-1);
	}
	if (header.Flag_SIG)
	{
		fprintf(stderr, "%s: %s: no symbols\n", argv[0], argv[1]);
		destroy_header(&header);
		return (0);
	}
	if (parse_symbol_header(&header) == -1)
	{
		destroy_header(&header);
		fprintf(stderr, "%s: %s: no symbols\n", argv[0], argv[1]);
		return (0);
	}
	process_symbols(&header);
	destroy_header(&header);
	return (0);
}

/**
 * map_header - Maps open ELF file into virtual memory
 * @header: Pointer to `SymbolReader` struct
 * @fd: File descriptor for ELF file
 * @prog: program name
 * Return: `0` on success, `-1` on failure
 */

int map_header(elf_hdr *header, int fd, char *prog)
{
	struct stat statbuf;

	/* track fd and get size of the ELF file */
	header->fd = fd;
	if (fstat(header->fd, &statbuf) == -1)
		return (-1);
	header->fsize64 = (uint64_t)statbuf.st_size;
	/* map the ELF-file contents to a virtual-memory address */
	header->Ehdr64 = mmap(NULL, header->fsize64, PROT_READ, MAP_PRIVATE,
		header->fd, 0);
	if (memcmp(header->Ehdr64->e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: Error Not an ELF file\n", prog);
		return (-1);
	}
	if (header->Ehdr64->e_ident[EI_DATA] == ELFDATA2MSB)
		header->Flag_SIG = 1;
	else
		header->Flag_SIG = 0;
	if (header->Ehdr64->e_ident[EI_CLASS] == ELFCLASS64)
	{
		header->Flag_OP = 1;
		return (header->Ehdr64 == MAP_FAILED ? -1 : 0);
	}
	else
	{
		header->Flag_OP = 0;
		header->fsize32 = (uint32_t)statbuf.st_size;
		/* map the ELF-file contents to a virtual-memory address */
		header->Ehdr32 = mmap(NULL, header->fsize32, PROT_READ, MAP_PRIVATE,
			header->fd, 0);
		return (header->Ehdr32 == MAP_FAILED ? -1 : 0);
	}
	return(-1);
}

/**
 * parse_symbol_header - Finds symbol-table section header and symbol count
 * @header: Pointer to struct
 * Return: `0` on success, `-1` on failure
 */

int parse_symbol_header(elf_hdr *header)
{
	uint64_t i;
	uint32_t j;

	/* assign section header address and find symbol-table header */
	if (header->Flag_OP)
	{
		header->Shdr64 = SECTION_HEADERS64(header->Ehdr64);
		header->Sym_sh64 = NULL;
		for (i = 0; i < SECTION_COUNT64(header->Ehdr64); ++i)
		{
			if (header->Shdr64[i].sh_type == SHT_SYMTAB)
			{
				header->Sym_sh64 = header->Shdr64 + i;
				break;
			}
		}
		if (!header->Sym_sh64)
			return (-1);
		header->Sym_count64 = SYMBOL_COUNT64(header->Sym_sh64);
		header->Sym_tbl_64 = SYMBOL_TABLE64(header->Ehdr64, header->Sym_sh64);
		header->str_table = STRING_TABLE(header->Ehdr64, header->Shdr64, header->Sym_sh64);
	}
	else
	{
		header->Shdr32 = SECTION_HEADERS32(header->Ehdr32);
		header->Sym_sh32 = NULL;
		for (j = 0; j < SECTION_COUNT32(header->Ehdr32); ++j)
		{
			if (header->Shdr32[j].sh_type == SHT_SYMTAB)
			{
				header->Sym_sh32 = header->Shdr32 + j;
				break;
			}
		}
		if (!header->Sym_sh32)
			return (-1);
		header->Sym_count32 = SYMBOL_COUNT32(header->Sym_sh32);
		header->Sym_tbl_32 = SYMBOL_TABLE32(header->Ehdr32, header->Sym_sh32);
		header->str_table = STRING_TABLE(header->Ehdr32, header->Shdr32, header->Sym_sh32);
	}
	return (0);
}

/**
 * destroy_header - Frees memory used by struct
 * @header: pointer to struct
*/

void destroy_header(elf_hdr *header)
{
	if (!header)
		return;
	if (header->Flag_OP)
		munmap(header->Ehdr64, header->fsize64);
	else
		munmap(header->Ehdr32, header->fsize32);
	close(header->fd);
	memset(header, 0, sizeof(elf_hdr));
}

/**
 * process_symbols - Sequentially performs `action` on all symbols
 * @header: Pointer to `SymbolReader` structure
 */

void process_symbols(elf_hdr *header)
{
	uint64_t i;
	uint32_t j;

	if (header->Flag_OP)
	{
		/* iterate over the symbol table entries */
		for (i = 0; i < header->Sym_count64; ++i)
		{
			print_symbol(header, header->Sym_tbl_64 + i, NULL);
		}
	}
	else
	{
		/* iterate over the symbol table entries */
		for (j = 0; j < header->Sym_count32; ++j)
		{
			print_symbol(header, NULL, header->Sym_tbl_32 + j);
		}
	}
}
