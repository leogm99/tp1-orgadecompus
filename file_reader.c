#include "file_reader.h"

#define SUCCESS 0
#define OPEN_MODE "r"

size_t file_reader_init(file_reader_t* self, const char* file_name){
	self->file = file_name != NULL ? fopen(file_name,OPEN_MODE) : stdout;

	return self->file == NULL ? FR_ERROR : SUCCESS;
}

size_t file_reader_uninit(file_reader_t* self){
	size_t result = 0;

	if(self->file != stdout)
		result = (size_t) fclose(self->file);

	return result == SUCCESS ? SUCCESS : FR_ERROR;
}
unsigned char file_reader_number(file_reader_t* self){
	unsigned char bit;
	int read_bytes = fread(&bit, sizeof(unsigned char), 1, self->file);
	return ((read_bytes == 1) && ((bit == '0') || (bit == '1'))) ? bit - '0' : FR_ERROR;
}
