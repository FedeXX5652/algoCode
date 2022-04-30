#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"

const int DIM_NIVEL_1 = 12;

void imprimir_terreno(juego_t juego){

    char terreno[DIM_NIVEL_1][DIM_NIVEL_1];

    printf("NIVEL: %d\n", juego.nivel_actual);
    printf("PERSONAJE: %c\n", juego.personaje_tp1);
    printf("POSICION JUGADOR: %d, %d\n", juego.jugador.posicion.fil, juego.jugador.posicion.col);
    printf("MOVIMIENTOS: %d\n", juego.jugador.movimientos);
    printf("TOPE PAREDES: %d\n", juego.niveles[juego.nivel_actual-1].tope_paredes);

    for(int i=0; i<juego.niveles[juego.nivel_actual-1].tope_paredes; i++){
        printf("%d, %d ES PARED\n", juego.niveles[0].paredes[i].fil, juego.niveles[0].paredes[i].col);
        terreno[juego.niveles[0].paredes[i].fil][juego.niveles[0].paredes[i].col] = '|';
    }

    for(int i=0; i<DIM_NIVEL_1; i++){
        for(int j=0; j<DIM_NIVEL_1; j++){
            printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
}