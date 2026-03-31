#ifndef ELFDETECTIVE_H
#define ELFDETECTIVE_H

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include <ELFError.h>
#include <ELFFiles.h>
#include <ELFHeader.h>
#include <ELFProgramHeader.h>
#include <ELFSection.h>
#include <ELFUtils.h>

void help();

int exec_main(int argc, char* argv[]);

#endif
