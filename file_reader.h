#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define FR_ERROR 5

typedef struct file_reader{
	FILE* file;
} file_reader_t;

size_t file_reader_init(file_reader_t* self, const char* file_name);

size_t file_reader_uninit(file_reader_t* self);

// Lee del archivo correspondiente un bit. Devuelve FR_ERROR al terminar.
unsigned char file_reader_number(file_reader_t* self);

#endif
