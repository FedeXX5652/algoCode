#include <stdio.h>

#define MAX_EDADES 120

int main(){

    int edades[MAX_EDADES];
    int last_edades = 0;

    edades[last_edades] = 76;
    last_edades++;

    edades[last_edades] = 20;
    last_edades++;

    edades[last_edades] = 88;
    last_edades++;

    // printf("Decime tu edad: ");
    // scanf("%d", &edades[last_edades]);
    // printf("La edad ingresada es: %d\n", edades[last_edades]);
    // last_edades++;

    for(int i = 0; i < last_edades; i++){
        printf("La edad %d es: %d\n", i, edades[i]);
    }

    return 0;
}