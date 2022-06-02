#include <stdio.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

const int JUGANDO = 0;
const int GANADO = 1;
const int PERDIDO = -1;
const char USAR_MARTILLO = 'Z';
const char USAR_EXTINTOR = 'C';
const char ACCION_DERECHA = 'D';
const char ACCION_IZQUIERDA = 'A';
const char ACCION_ARRIBA = 'W';
const char ACCION_ABAJO = 'S';
const char ROTAR_HORARIO = 'E';
const char ROTAR_ANTIHORARIO = 'Q';

char pedir_movimiento(){
    char movimiento;
    printf("Ingrese un movimiento:\nUtilizar martillo: Z.\nUtilizar extintor: C.\nMover o martillar/extinguir a izquierda: A.\nMover o martillar/extinguir a derecha: D.\nMartillar/extinguir hacia arriba: W.\nMartillar hacia abajo: S.\nMov. rotacional horario: E.\nMov. rotacional antihorario: Q.\n\n");
    scanf(" %c", &movimiento);
    movimiento = (char)toupper(movimiento);

    while(movimiento != USAR_MARTILLO && movimiento != USAR_EXTINTOR && movimiento != ACCION_DERECHA && movimiento != ACCION_IZQUIERDA && movimiento != ACCION_ARRIBA && movimiento != ACCION_ABAJO && movimiento != ROTAR_HORARIO && movimiento != ROTAR_ANTIHORARIO){
        printf("Ingrese un movimiento valido: ");
        scanf(" %c", &movimiento);
        movimiento = (char)toupper(movimiento);
    }
    return movimiento;
}

int main(){

    //char personaje_elegido = elegir_personaje();
    char personaje_elegido = 'O';

    int estado_juego = JUGANDO;

    juego_t juego;

    srand ((unsigned)time(NULL));
    
    inicializar_juego(&juego, personaje_elegido);

    while(estado_juego == 0){
        imprimir_terreno(juego);
        char accion = pedir_movimiento();
        realizar_jugada(&juego, accion);
        system("clear");
    }

    return 0;
}

//compile with: gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm