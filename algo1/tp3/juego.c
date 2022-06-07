#include <stdio.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"
#include <stdlib.h>
#include <time.h>

const int JUGANDO_MAIN = 0;
const int GANADO_MAIN = 1;
const int PERDIDO_MAIN = -1;

int main(){

    //char personaje_elegido = elegir_personaje();
    char personaje_elegido = 'O';

    int status_juego = JUGANDO_MAIN;

    juego_t juego;

    srand ((unsigned)time(NULL));
    
    inicializar_juego(&juego, personaje_elegido);

    while(status_juego == JUGANDO_MAIN){
        imprimir_terreno(juego);
        realizar_jugada(&juego);
        system("clear");
        status_juego = estado_juego(juego);
    }

    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm