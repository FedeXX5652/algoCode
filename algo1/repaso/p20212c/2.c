#include <stdio.h>
#include <string.h>

#define MAX 40
#define MAX_LUGARES 10

typedef struct chico_del_barrio{
    char nombre[MAX];
    char apellido[MAX];
    int edad;
    int id;
    char color_ojos[MAX];
    char lugares_favoritos[MAX_LUGARES][MAX];
    int tope_lugares_favoritos;
} chico_t;


void crear_chico(chico_t *chico, char nombre[MAX], char apellido[MAX], int edad, int id, char color_ojos[MAX], char lugares_favoritos[MAX_LUGARES][MAX], int tope_lugares_favoritos){
    strcpy(chico->nombre, nombre);
    strcpy(chico->apellido, apellido);
    chico->edad = edad;
    chico->id = id;
    strcpy(chico->color_ojos, color_ojos);
    for(int i = 0; i < tope_lugares_favoritos; i++){
        strcpy(chico->lugares_favoritos[i], lugares_favoritos[i]);
    }
    chico->tope_lugares_favoritos = tope_lugares_favoritos;
}


int main(){
    chico_t chico;

    char lista[4][MAX] = {"CABA", "Mar del Plata", "Cordoba", "Lujan"};

    char nombre[MAX] = "Juan";
    char apellido[MAX] = "Perez";
    int edad = 20;
    int id = 1;
    char color_ojos[MAX] = "azul";

    crear_chico(&chico, nombre, apellido, edad, id, color_ojos, lista, 4);

    printf("%s %s\n", chico.nombre, chico.apellido);
    printf("%d\n", chico.edad);
    printf("%d\n", chico.id);
    printf("%s\n", chico.color_ojos);
    for(int i = 0; i < chico.tope_lugares_favoritos; i++){
        printf("%s\n", chico.lugares_favoritos[i]);
    }
    return 0;
}