#ifndef NM_MACROS_H
#define NM_MACROS_H

#include <elf.h>
#include <stdint.h>

/**
 * OFFSET - Moves a pointer an arbitrary number of bytes
 * @ptr: Pointer to offset
 * @n: Number of bytes to offset by
 *
 * Return: Pointer `ptr` offset by `n` bytes
 */
#define OFFSET(ptr, n) ((char *)(ptr) + (n))

/**
 * SECTION_HEADERS64 - Fetches pointer to section headers
 * @ehdr: Pointer to ELF header
 * Return: Pointer to first section header
 */
#define SECTION_HEADERS64(ehdr) ((Elf64_Shdr *)OFFSET((Ehdr64), (Ehdr64)->e_shoff))

/**
 * SECTION_HEADERS32 - Fetches pointer to section headers
 * @ehdr: Pointer to ELF header
 * Return: Pointer to first section header
 */
#define SECTION_HEADERS32(ehdr) ((Elf32_Shdr *)OFFSET((Ehdr32), (Ehdr32)->e_shoff))

/**
 * SECTION_COUNT64 - Returns the number of section headers
 * @ehdr: Pointer to ELF header
 * Return: Number of section headers
 */
#define SECTION_COUNT64(ehdr) ((uint64_t)(Ehdr64)->e_shnum)

/**
 * SECTION_COUNT32 - Returns the number of section headers
 * @ehdr: Pointer to ELF header
 * Return: Number of section headers
 */
#define SECTION_COUNT32(ehdr) ((uint32_t)(Ehdr32)->e_shnum)

/**
 * SYMBOL_COUNT64 - Returns number of symbol-table entries
 * @sh: Pointer to section header for symbol table
 * Return: Number of symbol-table entries
 */
#define SYMBOL_COUNT64(sh) ((uint64_t)(sh)->sh_size / sizeof(Elf64_Sym))

/**
 * SYMBOL_COUNT32 - Returns number of symbol-table entries
 * @sh: Pointer to section header for symbol table
 * Return: Number of symbol-table entries
 */
#define SYMBOL_COUNT32(sh) ((uint32_t)(sh)->sh_size / sizeof(Elf32_Sym))

/**
 * SECTION - Fetches pointer to section given a section header
 * @ehdr: Pointer to ELF header
 * @sh: Pointer to section header
 * Return: Pointer to section (caller will need to cast)
 */
#define SECTION(ehdr, sh) OFFSET((ehdr), (sh)->sh_offset)

/**
 * SYMBOL_TABLE64 - Fetches typed pointer to symbol table
 * @ehdr: Pointer to ELF header
 * @sh: Pointer to section header for symbol table
 * Return: Pointer to first symbol-table entry (`Elf64_Sym`)
 */
#define SYMBOL_TABLE64(ehdr, sh) ((Elf64_Sym *)SECTION(ehdr, sh))

/**
 * SYMBOL_TABLE32 - Fetches typed pointer to symbol table
 * @ehdr: Pointer to ELF header
 * @sh: Pointer to section header for symbol table
 * Return: Pointer to first symbol-table entry (`Elf64_Sym`)
 */
#define SYMBOL_TABLE32(ehdr, sh) ((Elf32_Sym *)SECTION(ehdr, sh))

/**
 * STRING_TABLE - Fetches pointer to string table
 * @ehdr: Pointer to ELF header
 * @shdrs: Pointer to first section header
 * @sh: Pointer to section header for symbol table
 * Return: Pointer to first `char` of string table
 */
#define STRING_TABLE(ehdr, shdrs, sh) SECTION(ehdr, (shdrs) + (sh)->sh_link)

/**
 * SYMBOL_STRING - Fetches the string that corresponds to a symbol-table entry
 * @strtab: Pointer to string table
 * @sym: Pointer to symbol-table entry
 * Return: Pointer to first `char` of the symbol's string
 */
#define SYMBOL_STRING(strtab, sym) ((strtab) + (sym)->st_name)

#endif
