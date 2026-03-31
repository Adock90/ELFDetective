#pragma once

#ifndef ELFERROR_H
#define ELFERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void raise_elf_error(const char* msg);

#endif
