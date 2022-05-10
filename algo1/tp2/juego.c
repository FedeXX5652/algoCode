#include <stdio.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"
#include <stdlib.h>
#include <time.h>

int main(){

    //char personaje_elegido = elegir_personaje();
    char personaje_elegido = 'O';

    juego_t juego;

    srand ((unsigned)time(NULL));
    
    inicializar_juego(&juego, personaje_elegido);

    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm