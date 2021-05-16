#include "autcel.h"
#include "file_reader.h"
#define N_LIM 1000 // 1 mb
#define MAX_FILE_LENGTH 40

int get_cells_values(unsigned int N, unsigned char *a, const char* input){
    unsigned char bit;
    unsigned int tope_a = 0;

    file_reader_t file;

    if (file_reader_init(&file, input) == FR_ERROR)
        return FR_ERROR;
    while(((bit = file_reader_number(&file)) != FR_ERROR)){
        a[tope_a++] = bit;
    }

    if (tope_a != N) return -1;
    file_reader_uninit(&file);

    return 0;
}

unsigned char* start(unsigned char regla, unsigned int N, const char* filename){
  printf("%s\n","Leyendo estado inicial...");
  if (N > N_LIM){
    fprintf(stderr, "%s", "N exceded max limit\n");
    return NULL;
  }

  unsigned int array_size = N * N * sizeof(unsigned char);
  unsigned char* a = malloc(array_size);
  if(!a){
    fprintf(stderr, "%s", "Could not allocate memory\n");
    return NULL;
  }

  if(get_cells_values(N, a, filename) != 0) {
      fprintf(stderr, "%s", "Bad file format\n");
      free(a);
      return NULL;
  }

  for (size_t i = 0; i < N*(N-1); ++i){
       unsigned char caracter = proximo(a, i/N, i % N, regla, N);
       a[i + N] = caracter;
  }
  return a;
}

int build_pbm(const char* outputprefix,
              unsigned char* a, unsigned int N){
  //Guardo el arreglo en una imagen pbm
  printf("%d\n", N);
  char outformat[5] = ".pbm";
  char filename[MAX_FILE_LENGTH] = { 0 };

  strncpy(filename, outputprefix, MAX_FILE_LENGTH);
  strncat(filename, outformat, 5);
  printf("Grabando %s\n", filename);

  size_t i, temp = 0;
  FILE* pbmimg;
  pbmimg = fopen(filename, "wb");
  fprintf(pbmimg, "P1\n");

  fprintf(pbmimg, "%d %d\n", N, N);

  for (i = 0; i < N * N; i++) {
      temp = a[i];
      fprintf(pbmimg, "%d ", (int)temp);
      if ((i+1)%N==0) fprintf(pbmimg, "\n");
  }

  fclose(pbmimg);
  printf("Listo\n");

  free(a);
  return 0;
}
