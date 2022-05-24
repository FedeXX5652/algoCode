#include <stdio.h>

#define MAX_ELEMENTOS 100

void print_vector(int v[2 * MAX_ELEMENTOS], int n){
    int i;
    for(i=0; i<n; i++){
        printf("%d ", v[i]);
    }
    printf("\n\n");
}

/*
pre:vector1 y vector2 deben estar ordenados y no deben tener elementos repetidos
    tope1 y top2 deben ser >= 0
post:vector_resultado tendra los elementos ordenados
*/
void mezcla(int vector1[MAX_ELEMENTOS], int vector2[MAX_ELEMENTOS], int tope1, int tope2, int vector_resultado[2 * MAX_ELEMENTOS], int* tope_resultado){
    int i = 0;
    int j = 0;

    // secuencia de mezcla

    while(i < tope1 && j < tope2){
        if(vector1[i] < vector2[j]){
            vector_resultado[*tope_resultado] = vector1[i];
            i++;
        }else{
            vector_resultado[*tope_resultado] = vector2[j];
            j++;
        }
        *tope_resultado = *tope_resultado + 1;
    }

    // los siguientes while son para completar el vector con los elementos que quedan en caso de no completarse

    while(i < tope1){
        vector_resultado[*tope_resultado] = vector1[i];
        i++;
        *tope_resultado = *tope_resultado + 1;
    }

    while(j < tope2){
        vector_resultado[*tope_resultado] = vector2[j];
        j++;
        *tope_resultado = *tope_resultado + 1;
    }
}

/*
pre:vector1 y vector2 deben estar ordenados y no deben tener elementos repetidos
    tope1 y top2 deben ser >= 0
post:vector_resultado tendra los elementos ordenados sin repetir
*/
void v_union(int vector1[MAX_ELEMENTOS], int vector2[MAX_ELEMENTOS], int tope1, int tope2, int vector_resultado[2 * MAX_ELEMENTOS], int* tope_resultado){
    int i = 0;
    int j = 0;

    // secuencia de unión

    while(i < tope1 && j < tope2){
        if(vector1[i] < vector2[j]){
            vector_resultado[*tope_resultado] = vector1[i];
            i++;
        }
        else if(vector1[i] > vector2[j]){
            vector_resultado[*tope_resultado] = vector2[j];
            j++;
        }
        else{
            vector_resultado[*tope_resultado] = vector1[i];
            i++;
            j++;
        }
        *tope_resultado = *tope_resultado + 1;
    }

    // los siguientes while son para completar el vector con los elementos que quedan en caso de no completarse

    while(i < tope1){
        vector_resultado[*tope_resultado] = vector1[i];
        i++;
        *tope_resultado = *tope_resultado + 1;
    }

    while(j < tope2){
        vector_resultado[*tope_resultado] = vector2[j];
        j++;
        *tope_resultado = *tope_resultado + 1;
    }
}


/*
pre:vector1 y vector2 deben estar ordenados y no deben tener elementos repetidos
    tope1 y top2 deben ser >= 0
post:Llena el vector_resultado con los elementos de vector1 que NO esten en vector2 y establece su tope
*/
void diferencia(int vector1[MAX_ELEMENTOS], int vector2[MAX_ELEMENTOS], int tope1, int tope2, int vector_resultado[2 * MAX_ELEMENTOS], int* tope_resultado){
    int i = 0;
    int j = 0;

    // secuencia de diferencia

    while(i < tope1 && j < tope2){
        if(vector1[i] < vector2[j]){    // si el elemento de vector1 es menor que el de vector2, se agrega al vector_resultado
            vector_resultado[*tope_resultado] = vector1[i];
            i++;
            *tope_resultado = *tope_resultado + 1;
        }
        else if(vector1[i] > vector2[j]){   // si el elemento de vector1 es mayor que el de vector2, no se incluye en el vector_resultado
            j++;
        }
        else{   // si son iguales
            i++;
            j++;
        }
    }

    // los siguientes while son para completar el vector con los elementos que quedan en caso de no completarse

    while(i < tope1){
        vector_resultado[*tope_resultado] = vector1[i];
        i++;
        *tope_resultado = *tope_resultado + 1;
    }
}


void interseccion(int vector1[MAX_ELEMENTOS], int vector2[MAX_ELEMENTOS], int tope1, int tope2, int vector_resultado[2 * MAX_ELEMENTOS], int* tope_resultado){
    int i = 0;
    int j = 0;

    // secuencia de intersección

    while(i < tope1 && j < tope2){
        if(vector1[i] < vector2[j]){    // si el elemento de vector1 es menor que el de vector2, no se incluye en el vector_resultado
            i++;
        }
        else if(vector1[i] > vector2[j]){   // si el elemento de vector1 es mayor que el de vector2, no se incluye en el vector_resultado
            j++;
        }
        else{   // si son iguales
            vector_resultado[*tope_resultado] = vector1[i];
            *tope_resultado = *tope_resultado + 1;
            i++;
            j++;
        }
    }
}


int main(){
    int vector_primos[MAX_ELEMENTOS] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
    int vector_impares[MAX_ELEMENTOS] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};

    int tope_primos = 9;
    int tope_impares = 12;

    int vector_mezcla[2 * MAX_ELEMENTOS];
    int tope_mezcla = 0;

    printf("MEZCLA:\n");
    mezcla(vector_primos, vector_impares, tope_primos, tope_impares, vector_mezcla, &tope_mezcla);
    print_vector(vector_mezcla, tope_mezcla);


    int vector_union[2 * MAX_ELEMENTOS];
    int tope_union = 0;

    printf("UNION:\n");
    v_union(vector_primos, vector_impares, tope_primos, tope_impares, vector_union, &tope_union);
    print_vector(vector_union, tope_union);


    int vector_diferencia[2 * MAX_ELEMENTOS];
    int tope_diferencia = 0;

    printf("DIFERENCIA:\n");
    diferencia(vector_impares, vector_primos, tope_impares, tope_primos, vector_diferencia, &tope_diferencia);
    print_vector(vector_diferencia, tope_diferencia);


    int vector_interseccion[2 * MAX_ELEMENTOS];
    int tope_interseccion = 0;

    printf("INTERSECCION:\n");
    interseccion(vector_primos, vector_impares, tope_primos, tope_impares, vector_interseccion, &tope_interseccion);
    print_vector(vector_interseccion, tope_interseccion);

    return 0;
}