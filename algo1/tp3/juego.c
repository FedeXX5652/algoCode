#include <stdio.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"
#include <stdlib.h>
#include <time.h>
#include "controlador.h"

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

    inicializar_controlador();

    while(status_juego == JUGANDO_MAIN){
        imprimir_terreno(juego);
        realizar_jugada(&juego);
        system("clear");
        if(estado_nivel(juego.niveles[juego.nivel_actual-1].papeleos, juego.niveles[juego.nivel_actual-1].tope_papeleos) == GANADO_MAIN && juego.nivel_actual < MAX_NIVELES){
            juego.nivel_actual = juego.nivel_actual + 1;
            juego.jugador.posicion.fil = juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.fil;
            juego.jugador.posicion.col = juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.col;
        }
        status_juego = estado_juego(juego);
    }
    printf("Gracias por jugar!!!\n");
    terminar_controlador();

    return 0;
}

//compile with: gcc *.c utiles.o controlador.o  -o juego -std=c99 -Wall -Wconversion -Werror -lm