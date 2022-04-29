#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"

int main(){

    char personaje_elegido = elegir_personaje();

    // juego_t juego;

    // juego.nivel_actual = 1;

    // inicializar_nivel(&juego.niveles[0], 1, 'A');

    printf("PERSONAJE ELEJIDO: %c\n", personaje_elegido);

    return 0;
}

//compiel with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm