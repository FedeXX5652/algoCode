#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"

const int DIM_NIVEL_1 = 12;
const int DIM_NIVEL_2 = 17;
const int DIM_NIVEL_3 = 22;

void imprimir_terreno(juego_t juego){
    int dim_nivel;

    if(juego.nivel_actual == 1){
        dim_nivel = DIM_NIVEL_1;
    }
    else if (juego.nivel_actual == 2){
        dim_nivel = DIM_NIVEL_2;
    }
    else if (juego.nivel_actual == 3){
        dim_nivel = DIM_NIVEL_3;
    }

    printf("DIM_NIVEL: %d\n", dim_nivel);

    char terreno[dim_nivel][dim_nivel];

    printf("NIVEL: %d\n", juego.nivel_actual);
    printf("PERSONAJE: %c\n", juego.personaje_tp1);
    printf("POSICION JUGADOR: %d, %d\n", juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.fil, juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.col);
    printf("MOVIMIENTOS: %d\n", juego.jugador.movimientos);
    printf("TOPE PAREDES: %d\n", juego.niveles[juego.nivel_actual-1].tope_paredes);

    for(int i = 0; i < dim_nivel; i++){
        for(int j = 0; j < dim_nivel; j++){
            terreno[i][j] = ' ';
        }
    }

    for(int i=0; i<juego.niveles[juego.nivel_actual-1].tope_paredes; i++){
        terreno[juego.niveles[juego.nivel_actual-1].paredes[i].fil][juego.niveles[juego.nivel_actual-1].paredes[i].col] = '#';
    }

    terreno[juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.fil][juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.col] = '0';

    for(int i=0; i<dim_nivel; i++){
        for(int j=0; j<dim_nivel; j++){
            printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
}