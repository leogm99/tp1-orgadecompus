#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "file_reader.h"
#define V "0.0.1"

size_t get_cells_values();

unsigned char proximo(unsigned char* a,
                      unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N);