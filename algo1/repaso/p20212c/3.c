#include <stdio.h>

#define MAX_CARAMELOS 10
#define MAX_NOMBRE_COLOR 20

typedef struct caramelo {
   char color[MAX_NOMBRE_COLOR];
   unsigned int radio; //en milímetros
} caramelo_t;

void ordenar_por_radio(caramelo_t caramelos[MAX_CARAMELOS], int tope_caramelos){
    int i, j;
    caramelo_t aux;
    for(i = 0; i < tope_caramelos; i++){
        for(j = i + 1; j < tope_caramelos; j++){
            if(caramelos[i].radio < caramelos[j].radio){
                aux = caramelos[i];
                caramelos[i] = caramelos[j];
                caramelos[j] = aux;
            }
        }
    }
}


int busqueda_binaria_rec(caramelo_t caramelos[MAX_CARAMELOS], int inicio, int fin, int buscado){
    int medio = (inicio + fin) / 2;

    for(int i = inicio; i <= fin; i++){
        printf("%d ", caramelos[i].radio);
    }
    printf("\n");

    if(inicio > fin){
        printf("No se encontro el valor\n");
        return -1;
    }
    if(caramelos[medio].radio == buscado){
        printf("Se encontro el valor\n");
        return medio;
    }
    if(caramelos[medio].radio < buscado){
        printf("%d > %d\n", caramelos[medio].radio, buscado);
        return busqueda_binaria_rec(caramelos, inicio, medio - 1, buscado);
    }
    if(caramelos[medio].radio > buscado){
        printf("%d < %d\n", caramelos[medio].radio, buscado);
        return busqueda_binaria_rec(caramelos, medio + 1, fin, buscado);
    }
    printf("\n");
}


int busqueda_binaria(caramelo_t caramelos[MAX_CARAMELOS], int tope_caramelos, unsigned int radio){
    return busqueda_binaria_rec(caramelos, 0, tope_caramelos - 1, radio);
}



int main(){
    caramelo_t caramelos[MAX_CARAMELOS];
    int tope_caramelos = 5;
    int i;

    caramelos[0].radio = 9;

    caramelos[1].radio = 5;

    caramelos[2].radio = 4;

    caramelos[3].radio = 7;

    caramelos[4].radio = 6;
    
    for(i = 0; i < tope_caramelos; i++){
        printf("Caramelo %d: radio: %d\n", i, caramelos[i].radio);
    }
    ordenar_por_radio(caramelos, tope_caramelos);
    printf("\n");
    for(i = 0; i < tope_caramelos; i++){
        printf("Caramelo %d: radio: %d\n", i, caramelos[i].radio);
    }
    printf("\n");

    int posicion = busqueda_binaria(caramelos, tope_caramelos, 5);
    printf("Posicion: %d\n", posicion);

    return 0;
}