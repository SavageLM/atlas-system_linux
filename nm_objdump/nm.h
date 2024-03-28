#ifndef NM_H
#define NM_H

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>	/* open */
#include <sys/mman.h>	/* mmap, munmap */
#include <unistd.h>

/**
 * struct elf_hdr - struct for 32 and 64 bit  ELF file headers
 * @Ehdr32: 32 bit ELF header
 * @Ehdr64: 64 bit ELF header
 * @Shdr32: 32 bit section header
 * @Shdr64: 64 bit section header
 * @Sym_sh32: 32 bit Symbol table section header
 * @Sym_sh64: 64 bit Symbol table section header
 * @Sym_tbl_64: 64 bit Symbol Table
 * @Sym_tbl_32: 32 bit symbol Table
 * @Sym_count32: 32 bit number of symbols
 * @Sym_count64: 64 bit number of symbols
 * @str_table: start of string table
 * @fsize32: 32 bit size of elf file
 * @fsize64: 64 bit size of elf file
 * @fd: file discriptor
 * @Flag_OP: flag for 64 or 32 bit
 * @Flag_SIG: flag for msb
*/
typedef struct elf_hdr
{
	Elf32_Ehdr *Ehdr32;
	Elf64_Ehdr *Ehdr64;
	Elf32_Shdr *Shdr32;
	Elf64_Shdr *Shdr64;
	Elf32_Shdr *Sym_sh32;
	Elf64_Shdr *Sym_sh64;
	Elf32_Sym *Sym_tbl_32;
	Elf64_Sym *Sym_tbl_64;
	uint32_t Sym_count32;
	uint64_t Sym_count64;
	char *str_table;
	uint64_t fsize64;
	uint32_t fsize32;
	int fd;
	int Flag_OP;
	int Flag_SIG;
} elf_hdr;

/*Prototypes*/
int main(int argc, char **argv);
static int map_header(elf_hdr *header, int fd, char *prog);
static int parse_symbol_header(elf_hdr *header);
void destroy_header(elf_hdr *header);
void process_symbols(elf_hdr *header);
void process_symbols(elf_hdr *header);
void print_symbol(elf_hdr *header, Elf64_Sym *sym64, Elf32_Sym *sym32);
char get_type64(elf_hdr *header, Elf64_Sym *sym64);
char get_type32(elf_hdr *header, Elf32_Sym *sym32);

#endif
