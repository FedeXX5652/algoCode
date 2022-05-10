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
const char MIKE = 'W';

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
    bool usado;
} coordenada_libre_t;


void imprimir_terreno(juego_t juego){
    int dim_nivel = DIM_POR_NIVEL[juego.nivel_actual - 1];

    printf("DIM_NIVEL: %d\n", dim_nivel);

    char terreno[dim_nivel][dim_nivel];

    printf("--------------DATA NIVEL--------------\n");
    printf("NIVEL: %d\n", juego.nivel_actual);
    printf("PERSONAJE TP1: %c\n", juego.personaje_tp1);
    printf("POSICION JUGADOR: %d, %d\n\n", juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.fil, juego.niveles[juego.nivel_actual-1].pos_inicial_jugador.col);
    printf("--------------INVENTARIO--------------\n");
    printf("MOVIMIENTOS: %i\n", juego.jugador.movimientos);
    printf("MARTILLOS: %i\n", juego.jugador.martillos);
    printf("EXTINTORES: %i\n", juego.jugador.extintores);
    printf("\n");
    printf("--------------OBSTACULOS Y OBJETOS--------------\n");
    printf("TOPE PAREDES: %d\n", juego.niveles[juego.nivel_actual-1].tope_paredes);
    printf("TOPE OBSTACULOS: %d\n", juego.niveles[juego.nivel_actual-1].tope_obstaculos);
    printf("TOPE HERRAMIENTAS: %d\n", juego.niveles[juego.nivel_actual-1].tope_herramientas);
    printf("\n");

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

    for(int i=0; i<juego.niveles[juego.nivel_actual-1].tope_herramientas; i++){
        terreno[juego.niveles[juego.nivel_actual-1].herramientas[i].posicion.fil][juego.niveles[juego.nivel_actual-1].herramientas[i].posicion.col] = juego.niveles[juego.nivel_actual-1].herramientas[i].tipo;
    }

    for(int i=0; i<juego.niveles[juego.nivel_actual-1].tope_papeleos; i++){
        terreno[juego.niveles[juego.nivel_actual-1].papeleos[i].posicion.fil][juego.niveles[juego.nivel_actual-1].papeleos[i].posicion.col] = 'P';
        printf("Id papeleo: %d\n", juego.niveles[juego.nivel_actual-1].papeleos[i].id_papeleo);
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
                    espacios_libres[*tope_espacios_libres].es_adyacente = es_pared_adyacente(nivel, fila, columna, espacios_libres);
                    espacios_libres[*tope_espacios_libres].usado = false;
                    index_esp_libre = index_esp_libre+1;
                    *tope_espacios_libres += 1;
                }
                espacio_invalido = false;
            }
        }
    }
}


void posicionar_fuegos(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres, int cantidad_fuegos){
    int index_espacio_libre;

    srand ((unsigned)time(NULL));

    for(int fuegos_colocados = 0; fuegos_colocados < cantidad_fuegos; fuegos_colocados++){
        do{
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while(espacios_libres[index_espacio_libre].es_adyacente == false || espacios_libres[index_espacio_libre].usado == true);
        
        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->obstaculos[nivel->tope_obstaculos].tipo = FUEGO_TIPO;
        nivel->tope_obstaculos ++;
        espacios_libres[index_espacio_libre].usado = true;
    }
}


void posicionar_medias(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres, int cantidad_medias){
    int index_espacio_libre;

    srand ((unsigned)time(NULL));

    for(int medias_colocadas = 0; medias_colocadas < cantidad_medias; medias_colocadas++){
        do{
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while(espacios_libres[index_espacio_libre].usado != false);

        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->obstaculos[nivel->tope_obstaculos].tipo = MEDIA_TIPO;
        nivel->tope_obstaculos ++;
        espacios_libres[index_espacio_libre].usado = true;
    }
}


void inicializar_obstaculos(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){

    int cantidad_fuegos = FUEGOS_POR_NIVEL[numero_nivel-1];
    int cantidad_medias = MEDIAS_POR_NIVEL[numero_nivel-1];

    nivel->tope_obstaculos = 0;

    if(personaje_tp1 == OLAF_ID && numero_nivel == NIVELES_TOTALES[0]){
        cantidad_fuegos =- 2;
        printf("Olaf apaga 2 fuegos\n");
    }
    else if(personaje_tp1 == OLAF_ID && numero_nivel == NIVELES_TOTALES[1]){
        cantidad_fuegos =- 1;
        printf("Olaf apaga un fuego\n");
    }

    posicionar_fuegos(nivel, espacios_libres, tope_espacios_libres, cantidad_fuegos);
    posicionar_medias(nivel, espacios_libres, tope_espacios_libres, cantidad_medias);
}


void posicionar_botellas(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres, int cantidad_botellas){
    int index_espacio_libre;

    srand ((unsigned)time(NULL));

    for(int botellas_colocadas = 0; botellas_colocadas < cantidad_botellas; botellas_colocadas++){
        do{
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while(espacios_libres[index_espacio_libre].usado != false);

        (nivel->herramientas[nivel->tope_herramientas]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->herramientas[nivel->tope_herramientas]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->herramientas[nivel->tope_herramientas].tipo = BOTELLA_TIPO;
        nivel->tope_herramientas ++;
        espacios_libres[index_espacio_libre].usado = true;
    }
}


void posicionar_interruptores(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres, int cantidad_interruptores){
    int index_espacio_libre;

    srand ((unsigned)time(NULL));

    for(int interruptores_colocados = 0; interruptores_colocados < cantidad_interruptores; interruptores_colocados++){
        do{
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while(espacios_libres[index_espacio_libre].usado != false);

        (nivel->herramientas[nivel->tope_herramientas]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->herramientas[nivel->tope_herramientas]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->herramientas[nivel->tope_herramientas].tipo = INTERRUPTOR_TIPO;
        nivel->tope_herramientas ++;
        espacios_libres[index_espacio_libre].usado = true;
    }
}


void inicializar_herramientas(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){

    int cantidad_botellas = BOTELLAS_POR_NIVEL[numero_nivel-1];
    int cantidad_interruptores = INTERRUPTORES_POR_NIVEL[numero_nivel-1];

    nivel->tope_herramientas = 0;

    posicionar_botellas(nivel, espacios_libres, tope_espacios_libres, cantidad_botellas);
    posicionar_interruptores(nivel, espacios_libres, tope_espacios_libres, cantidad_interruptores);
}


void posicionar_papeleos(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){
    int index_espacio_libre;

    srand ((unsigned)time(NULL));

    for(int papeleos_colocados = 0; papeleos_colocados < nivel->tope_papeleos; papeleos_colocados++){
        do{
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while(espacios_libres[index_espacio_libre].usado != false);

        (nivel->papeleos[papeleos_colocados]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->papeleos[papeleos_colocados]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->papeleos[papeleos_colocados].recolectado = false;
        nivel->papeleos[papeleos_colocados].id_papeleo = papeleos_colocados;
        espacios_libres[index_espacio_libre].usado = true;
    }
}


void inicializar_papeleos(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){

    int cantidad_papeleos = PAPELEOS_POR_NIVEL[numero_nivel-1];

    if(personaje_tp1 == STITCH_ID && numero_nivel == NIVELES_TOTALES[-1]){
        cantidad_papeleos =- 1;
        printf("Stitch quema un papeleo\n");
    }

    nivel->tope_papeleos = cantidad_papeleos;

    posicionar_papeleos(nivel, espacios_libres, tope_espacios_libres);
}


void inicializar_objetos(nivel_t* nivel, int numero_nivel, char personaje_tp1){
    
    int tope_espacios_libres = 0;
    coordenada_libre_t espacios_libres[MAX_PAREDES];

    get_espacios_libres(nivel, espacios_libres, numero_nivel, &tope_espacios_libres);

    printf("TOPE ESPACIOS LIBRES PARA OBJETOS: %d, Ej: %d, %d\n", tope_espacios_libres, espacios_libres[0].fil, espacios_libres[0].col);

    inicializar_obstaculos(nivel, numero_nivel, personaje_tp1, espacios_libres, &tope_espacios_libres);
    inicializar_herramientas(nivel, numero_nivel, personaje_tp1, espacios_libres, &tope_espacios_libres);
    inicializar_papeleos(nivel, numero_nivel, personaje_tp1, espacios_libres, &tope_espacios_libres);
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
        printf("Jasmin da martillo\n");
        jugador->martillos += 1;
    }
    else if (personaje_tp1 == RAYO_ID && numero_nivel == NIVELES_TOTALES[0]){
        printf("Rayo da movimientos extra\n");
        jugador->movimientos += 10;
    }
}


void inicializar_juego(juego_t* juego, char personaje_tp1){
    nivel_t nivel_1;
    nivel_t nivel_2;
    nivel_t nivel_3;

    juego->personaje_tp1 = personaje_tp1;
    (juego->jugador).movimientos = 0;

    
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
    }



    // inicializar_nivel(&nivel_1, 1, personaje_tp1);
    // // inicializar_nivel(&nivel_3, 3, personaje_tp1);
    // // inicializar_nivel(&nivel_2, 2, personaje_tp1);

    // juego->niveles[0] = nivel_1;
    // // juego->niveles[1] = nivel_2;
    // // juego->niveles[2] = nivel_3;


    // juego->nivel_actual = 1;
    // inicializar_jugador(&juego->jugador, &juego->niveles[0].pos_inicial_jugador, juego->nivel_actual, personaje_tp1);
    // imprimir_terreno(*juego);
    // // juego->nivel_actual = 2;
    // // imprimir_terreno(*juego);
    // // juego->nivel_actual = 3;
    // // imprimir_terreno(*juego);
}