#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "papeleo.h"
#include "utiles.h"
#include "dia_en_la_uni.h"

const char PARED = '#';
const char FUEGO_TIPO = 'F';
const char MEDIA_TIPO = 'M';
const char BOTELLA_TIPO = 'G';
const char INTERRUPTOR_TIPO = 'I';
const char MIKE = 'M';

const int NIVELES_TOTALES[MAX_NIVELES] = {1, 2, 3};
const int DIM_POR_NIVEL[MAX_NIVELES] = {12, 17, 22};
const int PAPELEOS_POR_NIVEL[MAX_NIVELES] = {2, 3, 4};
const int MOVIMIENTOS_POR_NIVEL[MAX_NIVELES] = {40, 30, 20};
const int FUEGOS_POR_NIVEL[MAX_NIVELES] = {10, 5, 3};
const int MEDIAS_POR_NIVEL[MAX_NIVELES] = {5, 4, 3};
const int BOTELLAS_POR_NIVEL[MAX_NIVELES] = {4, 3, 3};
const int INTERRUPTORES_POR_NIVEL[MAX_NIVELES] = {1, 1, 0};
const int MARTILLOS_POR_NIVEL[MAX_NIVELES] = {4, 5, 6};
const int EXTINTORES_POR_NIVEL[MAX_NIVELES] = {4, 2, 2};


typedef struct coordenada_libre_pared {
	int fil;
	int col;
    bool es_adyacente;
} coordenada_libre_t;


void imprimir_terreno(juego_t juego){
    int dim_nivel = DIM_POR_NIVEL[juego.nivel_actual - 1];

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
    printf("TOPE PAREDES: %d\n", juego.niveles[juego.nivel_actual-1].tope_paredes);

    for(int i = 0; i < dim_nivel; i++){
        for(int j = 0; j < dim_nivel; j++){
            terreno[i][j] = ' ';
        }
    }

    for(int i=0; i<juego.niveles[juego.nivel_actual-1].tope_paredes; i++){
        terreno[juego.niveles[juego.nivel_actual-1].paredes[i].fil][juego.niveles[juego.nivel_actual-1].paredes[i].col] = PARED;
    }

    for(int i=0; i<juego.niveles[juego.nivel_actual-1].tope_obstaculos; i++){
        terreno[juego.niveles[juego.nivel_actual-1].obstaculos[i].posicion.fil][juego.niveles[juego.nivel_actual-1].obstaculos[i].posicion.col] = juego.niveles[juego.nivel_actual-1].obstaculos[i].tipo;
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


bool es_pared_adyacente(nivel_t* nivel, int fila, int columna, coordenada_libre_t espacios_libres[MAX_PAREDES]){
    bool es_adyacente = false;

    for(int i = 0; i < nivel->tope_paredes; i++){
        if(nivel->paredes[i].fil == fila-1 && nivel->paredes[i].col == columna && es_adyacente == false){
            es_adyacente = true;
            //printf("ES ADYACENTE CON FILA ANTERIOR: %d, %d; %d\n", fila, columna, es_adyacente);
        }
        else if(nivel->paredes[i].fil == fila+1 && nivel->paredes[i].col == columna && es_adyacente == false){
            es_adyacente = true;
            //printf("ES ADYACENTE CON FILA SIGUIENTE: %d, %d; %d\n", fila, columna, es_adyacente);
        }
        else if(nivel->paredes[i].fil == fila && nivel->paredes[i].col == columna-1 && es_adyacente == false){
            es_adyacente = true;
            //printf("ES ADYACENTE CON COLUMNA ANTERIOR: %d, %d; %d\n", fila, columna, es_adyacente);
        }
        else if(nivel->paredes[i].fil == fila && nivel->paredes[i].col == columna+1 && es_adyacente == false){
            es_adyacente = true;
            //printf("ES ADYACENTE CON COLUMNA SIGUIENTE: %d, %d; %d\n", fila, columna, es_adyacente);
        }
    }
    return es_adyacente;
}


void get_espacios_libres(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int numero_nivel, int* tope_espacios_libres){
    int dim_nivel = DIM_POR_NIVEL[numero_nivel - 1];
    bool espacio_invalido = false;
    int index_esp_libre = 0;

    // printf("DIM_NIVEL: %d\n", dim_nivel);
    // printf("TOPE PAREDES: %d\n", nivel->tope_paredes);
    printf("POS INICIAL JUGADOR: %d, %d\n", nivel->pos_inicial_jugador.fil, nivel->pos_inicial_jugador.col);

    for(int fila = 0; fila < dim_nivel; fila++){
        for(int columna = 0; columna < dim_nivel; columna++){
            for(int coords_pared = 0; coords_pared<nivel->tope_paredes; coords_pared++){
                if((nivel->pos_inicial_jugador.fil == fila && nivel->pos_inicial_jugador.col == columna) && espacio_invalido == false){ //si es el mismo espacio que el jugador
                    espacio_invalido = true;
                }
                else if(nivel->paredes[coords_pared].fil == fila && nivel->paredes[coords_pared].col == columna && espacio_invalido == false){  //si es una pared
                    coords_pared = nivel->tope_paredes;
                    espacio_invalido = true;
                }
                else if(coords_pared == nivel->tope_paredes-1 && espacio_invalido == false){
                    espacios_libres[index_esp_libre].fil = fila;
                    espacios_libres[index_esp_libre].col = columna;
                    index_esp_libre = index_esp_libre+1;
                    espacios_libres[*tope_espacios_libres].es_adyacente = es_pared_adyacente(nivel, fila, columna, espacios_libres);
                    *tope_espacios_libres += 1;
                }
                espacio_invalido = false;
            }
        }
    }
}


void posicionar_fuegos(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres, int cantidad_fuegos){
    // int posicion_fuego;
    //int index_espacio_libre;

    srand ((unsigned)time(NULL));
    printf("TOPE ESPACIOS LIBRES: %d\n", *tope_espacios_libres);

    for(int fuegos_colocados = 0; fuegos_colocados < *tope_espacios_libres; fuegos_colocados++){
        // do{
        //     index_espacio_libre = rand() % *tope_espacios_libres;
        // } while(espacios_libres[index_espacio_libre].es_adyacente == false);
        if(espacios_libres[fuegos_colocados].es_adyacente == true){
            // printf("Espacio adyacente en: %d, %d; %d\n", espacios_libres[fuegos_colocados].fil, espacios_libres[fuegos_colocados].col, espacios_libres[fuegos_colocados].es_adyacente);
            (nivel->obstaculos[fuegos_colocados]).posicion.fil = espacios_libres[fuegos_colocados].fil;
            (nivel->obstaculos[fuegos_colocados]).posicion.col = espacios_libres[fuegos_colocados].col;
            nivel->obstaculos[fuegos_colocados].tipo = '.';
            nivel->tope_obstaculos ++;
        }
        // else{
        //     printf("No es adyacente en: %d, %d; %d\n", espacios_libres[fuegos_colocados].fil, espacios_libres[fuegos_colocados].col, espacios_libres[fuegos_colocados].es_adyacente);
        // }
    }
}


void inicializar_obstaculos(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){

    printf("INICIALIZANDO OBSTACULOS EN MAPA\n");
    printf("TOPE ESPACIOS LIBRES PARA OBSTACULOS: %d, Ej: %d, %d\n", *tope_espacios_libres, espacios_libres[0].fil, espacios_libres[0].col);

    int cantidad_fuegos = FUEGOS_POR_NIVEL[numero_nivel-1];
    // int cantidad_medias = MEDIAS_POR_NIVEL[numero_nivel-1];

    if(personaje_tp1 == OLAF_ID && numero_nivel == NIVELES_TOTALES[0]){
        cantidad_fuegos =- 2;
    }
    else if(personaje_tp1 == OLAF_ID && numero_nivel == NIVELES_TOTALES[1]){
        cantidad_fuegos =- 1;
    }

    posicionar_fuegos(nivel, espacios_libres, tope_espacios_libres, cantidad_fuegos);
}


void inicializar_herramientas(nivel_t* nivel, int numero_nivel, int cantidad_botellas, int cantidad_interruptores, char personaje_tp1){
    printf("INICIALIZANDO HERRAMIENTAS EN MAPA\n");
    //nivel->tope_herramientas =  cantidad_botellas + cantidad_interruptores;
}


void inicializar_objetos(nivel_t* nivel, int numero_nivel, char personaje_tp1){

    int cantidad_botellas = BOTELLAS_POR_NIVEL[numero_nivel-1];
    int cantidad_interruptores = INTERRUPTORES_POR_NIVEL[numero_nivel-1];
    
    int tope_espacios_libres = 0;
    coordenada_libre_t espacios_libres[MAX_PAREDES];

    get_espacios_libres(nivel, espacios_libres, numero_nivel, &tope_espacios_libres);

    printf("TOPE ESPACIOS LIBRES PARA OBJETOS: %d, Ej: %d, %d\n", tope_espacios_libres, espacios_libres[0].fil, espacios_libres[0].col);

    // ACA NO ESTA EL ERROR DE ADYACENTES A PAREDES AIUDA
    // for(int i = 0; i < tope_espacios_libres; i++){
    //     printf("ESPACIO LIBRE POST PROCESS: %d, %d; %d\n", espacios_libres[i].fil, espacios_libres[i].col, espacios_libres[i].es_adyacente);
    // }

    inicializar_obstaculos(nivel, numero_nivel, personaje_tp1, espacios_libres, &tope_espacios_libres);
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

    jugador->movimientos += MOVIMIENTOS_POR_NIVEL[numero_nivel-1];
    jugador->martillos = MARTILLOS_POR_NIVEL[numero_nivel-1];
    jugador->extintores = EXTINTORES_POR_NIVEL[numero_nivel-1];

    if(personaje_tp1 == JASMIN_ID){
        jugador->martillos += 1;
    }
    else if (personaje_tp1 == RAYO_ID && numero_nivel == NIVELES_TOTALES[0]){
        jugador->movimientos += 10;
    }
}


void inicializar_juego(juego_t* juego, char personaje_tp1){
    nivel_t nivel_1;
    // nivel_t nivel_2;
    // nivel_t nivel_3;

    juego->personaje_tp1 = personaje_tp1;
    (juego->jugador).movimientos = 0;

    
    // for(int i=0; i<MAX_NIVELES; i++){
    //     juego->nivel_actual = i+1;
    //     if(i+1 == 1){
    //         inicializar_nivel(&nivel_1, juego->nivel_actual, juego->personaje_tp1);
    //         juego->niveles[i] = nivel_1;
    //     }
    //     else if(i+1 == 2){
    //         inicializar_nivel(&nivel_2, juego->nivel_actual, juego->personaje_tp1);
    //         juego->niveles[i] = nivel_2;
    //     }
    //     else if(i+1 == 3){
    //         inicializar_nivel(&nivel_3, juego->nivel_actual, juego->personaje_tp1);
    //         juego->niveles[i] = nivel_3;
    //     }
    //     inicializar_jugador(&juego->jugador, &juego->niveles[i].pos_inicial_jugador, juego->nivel_actual, personaje_tp1);
    //     imprimir_terreno(*juego);
    // }



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