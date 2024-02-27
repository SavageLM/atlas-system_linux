#ifndef READELF_H
#define READELF_H

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/**
 * struct elf_hdr - struct for 32 and 64 bit  ELF file headers
 * @elf32_hdr: 32 bit ELF header
 * @elf64_hdr: 64 bit ELF header
 * @elf32_sec: 32 bit section header
 * @elf64_sec: 64 bit section header
 * @flag_OP: flag for 32 or 64 bit op
 * @flag_SIG: flag for lsb or msb
*/
typedef struct elf_hdr
{
	elf_head Ehdr;
	elf_sec Shdr;
	int flag_OP = 0;
	int flag_SIG = 0;
} elf_hdr;

/*Prototypes*/

#endif