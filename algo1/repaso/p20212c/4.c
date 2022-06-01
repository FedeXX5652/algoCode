#include <stdio.h>

#define MAX_COLUMNAS 20
#define MAX_FILAS 20

typedef struct campo{
    int tope_filas;
    int tope_columnas;
    char cuadrantes[MAX_FILAS][MAX_COLUMNAS];
} campo_t;

void encontrar_chloe(campo_t campo, int *fila, int *columna){
    int i, j;
    int encontrada = 0;
    for(i = 0; i < campo.tope_filas; i++){
        for(j = 0; j < campo.tope_columnas; j++){
            if(campo.cuadrantes[i][j] == 'C'){
                *fila = i;
                *columna = j;
                encontrada = 1;
            }    if(!encontrada){
        printf("No se encontro a Chloe\n");
    }
        }
    }
}

bool oso_en_vision(campo_t campo){
    int i, j;
    int encontrado = 0;
    
    if(encontrado){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    campo_t campo;
    int i, j;

    int fila, columna = 0;

    campo.tope_filas = MAX_FILAS;
    campo.tope_columnas = MAX_COLUMNAS;

    for(i = 0; i < campo.tope_filas; i++){
        for(j = 0; j < campo.tope_columnas; j++){
            campo.cuadrantes[i][j] = '-';
        }
    }

    campo.cuadrantes[5][8] = 'C';

    encontrar_chloe(campo, &fila, &columna);
    printf("Chloe esta en la posicion (%d, %d)\n", fila, columna);
    return 0;
}