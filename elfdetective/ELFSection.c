#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include <ELFFiles.h>
#include <ELFError.h>

#define MAX_BUFF_SIZE 256

Elf64_Shdr* parse_64_bit_section_headers(FILE* fptr, Elf64_Ehdr bit_64_header)
{
	int function_return_fseek;
	size_t function_return_fread;

	function_return_fseek = fseek(fptr, bit_64_header.e_shoff, SEEK_SET);
	if (function_return_fseek != 0)
	{
		raise_elf_error("Failed to retrieve 64 bit section header table");
		elf_cleanup(fptr);
		exit(1);
	}

	if (bit_64_header.e_shentsize != sizeof(Elf64_Shdr))
	{
		raise_elf_error("Failed to verify size");
		elf_cleanup(fptr);
		exit(1);
	}

	Elf64_Shdr* section_headers = malloc(bit_64_header.e_shentsize * bit_64_header.e_shnum);
	if (!section_headers)
	{
		raise_elf_error("Failed to alloc memory for 64 bit section headers");
		elf_cleanup(fptr);
		exit(1);
	}

	function_return_fread = fread(section_headers, bit_64_header.e_shentsize, bit_64_header.e_shnum, fptr);
	if (function_return_fread != bit_64_header.e_shnum)
	{
		printf("%d:%d\n", function_return_fread, bit_64_header.e_shnum);
		raise_elf_error("Failed to read 64 bit section headers");
		free(section_headers);
		elf_cleanup(fptr);
		exit(1);
	}
	
	return section_headers;
}

Elf32_Shdr* parse_32_bit_section_headers(FILE* fptr, Elf32_Ehdr bit_32_header)
{
	int function_return_fseek;
	size_t function_return_fread;

	function_return_fseek = fseek(fptr, bit_32_header.e_shoff, SEEK_SET);
	if (function_return_fseek != 0)
	{
		raise_elf_error("Failed to retrieve 32 bit section header table");
		elf_cleanup(fptr);
		exit(1);
	}

	if (bit_32_header.e_shentsize != sizeof(Elf32_Shdr))
	{
		raise_elf_error("Failed to verify size");
		elf_cleanup(fptr);
		exit(1);
	}
	

	Elf32_Shdr* section_headers = malloc(bit_32_header.e_shentsize * bit_32_header.e_shnum);
	if (!section_headers)
	{
		raise_elf_error("Failed to alloc memory for 32 bit section headers");
		elf_cleanup(fptr);
		exit(1);
	}

	function_return_fread = fread(section_headers, bit_32_header.e_shentsize, bit_32_header.e_shnum, fptr);
	if (function_return_fread != bit_32_header.e_shnum)
	{
		raise_elf_error("Failed to read 32 bit section headers");
		free(section_headers);
		elf_cleanup(fptr);
		exit(1);
	}

	return section_headers;
}




void dump_64_bit_section_headers(FILE* fptr, Elf64_Shdr* section_header, uint16_t shnum, uint16_t e_shstrndx)
{
	if (e_shstrndx >= shnum)
	{
		raise_elf_error("Section header string table index out of range");
		elf_cleanup(fptr);
		exit(EXIT_FAILURE);
	}
	
	Elf64_Shdr section_header_strings = section_header[e_shstrndx];
	
	if (fseek(fptr, 0, SEEK_END) != 0)
	{
		raise_elf_error("Cannot determine file size");
		elf_cleanup(fptr);
		exit(EXIT_FAILURE);
	}
	
	long file_end = ftell(fptr);
	if (file_end < 0 || section_header_strings.sh_offset > (uint64_t)file_end || section_header_strings.sh_size > (uint64_t)file_end - section_header_strings.sh_offset)
	{
		raise_elf_error("Section header string table out of file bounds");
		elf_cleanup(fptr);
		exit(EXIT_FAILURE);
	}

	char* section_header_string_table = calloc((section_header_strings.sh_size + 1), 1);
	if (!section_header_string_table)
	{
		raise_elf_error("Cannot alloc for section name");
		elf_cleanup(fptr);
		exit(EXIT_FAILURE);
	}
	if (fseek(fptr, section_header_strings.sh_offset, SEEK_SET) != 0)
	{
		free(section_header_string_table);
		raise_elf_error("Cannot locate section header name");
		exit(EXIT_FAILURE);
	}
	
	fread(section_header_string_table, 1, section_header_strings.sh_size, fptr);
	
	printf("               SECTION_HEADERS               \n");
	for (int i = 0; i < shnum; i++)
	{
		char* name;
		if (section_header[i].sh_name <= section_header_strings.sh_size)
		{
			name = section_header_string_table + section_header[i].sh_name;
		}
		else
		{
			name = "<invalid>";
		}

		printf("\tName of section (sh_name): %s\n", name);
		printf("\t\tSection Content and Semantics (sh_type): %u\n", section_header[i].sh_type);
		printf("\t\tSection Attribute Flags (sh_flags): %u\n", section_header[i].sh_flags);
		printf("\t\tSection Memory Image Address (sh_addr): %u\n", section_header[i].sh_addr);
		printf("\t\tSection Offset (sh_offset): %u\n", section_header[i].sh_offset);
		printf("\t\tSection Size (sh_size): %u\n", section_header[i].sh_size);
		printf("\t\tSection Index Link (sh_link): %u\n", section_header[i].sh_link);
		printf("\t\tExtra Information (sh_info): %u\n", section_header[i].sh_info);
		printf("\t\tAddress Alignment Contraints (sh_addralign): %u\n", section_header[i].sh_addralign);
		printf("\t\tEntry Size (sh_entsize): %u\n", section_header[i].sh_entsize);
	}
	free(section_header_string_table);
}

void dump_32_bit_section_headers(FILE* fptr, Elf32_Shdr* section_header, uint16_t shnum, uint16_t e_shstrndx)
{
	if (e_shstrndx >= shnum)
        {
                raise_elf_error("Section header string table index out of range");
                elf_cleanup(fptr);
                exit(EXIT_FAILURE);
        }

	Elf32_Shdr section_header_strings = section_header[e_shstrndx];

        if (fseek(fptr, 0, SEEK_END) != 0)
        {
                raise_elf_error("Cannot determine file size");
                elf_cleanup(fptr);
                exit(EXIT_FAILURE);
        }

        long file_end = ftell(fptr);
        if (file_end < 0 || section_header_strings.sh_offset > (uint64_t)file_end || section_header_strings.sh_size > (uint64_t)file_end - section_header_strings.sh_offset)
        {
                raise_elf_error("Section header string table out of file bounds");
                elf_cleanup(fptr);
                exit(EXIT_FAILURE);
        }

	char* section_header_string_table = calloc(section_header_strings.sh_size + 1, 1);
	if (!section_header_string_table)
	{
		raise_elf_error("Cannot alloc for section name");
		elf_cleanup(fptr);
		exit(EXIT_FAILURE);
	}
	if (fseek(fptr, section_header_strings.sh_offset, SEEK_SET) != 0)
	{
		free(section_header_string_table);
		raise_elf_error("Cannot locate section header name");
		exit(EXIT_FAILURE);
	}
	
	fread(section_header_string_table, 1, section_header_strings.sh_size, fptr);

    	printf("[              SECTION_HEADERS             ]\n");
    	for (int i = 0; i < shnum; i++)
    	{
	 	char* name;
                if (section_header[i].sh_name <= section_header_strings.sh_size)
                {
                        name = section_header_string_table + section_header[i].sh_name;
                }
                else
                {
                        name = "<invalid>";
                }

            	printf("\tName of section (sh_name): %s\n", name);
            	printf("\t\tSection Content and Semantics (sh_type): %u\n", section_header[i].sh_type);
            	printf("\t\tSection Attribute Flags (sh_flags): %u\n", section_header[i].sh_flags);
            	printf("\t\tSection Memory Image Address (sh_addr): %u\n", section_header[i].sh_addr);
            	printf("\t\tSection Offset (sh_offset): %u\n", section_header[i].sh_offset);
            	printf("\t\tSection Size (sh_size): %u\n", section_header[i].sh_size);
            	printf("\t\tSection Index Link (sh_link): %u\n", section_header[i].sh_link);
            	printf("\t\tExtra Information (sh_info): %u\n", section_header[i].sh_info);
            	printf("\t\tAddress Alignment Contraints (sh_addralign): %u\n", section_header[i].sh_addralign);
            	printf("\t\tEntry Size (sh_entsize): %u\n", section_header[i].sh_entsize);
    	}			
	free(section_header_string_table);
}


void bit_32_section_header_pointer_cleanup(Elf32_Shdr* section_header)
{
	if (section_header == NULL)
	{
		raise_elf_error("No valid 32 bit section header assigned");
		exit(1);
	}
	else
	{
		free(section_header);
	}
}

void bit_64_section_header_pointer_cleanup(Elf64_Shdr* section_header)
{
        if (section_header == NULL)
        {
                raise_elf_error("No valid 64 bit section header assigned");
                exit(1);
        }
        else
        {
                free(section_header);
        }
}


