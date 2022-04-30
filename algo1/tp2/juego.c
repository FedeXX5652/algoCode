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
    
    juego_t juego;
    coordenada_t paredes[MAX_PAREDES];
    nivel_t nivel_1;

    juego.nivel_actual = 1;

    obtener_paredes(juego.nivel_actual, paredes, &nivel_1.tope_paredes, &nivel_1.pos_inicial_jugador);
    juego.niveles[0] = nivel_1;
    juego.personaje_tp1 = 'R';

    imprimir_terreno(juego);

    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm