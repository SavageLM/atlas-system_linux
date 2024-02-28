#include "readelf.h"

/**
 * print_ver - Function for printing the version of ELF spec
 * @prog: Program name
 * @header: Struct containing ELF head data
 * Return: 1 on success, 0 on failure.
*/

int print_ver(char *prog, elf_hdr header)
{
	if (header.Ehdr64.e_ident[EI_VERSION] == EV_NONE)
	{
		fprintf(stderr, "%s: Error: Invalid version.", prog);
		return (0);
	}
	else
		printf("  Version:                           %i (current)\n", EV_CURRENT);
	return (1);
}

/**
 * print_osabi - Function to print OS, ABI, and ABI ver
 * @header: Struct containing ELF head data
*/

void print_osabi(elf_hdr header)
{
	printf("  OS/ABI:                            ");
	if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_NONE)
		printf("UNIX - System V\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_SYSV)
		printf("UNIX System V\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_HPUX)
		printf("HP-UX\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		printf("NetBSD\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_LINUX)
		printf("UNIX - Linux\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		printf("UNIX - Solaris\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_IRIX)
		printf("UNIX - SGI Irix\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		printf("UNOX - FreeBSD\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_TRU64)
		printf("UNIX - Compaq TRU64\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_ARM)
		printf("UNIX - ARM\n");
	else if (header.Ehdr64.e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		printf("SUNIX - Standalone (embedded) application\n\n");
	else
		printf("<unknown: %x>\n",header.Ehdr64.e_ident[EI_OSABI]);
	printf("  ABI Version:                       %i\n", header.Ehdr64.e_ident[EI_ABIVERSION]);
}

/**
 * print_type - Function that prints file type
 * @header: Struct containing ELF header data
 * @flag_SIG: flag for lsb or msb
*/

void print_type(elf_hdr header, int flag_SIG)
{
	Elf64_Half elf_type = header.Ehdr64.e_type;

	if (flag_SIG == 1)
		convert_bits((char *) &elf_type, sizeof(elf_type));
	printf("  Type:                              ");
	if (elf_type == ET_NONE)
		printf("NONE (No file type)\n");
	else if (elf_type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (elf_type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (elf_type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else
		printf(" CORE (Core file)\n");
}

/**
 * print_machine - Function that prints the required architecture for a file
 * @header: Struct that contains the ELF header data
 * @flag_SIG: flag for lsb or msb
*/

void print_machine(elf_hdr header, int flag_SIG)
{
	Elf64_Half elf_machine = header.Ehdr64.e_machine;

	if (flag_SIG == 1)
		convert_bits((char *) &elf_machine, sizeof(elf_machine));
	printf("  Machine:                           ");
	if (elf_machine == EM_NONE)
		printf("No machine\n");
	else if (elf_machine == EM_M32)
		printf("AT&T WE 32100\n");
	else if (elf_machine == EM_SPARC)
		printf("Sparc\n");
	else if (elf_machine == EM_386)
		printf("Intel 80386\n");
	else if (elf_machine == EM_68K)
		printf(" Motorola m68k family\n");
	else if (elf_machine == EM_88K)
		printf("Motorola m88k family\n");
	else if (elf_machine == EM_860)
		printf("Intel 80860\n");
	else if (elf_machine == EM_MIPS)
		printf("MIPS RS3000 big-endian\n");
	else if (elf_machine == EM_PARISC)
		printf("HPPA\n");
	else if (elf_machine == EM_SPARC32PLUS)
		printf("SPARC with enhanced in struction set\n");
	else if (elf_machine == EM_PPC)
		printf("PowerPC\n");
	else if (elf_machine == EM_PPC64)
		printf("PowerPC 64-bit\n");
	else if (elf_machine == EM_S390)
		printf("IBM S390\n");
	else if (elf_machine == EM_ARM)
		printf("ARM\n");
	else if (elf_machine == EM_SH)
		printf("Hitachi SH\n");
	else if (elf_machine == EM_SPARCV9)
		printf("SPARC v9 64-bit\n");
	else if (elf_machine == EM_IA_64)
		printf("Intel Merced\n");
	else if (elf_machine == EM_X86_64)
		printf("Advanced Micro Devices X86-64\n");
	else
		printf("Digital VAX\n");
}

/**
 * print_fver - Function that prints the file version
 * @header: Struct containing the ELF header data
 * @flag_SIG: flag for lsb or msb
*/

void print_fver(elf_hdr header, int flag_SIG)
{
	Elf64_Word elf_ver = header.Ehdr64.e_version;

	if (flag_SIG)
		convert_bits((char *) &elf_ver, sizeof(elf_ver));
	printf("  Version:                           ");
	if (elf_ver == EV_NONE)
		printf("Invalid version\n");
	else
		printf("%#x\n", EV_CURRENT);
}
