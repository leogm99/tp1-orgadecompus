#include <stdio.h>
#include <string.h>
#include "autcel.h"

int main(int argc, char* const* argv){
    int opt;
/*
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
*/
    unsigned int n = atoi(argv[2]);
    int array_size = n * n * sizeof(unsigned char);
    unsigned char* a = malloc(array_size); 
    get_cells_values(n,a,array_size);
    unsigned char regla = (unsigned char)atoi(argv[1]);

   // for (int j = 0; j<n; ++j) printf("%d",a[j]);
    printf("\n");
    for (int i = 0; i < n*(n-1); ++i){
         unsigned char caracter = proximo(a,i/n,i%n,regla,n);
       //  printf("%d",caracter);
       //  if ((i+1)%n == 0) printf("\n");
         a[i+n] = caracter;
    }

    //Guardo el arreglo en una imagen pbm
    char* nombre_salida = "";
    if (argc == 5) nombre_salida = argv[4];
    else nombre_salida = argv[3];
    strstr(nombre_salida,".pbm");
    
    int i,temp = 0;
    FILE* pbmimg;
    pbmimg = fopen(nombre_salida, "wb");
    // Writing Magic Number to the File
    fprintf(pbmimg, "P1\n"); 
    // Writing Width and Height
    fprintf(pbmimg, "%d %d\n", n, n); 
    int count = 0;
    for (i = 0; i < n*n; i++) {
        temp = a[i];
        // Writing the gray values in the 2D array to the file
        fprintf(pbmimg, "%d ", temp);
        if ((i+1)%n==0) fprintf(pbmimg, "\n");
    }
    fclose(pbmimg);

    free(a);
    return 0;
}

/*
#include <stdio.h>
#include "controller.h"

#define MIN_ARGS 2
#define MAX_ARGS 8

int main(int argc, char const *argv[]){
	if (argc < MIN_ARGS || argc > MAX_ARGS) return (int)error_handler(ARGV_QUANTITY);

	controller_t controller;

	size_t controller_ret, execute_ret;

	controller_ret = controller_init(&controller, argc, argv);
	if(controller_ret != 0){
		error_handler(controller_ret);
		return -1;
	}

	execute_ret = controller_execute(&controller);
	if(execute_ret != 0){
		error_handler(execute_ret);
		return -1;
	}

	controller_destroy(&controller);

	return 0;
}

*/