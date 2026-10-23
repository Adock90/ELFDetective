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

size_t get_file_size(FILE* fptr)
{
	if (fptr == NULL)
	{
		raise_elf_error("Not a valid file handle");
		exit(1);
	}
	
	long current_pos = ftell(fptr);
	if (current_pos < 0 || fseek(fptr, 0, SEEK_END) != 0)
	{
		raise_elf_error("Cannot determine file size");
		exit(EXIT_FAILURE);
	}

	long sizeoffile = ftell(fptr);
	if (sizeoffile < 0 || fseek(fptr, current_pos, SEEK_SET) != 0)
	{
		raise_elf_error("Cannot determine file size");
		exit(EXIT_FAILURE);
	}

	return (size_t)sizeoffile;
}

void elf_cleanup(FILE* file_handle)
{
	fclose(file_handle);
}
