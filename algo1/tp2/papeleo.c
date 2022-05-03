#include <stdio.h>
#include <stdbool.h>
#include "papeleo.h"
#include "utiles.h"
#include "dia_en_la_uni.h"

const char PARED = '#';
const char FUEGOS = 'F';
const char MEDIAS = 'M';
const char BOTELLAS = 'G';
const char INTERRUPTORES = 'I';
const char MIKE = 'M';

const int DIM_NIVEL_1 = 12;
const int DIM_NIVEL_2 = 17;
const int DIM_NIVEL_3 = 22;

const int PAPELEOS_NIVEL_1 = 2;
const int MOVIMIENTOS_NIVEL_1 = 40;
const int FUEGOS_NIVEL_1 = 10;
const int MEDIAS_NIVEL_1 = 5;
const int BOTELLAS_NIVEL_1 = 4;
const int INTERRUPTORES_NIVEL_1 = 1;
const int MARTILLOS_NIVEL_1 = 4;
const int EXTINTORES_NIVEL_1 = 4;

const int PAPELEOS_NIVEL_2 = 3;
const int MOVIMIENTOS_NIVEL_2 = 30;
const int FUEGOS_NIVEL_2 = 5;
const int MEDIAS_NIVEL_2 = 4;
const int BOTELLAS_NIVEL_2 = 3;
const int INTERRUPTORES_NIVEL_2 = 1;
const int MARTILLOS_NIVEL_2 = 5;
const int EXTINTORES_NIVEL_2 = 2;

const int PAPELEOS_NIVEL_3 = 4;
const int MOVIMIENTOS_NIVEL_3 = 20;
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

    printf("--------------DATA NIVEL--------------\n");
    printf("NIVEL: %d\n", juego.nivel_actual);
    printf("PERSONAJE: %c\n", juego.personaje_tp1);
    printf("POSICION JUGADOR: %d, %d\n", juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.fil, juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.col);
    printf("--------------INVENTARIO--------------\n");
    printf("MOVIMIENTOS: %i\n", juego.jugador.movimientos);
    printf("MARTILLOS: %i\n", juego.jugador.martillos);
    printf("EXTINTORES: %i\n", juego.jugador.extintores);
    printf("\n");
    printf("--------------OBSTACULOS Y OBJETOS--------------\n");
    printf("\n");
    printf("TOPE PAREDES: %d\n", juego.niveles[juego.nivel_actual-1].tope_paredes);

    for(int i = 0; i < dim_nivel; i++){
        for(int j = 0; j < dim_nivel; j++){
            terreno[i][j] = ' ';
        }
    }

    for(int i=0; i<juego.niveles[juego.nivel_actual-1].tope_paredes; i++){
        terreno[juego.niveles[juego.nivel_actual-1].paredes[i].fil][juego.niveles[juego.nivel_actual-1].paredes[i].col] = PARED;
    }

    terreno[juego.jugador.posicion.fil][juego.jugador.posicion.col] = MIKE;

    for(int i=0; i<dim_nivel; i++){
        for(int j=0; j<dim_nivel; j++){
            printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------------------------\n");
}


void get_espacios_libres(nivel_t* nivel, coordenada_t* espacios_libres, int numero_nivel, int* tope_espacios_libres){
    int dim_nivel;

    if(numero_nivel == 1){
        dim_nivel = DIM_NIVEL_1;
    }
    else if (numero_nivel == 2){
        dim_nivel = DIM_NIVEL_2;
    }
    else if (numero_nivel == 3){
        dim_nivel = DIM_NIVEL_3;
    }

    // printf("DIM_NIVEL: %d\n", dim_nivel);
    // printf("TOPE PAREDES: %d\n", nivel->tope_paredes);

    for(int i = 0; i < dim_nivel; i++){
        for(int j = 0; j < dim_nivel; j++){
            for(int k = 0; k<nivel->tope_paredes; k++){
                if(nivel->paredes[k].fil == i && nivel->paredes[k].col == j){
                    k = nivel->tope_paredes;
                }
                else if(k == nivel->tope_paredes-1){
                    espacios_libres[*tope_espacios_libres].fil = i;
                    espacios_libres[*tope_espacios_libres].col = j;
                    *tope_espacios_libres = *tope_espacios_libres + 1;
                }
            }
        }
    }

    // printf("TOPE ESPACIOS LIBRES: %d\n", *tope_espacios_libres);
}


void inicializar_obstaculos(nivel_t* nivel, int numero_nivel, int cantidad_fuegos, int cantidad_medias, char personaje_tp1){
    coordenada_t espacios_libres[MAX_OBSTACULOS];
    int tope_espacios_libres = 0;

    printf("INICIALIZANDO OBSTACULOS EN MAPA\n");
    //nivel->tope_obstaculos = cantidad_fuegos+cantidad_medias;
    if(personaje_tp1 == OLAF_ID && numero_nivel == 1){
        cantidad_fuegos =- 2;
    }
    else if(personaje_tp1 == OLAF_ID && numero_nivel == 2){
        cantidad_fuegos =- 1;
    }

    get_espacios_libres(nivel, espacios_libres, numero_nivel, &tope_espacios_libres);
}


void inicializar_herramientas(nivel_t* nivel, int numero_nivel, int cantidad_botellas, int cantidad_interruptores, char personaje_tp1){
    printf("INICIALIZANDO HERRAMIENTAS EN MAPA\n");
    //nivel->tope_herramientas =  cantidad_botellas + cantidad_interruptores;

}


void inicializar_objetos(nivel_t* nivel, int numero_nivel, char personaje_tp1){

    int cantidad_fuegos = 0;
    int cantidad_medias = 0;
    int cantidad_botellas = 0;
    int cantidad_interruptores = 0;

    if(numero_nivel == 1){
        cantidad_fuegos = FUEGOS_NIVEL_1;
        cantidad_medias = MEDIAS_NIVEL_1;
        cantidad_botellas = BOTELLAS_NIVEL_1;
        cantidad_interruptores = INTERRUPTORES_NIVEL_1;
    }
    else if(numero_nivel == 2){
        cantidad_fuegos = FUEGOS_NIVEL_2;
        cantidad_medias = MEDIAS_NIVEL_2;
        cantidad_botellas = BOTELLAS_NIVEL_2;
        cantidad_interruptores = INTERRUPTORES_NIVEL_2;
    }
    else if(numero_nivel == 3){
        cantidad_fuegos = FUEGOS_NIVEL_3;
        cantidad_medias = MEDIAS_NIVEL_3;
        cantidad_botellas = BOTELLAS_NIVEL_3;
        cantidad_interruptores = INTERRUPTORES_NIVEL_3;
    }

    inicializar_obstaculos(nivel, numero_nivel, cantidad_fuegos, cantidad_medias, personaje_tp1);
    inicializar_herramientas(nivel, numero_nivel, cantidad_botellas, cantidad_interruptores, personaje_tp1);
}


void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){
    
    if(numero_nivel == 1){
        obtener_paredes(3, nivel->paredes, &nivel->tope_paredes, &nivel->pos_inicial_jugador);
    }
    else if(numero_nivel == 2){
        obtener_paredes(2, nivel->paredes, &nivel->tope_paredes, &nivel->pos_inicial_jugador);
    }
    else if(numero_nivel == 3){
        obtener_paredes(1, nivel->paredes, &nivel->tope_paredes, &nivel->pos_inicial_jugador);
    }
    
    inicializar_objetos(nivel, numero_nivel, personaje_tp1);
}


void inicializar_jugador(jugador_t* jugador, coordenada_t* pos_inicial_jugador, int numero_nivel, char personaje_tp1){
    printf("INICIALIZANDO POSICION JUGADOR: %d,%d\n", pos_inicial_jugador->fil, pos_inicial_jugador->col);
    jugador->posicion = *pos_inicial_jugador;
    
    if(numero_nivel == 1){
        jugador->movimientos += MOVIMIENTOS_NIVEL_1;
        jugador->martillos = MARTILLOS_NIVEL_1;
        jugador->extintores = EXTINTORES_NIVEL_1;
    }
    else if(numero_nivel == 2){
        jugador->movimientos += MOVIMIENTOS_NIVEL_2;
        jugador->martillos = MARTILLOS_NIVEL_2;
        jugador->extintores = EXTINTORES_NIVEL_2;
    }
    else if(numero_nivel == 3){
        jugador->movimientos += MOVIMIENTOS_NIVEL_3;
        jugador->martillos = MARTILLOS_NIVEL_3;
        jugador->extintores = EXTINTORES_NIVEL_3;
    }

    if(personaje_tp1 == JASMIN_ID){
        jugador->martillos += 1;
    }
    else if (personaje_tp1 == RAYO_ID && numero_nivel == 1){
        jugador->movimientos += 10;
    }
}


void inicializar_juego(juego_t* juego, char personaje_tp1){
    nivel_t nivel_1;
    // nivel_t nivel_2;
    // nivel_t nivel_3;

    juego->personaje_tp1 = personaje_tp1;
    (juego->jugador).movimientos = 0;

    /*
    for(int i=0; i<MAX_NIVELES; i++){
        juego->nivel_actual = i+1;
        if(i+1 == 1){
            inicializar_nivel(&nivel_1, juego->nivel_actual, juego->personaje_tp1);
            juego->niveles[i] = nivel_1;
        }
        else if(i+1 == 2){
            inicializar_nivel(&nivel_2, juego->nivel_actual, juego->personaje_tp1);
            juego->niveles[i] = nivel_2;
        }
        else if(i+1 == 3){
            inicializar_nivel(&nivel_3, juego->nivel_actual, juego->personaje_tp1);
            juego->niveles[i] = nivel_3;
        }
        inicializar_jugador(&juego->jugador, &juego->niveles[i].pos_inicial_jugador, juego->nivel_actual, personaje_tp1);
        imprimir_terreno(*juego);
    }*/



    inicializar_nivel(&nivel_1, 1, personaje_tp1);
    // inicializar_nivel(&nivel_3, 3, personaje_tp1);
    // inicializar_nivel(&nivel_2, 2, personaje_tp1);

    juego->niveles[0] = nivel_1;
    // juego->niveles[1] = nivel_2;
    // juego->niveles[2] = nivel_3;


    juego->nivel_actual = 1;
    inicializar_jugador(&juego->jugador, &juego->niveles[0].pos_inicial_jugador, juego->nivel_actual, personaje_tp1);
    imprimir_terreno(*juego);
    // juego->nivel_actual = 2;
    // imprimir_terreno(*juego);
    // juego->nivel_actual = 3;
    // imprimir_terreno(*juego);
}