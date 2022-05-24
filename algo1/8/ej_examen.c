#include <stdio.h>

#define MAX_NUMEROS 25


int vueltas_rec(int vector[MAX_NUMEROS], int tope, int numero, int posicion){
    if(vector[posicion] == numero){
        return 0;
    }
    return 1 + vueltas_rec(vector, tope, numero, vector[posicion]);
}


int vueltas(int vector[MAX_NUMEROS], int tope, int numero){
    return vueltas_rec(vector, tope, numero, 0);
}


int main(){
    int vector[MAX_NUMEROS];
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

    int movimientos = vueltas(vector, tope, 3);

    printf("%d\n", movimientos);

    return 0;
}