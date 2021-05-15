#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "file_reader.h"
#define V "0.0.1"

extern unsigned char proximo(unsigned char*,
                             unsigned int, unsigned int,
                             unsigned char, unsigned int);

int get_cells_values(unsigned int N, unsigned char *a, const char* input);
unsigned char* start(unsigned char regla, unsigned int N, const char* filename);
int build_pbm();
