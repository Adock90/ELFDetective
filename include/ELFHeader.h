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

Elf64_Ehdr get_elf_header(FILE* file_handle);

HeaderArch check_if_elf_is_valid(Elf64_Ehdr header);

void dump_elf_header_data(Elf64_Ehdr header);

