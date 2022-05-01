#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"
#include "utiles.h"

const char PARED = '#';
const char FUEGOS = 'F';
const char MEDIAS = 'M';
const char BOTELLAS = 'G';
const char INTERRUPTORES = 'I';
const char MIKE = 'M';

const int DIM_NIVEL_1 = 12;
const int DIM_NIVEL_2 = 17;
const int DIM_NIVEL_3 = 22;

const int PAPELEOS_LVL_1 = 2;
const int MOVIMIENTOS_LVL_1 = 40;
const int FUEGOS_NIVEL_1 = 10;
const int MEDIAS_NIVEL_1 = 5;
const int BOTELLAS_NIVEL_1 = 4;
const int INTERRUPTORES_NIVEL_1 = 1;
const int MARTILLOS_NIVEL_1 = 4;
const int EXTINTORES_NIVEL_1 = 4;

const int PAPELEOS_LVL_2 = 3;
const int MOVIMIENTOS_LVL_2 = 30;
const int FUEGOS_NIVEL_2 = 5;
const int MEDIAS_NIVEL_2 = 4;
const int BOTELLAS_NIVEL_2 = 3;
const int INTERRUPTORES_NIVEL_2 = 1;
const int MARTILLOS_NIVEL_2 = 5;
const int EXTINTORES_NIVEL_2 = 2;

const int PAPELEOS_LVL_3 = 4;
const int MOVIMIENTOS_LVL_3 = 20;
const int FUEGOS_NIVEL_3 = 3;
const int MEDIAS_NIVEL_3 = 3;
const int BOTELLAS_NIVEL_3 = 2;
const int INTERRUPTORES_NIVEL_3 = 0;
const int MARTILLOS_NIVEL_3 = 6;
const int EXTINTORES_NIVEL_3 = 2;


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
        terreno[juego.niveles[juego.nivel_actual-1].paredes[i].fil][juego.niveles[juego.nivel_actual-1].paredes[i].col] = PARED;
    }

    terreno[juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.fil][juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.col] = MIKE;

    for(int i=0; i<dim_nivel; i++){
        for(int j=0; j<dim_nivel; j++){
            printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------------------------\n");
}

void inicializar_obstaculos(nivel_t* nivel, int cantidad_fuegos, int cantidad_medias, int amigo_pide_favor)


void inicializar_objetos(nivel_t* nivel, int numero_nivel, char amigo_pide_favor){

    int cantidad_fuegos = 0;
    int cantidad_medias = 0;
    int cantidad_botellas = 0;
    int cantidad_interruptores = 0;
    int cantidad_martillos = 0;
    int cantidad_extintores = 0;

    if(numero_nivel == 1){
        nivel->tope_herramientas = MEDIAS_NIVEL_1+BOTELLAS_NIVEL_1+MARTILLOS_NIVEL_1+EXTINTORES_NIVEL_1+INTERRUPTORES_NIVEL_1;
        nivel->tope_obstaculos = FUEGOS_NIVEL_1+MEDIAS_NIVEL_1;
        
        cantidad_fuegos = FUEGOS_NIVEL_1;
        cantidad_medias = MEDIAS_NIVEL_1;
        cantidad_botellas = BOTELLAS_NIVEL_1;
        cantidad_martillos = MARTILLOS_NIVEL_1;
        cantidad_extintores = EXTINTORES_NIVEL_1;
        cantidad_interruptores = INTERRUPTORES_NIVEL_1;
    }
    else if(numero_nivel == 2){
        nivel->tope_herramientas = MEDIAS_NIVEL_2+BOTELLAS_NIVEL_2+MARTILLOS_NIVEL_2+EXTINTORES_NIVEL_2+INTERRUPTORES_NIVEL_2;
        nivel->tope_obstaculos = FUEGOS_NIVEL_2+MEDIAS_NIVEL_2;
        
        cantidad_fuegos = FUEGOS_NIVEL_2;
        cantidad_medias = MEDIAS_NIVEL_2;
        cantidad_botellas = BOTELLAS_NIVEL_2;
        cantidad_martillos = MARTILLOS_NIVEL_2;
        cantidad_extintores = EXTINTORES_NIVEL_2;
        cantidad_interruptores = INTERRUPTORES_NIVEL_2;
    }
    else if(numero_nivel == 3){
        nivel->tope_herramientas = MEDIAS_NIVEL_3+BOTELLAS_NIVEL_3+MARTILLOS_NIVEL_3+EXTINTORES_NIVEL_3+INTERRUPTORES_NIVEL_3;
        nivel->tope_obstaculos = FUEGOS_NIVEL_3+MEDIAS_NIVEL_3;

        cantidad_fuegos = FUEGOS_NIVEL_3;
        cantidad_medias = MEDIAS_NIVEL_3;
        cantidad_botellas = BOTELLAS_NIVEL_3;
        cantidad_martillos = MARTILLOS_NIVEL_3;
        cantidad_extintores = EXTINTORES_NIVEL_3;
        cantidad_interruptores = INTERRUPTORES_NIVEL_3;
    }

    inicializar_obstaculos(nivel, cantidad_fuegos, cantidad_medias, amigo_pide_favor);
}


void inicializar_nivel(nivel_t* nivel, int numero_nivel, char amigo_pide_favor){
    
    if(numero_nivel == 1){
        obtener_paredes(3, nivel->paredes, &nivel->tope_paredes, &nivel->pos_inicial_jugador);
    }
    else if(numero_nivel == 2){
        obtener_paredes(2, nivel->paredes, &nivel->tope_paredes, &nivel->pos_inicial_jugador);
    }
    else if(numero_nivel == 3){
        obtener_paredes(1, nivel->paredes, &nivel->tope_paredes, &nivel->pos_inicial_jugador);
    }

    inicializar_objetos(nivel, numero_nivel, amigo_pide_favor);
}