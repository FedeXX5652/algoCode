#include <stdio.h>

#define MAX_NUMEROS 10
#define ERROR -1


int enteros_antes_de_numero_rec(int vector[MAX_NUMEROS], int tope, int numero, int posicion){
    if(vector[posicion] == numero){
        return posicion;
    }
    else if(posicion >= tope){
        return ERROR;
    }
    else{
        return enteros_antes_de_numero_rec(vector, tope, numero, posicion + 1);
    }
}


int enteros_antes_de_numero(int vector[MAX_NUMEROS], int tope, int numero){
    return enteros_antes_de_numero_rec(vector, tope, numero, 0);
}


int suma_rec(int vector[MAX_NUMEROS], int tope, int posicion){
    // if(posicion >= tope){
        // return 0;   // se retorna 0 si se llega al final del vector ya que es el elemento neutro de la suma
    // }

    if(posicion >= tope-1){
        return vector[posicion];    // este caso retorna el elemento previo al final del vector
    }

    else{
        return vector[posicion] + suma_rec(vector, tope, posicion + 1);
    }
}


int suma(int vector[MAX_NUMEROS], int tope){
    return suma_rec(vector, tope, 0);
}


int suma_invertida(int vector[MAX_NUMEROS], int tope){
    if(tope <= 0){
        return 0;
    }

    return vector[tope-1] - suma_invertida(vector, tope-1);     // cuando se va para abajo hay que tener cuidado con el paso inicial
}


int main(){
    int vector[MAX_NUMEROS];
    int tope = 10;

    vector[0] = 95;
    vector[1] = 9;
    vector[2] = 21;
    vector[3] = 25;
    vector[4] = 17;
    vector[5] = 10;
    vector[6] = 19;
    vector[7] = 31;
    vector[8] = 1;
    vector[9] = 20;

    int enteros = enteros_antes_de_numero(vector, tope, 67);
    printf("posicion del nro: %i\n", enteros);

    int suma_vector = suma(vector, tope);
    printf("suma vector recursiva: %i\n", suma_vector);

    return 0;
}