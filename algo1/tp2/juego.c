#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"


int main(){

    // char personaje_elegido = elegir_personaje();
    char personaje_elegido = 'R';

    // printf("PERSONAJE ELEJIDO: %c\n", personaje_elegido);
    
    juego_t juego;
    nivel_t nivel_1;
    nivel_t nivel_2;
    nivel_t nivel_3;

    inicializar_nivel(&nivel_3, 3, personaje_elegido);
    inicializar_nivel(&nivel_1, 1, personaje_elegido);
    inicializar_nivel(&nivel_2, 2, personaje_elegido);

    juego.niveles[0] = nivel_1;
    juego.niveles[1] = nivel_2;
    juego.niveles[2] = nivel_3;


    juego.personaje_tp1 = personaje_elegido;

    juego.nivel_actual = 1;
    imprimir_terreno(juego);
    juego.nivel_actual = 2;
    imprimir_terreno(juego);
    juego.nivel_actual = 3;
    imprimir_terreno(juego);

    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm