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
            default:
            		if (argc != 4 && argc != 6){
            		    fprintf(stderr,"%s", "received wrong number of arguments, expected 4 or 6\n");
                    return -1;
            		}
                    unsigned char* a = start(atoi(argv[1]), atoi(argv[2]), argv[3]);
                    if (!a){
                        return -1;
                    }
            		build_pbm((argc == 6 ? argv[5] : argv[3]), a, atoi(argv[2]));
                    return 0;
        }
    }

    return 0;
}
