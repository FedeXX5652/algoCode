#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"

const int PAPELEOS_LVL_1 = 3;
const int FUEGOS_LVL_1 = 10;
const int MEDIAS_LVL_1 = 5;
const int BOTELLAS_LVL_1 = 4;
const int PAREDES_LVL_1 = 12;

int main(){

    // char personaje_elegido = elegir_personaje();

    // printf("PERSONAJE ELEJIDO: %c\n", personaje_elegido);
    
    nivel_t nivel_1;
    papeleo_t papeleo;
    objeto_t objeto;
    coordenada_t coordenada;
    jugador_t jugador;
    juego_t juego;
    
    for(int i; i<=PAPELEOS_LVL_1; i++){
        papeleo.id_papeleo = i;
        papeleo.posicion.fil = i;
        papeleo.posicion.col = i;
        papeleo.recolectado = false;
        printf("id: %d\n", papeleo.id_papeleo);
        printf("pos fil: %d\n", papeleo.posicion.fil);
        printf("pos col: %d\n", papeleo.posicion.col);
        printf("recolectado: %d\n----------------------\n", papeleo.recolectado);
        nivel_1.papeleos[i] = papeleo;
        nivel_1.tope_papeleos = i;
    }

    for(int i; i<=FUEGOS_LVL_1; i++){
        objeto.tipo = 'F';
        objeto.posicion.fil = i+PAPELEOS_LVL_1;
        objeto.posicion.col = i+PAPELEOS_LVL_1;
        printf("tipo: %c\n", objeto.tipo);
        printf("pos fil: %d\n", objeto.posicion.fil);
        printf("pos col: %d\n----------------------\n", objeto.posicion.col);
        nivel_1.obstaculos[i] = objeto;
        nivel_1.tope_obstaculos = i;
    }

    for(int i; i<=BOTELLAS_LVL_1; i++){
        objeto.tipo = 'B';
        objeto.posicion.fil = i+PAPELEOS_LVL_1+FUEGOS_LVL_1;
        objeto.posicion.col = i+PAPELEOS_LVL_1+FUEGOS_LVL_1;
        printf("tipo: %c\n", objeto.tipo);
        printf("pos fil: %d\n", objeto.posicion.fil);
        printf("pos col: %d\n----------------------\n", objeto.posicion.col);
        nivel_1.obstaculos[i] = objeto;
        nivel_1.tope_obstaculos = i;
    }

    for(int i; i<=PAREDES_LVL_1; i++){
        coordenada.fil = i+PAPELEOS_LVL_1+FUEGOS_LVL_1+BOTELLAS_LVL_1;
        coordenada.col = i+PAPELEOS_LVL_1+FUEGOS_LVL_1+BOTELLAS_LVL_1;
        printf("pos wall fil: %d\n", coordenada.fil);
        printf("pos wall col: %d\n----------------------\n", coordenada.col);
        nivel_1.paredes[i] = coordenada;
        nivel_1.tope_paredes = i;
    }


    jugador.posicion.fil = PAPELEOS_LVL_1+FUEGOS_LVL_1+BOTELLAS_LVL_1+1;
    jugador.posicion.col = PAPELEOS_LVL_1+FUEGOS_LVL_1+BOTELLAS_LVL_1+1;

    juego.personaje_tp1 = 'J';
    juego.nivel_actual = 1;
    juego.niveles[0] = nivel_1;
    juego.jugador = jugador;

    imprimir_terreno(juego);


    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm