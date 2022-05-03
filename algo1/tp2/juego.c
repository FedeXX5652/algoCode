#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"


int main(){

    // char personaje_elegido = elegir_personaje();
    char personaje_elegido = 'R';

    // printf("PERSONAJE ELEJIDO: %c\n", personaje_elegido);
    
    juego_t juego;
    
    inicializar_juego(&juego, personaje_elegido);

    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm