#ifndef ELFUTILS_H
#define ELFUTILS_H

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

int verify_file_existance(char* filename);

int is_string_in_array(char* string, char* array[]);

arg_data parse_args(int argc, char* argv[]);


#endif
