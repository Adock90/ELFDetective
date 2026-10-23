#include <stdlib.h>
#include <stdio.h>
#include <elf.h>

#include <ELFError.h>
#include <ELFFiles.h>

Elf64_Phdr* get_64_bit_program_header(FILE* fptr, Elf64_Ehdr header)
{
	int header_table = fseek(fptr, header.e_phoff, SEEK_SET);
	if (header_table != 0)
	{
		raise_elf_error("Failed to seek to 64 bit program header table");
		fclose(fptr);
		exit(1);
	}
	
	if (header.e_phnum == 0)
	{
		raise_elf_error("No 64 bit program header entries");
		fclose(fptr);
		exit(EXIT_FAILURE);
	}

	if (header.e_phentsize != sizeof(Elf64_Phdr))
        {
                raise_elf_error("Failed to verify sizeof Program Header");
                fclose(fptr);
                exit(EXIT_FAILURE);
        }
	

	
	size_t file_size = get_file_size(fptr);
	uint64_t table_bytes = (uint64_t)header.e_phnum * sizeof(Elf64_Phdr);
	if (header.e_phoff > file_size || table_bytes > file_size - header.e_phoff)
	{
		raise_elf_error("Program header tables are too big");
		fclose(fptr);
		exit(EXIT_FAILURE);
	}	

	Elf64_Phdr* program_header = malloc((size_t)header.e_phentsize * header.e_phnum);
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

Elf32_Phdr* get_32_bit_program_header(FILE* fptr, Elf32_Ehdr header)
{       
        int header_table = fseek(fptr, header.e_phoff, SEEK_SET);
        if (header_table != 0)
        {       
                raise_elf_error("Failed to seek to 64 bit program header table");
                fclose(fptr);
                exit(1);
        }       
        
        if (header.e_phnum == 0)
        {
                raise_elf_error("No 64 bit program header entries");
                fclose(fptr);
                exit(EXIT_FAILURE);
        }

	if (header.e_phentsize != sizeof(Elf32_Phdr))
	{
		raise_elf_error("Failed to verify sizeof Program Header");
		fclose(fptr);
		exit(EXIT_FAILURE);
	}


	uint32_t table_bytes = (uint32_t)header.e_phnum * sizeof(Elf32_Phdr);
        if (header.e_phoff > get_file_size(fptr) || table_bytes > get_file_size(fptr) - header.e_phoff)
        {
                raise_elf_error("Program header tables are too big");
                fclose(fptr);
                exit(EXIT_FAILURE);
        }	

        Elf32_Phdr* program_header = malloc((size_t)header.e_phentsize * header.e_phnum);
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

void dump_64_bit_program_header(Elf64_Phdr* program_header, uint16_t phnum)
{
	printf("[               PROGRAM HEADER               ]\n\n");
	for (int i = 0; i < phnum; i++)
	{
		printf("\tProgram Header: %d\n", i);
		printf("\t\tArray Element Type (p_type): 0x%" PRIx32 "\n", program_header[i].p_type);
		printf("\t\tStart of file offset (p_offset): 0x%" PRIx64 "\n", program_header[i].p_offset);
		printf("\t\tVirtual Address of First Byte (p_vaddr): 0x%" PRIx64 "\n", program_header[i].p_vaddr);
		printf("\t\tPhysical Address (p_paddr): 0x%" PRIx64 "\n", program_header[i].p_paddr);
		printf("\t\tFile Image Size in Bytes (p_filesz): 0x%" PRIx64 "\n", program_header[i].p_filesz);
		printf("\t\tMemory Image Size in Bytes (p_memsz): 0x%" PRIx64 "\n", program_header[i].p_memsz);
		printf("\t\tBit mask of flags relevant to the segment (p_flags): 0x%" PRIx32 "\n", program_header[i].p_flags);
		printf("\t\tSegments aligned in memory (p_align): 0x%" PRIx64 "\n\n", program_header[i].p_align);
	}
}

void dump_32_bit_program_header(Elf32_Phdr* program_header, uint16_t phnum)
{
	printf("[               PROGRAM HEADER               ]\n\n");
	for (int i = 0; i < phnum; i++)
	{
		printf("\tProgram Header: %d\n", i);
                printf("\t\tArray Element Type (p_type): 0x%" PRIx32 "\n", program_header[i].p_type);
                printf("\t\tStart of file offset (p_offset): 0x%" PRIx32 "\n", program_header[i].p_offset);
                printf("\t\tVirtual Address of First Byte (p_vaddr): 0x%" PRIx32 "\n", program_header[i].p_vaddr);
                printf("\t\tPhysical Address (p_paddr): 0x%" PRIx32 "\n", program_header[i].p_paddr);
                printf("\t\tFile Image Size in Bytes (p_filesz): 0x%" PRIx32 "\n", program_header[i].p_filesz);
                printf("\t\tMemory Image Size in Bytes (p_memsz): 0x%" PRIx32 "\n", program_header[i].p_memsz);
                printf("\t\tBit mask of flags relevant to the segment (p_flags): 0x%" PRIx32 "\n", program_header[i].p_flags);
                printf("\t\tSegments aligned in memory (p_align): 0x%" PRIx32 "\n\n", program_header[i].p_align);
        }
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


