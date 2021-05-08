#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#define V "0.0.1"

int main(int argc, char* const* argv){
    int opt;

    while (1){
        static struct option options[] = {
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {"output", required_argument, 0, 'o'},
            {0,0,0,0}
        };

        int id = 0; 
        opt = getopt_long(argc, argv, "hvo:", options, &id);
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
}
