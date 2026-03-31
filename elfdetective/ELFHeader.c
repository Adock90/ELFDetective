#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include <ELFError.h>
#include <ELFFiles.h>


typedef struct
{
	int Elf64;
	int Elf32;
} HeaderArch;

Elf64_Ehdr get_elf_header(FILE* file_handle)
{
	Elf64_Ehdr header;
	fread(&header, 1, sizeof(header), file_handle);

	if (header.e_ident[EI_MAG0] != 0x7F ||
	    header.e_ident[EI_MAG1] != 'E' ||
	    header.e_ident[EI_MAG2] != 'L' ||
	    header.e_ident[EI_MAG3] != 'F')
	{
		raise_elf_error("Not a valid ELF\n");
		elf_cleanup(file_handle);
		exit(1);
	}

	return header;
}

HeaderArch check_if_elf_is_valid(Elf64_Ehdr header)
{
	HeaderArch Res = { 0 };
	if (header.e_ident[EI_CLASS] == ELFCLASS64)
	{
		Res.Elf64 = 1;
		printf("\tELF64\n");
	}
	else if (header.e_ident[EI_CLASS] == ELFCLASS32)
	{
		Res.Elf32 = 1;
		printf("\tELF32\n");
	}
	else
	{
		raise_elf_error("Not valid 32 or 64 bit ELF");
		Res.Elf64 = -1;
		Res.Elf32 = -1;
	}
	return Res;
}

void dump_elf_header_data(Elf64_Ehdr header)
{
	printf("[               ELF Header               ]\n");
	printf("\tInterpret Data (e_ident)\n\n");
	char* dataArr[EI_NIDENT] = {"ELF Magic Number 0", "ELF Magic Number 1", "ELF Magic Number 2", "ELF Magic Number 3", "EI_CLASS", "EI_DATA", "Version", "OS", "ABI Version", "Padding", "Size of e_ident array"};
	for (int i = 0; i < EI_NIDENT; i++)
	{
		printf("\t\t%s: %x\n", dataArr[i], header.e_ident[i]);
	}
	
	printf("\tObject Type (e_type): %u\n", header.e_type);
	printf("\tMachine Architecture (e_machine): %u\n", header.e_machine);
	printf("\tFile Version (e_version): %u\n", header.e_version);
	printf("\tEntry point (e_entry): %u\n", header.e_entry);
	printf("\tProgram Header table file offset (e_phoff): %u\n", header.e_phoff);
	printf("\tSection Header table file offset (e_shoff): %u\n", header.e_shoff);
	printf("\tProcesser-Specific flags (e_flags): %u\n", header.e_flags);
	printf("\tELF header size (e_ehsize): %u\n", header.e_ehsize);
	printf("\tSize of one entry (e_phentsize): %u\n", header.e_phentsize);
	printf("\tNumber of entries in the program header table (e_phnum): %u\n", header.e_phnum);
	printf("\tSection header's size (e_shentsize): %u\n", header.e_shentsize);
	printf("\tSection header's table index (e_shstrndx): %u\n", header.e_shstrndx);
}


