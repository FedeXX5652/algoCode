#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MES 20
#define FIESTAS 15

const char *ENERO = "enero";
const char *FEBRERO = "febrero";
const char *DICIEMBRE = "diciembre";

bool es_festividad(char mes[MES]){
    if((strcmp(mes, "enero") == 0) || (strcmp(mes, "febrero") == 0) || (strcmp(mes, "diciembre") == 0)){
        return true;
    }
    return false;
}

int fiestas_rec(char fiestas[MES][FIESTAS], int tope, int pos){
    if(pos == tope){
        return 0;
    }
    if(es_festividad(fiestas[pos])){
        return 1 + fiestas_rec(fiestas, tope, pos + 1);
    }
    return fiestas_rec(fiestas, tope, pos + 1);
}

int fiestas_verano(char fiestas[MES][FIESTAS], int tope){
    return fiestas_rec(fiestas, tope, 0);
}

int main(){
    char fiestas[MES][FIESTAS] = {"enero", "marzo", "diciembre", "febrero", "diceimbre"};
    int tope = 5;
    printf("%d\n", fiestas_verano(fiestas, tope));
    return 0;
}