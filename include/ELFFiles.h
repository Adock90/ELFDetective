#ifndef ELFFILES_H
#define ELFFILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

#include <ELFError.h>

FILE* get_elf_file_handle(char* filename);


void elf_cleanup(FILE* file_handle);

#endif
