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
*/
typedef struct elf_hdr
{
	Elf32_Ehdr Ehdr32;
	Elf64_Ehdr Ehdr64;
	Elf32_Shdr Shdr32;
	Elf64_Shdr Shdr64;
} elf_hdr;

/*Prototypes*/
int main(int argc, char **argv);
int proute_header(FILE *fptr, char *prog);
void print_magnum(elf_hdr header);
int print_class(char *prog, elf_hdr header);
int print_data(char *prog, elf_hdr header);
int print_ver(char *prog, elf_hdr header);
void print_osabi(elf_hdr header);
void print_type(elf_hdr header, int flag_SIG);
void print_machine(elf_hdr header,int flag_SIG);
void print_fver(elf_hdr header, int flag_SIG);
void print_entry(elf_hdr header, int flag_OP, int flag_SIG);
void print_phoff_shoff(elf_hdr header, int flag_OP, int flag_SIG);
void print_flags(elf_hdr header, int flag_OP, int flag_SIG);
void print_phehsize(elf_hdr header, int flag_OP, int flag_SIG);
void print_phnum(elf_hdr header, int flag_OP, int flag_SIG);
void print_shentsize_num(elf_hdr header, int flag_OP, int flag_SIG);
void print_shstrndx(elf_hdr header, int flag_OP, int flag_SIG);
void convert_bits(char *ptr, size_t size);

#endif