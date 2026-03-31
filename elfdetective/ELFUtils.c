#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHOICES 6

typedef struct
{
	char* filename;
	char* fetch_array[MAX_CHOICES];
	int argument_violation;
} arg_data;

int verify_file_existance(char* filename)
{
	FILE* fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		return 1;
	}
	else
	{
		fclose(fptr);
		return 0;
	}
}

int is_string_in_array(char* string, char* array[])
{
	for (size_t i = 0; i < MAX_CHOICES; i++)
	{
		if (array[i] == NULL)
		{
			continue;
		}
		else if (strcmp(array[i], string) == 0)
		{
			return 0;
		}
	}
	return 1;
}

arg_data parse_args(int argc, char* argv[])
{
	int array_count = 0;
	int file_count = 0;
	char *arg_list[MAX_CHOICES] = {"--Header", "--Program-Header", "--Section-Headers", "--String-Symbol", "--Reloaction-Entries", "--Notes"};
	arg_data argument_content = { 0 };
	for (int i = 1; i < argc; i++)
	{
		if (verify_file_existance(argv[i]) == 0)
		{
			if (file_count != 0)
			{
				argument_content.argument_violation = 1;
			}
			else
			{
				argument_content.filename = argv[i];
				file_count++;
			}
		}
		else
		{
			if (is_string_in_array(argv[i], arg_list) == 0)
			{
				argument_content.fetch_array[array_count] = argv[i];
				array_count++;
			}
			else
			{
				argument_content.argument_violation = 1;
			}
		}
	}
	return argument_content;
}



