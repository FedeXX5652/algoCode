#include <stdio.h>
#include <stdbool.h>

#define MAX_CANALES 20

int salto_canal_rec(int canal[MAX_CANALES], int tope_canales, int canal_buscado, int posicion){
    if(canal[posicion] == canal_buscado){
        return 0;
    }
    return 1 + salto_canal_rec(canal, tope_canales, canal_buscado, canal[posicion]);
}

int salto_canal(int canal[MAX_CANALES], int tope_canales, int canal_buscado){
    return salto_canal_rec(canal, tope_canales, canal_buscado, 0);
}

int main() {
    int vector[MAX_CANALES];
    int tope = 10;

    vector[0] = 7;
    vector[1] = 9;
    vector[2] = 6;
    vector[3] = 5;
    vector[4] = 3;
    vector[5] = 0;
    vector[6] = 4;
    vector[7] = 9;
    vector[8] = 1;
    vector[9] = 2;

    int movimientos = salto_canal(vector, tope, 3);

    printf("%d\n", movimientos);
    return 0;
}