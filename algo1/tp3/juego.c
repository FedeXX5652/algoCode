#include <stdio.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"
#include <stdlib.h>
#include <time.h>


const int JUGANDO = 0;
const int GANADO = 1;
const int PERDIDO = -1;

int main(){

    //char personaje_elegido = elegir_personaje();
    char personaje_elegido = 'O';

    int estado_juego = JUGANDO;

    juego_t juego;

    srand ((unsigned)time(NULL));
    
    inicializar_juego(&juego, personaje_elegido);

    while(estado_juego == JUGANDO){
        imprimir_terreno(juego);
        realizar_jugada(&juego);
        system("clear");
    }

    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm