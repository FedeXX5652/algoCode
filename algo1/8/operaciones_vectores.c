#include <stdio.h>

#define MAX_ELEMENTOS 100

void print_vector(int v[2 * MAX_ELEMENTOS], int n){
    int i;
    for(i=0; i<n; i++){
        printf("%d ", v[i]);
    }
    printf("\n\n");
}


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


int main(){
    int vector_primos[MAX_ELEMENTOS] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int vector_impares[MAX_ELEMENTOS] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};

    int tope_primos = 9;
    int tope_impares = 12;

    int vector_mezcla[2 * MAX_ELEMENTOS];
    int tope_mezcla = 0;

    mezcla(vector_primos, vector_impares, tope_primos, tope_impares, vector_mezcla, &tope_mezcla);
    printf("MEZCLA:\n");
    print_vector(vector_mezcla, tope_mezcla);


    int vector_union[2 * MAX_ELEMENTOS];
    int tope_union = 0;

    v_union(vector_primos, vector_impares, tope_primos, tope_impares, vector_union, &tope_union);
    printf("UNION:\n");
    print_vector(vector_union, tope_union);

/*
    int vector_union[2 * MAX_ELEMENTOS];
    int tope_union = 0;

    v_union(vector_primos, vector_impares, tope_primos, tope_impares, vector_union, &tope_union);
    printf("UNION:\n");
    print_vector(vector_union, tope_union);
*/
    return 0;
}