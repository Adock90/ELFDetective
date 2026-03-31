#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void raise_elf_error(const char* msg)
{
	fprintf(stderr, "[ELFDetective] %s\n", msg);
}

