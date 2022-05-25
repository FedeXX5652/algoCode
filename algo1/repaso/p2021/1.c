#include <stdio.h>
#include <stdbool.h>

#define MAX_CARCEL 20

const int NORMAL = 'N';
const int VILLANO = 'V';
const int SECUAZ = 'S';


bool secuaz_cerca(char carcel[MAX_CARCEL][MAX_CARCEL], int fila, int columna){
    return (carcel[fila-1][columna] == SECUAZ || carcel[fila+1][columna] == SECUAZ || carcel[fila][columna-1] == SECUAZ || carcel[fila][columna+1] == SECUAZ);
}


bool es_carcel_valida(char carcel[MAX_CARCEL][MAX_CARCEL], int filas, int columnas){

    bool es_carcel_valida = true;
    int fila = 0;
    int columna = 0;
    
    while(es_carcel_valida && fila < filas){
        while(es_carcel_valida && columna < columnas){
            if(carcel[fila][columna] == VILLANO && secuaz_cerca(carcel, fila, columna)){
                es_carcel_valida = false;
            }
            columna++;
        }
        fila++;
    }

    return es_carcel_valida;
}


int main(){

    //char carcel_valida[MAX_CARCEL][MAX_CARCEL] = {{'N', 'V', 'N', 'N'}, {'N', 'V', 'N', 'S'}, {'N', 'V', 'N', 'N'}, {'S', 'N', 'S', 'S'}};
    char carcel_invalida[MAX_CARCEL][MAX_CARCEL] = {{'N', 'V', 'V', 'V'}, {'N', 'N', 'N', 'S'}, {'N', 'V', 'N', 'S'}, {'S', 'S', 'N', 'S'}};
    
    bool returned = esta_organizada(carcel_invalida, 4, 4);

    if (returned == true){
        printf("es carcel valida\n");
    }
    else{
        printf("no es carcel valida\n");
    }

    return 0;
}
