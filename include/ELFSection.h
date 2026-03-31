#ifndef ELFSECTION_H
#define ELFSECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include <ELFFiles.h>
#include <ELFError.h>

#define MAX_BUFF_SIZE 256

Elf64_Shdr* parse_64_bit_section_headers(FILE* fptr, Elf64_Ehdr bit_64_header);

Elf32_Shdr* parse_32_bit_section_headers(FILE* fptr, Elf32_Ehdr bit_32_header);


void dump_64_bit_section_headers(FILE* fptr, Elf64_Shdr* section_header, uint16_t shnum, uint16_t e_shstrndx);

void dump_32_bit_section_headers(FILE* fptr, Elf32_Shdr* section_header, uint16_t shnum, uint16_t e_shstrndx);


void bit_32_section_header_pointer_cleanup(Elf32_Shdr* section_header);

void bit_64_section_header_pointer_cleanup(Elf64_Shdr* section_header);

#endif
