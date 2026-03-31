#include <stdlib.h>
#include <stdio.h>
#include <elf.h>

#include <ELFError.h>

Elf64_Phdr* get_64_bit_program_header(FILE* fptr, Elf64_Ehdr header)
{
	int header_table = fseek(fptr, header.e_phoff, SEEK_SET);
	if (header_table != 0)
	{
		raise_elf_error("Failed to seek to 64 bit program header table");
		fclose(fptr);
		exit(1);
	}

	Elf64_Phdr* program_header = malloc(header.e_phentsize * header.e_phnum);
	if (!program_header)
	{
		raise_elf_error("Failed to alloc memory for 64 bit program header table");
		fclose(fptr);
		exit(1);
	}

	size_t read_program_header = fread(program_header, header.e_phentsize, header.e_phnum, fptr);
	if (read_program_header != header.e_phnum)
	{
		raise_elf_error("Failed to read 64 bit program header");
		free(program_header);
		fclose(fptr);
		exit(1);
	}

	return program_header;
}

Elf32_Phdr* get_32_bit_program_header(FILE* fptr, Elf64_Ehdr header)
{       
        int header_table = fseek(fptr, header.e_phoff, SEEK_SET);
        if (header_table != 0)
        {       
                raise_elf_error("Failed to seek to 64 bit program header table");
                fclose(fptr);
                exit(1);
        }       
        
        Elf32_Phdr* program_header = malloc(header.e_phentsize * header.e_phnum);
        if (!program_header)
        {       
                raise_elf_error("Failed to alloc memory for 64 bit program header table");
                fclose(fptr);
                exit(1);
        }       
        
        size_t read_program_header = fread(program_header, header.e_phentsize, header.e_phnum, fptr);
        if (read_program_header != header.e_phnum)
        {       
                raise_elf_error("Failed to read 64 bit program header");
                free(program_header);
                fclose(fptr);
                exit(1);
        }       
        
        return program_header;
}

void dump_64_bit_program_header(Elf64_Phdr* program_header)
{
	printf("[               PROGRAM HEADER               ]\n");
	printf("\tArray Element Type (p_type): %u\n", program_header->p_type);
	printf("\tStart of file offset (p_offset): %u\n", program_header->p_offset);
	printf("\tVirtual Address of First Byte (p_vaddr): %u\n", program_header->p_vaddr);
	printf("\tPhysical Address (p_paddr): %u\n", program_header->p_paddr);
	printf("\tFile Image Size in Bytes (p_filesz): %u\n", program_header->p_filesz);
	printf("\tMemory Image Size in Bytes (p_memsz): %u\n", program_header->p_memsz);
	printf("\tBit mask of flags relevant to the segment (p_flags): %u\n", program_header->p_flags);
	printf("\tSegments aligned in memory (p_align): %u\n", program_header->p_align);
}

void dump_32_bit_program_header(Elf32_Phdr* program_header)
{
        printf("[               PROGRAM HEADER               ]\n");
        printf("\tArray Element Type (p_type): %u\n", program_header->p_type);
        printf("\tStart of file offset (p_offset): %u\n", program_header->p_offset);
        printf("\tVirtual Address of First Byte (p_vaddr): %u\n", program_header->p_vaddr);
        printf("\tPhysical Address (p_paddr): %u\n", program_header->p_paddr);
        printf("\tFile Image Size in Bytes (p_filesz): %u\n", program_header->p_filesz);
        printf("\tMemory Image Size in Bytes (p_memsz): %u\n", program_header->p_memsz);
        printf("\tBit mask of flags relevant to the segment (p_flags): %u\n", program_header->p_flags);
        printf("\tSegments aligned in memory (p_align): %u\n", program_header->p_align);
}


void bit_32_program_header_pointer_cleanup(Elf32_Phdr* program_header)
{
	if (program_header == NULL)
	{
		raise_elf_error("No valid 32 bit program header assigned");
		exit(1);
	}
	else
	{
		free(program_header);
	}
}

void bit_64_program_header_pointer_cleanup(Elf64_Phdr* program_header)
{
        if (program_header == NULL)
        {
                raise_elf_error("No valid 64 bit program header assigned");
                exit(1);
        }
        else
        {
                free(program_header);
        }
}


