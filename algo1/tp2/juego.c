#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"
#include "utiles.h"
#include "dia_en_la_uni.h"

const int PAREDES_LVL_1 = 12;
const int PAPELEOS_LVL_1 = 3;
const int FUEGOS_LVL_1 = 10;
const int MEDIAS_LVL_1 = 5;
const int BOTELLAS_LVL_1 = 4;
const int INTERRUPTORES_LVL_1 = 1;

const int PAREDES_LVL_2 = 12;
const int PAPELEOS_LVL_2 = 3;
const int FUEGOS_LVL_2 = 10;
const int MEDIAS_LVL_2 = 5;
const int BOTELLAS_LVL_2 = 4;
const int INTERRUPTORES_LVL_2 = 1;

const int PAREDES_LVL_3 = 12;
const int PAPELEOS_LVL_3 = 3;
const int FUEGOS_LVL_3 = 10;
const int MEDIAS_LVL_3 = 5;
const int BOTELLAS_LVL_3 = 4;
const int INTERRUPTORES_LVL_3 = 1;


int main(){

    // char personaje_elegido = elegir_personaje();

    // printf("PERSONAJE ELEJIDO: %c\n", personaje_elegido);
    
    // nivel_t nivel_1;
    // papeleo_t papeleo;
    // objeto_t objeto;
    // coordenada_t coordenada;
    // jugador_t jugador;
    // juego_t juego;

    coordenada_t pos_inicial_jugador;
    coordenada_t paredes[12];
    int tope_paredes;

    obtener_paredes(1, paredes, &tope_paredes, &pos_inicial_jugador);

    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm