#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

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
const int TOPE_NIVELES = 3;
const int DIM_POR_NIVEL[MAX_NIVELES] = {22, 17, 12};
const int PAPELEOS_POR_NIVEL[MAX_NIVELES] = {2, 3, 4};
const int MOVIMIENTOS_POR_NIVEL[MAX_NIVELES] = {40, 30, 20};
const int FUEGOS_POR_NIVEL[MAX_NIVELES] = {10, 5, 3};
const int MEDIAS_POR_NIVEL[MAX_NIVELES] = {5, 4, 3};
const int BOTELLAS_POR_NIVEL[MAX_NIVELES] = {4, 3, 2};
const int INTERRUPTORES_POR_NIVEL[MAX_NIVELES] = {1, 1, 0};
const int MARTILLOS_POR_NIVEL[MAX_NIVELES] = {4, 5, 6};
const int EXTINTORES_POR_NIVEL[MAX_NIVELES] = {4, 2, 2};
const int INTERVALOS_RANDALL_POR_NIVEL[MAX_NIVELES] = {7, 5, 3};

const char USAR_MARTILLO = 'Z';
const char USAR_EXTINTOR = 'C';
const char ACCION_DERECHA = 'D';
const char ACCION_IZQUIERDA = 'A';
const char ACCION_ARRIBA = 'W';
const char ACCION_ABAJO = 'S';
const char ROTAR_HORARIO = 'E';
const char ROTAR_ANTIHORARIO = 'Q';

const bool IZQUIERDA = false;
const bool DERECHA = true;


typedef struct coordenada_libre_pared {
	int fil;
	int col;
    bool es_adyacente;
    bool usado;
} coordenada_libre_t;


/* 
    precondicion:
        - juego inicializado
        - nivel asociado a nivel_actual inicializado

    postcondicion:
        - imprime por pantalla el nivel actual
*/
void imprimir_terreno(juego_t juego){
    int dim_nivel = DIM_POR_NIVEL[juego.nivel_actual - 1];

    char terreno[dim_nivel][dim_nivel];

    printf("--------------MIKE--------------\n");
    printf("MOVIMIENTOS: %i\n", juego.jugador.movimientos);
    printf("MARTILLOS: %i\n", juego.jugador.martillos);
    printf("EXTINTORES: %i\n", juego.jugador.extintores);
    printf("AHUYENTA RANDALL: %s\n", juego.jugador.ahuyenta_randall ? "SI" : "NO");
    printf("MOVIMIENTOS REALIZADOS: %i\n", juego.jugador.movimientos_realizados);
    int papeleos_recolectados=0;
    int i=0;
    while(i<juego.niveles[juego.nivel_actual - 1].tope_papeleos){
        if(juego.niveles[juego.nivel_actual - 1].papeleos[papeleos_recolectados].recolectado){
            papeleos_recolectados++;
        }
        i++;
    }
    printf("PAPELEOS RECOLECTADOS: %i\n", papeleos_recolectados);
    printf("--------------------------------\n\n");

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
        if(juego.niveles[juego.nivel_actual-1].papeleos[i].recolectado == false){
            terreno[juego.niveles[juego.nivel_actual-1].papeleos[i].posicion.fil][juego.niveles[juego.nivel_actual-1].papeleos[i].posicion.col] = 'P';  //AIUDA pasar ID de int a char
        }
        else{
            terreno[juego.niveles[juego.nivel_actual-1].papeleos[i].posicion.fil][juego.niveles[juego.nivel_actual-1].papeleos[i].posicion.col] = ' ';
        }
    }


    terreno[juego.jugador.posicion.fil][juego.jugador.posicion.col] = MIKE;

    for(int i=0; i<dim_nivel; i++){
        for(int j=0; j<dim_nivel; j++){
            printf("%c ", terreno[i][j]);
        }
        printf("\n");
    }
    // printf("----------------------------------------------------\n\n");
}


/*
    precondiciones: 
        - el nivel debe tener las paredes y su tope inicializados
        - fila y columna deben estar dentro de la dimension del nivel y corresponder al valor a verificar

    postcondiciones:
        - devuelve true si la posicion es adyacente a una pared
        - devuelve false si la posicion no es adyacente a una pared
*/
bool es_pared_adyacente(nivel_t* nivel, int fila, int columna, coordenada_libre_t espacios_libres[MAX_PAREDES]){
    bool es_adyacente = false;

    for(int i = 0; i < nivel->tope_paredes; i++){
        if(nivel->paredes[i].fil == fila-1 && nivel->paredes[i].col == columna && es_adyacente == false){
            es_adyacente = true;
        }
        else if(nivel->paredes[i].fil == fila+1 && nivel->paredes[i].col == columna && es_adyacente == false){
            es_adyacente = true;
        }
        else if(nivel->paredes[i].fil == fila && nivel->paredes[i].col == columna-1 && es_adyacente == false){
            es_adyacente = true;
        }
        else if(nivel->paredes[i].fil == fila && nivel->paredes[i].col == columna+1 && es_adyacente == false){
            es_adyacente = true;
        }
    }
    return es_adyacente;
}


/*
    precondiciones:
        - nivel_actual debe ser un nivel valido (entre 1 y 3)
        - el nivel debe tener las paredes inicializadas al igual que su tope
    
    postcondiciones:
        - se devuelve una lista de coordenadas libres indicando si son o no adyacentes a una pared e indicando que no estan siendo usadas
*/
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


/*
    precondiciones:
        - paredes del nivel inicializadas
        - espacios_libres tiene que tener la posicion de todos los espacios libres del nivel y tener tantos espacios disponibles como obstaculos adyacentes a colocar
        - tope_espacios_libres tiene que tener la cantidad de espacios libres del nivel
    
    postcondiciones:
        - se inicializan los datos de posicion y tipo cada obstaculo adyacente del nivel

*/
void posicionar_obstaculo_adyacente(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres, int cantidad_obstaculos, char tipo_obstaculo){
    int index_espacio_libre;

    for(int obstaculos_colocados = 0; obstaculos_colocados < cantidad_obstaculos; obstaculos_colocados++){
        do{
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while(espacios_libres[index_espacio_libre].es_adyacente == false || espacios_libres[index_espacio_libre].usado == true);
        
        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->obstaculos[nivel->tope_obstaculos].tipo = tipo_obstaculo;
        nivel->tope_obstaculos ++;
        espacios_libres[index_espacio_libre].usado = true;
    }
}


/*
    precondiciones:
        - paredes del nivel inicializadas
        - espacios_libres tiene que tener la posicion de todos los espacios libres del nivel y tener tantos espacios disponibles como obstaculos a colocar
        - tope_espacios_libres tiene que tener la cantidad de espacios libres del nivel
    
    postcondiciones:
        - se inicializan los datos de posicion y tipo cada obstaculo del nivel

*/
void posicionar_obstaculo(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres, int cantidad_obstaculos, char tipo_obstaculo){
    int index_espacio_libre;

    for(int obstaculos_colocados = 0; obstaculos_colocados < cantidad_obstaculos; obstaculos_colocados++){
        do{
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while(espacios_libres[index_espacio_libre].usado != false);

        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->obstaculos[nivel->tope_obstaculos].tipo = tipo_obstaculo;
        nivel->tope_obstaculos ++;
        espacios_libres[index_espacio_libre].usado = true;
    }
}


void inicializar_obstaculos(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){

    int cantidad_fuegos = FUEGOS_POR_NIVEL[numero_nivel-1];
    int cantidad_medias = MEDIAS_POR_NIVEL[numero_nivel-1];

    nivel->tope_obstaculos = 0;

    if(personaje_tp1 == OLAF_ID && numero_nivel == NIVELES_TOTALES[0]){
        cantidad_fuegos = cantidad_fuegos - 2;
    }
    else if(personaje_tp1 == OLAF_ID && numero_nivel == NIVELES_TOTALES[1]){
        cantidad_fuegos = cantidad_fuegos - 1;
    }

    posicionar_obstaculo_adyacente(nivel, espacios_libres, tope_espacios_libres, cantidad_fuegos, FUEGO_TIPO);
    posicionar_obstaculo(nivel, espacios_libres, tope_espacios_libres, cantidad_medias, MEDIA_TIPO);
}


/*
    precondiciones:
        - paredes del nivel inicializadas
        - espacios_libres tiene que tener la posicion de todos los espacios libres del nivel y tener tantos espacios disponibles como herramientas a colocar
        - tope_espacios_libres tiene que tener la cantidad de espacios libres del nivel
    
    postcondiciones:
        - se inicializan los datos de posicion y tipo cada herramienta del nivel

*/
void posicionar_herramienta(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres, int cantidad_herramienta, char tipo_herramienta){
    int index_espacio_libre;

    for(int herramientas_colocadas = 0; herramientas_colocadas < cantidad_herramienta; herramientas_colocadas++){
        do{
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while(espacios_libres[index_espacio_libre].usado != false);

        (nivel->herramientas[nivel->tope_herramientas]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->herramientas[nivel->tope_herramientas]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->herramientas[nivel->tope_herramientas].tipo = tipo_herramienta;
        nivel->tope_herramientas ++;
        espacios_libres[index_espacio_libre].usado = true;
    }
}


/*
    precondiciones:
        - paredes del nivel inicializadas
        - numero_nivel tiene que ser un valor dentro de los niveles disponibles en el array NIVELES_TOTALES y corresponder al nivel a inicializar
        - personaje_tp1 es una de las constantes definidas en el archivo de dia_en_la_uni.h
        - espacios_libres tiene que tener la posicion de todos los espacios libres del nivel y un tamanio mayor a la cantidad de objetos a colocar
        - tope_espacios_libres tiene que tener la cantidad de espacios libres del nivel
    
    postcondiciones:
        - se inicializan los datos de cada herramienta del nivel (botellas, interruptores con su posicion y tipo)

*/
void inicializar_herramientas(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){

    int cantidad_botellas = BOTELLAS_POR_NIVEL[numero_nivel-1];
    int cantidad_interruptores = INTERRUPTORES_POR_NIVEL[numero_nivel-1];

    nivel->tope_herramientas = 0;

    posicionar_herramienta(nivel, espacios_libres, tope_espacios_libres, cantidad_botellas, BOTELLA_TIPO);
    posicionar_herramienta(nivel, espacios_libres, tope_espacios_libres, cantidad_interruptores, INTERRUPTOR_TIPO);
}


/*
    precondiciones:
        - paredes del nivel inicializadas
        - espacios_libres tiene que tener la posicion de todos los espacios libres del nivel y un tamanio mayor a la cantidad de objetos a colocar
        - tope_espacios_libres tiene que tener la cantidad de espacios libres del nivel
    
    postcondiciones:
        - se inicializan los datos de posicion y id cada papeleo del nivel

*/
void posicionar_papeleos(nivel_t* nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){
    int index_espacio_libre;

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

/*
    precondiciones:
        - paredes del nivel inicializadas
        - numero_nivel tiene que ser un valor dentro de los niveles disponibles en el array NIVELES_TOTALES y corresponder al nivel a inicializar
        - personaje_tp1 es una de las constantes definidas en el archivo de dia_en_la_uni.h
        - espacios_libres tiene que tener la posicion de todos los espacios libres del nivel y un tamanio mayor a la cantidad de objetos a colocar
        - tope_espacios_libres tiene que tener la cantidad de espacios libres del nivel
    
    postcondiciones:
        - se inicializan los datos de cada papeleo del nivel (posicion, recolectado, id)

*/
void inicializar_papeleos(nivel_t* nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int* tope_espacios_libres){

    int cantidad_papeleos = PAPELEOS_POR_NIVEL[numero_nivel-1];

    if(personaje_tp1 == STITCH_ID && numero_nivel == NIVELES_TOTALES[TOPE_NIVELES]){
        cantidad_papeleos--;
    }

    nivel->tope_papeleos = cantidad_papeleos;

    posicionar_papeleos(nivel, espacios_libres, tope_espacios_libres);
}


/*
    precondiciones:
        - paredes del nivel inicializadas
        - numero_nivel tiene que ser un valor dentro de los niveles disponibles en el array NIVELES_TOTALES y corresponder al nivel a inicializar
        - personaje_tp1 es una de las constantes definidas en el archivo de dia_en_la_uni.h

    postcondiciones:
        - agrega los objetos con sus respectivos datos al nivel
*/
void inicializar_objetos(nivel_t* nivel, int numero_nivel, char personaje_tp1){
    
    int tope_espacios_libres = 0;
    coordenada_libre_t espacios_libres[MAX_PAREDES];

    get_espacios_libres(nivel, espacios_libres, numero_nivel, &tope_espacios_libres);

    inicializar_obstaculos(nivel, numero_nivel, personaje_tp1, espacios_libres, &tope_espacios_libres);
    inicializar_herramientas(nivel, numero_nivel, personaje_tp1, espacios_libres, &tope_espacios_libres);
    inicializar_papeleos(nivel, numero_nivel, personaje_tp1, espacios_libres, &tope_espacios_libres);
}


/*
    precondiciones:
        - numero_nivel tiene que ser un valor dentro de los niveles disponibles en el array NIVELES_TOTALES y corresponder al nivel a inicializar
        - personaje_tp1 es una de las constantes definidas en el archivo de dia_en_la_uni.h

    postcondiciones:
        - Se inicializa el nivel con los datos correspondientes (paredes y objetos)
*/
void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){
    
    obtener_paredes(numero_nivel, nivel->paredes, &nivel->tope_paredes, &nivel->pos_inicial_jugador);
    inicializar_objetos(nivel, numero_nivel, personaje_tp1);
}


/*
    precondiciones:
        - personaje_tp1 es una de las constantes definidas en el archivo de dia_en_la_uni.h
        - numero_nivel tiene que ser un valor dentro de los niveles disponibles en el array NIVELES_TOTALES y corresponder al nivel a inicializar
        - pos_inicial_jugador tiene que tener la posicion inicial del jugador

    postcondiciones: inicializa los datos del inventario (martillos, movimientos y extintores) y posicion inicial del jugador
*/
void inicializar_jugador(jugador_t* jugador, coordenada_t* pos_inicial_jugador, int numero_nivel, char personaje_tp1){
    jugador->posicion.fil = pos_inicial_jugador->fil;
    jugador->posicion.col = pos_inicial_jugador->col;

    jugador->movimientos_realizados = 0;

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


/*
    precondiones: personaje_tp1 debe ser una de las constantes definidas en el archivo dia_en_la_uni.h

    postcondiciones: inicializa el juego con 3 niveles
*/
void inicializar_juego(juego_t* juego, char personaje_tp1){

    juego->personaje_tp1 = personaje_tp1;
    (juego->jugador).movimientos = 0;
    juego->nivel_actual = 1;

    for(int i=0; i<MAX_NIVELES; i++){
        inicializar_nivel(&juego->niveles[i], i+1, juego->personaje_tp1);
    }
    inicializar_jugador(&juego->jugador, &juego->niveles[(juego->nivel_actual)-1].pos_inicial_jugador, juego->nivel_actual, personaje_tp1);
}


char pedir_movimiento(){
    char movimiento;
    printf("\nIngrese un movimiento:\nUtilizar martillo: Z.\nUtilizar extintor: C.\nMover o martillar/extinguir a izquierda: A.\nMover o martillar/extinguir a derecha: D.\nMartillar/extinguir hacia arriba: W.\nMartillar hacia abajo: S.\nMov. rotacional horario: E.\nMov. rotacional antihorario: Q.\n\n");
    scanf(" %c", &movimiento);
    movimiento = (char)toupper(movimiento);

    while(movimiento != USAR_MARTILLO && movimiento != USAR_EXTINTOR && movimiento != ACCION_DERECHA && movimiento != ACCION_IZQUIERDA && movimiento != ACCION_ARRIBA && movimiento != ACCION_ABAJO && movimiento != ROTAR_HORARIO && movimiento != ROTAR_ANTIHORARIO){
        printf("Ingrese un movimiento valido: ");
        scanf(" %c", &movimiento);
        movimiento = (char)toupper(movimiento);
    }
    return movimiento;
}


void restar_movimientos(jugador_t* jugador, int cantidad_movimientos){
    jugador->movimientos -= cantidad_movimientos;
}


void sumar_movimientos(jugador_t* jugador, int cantidad_movimientos){
    jugador->movimientos += cantidad_movimientos;
}


void rotar_antihorario(nivel_t* nivel, jugador_t* jugador, int numero_nivel){
    int dimension = DIM_POR_NIVEL[numero_nivel-1]-1;

    int col_jugador = jugador->posicion.col;
    jugador->posicion.col = jugador->posicion.fil;
    jugador->posicion.fil = abs(col_jugador-dimension);

    for(int i=0; i<nivel->tope_paredes; i++){
        int col_aux = nivel->paredes[i].col;
        nivel->paredes[i].col = nivel->paredes[i].fil;
        nivel->paredes[i].fil = abs(col_aux-dimension);
    }

    for(int i=0; i<nivel->tope_obstaculos; i++){
        int col_aux = nivel->obstaculos[i].posicion.col;
        nivel->obstaculos[i].posicion.col = nivel->obstaculos[i].posicion.fil;
        nivel->obstaculos[i].posicion.fil = abs(col_aux-dimension);
    }

    for(int i=0; i<nivel->tope_herramientas; i++){
        int col_aux = nivel->herramientas[i].posicion.col;
        nivel->herramientas[i].posicion.col = nivel->herramientas[i].posicion.fil;
        nivel->herramientas[i].posicion.fil = abs(col_aux-dimension);
    }

    for(int i=0; i<nivel->tope_papeleos; i++){
        int col_aux = nivel->papeleos[i].posicion.col;
        nivel->papeleos[i].posicion.col = nivel->papeleos[i].posicion.fil;
        nivel->papeleos[i].posicion.fil = abs(col_aux-dimension);
    }

    jugador->movimientos_realizados++;
    restar_movimientos(jugador, 1);
}


void rotar_horario(nivel_t* nivel, jugador_t* jugador, int numero_nivel){
    int dimension = DIM_POR_NIVEL[numero_nivel-1]-1;

    int fil_jugador = jugador->posicion.fil;
    jugador->posicion.fil = jugador->posicion.col;
    jugador->posicion.col = abs(fil_jugador-dimension);

    for(int i=0; i<nivel->tope_paredes; i++){
        int fila_aux = nivel->paredes[i].fil;
        nivel->paredes[i].fil = nivel->paredes[i].col;
        nivel->paredes[i].col = abs(fila_aux-dimension);
    }

    for(int i=0; i<nivel->tope_obstaculos; i++){
        int fila_aux = nivel->obstaculos[i].posicion.fil;
        nivel->obstaculos[i].posicion.fil = nivel->obstaculos[i].posicion.col;
        nivel->obstaculos[i].posicion.col = abs(fila_aux-dimension);
    }

    for(int i=0; i<nivel->tope_herramientas; i++){
        int fila_aux = nivel->herramientas[i].posicion.fil;
        nivel->herramientas[i].posicion.fil = nivel->herramientas[i].posicion.col;
        nivel->herramientas[i].posicion.col = abs(fila_aux-dimension);
    }

    for(int i=0; i<nivel->tope_papeleos; i++){
        int fila_aux = nivel->papeleos[i].posicion.fil;
        nivel->papeleos[i].posicion.fil = nivel->papeleos[i].posicion.col;
        nivel->papeleos[i].posicion.col = abs(fila_aux-dimension);
    }

    jugador->movimientos_realizados++;
    restar_movimientos(jugador, 1);
}


bool chequear_movimiento(nivel_t* nivel, jugador_t* jugador, bool movimiento){
    int delta_movimiento = 0;

    if(movimiento == DERECHA){
        delta_movimiento = 1;
    }
    else if(movimiento == IZQUIERDA){
        delta_movimiento = -1;
    }

    for(int i=0; i<nivel->tope_paredes; i++){
        if(nivel->paredes[i].col == jugador->posicion.col+delta_movimiento && nivel->paredes[i].fil == jugador->posicion.fil){
            return false;    // Si hay una pared en la posicion del jugador, no se puede mover
        }
    }
    return true;    // Si no hay paredes en la posicion del jugador, se puede mover
}


void confirmar_colision(nivel_t* nivel, jugador_t* jugador){
    bool choque_confirmado = false;
    int i=0;
    while(!choque_confirmado &&i<nivel->tope_obstaculos){
        if(nivel->obstaculos[i].posicion.col == jugador->posicion.col && nivel->obstaculos[i].posicion.fil == jugador->posicion.fil){
            choque_confirmado = true;
            if(nivel->obstaculos[i].tipo == MEDIA_TIPO){
                restar_movimientos(jugador, 10);
            }
        }
        i++;
    }

    i=0;
    while(!choque_confirmado && i<nivel->tope_herramientas){
        if(nivel->herramientas[i].posicion.col == jugador->posicion.col && nivel->herramientas[i].posicion.fil == jugador->posicion.fil){
            choque_confirmado = true;
            if(nivel->herramientas[i].tipo == BOTELLA_TIPO){
                nivel->herramientas[i].tipo = nivel->herramientas[-1].tipo;
                sumar_movimientos(jugador, 7);
            }
            else if(nivel->herramientas[i].tipo == INTERRUPTOR_TIPO){
                if(jugador->ahuyenta_randall){
                    jugador->ahuyenta_randall = false;
                }
                else{
                    jugador->ahuyenta_randall = true;
                }
            }
        }
        i++;
    }

    i=0;
    bool falta_papeleo_anterior = false;
    while(!choque_confirmado && i<nivel->tope_papeleos && !falta_papeleo_anterior){
        if(nivel->papeleos[i].posicion.col == jugador->posicion.col && nivel->papeleos[i].posicion.fil == jugador->posicion.fil){
            if((i-1)>=0){
                if(nivel->papeleos[i-1].recolectado == true){
                    choque_confirmado = true;
                    nivel->papeleos[i].recolectado = true;
                }
                else{
                    falta_papeleo_anterior = true;
                }
            }
            else{
                choque_confirmado = true;
                nivel->papeleos[i].recolectado = true;
            }
        }
        i++;
    }
}


void mover_derecha(nivel_t* nivel, jugador_t* jugador){
    bool check_movimiento = chequear_movimiento(nivel, jugador, DERECHA);
    if(check_movimiento){
        jugador->posicion.col++;
        jugador->movimientos_realizados++;
        restar_movimientos(jugador, 1);
        confirmar_colision(nivel, jugador);
    }
    else{
        int rand_num = rand()%3;
        if(rand_num == 0){
            printf("\nLinda pared, pero no podes pasar 0(\n");
        }
        else if(rand_num == 1){
            printf("\nHay una pared, no podes pasar 0(\n");
        }
        else{
            printf("\nYOU SHALL NOT PASS!!! 0(\n");
        }
        sleep(1);
    }
}

void mover_izquierda(nivel_t* nivel, jugador_t* jugador){
    bool check_movimiento = chequear_movimiento(nivel, jugador, IZQUIERDA);
    if(check_movimiento){
        jugador->posicion.col--;
        jugador->movimientos_realizados++;
        restar_movimientos(jugador, 1);
        confirmar_colision(nivel, jugador);
    }
    else{
        int rand_num = rand()%3;
        if(rand_num == 0){
            printf("\nLinda pared, pero no podes pasar 0(\n");
        }
        else if(rand_num == 1){
            printf("\nHay una pared, no podes pasar 0(\n");
        }
        else{
            printf("\nYOU SHALL NOT PASS!!! 0(\n");
        }
    }
}


bool sin_piso(nivel_t* nivel, jugador_t* jugador){
    for(int i=0; i<nivel->tope_paredes; i++){
        if(nivel->paredes[i].col == jugador->posicion.col && nivel->paredes[i].fil == (jugador->posicion.fil+1)){
            return false;
        }
    }
    return true;
}


void chequear_gravedad(juego_t* juego){
    while(sin_piso(&juego->niveles[juego->nivel_actual-1], &juego->jugador)){
        system("clear");
        juego->jugador.posicion.fil++;
        confirmar_colision(&juego->niveles[juego->nivel_actual-1], &juego->jugador);
        imprimir_terreno(*juego);
        sleep(1);
    }
}


bool viene_randall(int movimientos, int numero_nivel){
    if(movimientos%(INTERVALOS_RANDALL_POR_NIVEL[numero_nivel-1]) == 0){
        return true;
    }
    return false;
}


void mover_papeleo(nivel_t* nivel, jugador_t* jugador, int numero_nivel){
    int tope_espacios_libres = 0;
    coordenada_libre_t espacios_libres[MAX_PAREDES];

    get_espacios_libres(nivel, espacios_libres, numero_nivel, &tope_espacios_libres);

    bool papeleo_movido = false;
    if(tope_espacios_libres > 0 && !jugador->ahuyenta_randall){
        int rand_num = rand()%tope_espacios_libres;
        while(!papeleo_movido){
            int rand_num_papeleo = rand()%nivel->tope_papeleos;
            if(nivel->papeleos[rand_num_papeleo].recolectado == false){
                nivel->papeleos[rand_num_papeleo].posicion.col = espacios_libres[rand_num].col;
                nivel->papeleos[rand_num_papeleo].posicion.fil = espacios_libres[rand_num].fil;
                papeleo_movido = true;
            }
        }
    }
}


void realizar_jugada(juego_t* juego){
    char accion = pedir_movimiento();
    bool movimiento_rotacion = false;

    if(accion == ROTAR_HORARIO){
        movimiento_rotacion = true;
        rotar_horario(&juego->niveles[(juego->nivel_actual)-1], &juego->jugador, juego->nivel_actual);
    }
    else if(accion == ROTAR_ANTIHORARIO){
        movimiento_rotacion = true;
        rotar_antihorario(&juego->niveles[(juego->nivel_actual)-1], &juego->jugador, juego->nivel_actual);
    }
    else if(accion == ACCION_DERECHA){
        movimiento_rotacion = true;
        mover_derecha(&juego->niveles[(juego->nivel_actual)-1], &juego->jugador);
    }
    else if(accion == ACCION_IZQUIERDA){
        movimiento_rotacion = true;
        mover_izquierda(&juego->niveles[(juego->nivel_actual)-1], &juego->jugador);
    }
    // }
    // else if(accion == ACCION_ARRIBA){
    //     accion_arriba(&juego);
    // }
    // else if(accion == ACCION_ABAJO){
    //     accion_abajo(&juego);
    // }
    // else if(accion == USAR_MARTILLO){
    //     usar_martillo(&juego);
    // }
    // else if(accion == USAR_EXTINTOR){
    //     usar_extintor(&juego);
    if(movimiento_rotacion){
        chequear_gravedad(juego);
    }

    if(viene_randall(juego->jugador.movimientos_realizados, juego->nivel_actual)){
        mover_papeleo(&juego->niveles[(juego->nivel_actual)-1], &juego->jugador, juego->nivel_actual);
    }

    // if(hay_que_aniadir_pared(juego->niveles[juego->nivel_actual-1], juego->jugador)){
    //     aniadir_pared(juego->niveles[juego->nivel_actual-1], juego->jugador);
    // }
}