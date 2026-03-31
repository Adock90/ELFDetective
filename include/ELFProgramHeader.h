#ifndef ELFPROGRAMHEADER_H
#define ELFPROGRAMHEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>

#include <ELFError.h>

Elf64_Phdr* get_64_bit_program_header(FILE* fptr, Elf64_Ehdr header);

Elf32_Phdr* get_32_bit_program_header(FILE* fptr, Elf64_Ehdr header);


void dump_64_bit_program_header(Elf64_Phdr* program_header);

void dump_32_bit_program_header(Elf32_Phdr* program_header);


void bit_32_program_header_pointer_cleanup(Elf32_Phdr* program_header);

void bit_64_program_header_pointer_cleanup(Elf64_Phdr* program_header);

#endif
