#include "autcel.h"
#include "file_reader.h"
#define TAMANIO_INICIAL_A 8
size_t get_cells_values(int n,unsigned char *a,int array_size){

    //unsigned char a[] = {0, 0, 1, 0, 0, 0, 1, 0, 1, 1};
/*
    int array_size = n * n * sizeof(unsigned char), 
    
    a = malloc(array_size);    //todo check null 
  */  unsigned char bit;
    int tope_a = 0;
   
    file_reader_t file;
    
    if (file_reader_init(&file, "inicial") == FR_ERROR)
        return FR_ERROR;
    while(((bit = file_reader_number(&file)) != FR_ERROR)){
        if (array_size<(tope_a+1)*sizeof(unsigned char)){
            a = realloc(a, array_size*2);    //todo check null 
            array_size*=2;
        }
        a[tope_a++] = bit;
    }

    file_reader_uninit(&file);

 //   unsigned char regla = 30;

   // printf("Proximo %d\n", proximo(a, 0, 4, regla, 10));

   // free(a);
}

// pensado como un arreglo donde cada char es una sola celda
unsigned char proximo(unsigned char* a,
                      unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N){
    char c = a[j + i*N]; // j es la celda a la que quiero acceder,
                             // i es la fila, pero como es solo un arreglo, tengo qeu moverme i*N bytes
                             // equivale a a[i][j]
                             // celda va a valer 1 o 0 en nuestro caso

    char l, r;

    if (!j){ // casos borde, si j es el bit 0 (la celda mas a la izq)
             // o el bit N-1 (la ultima celda), tenemos que hacer el tema circular
        l = a[j + i*N + N - 1]; // direccion del ultimo bit de la fila desreferenciada (el bit de la "izquierda");
        r = a[j + i*N + 1]; // celda derecha
    } else if (j == N - 1){ // si es el bit mas a la derecha
        l = a[j + i*N - 1]; // celda izquierda a "celda"
        r = a[j + i*N - N + 1]; // bit a la "derecha" de c (el primero de la fila)
    } else {
        l = a[j + i * N - 1];
        r = a[j + i * N + 1];
    }
 //   printf("l %d\n", l);
 //   printf("c %d\n", c);
 //   printf("r %d\n", r);

    // tenemos que acceder a regla en su bit lcr -> necesitamos una mascara para ese bit
    l <<= 2; // shifteamos l 2 posiciones (si es 0000 0001 quedara como 0000 0100)
    c <<= 1; // shifteamos c 1 posicion (si es 0000 0001 quedara como 0000 0010)
             // no shifteamos a r, (queda igual, asumo por ejemplo que es 0000 0000)

    char to_shift = l | c | r; // lo que tendremos que shiftear la mascara es (0000 0100 or 0000 0010 or 0000 0000 -> 0000 0110 == 6 -> bit 6)
                               // shifteamos una mascara tipo 0x1 110 posiciones (0x1 << 6)
    char mask = 0x1 << to_shift;
    return (regla & mask) ? 1 : 0; // delvolvemos el valor del bit 6 de la regla
}
