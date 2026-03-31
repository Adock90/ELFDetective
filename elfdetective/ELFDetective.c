#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include <ELFError.h>
#include <ELFFiles.h>
#include <ELFHeader.h>
#include <ELFProgramHeader.h>
#include <ELFSection.h>
#include <ELFUtils.h>

void help()
{
	printf("Usage: ELFDetective [<file>] [<options>]\n"
		"\t[<file>]: The path to the file you want to inspect.\n"
		"\t\tExample: ELFDetective /bin/bash --Header\n"
		"\n\t[<options>]: The different headers and sections of the elf to inspect.\n"
		"\t\tExamples: 'ELFDetective --Header' 'ELFDetective --Section-Headers'. Even have multiple 'ELFDetective --Header --Program-Header'\n"
	       "\t\tOptions: Include '--Header', '--Program-Header', '--Section-Headers'\n"
	      );
}


int exec_main(int argc, char* argv[])
{
	HeaderArch arch = {0};
	arg_data argument_parsing = parse_args(argc, argv);
	if (argument_parsing.filename == NULL)
	{
		raise_elf_error("No file specified");
		help();
		return EXIT_FAILURE;
	}
	else if (argument_parsing.argument_violation == 1)
	{
		raise_elf_error("Arguments Provided are ambiguous");
		help();
		return EXIT_FAILURE;
	}

	FILE* file_handle_ptr = get_elf_file_handle(argument_parsing.filename);
	Elf64_Ehdr elf_header = get_elf_header(file_handle_ptr);
	arch = check_if_elf_is_valid(elf_header);
	if (arch.Elf64 == -1 & arch.Elf32 == -1)
	{
		return EXIT_FAILURE;
	}
	if (is_string_in_array("--Header", argument_parsing.fetch_array) == 0)
	{
		dump_elf_header_data(elf_header);
	}
	if (arch.Elf64 == 1 & arch.Elf32 == 0)
	{
		Elf64_Ehdr bit_64_header;
		
		if (is_string_in_array("--Program-Header", argument_parsing.fetch_array) == 0)
		{
			Elf64_Phdr* program_header = get_64_bit_program_header(file_handle_ptr, elf_header);
			dump_64_bit_program_header(program_header);
			bit_64_program_header_pointer_cleanup(program_header);
		}
		else if (is_string_in_array("--Section-Headers", argument_parsing.fetch_array) == 0)
		{
			Elf64_Shdr* section_headers = parse_64_bit_section_headers(file_handle_ptr, elf_header);
			dump_64_bit_section_headers(file_handle_ptr, section_headers, elf_header.e_shnum, elf_header.e_shstrndx);
			bit_64_section_header_pointer_cleanup(section_headers);
		}
				

	}
	else if (arch.Elf32 == 1 & arch.Elf64 == 0)
	{
		Elf32_Ehdr bit_32_header;
		
		if (is_string_in_array("--Program-Header", argument_parsing.fetch_array) == 0)
		{
			Elf32_Phdr* program_header = get_32_bit_program_header(file_handle_ptr, elf_header);
			dump_32_bit_program_header(program_header);
			bit_32_program_header_pointer_cleanup(program_header);
		}
		else if (is_string_in_array("--Section-Headers", argument_parsing.fetch_array) == 0)
		{
			Elf32_Shdr* section_headers = parse_32_bit_section_headers(file_handle_ptr, bit_32_header);
			dump_32_bit_section_headers(file_handle_ptr, section_headers, elf_header.e_shnum, elf_header.e_shstrndx);
			bit_32_section_header_pointer_cleanup(section_headers);
		}

	}
	else
	{
		raise_elf_error("No Valid Elf type value");
	}
	return EXIT_SUCCESS;
}
