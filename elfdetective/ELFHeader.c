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

Elf64_Ehdr get_elf64_header(FILE* file_handle)
{
	Elf64_Ehdr header;
	
	if (fread(&header, 1, sizeof(header), file_handle) != sizeof(header))
	{
		raise_elf_error("Header partially uninitialised");
		elf_cleanup(file_handle);
		exit(1);
	}
	
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

Elf32_Ehdr get_elf32_header(FILE* file_handle)
{
        Elf32_Ehdr header;

	if (fread(&header, 1, sizeof(header), file_handle) != sizeof(header))
        {
                raise_elf_error("Header partially uninitialised");
                elf_cleanup(file_handle);
                exit(1);
        }

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

void dump_elf64_header_data(Elf64_Ehdr header)
{
	printf("[               ELF Header               ]\n");
	printf("\tInterpret Data (e_ident)\n\n");
	static const char* dataArr[] = {"ELF Magic Number 0", "ELF Magic Number 1", "ELF Magic Number 2", "ELF Magic Number 3", "EI_CLASS", "EI_DATA", "Version", "OS", "ABI Version"};
	for (int i = 0; i < sizeof(dataArr)/sizeof(dataArr[0]); i++)
	{
		printf("\t\t%s: %x\n", dataArr[i], header.e_ident[i]);
	}
	
	printf("\t\tPadding:\n");
	for (int i = 9; i < EI_NIDENT; i++)
		printf("\t\t\t%02x\n", header.e_ident[i]);
	printf("\n\n");
	
	printf("\tObject Type (e_type): 0x%" PRIx16 "\n", header.e_type);
	printf("\tMachine Architecture (e_machine): 0x%" PRIx16 "\n", header.e_machine);
	printf("\tFile Version (e_version): 0x%" PRIx32 "\n", header.e_version);
	printf("\tEntry point (e_entry): 0x%" PRIx64 "\n", header.e_entry);
	printf("\tProgram Header table file offset (e_phoff): 0x%" PRIx64 "\n", header.e_phoff);
	printf("\tSection Header table file offset (e_shoff): 0x%" PRIx64 "\n", header.e_shoff);
	printf("\tProcesser-Specific flags (e_flags): 0x%" PRIx32 "\n", header.e_flags);
	printf("\tELF header size (e_ehsize): 0x%" PRIx16 "\n", header.e_ehsize);
	printf("\tSize of one entry (e_phentsize): 0x%" PRIx16 "\n", header.e_phentsize);
	printf("\tNumber of entries in the program header table (e_phnum): 0x%" PRIx16 "\n", header.e_phnum);
	printf("\tSection header's size (e_shentsize): 0x%" PRIx16 "\n", header.e_shentsize);
	printf("\tSection header's table index (e_shstrndx): 0x%" PRIx16 "\n", header.e_shstrndx);
}

void dump_elf32_header_data(Elf32_Ehdr header)
{
        printf("[               ELF Header               ]\n");
        printf("\tInterpret Data (e_ident)\n\n");
	
	static const char* dataArr[] = {"ELF Magic Number 0", "ELF Magic Number 1", "ELF Magic Number 2", "ELF Magic Number 3", "EI_CLASS", "EI_DATA", "Version", "OS", "ABI Version"};
        for (int i = 0; i < sizeof(dataArr)/sizeof(dataArr[0]); i++)
        {
                printf("\t\t%s: %x\n", dataArr[i], header.e_ident[i]);
        }

        printf("\t\tPadding:\n");
        for (int i = 9; i < EI_NIDENT; i++)
                printf("\t\t\t%02x\n", header.e_ident[i]);
        printf("\n\n");


        printf("\tObject Type (e_type): 0x%" PRIx16 "\n", header.e_type);
        printf("\tMachine Architecture (e_machine): 0x%" PRIx16 "\n", header.e_machine);
        printf("\tFile Version (e_version): 0x%" PRIx32 "\n", header.e_version);
        printf("\tEntry point (e_entry): 0x%" PRIx32 "\n", header.e_entry);
        printf("\tProgram Header table file offset (e_phoff): 0x%" PRIx32 "\n", header.e_phoff);
        printf("\tSection Header table file offset (e_shoff): 0x%" PRIx32 "\n", header.e_shoff);
        printf("\tProcesser-Specific flags (e_flags): 0x%" PRIx32 "\n", header.e_flags);
        printf("\tELF header size (e_ehsize): 0x%" PRIx16 "\n", header.e_ehsize);
        printf("\tSize of one entry (e_phentsize): 0x%" PRIx16 "\n", header.e_phentsize);
        printf("\tNumber of entries in the program header table (e_phnum): 0x%" PRIx16 "\n", header.e_phnum);
        printf("\tSection header's size (e_shentsize): 0x%" PRIx16 "\n", header.e_shentsize);
        printf("\tSection header's table index (e_shstrndx): 0x%" PRIx16 "\n", header.e_shstrndx);
}


