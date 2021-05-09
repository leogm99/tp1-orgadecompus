#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#define V "0.0.1"

unsigned char proximo(unsigned char* a,
                      unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N);

int main(int argc, char* const* argv){
    int opt;

    while (1){
        static struct option options[] = {
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {0,0,0,0}
        };

        opt = getopt_long(argc, argv, "hvo:", options, 0);
        if (opt == -1){
            break;
        }
        
        switch (opt){
            case 'h':
                printf("Uso:\n");
                printf(" autcel -h\n autcel -V\n autcel R N inputfile [-o outputprefix]");
                printf(" Opciones:\n");
                printf(" -h --help Imprime este mensaje.\n");
                printf(" -V --version Da la version de este programa.\n");
                printf(" -o Prefijo de los archivos de salida.\n");
                break;
            case 'v':
                printf("version %s\n", V);
                break;
            case 'o':
                // do stuff
                printf("%d %d\n", atoi(argv[1]), atoi(argv[2]));
                break;
            default:
                printf("Error\n");
                return -1;
        }
    }

    unsigned char regla = 30;
    unsigned char a[] = {0, 0, 1, 0, 0, 0, 1, 0, 1, 1};
    printf("Proximo %d\n", proximo(a, 0, 4, regla, 10));
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
    printf("l %d\n", l);
    printf("c %d\n", c);
    printf("r %d\n", r);

    // tenemos que acceder a regla en su bit lcr -> necesitamos una mascara para ese bit
    l <<= 2; // shifteamos l 2 posiciones (si es 0000 0001 quedara como 0000 0100)
    c <<= 1; // shifteamos c 1 posicion (si es 0000 0001 quedara como 0000 0010)
             // no shifteamos a r, (queda igual, asumo por ejemplo que es 0000 0000)

    char to_shift = l | c | r; // lo que tendremos que shiftear la mascara es (0000 0100 or 0000 0010 or 0000 0000 -> 0000 0110 == 6 -> bit 6)
                               // shifteamos una mascara tipo 0x1 110 posiciones (0x1 << 6)
    char mask = 0x1 << to_shift;
    return (regla & mask) ? 1 : 0; // delvolvemos el valor del bit 6 de la regla
}
