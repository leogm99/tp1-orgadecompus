#include <stdio.h>
#include <string.h>
#include "autcel.h"

int main(int argc, char* const* argv){
    int opt;
    while (1){
        static struct option options[] = {
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {0,0,0,0}
        };
        opt = getopt_long(argc, argv, "hvo::", options, 0);
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
            		if (argc != 5 && argc != 6){
                    printf("%d\n", argc);
            		    fprintf(stderr,"%s", "-o received wrong number of arguments, expected 6\n");
                    return -1;
            		}
                unsigned char* a = start(atoi(argv[1]), atoi(argv[2]), argv[3]);
                if (!a){
                    return -1;
                }
            		build_pbm((argc == 6 ? argv[5] : argv[3]), a, atoi(argv[2]));
                break;
            default:
                printf("Error\n");
                return -1;
        }
    }

    return 0;
}
