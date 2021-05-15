// pensado como un arreglo donde cada char es una sola celda
#include <stdio.h>

unsigned char proximo(unsigned char* a,
                      unsigned int i, unsigned int j,
                      unsigned char regla, unsigned int N){
    size_t bytes = i * N;
    char c = a[j + bytes];
    char l, r;

    if (!j){
        l = a[j + bytes + N - 1];
        r = a[j + bytes + 1];
    } else if (j == N - 1){
        l = a[j + bytes - 1];
        r = a[j + bytes - N + 1];
    } else {
        l = a[j + bytes - 1];
        r = a[j + bytes + 1];
    }

    l <<= 2;
    c <<= 1;
    char to_shift = l | c | r;
    char mask = 0x1 << to_shift;
    return (regla & mask) ? 1 : 0;
}
