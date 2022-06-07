#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("arg %i: %s\n", i, argv[i]);   //la pos 0 es el nombre del programa
    }

    int nro = atoi(argv[4]);    //array to integer
    printf("es nro: %i\n", nro);
    return 0;
}