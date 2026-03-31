#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

#include <ELFError.h>

FILE* get_elf_file_handle(char* filename)
{
	FILE* fptr = fopen(filename, "rb");
	if (fptr == NULL)
	{
		raise_elf_error("Error opening file");
		exit(1);
	}

	return fptr;
}


void elf_cleanup(FILE* file_handle)
{
	fclose(file_handle);
}
