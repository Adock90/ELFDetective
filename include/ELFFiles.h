#ifndef ELFFILES_H
#define ELFFILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

#include <ELFError.h>

FILE* get_elf_file_handle(char* filename);

size_t get_file_size(FILE* fptr);

void elf_cleanup(FILE* file_handle);

#endif
