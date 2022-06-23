#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

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
const int MOVIMIENTOS_PAREDES_NUEVAS_POR_NIVEL[MAX_NIVELES] = {40, 30, 20};

const int MEDIA_SACA_MOVIMIENTOS = 10;
const int MOVIMIENTOS_TOCA_FUEGO = -1;
const int BOTELLA_DA_MOVIMIENTOS = 7;

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

const bool IZQUIERDA = false;
const bool DERECHA = true;

typedef struct coordenada_libre_pared
{
    int fil;
    int col;
    bool es_adyacente;
    bool usado;
} coordenada_libre_t;

/*
pre:
    -
post:
    -
*/

/*
    precondicion:
        - juego inicializado
        - nivel asociado a nivel_actual inicializado

    postcondicion:
        - imprime por pantalla el nivel actual
*/
void imprimir_terreno(juego_t juego)
{
    int dim_nivel = DIM_POR_NIVEL[juego.nivel_actual - 1];

    char terreno[dim_nivel][dim_nivel];

    printf("--------------MIKE--------------\n");
    int papeleos_recolectados = 0;
    int i = 0;
    while (i < juego.niveles[juego.nivel_actual - 1].tope_papeleos)
    {
        if (juego.niveles[juego.nivel_actual - 1].papeleos[papeleos_recolectados].recolectado)
        {
            papeleos_recolectados++;
        }
        i++;
    }
    printf("MOVIMIENTOS: %i || ", juego.jugador.movimientos);
    printf("MOVIMIENTOS REALIZADOS: %i || ", juego.jugador.movimientos_realizados);
    printf("PAPELEOS RECOLECTADOS: %i/%i\n", papeleos_recolectados, juego.niveles[juego.nivel_actual - 1].tope_papeleos);
    printf("MARTILLOS: ");
    for (int i = 0; i < juego.jugador.martillos; i++)
    {
        printf("🔨");
    }
    printf(" || ");
    printf("EXTINTORES: ");
    for (int i = 0; i < juego.jugador.extintores; i++)
    {
        printf("🧯");
    }
    printf(" || ");
    printf("AHUYENTA RANDALL: %s\n", juego.jugador.ahuyenta_randall ? "✅" : "❌");
    printf("--------------------------------\n\n");

    for (int i = 0; i < dim_nivel; i++)
    {
        for (int j = 0; j < dim_nivel; j++)
        {
            terreno[i][j] = ' ';
        }
    }

    for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++)
    {
        terreno[juego.niveles[juego.nivel_actual - 1].paredes[i].fil][juego.niveles[juego.nivel_actual - 1].paredes[i].col] = PARED;
    }

    for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_obstaculos; i++)
    {
        terreno[juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.fil][juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.col] = juego.niveles[juego.nivel_actual - 1].obstaculos[i].tipo;
    }

    for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_herramientas; i++)
    {
        terreno[juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.fil][juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.col] = juego.niveles[juego.nivel_actual - 1].herramientas[i].tipo;
    }

    for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_papeleos; i++)
    {
        if (juego.niveles[juego.nivel_actual - 1].papeleos[i].recolectado == false)
        {
            int n_id = juego.niveles[juego.nivel_actual - 1].papeleos[i].id_papeleo;
            char id_papeleo_char = (char)((n_id + 1) + '0');
            terreno[juego.niveles[juego.nivel_actual - 1].papeleos[i].posicion.fil][juego.niveles[juego.nivel_actual - 1].papeleos[i].posicion.col] = id_papeleo_char;
        }
        else
        {
            terreno[juego.niveles[juego.nivel_actual - 1].papeleos[i].posicion.fil][juego.niveles[juego.nivel_actual - 1].papeleos[i].posicion.col] = ' ';
        }
    }

    terreno[juego.jugador.posicion.fil][juego.jugador.posicion.col] = MIKE;

    for (int i = 0; i < dim_nivel; i++)
    {
        for (int j = 0; j < dim_nivel; j++)
        {
            if (terreno[i][j] == INTERRUPTOR_TIPO)
            {
                if (juego.jugador.ahuyenta_randall)
                {
                    printf("✔ ");
                }
                else
                {
                    printf("x ");
                }
            }
            else
            {
                printf("%c ", terreno[i][j]);
            }
        }
        printf("\n");
    }
}

/*
    precondiciones:
        - el nivel debe tener las paredes y su tope inicializados
        - fila y columna deben estar dentro de la dimension del nivel y corresponder al valor a verificar

    postcondiciones:
        - devuelve true si la posicion es adyacente a una pared
        - devuelve false si la posicion no es adyacente a una pared
*/
bool es_pared_adyacente(nivel_t *nivel, int fila, int columna, coordenada_libre_t espacios_libres[MAX_PAREDES])
{
    bool es_adyacente = false;

    for (int i = 0; i < nivel->tope_paredes; i++)
    {
        if (nivel->paredes[i].fil == fila - 1 && nivel->paredes[i].col == columna && es_adyacente == false)
        {
            es_adyacente = true;
        }
        else if (nivel->paredes[i].fil == fila + 1 && nivel->paredes[i].col == columna && es_adyacente == false)
        {
            es_adyacente = true;
        }
        else if (nivel->paredes[i].fil == fila && nivel->paredes[i].col == columna - 1 && es_adyacente == false)
        {
            es_adyacente = true;
        }
        else if (nivel->paredes[i].fil == fila && nivel->paredes[i].col == columna + 1 && es_adyacente == false)
        {
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
void get_espacios_libres(nivel_t *nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int numero_nivel, int *tope_espacios_libres, int jugador_fil, int jugador_col)
{
    int dim_nivel = DIM_POR_NIVEL[numero_nivel - 1];
    bool espacio_invalido = false;
    int index_esp_libre = 0;

    for (int fila = 0; fila < dim_nivel; fila++)
    {
        for (int columna = 0; columna < dim_nivel; columna++)
        {
            for (int coords_pared = 0; coords_pared < nivel->tope_paredes; coords_pared++)
            {
                if ((jugador_fil == fila && jugador_col == columna) && espacio_invalido == false)
                {
                    espacio_invalido = true;
                }
                else if (nivel->paredes[coords_pared].fil == fila && nivel->paredes[coords_pared].col == columna && espacio_invalido == false)
                {
                    coords_pared = nivel->tope_paredes;
                    espacio_invalido = true;
                }
                else if (coords_pared == nivel->tope_paredes - 1 && espacio_invalido == false)
                {
                    espacios_libres[index_esp_libre].fil = fila;
                    espacios_libres[index_esp_libre].col = columna;
                    espacios_libres[*tope_espacios_libres].es_adyacente = es_pared_adyacente(nivel, fila, columna, espacios_libres);
                    espacios_libres[*tope_espacios_libres].usado = false;
                    index_esp_libre = index_esp_libre + 1;
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
void posicionar_obstaculo_adyacente(nivel_t *nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int *tope_espacios_libres, int cantidad_obstaculos, char tipo_obstaculo)
{
    int index_espacio_libre;

    for (int obstaculos_colocados = 0; obstaculos_colocados < cantidad_obstaculos; obstaculos_colocados++)
    {
        do
        {
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while (espacios_libres[index_espacio_libre].es_adyacente == false || espacios_libres[index_espacio_libre].usado == true);

        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->obstaculos[nivel->tope_obstaculos].tipo = tipo_obstaculo;
        nivel->tope_obstaculos++;
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
void posicionar_obstaculo(nivel_t *nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int *tope_espacios_libres, int cantidad_obstaculos, char tipo_obstaculo)
{
    int index_espacio_libre;

    for (int obstaculos_colocados = 0; obstaculos_colocados < cantidad_obstaculos; obstaculos_colocados++)
    {
        do
        {
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while (espacios_libres[index_espacio_libre].usado != false);

        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->obstaculos[nivel->tope_obstaculos]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->obstaculos[nivel->tope_obstaculos].tipo = tipo_obstaculo;
        nivel->tope_obstaculos++;
        espacios_libres[index_espacio_libre].usado = true;
    }
}

void inicializar_obstaculos(nivel_t *nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int *tope_espacios_libres)
{

    int cantidad_fuegos = FUEGOS_POR_NIVEL[numero_nivel - 1];
    int cantidad_medias = MEDIAS_POR_NIVEL[numero_nivel - 1];

    nivel->tope_obstaculos = 0;

    if (personaje_tp1 == OLAF_ID && numero_nivel == NIVELES_TOTALES[0])
    {
        cantidad_fuegos = cantidad_fuegos - 2;
    }
    else if (personaje_tp1 == OLAF_ID && numero_nivel == NIVELES_TOTALES[1])
    {
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
void posicionar_herramienta(nivel_t *nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int *tope_espacios_libres, int cantidad_herramienta, char tipo_herramienta)
{
    int index_espacio_libre;

    for (int herramientas_colocadas = 0; herramientas_colocadas < cantidad_herramienta; herramientas_colocadas++)
    {
        do
        {
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while (espacios_libres[index_espacio_libre].usado != false);

        (nivel->herramientas[nivel->tope_herramientas]).posicion.fil = espacios_libres[index_espacio_libre].fil;
        (nivel->herramientas[nivel->tope_herramientas]).posicion.col = espacios_libres[index_espacio_libre].col;
        nivel->herramientas[nivel->tope_herramientas].tipo = tipo_herramienta;
        nivel->tope_herramientas++;
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
void inicializar_herramientas(nivel_t *nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int *tope_espacios_libres)
{

    int cantidad_botellas = BOTELLAS_POR_NIVEL[numero_nivel - 1];
    int cantidad_interruptores = INTERRUPTORES_POR_NIVEL[numero_nivel - 1];

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
void posicionar_papeleos(nivel_t *nivel, coordenada_libre_t espacios_libres[MAX_PAREDES], int *tope_espacios_libres)
{
    int index_espacio_libre;

    for (int papeleos_colocados = 0; papeleos_colocados < nivel->tope_papeleos; papeleos_colocados++)
    {
        do
        {
            index_espacio_libre = rand() % *tope_espacios_libres;
        } while (espacios_libres[index_espacio_libre].usado != false);

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
void inicializar_papeleos(nivel_t *nivel, int numero_nivel, char personaje_tp1, coordenada_libre_t espacios_libres[MAX_PAREDES], int *tope_espacios_libres)
{

    int cantidad_papeleos = PAPELEOS_POR_NIVEL[numero_nivel - 1];

    if (personaje_tp1 == STITCH_ID && numero_nivel == NIVELES_TOTALES[TOPE_NIVELES])
    {
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
void inicializar_objetos(nivel_t *nivel, int numero_nivel, char personaje_tp1)
{

    int tope_espacios_libres = 0;
    coordenada_libre_t espacios_libres[MAX_PAREDES];

    get_espacios_libres(nivel, espacios_libres, numero_nivel, &tope_espacios_libres, nivel->pos_inicial_jugador.fil, nivel->pos_inicial_jugador.col);

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
void inicializar_nivel(nivel_t *nivel, int numero_nivel, char personaje_tp1)
{

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
void inicializar_jugador(jugador_t *jugador, coordenada_t *pos_inicial_jugador, int numero_nivel, char personaje_tp1)
{
    jugador->posicion.fil = pos_inicial_jugador->fil;
    jugador->posicion.col = pos_inicial_jugador->col;

    jugador->movimientos_realizados = 0;

    jugador->movimientos += MOVIMIENTOS_POR_NIVEL[numero_nivel - 1];
    jugador->martillos = MARTILLOS_POR_NIVEL[numero_nivel - 1];
    jugador->extintores = EXTINTORES_POR_NIVEL[numero_nivel - 1];

    if (personaje_tp1 == JASMIN_ID)
    {
        jugador->martillos += 1;
    }
    else if (personaje_tp1 == RAYO_ID && numero_nivel == NIVELES_TOTALES[0])
    {
        jugador->movimientos += 10;
    }
}

/*
    precondiones: personaje_tp1 debe ser una de las constantes definidas en el archivo dia_en_la_uni.h

    postcondiciones: inicializa el juego con 3 niveles
*/
void inicializar_juego(juego_t *juego, char personaje_tp1)
{

    juego->personaje_tp1 = personaje_tp1;
    (juego->jugador).movimientos = 0;
    juego->nivel_actual = 1;

    for (int i = 0; i < MAX_NIVELES; i++)
    {
        inicializar_nivel(&juego->niveles[i], i + 1, juego->personaje_tp1);
    }
    inicializar_jugador(&juego->jugador, &juego->niveles[(juego->nivel_actual) - 1].pos_inicial_jugador, juego->nivel_actual, personaje_tp1);
}



/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------TP3----------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

/*
pre:
    -
post:
    - retorna el movimiento ingresado por el usuario
*/
char pedir_movimiento()
{
    char movimiento;
    printf("\nIngrese un movimiento:\nUtilizar martillo: %c.\nUtilizar extintor: %c.\nMover a izquierda: %c.\nMover a derecha: %c.\nMov. rotacional horario: %c.\nMov. rotacional antihorario: %c.\n\n", USAR_MARTILLO, USAR_EXTINTOR, ACCION_DERECHA, ACCION_IZQUIERDA, ROTAR_HORARIO, ROTAR_ANTIHORARIO);
    scanf(" %c", &movimiento);
    movimiento = (char)toupper(movimiento);

    while (movimiento != USAR_MARTILLO && movimiento != USAR_EXTINTOR && movimiento != ACCION_DERECHA && movimiento != ACCION_IZQUIERDA && movimiento != ROTAR_HORARIO && movimiento != ROTAR_ANTIHORARIO)
    {
        printf("Ingrese un movimiento valido: ");
        scanf(" %c", &movimiento);
        movimiento = (char)toupper(movimiento);
    }
    return movimiento;
}

/*
pre:
    - jugador debe estar inicializado
    - cantidad_movimientos debe ser entero no menor a -1
post:
    - resta movimientos al jugador, poniendolo en -1 en caso de que haya tocado un fuego
*/
void restar_movimientos(jugador_t *jugador, int cantidad_movimientos)
{
    if (cantidad_movimientos == MOVIMIENTOS_TOCA_FUEGO)
    {
        jugador->movimientos = MOVIMIENTOS_TOCA_FUEGO;
    }
    else if (jugador->movimientos - cantidad_movimientos >= 0)
    {
        jugador->movimientos -= cantidad_movimientos;
    }
    else
    {
        jugador->movimientos = 0;
    }
}

/*
pre:
    - jugador debe estar inicializado
post:
    - suma al jugador los movimientos indicados
*/
void sumar_movimientos(jugador_t *jugador, int cantidad_movimientos)
{
    jugador->movimientos += cantidad_movimientos;
}

/*
pre:
    - nivel y jugador deben estar inicializados
    - numero_nivel debe ser un numero de nivel valido
post:
    - rota el nivel inidicado en sentido antihorario
*/
void rotar_antihorario(nivel_t *nivel, jugador_t *jugador, int numero_nivel)
{
    int dimension = DIM_POR_NIVEL[numero_nivel - 1] - 1;

    int col_jugador = jugador->posicion.col;
    jugador->posicion.col = jugador->posicion.fil;
    jugador->posicion.fil = abs(col_jugador - dimension);

    for (int i = 0; i < nivel->tope_paredes; i++)
    {
        int col_aux = nivel->paredes[i].col;
        nivel->paredes[i].col = nivel->paredes[i].fil;
        nivel->paredes[i].fil = abs(col_aux - dimension);
    }

    for (int i = 0; i < nivel->tope_obstaculos; i++)
    {
        int col_aux = nivel->obstaculos[i].posicion.col;
        nivel->obstaculos[i].posicion.col = nivel->obstaculos[i].posicion.fil;
        nivel->obstaculos[i].posicion.fil = abs(col_aux - dimension);
    }

    for (int i = 0; i < nivel->tope_herramientas; i++)
    {
        int col_aux = nivel->herramientas[i].posicion.col;
        nivel->herramientas[i].posicion.col = nivel->herramientas[i].posicion.fil;
        nivel->herramientas[i].posicion.fil = abs(col_aux - dimension);
    }

    for (int i = 0; i < nivel->tope_papeleos; i++)
    {
        int col_aux = nivel->papeleos[i].posicion.col;
        nivel->papeleos[i].posicion.col = nivel->papeleos[i].posicion.fil;
        nivel->papeleos[i].posicion.fil = abs(col_aux - dimension);
    }

    jugador->movimientos_realizados++;
    restar_movimientos(jugador, 1);
}

/*
pre:
    - nivel y jugador deben estar inicializados
    - numero_nivel debe ser un numero de nivel valido
post:
    - rota el nivel inidicado en sentido horario
*/
void rotar_horario(nivel_t *nivel, jugador_t *jugador, int numero_nivel)
{
    int dimension = DIM_POR_NIVEL[numero_nivel - 1] - 1;

    int fil_jugador = jugador->posicion.fil;
    jugador->posicion.fil = jugador->posicion.col;
    jugador->posicion.col = abs(fil_jugador - dimension);

    for (int i = 0; i < nivel->tope_paredes; i++)
    {
        int fila_aux = nivel->paredes[i].fil;
        nivel->paredes[i].fil = nivel->paredes[i].col;
        nivel->paredes[i].col = abs(fila_aux - dimension);
    }

    for (int i = 0; i < nivel->tope_obstaculos; i++)
    {
        int fila_aux = nivel->obstaculos[i].posicion.fil;
        nivel->obstaculos[i].posicion.fil = nivel->obstaculos[i].posicion.col;
        nivel->obstaculos[i].posicion.col = abs(fila_aux - dimension);
    }

    for (int i = 0; i < nivel->tope_herramientas; i++)
    {
        int fila_aux = nivel->herramientas[i].posicion.fil;
        nivel->herramientas[i].posicion.fil = nivel->herramientas[i].posicion.col;
        nivel->herramientas[i].posicion.col = abs(fila_aux - dimension);
    }

    for (int i = 0; i < nivel->tope_papeleos; i++)
    {
        int fila_aux = nivel->papeleos[i].posicion.fil;
        nivel->papeleos[i].posicion.fil = nivel->papeleos[i].posicion.col;
        nivel->papeleos[i].posicion.col = abs(fila_aux - dimension);
    }

    jugador->movimientos_realizados++;
    restar_movimientos(jugador, 1);
}

/*
pre:
    - jugador  y nivel deben estar inicializados
    - movimiento debe ser IZQUIERDA o DERECHA
post:
    - retorna si es el jugador puede moverser en la direccion indicada en movimiento
*/
bool chequear_movimiento(nivel_t *nivel, jugador_t *jugador, bool movimiento)
{
    int delta_movimiento = 0;

    if (movimiento == DERECHA)
    {
        delta_movimiento = 1;
    }
    else if (movimiento == IZQUIERDA)
    {
        delta_movimiento = -1;
    }

    for (int i = 0; i < nivel->tope_paredes; i++)
    {
        if (nivel->paredes[i].col == jugador->posicion.col + delta_movimiento && nivel->paredes[i].fil == jugador->posicion.fil)
        {
            return false;
        }
    }
    return true;
}

/*
pre:
    - nivel y jugador deben estar inicializados
post:
    - verifica si la posicion de un jugador es igual a la posicion de una herramienta, obstaculo o papeleo. Si coincide con alguno realiza la accion correspondiente
*/
void confirmar_colision(nivel_t *nivel, jugador_t *jugador)
{
    bool choque_confirmado = false;
    int i = 0;
    while (!choque_confirmado && i < nivel->tope_obstaculos)
    {
        if (nivel->obstaculos[i].posicion.col == jugador->posicion.col && nivel->obstaculos[i].posicion.fil == jugador->posicion.fil)
        {
            choque_confirmado = true;
            if (nivel->obstaculos[i].tipo == MEDIA_TIPO)
            {
                restar_movimientos(jugador, MEDIA_SACA_MOVIMIENTOS);
                printf("SE RESTAN MOVIMIENTOS POR MEDIA-------------------------------------------------------------------------------------------------------------\n");
            }
            else if (nivel->obstaculos[i].tipo == FUEGO_TIPO)
            {
                restar_movimientos(jugador, MOVIMIENTOS_TOCA_FUEGO);
            }
        }
        i++;
    }

    i = 0;
    while (!choque_confirmado && i < nivel->tope_herramientas)
    {
        if (nivel->herramientas[i].posicion.col == jugador->posicion.col && nivel->herramientas[i].posicion.fil == jugador->posicion.fil)
        {
            choque_confirmado = true;
            if (nivel->herramientas[i].tipo == BOTELLA_TIPO)
            {
                sumar_movimientos(jugador, BOTELLA_DA_MOVIMIENTOS);
            }
            else if (nivel->herramientas[i].tipo == INTERRUPTOR_TIPO)
            {
                if (jugador->ahuyenta_randall)
                {
                    jugador->ahuyenta_randall = false;
                }
                else
                {
                    jugador->ahuyenta_randall = true;
                }
            }
        }
        i++;
    }

    i = 0;
    bool falta_papeleo_anterior = false;
    while (!choque_confirmado && i < nivel->tope_papeleos && !falta_papeleo_anterior)
    {
        if (nivel->papeleos[i].posicion.col == jugador->posicion.col && nivel->papeleos[i].posicion.fil == jugador->posicion.fil)
        {
            if ((i - 1) >= 0)
            {
                if (nivel->papeleos[i - 1].recolectado == true)
                {
                    choque_confirmado = true;
                    nivel->papeleos[i].recolectado = true;
                }
                else
                {
                    falta_papeleo_anterior = true;
                }
            }
            else
            {
                choque_confirmado = true;
                nivel->papeleos[i].recolectado = true;
            }
        }
        i++;
    }
}

/*
pre:
    - nivel y jugador deben estar inicializados
post:
    - resuelve el movimiento del jugador hacia la derecha
    - actualiza el estado del jugador en caso de poder moverse
    - actualiza el estado de movimiento_realizado en caso de poder resolver correctamente el movimiento
*/
void mover_derecha(nivel_t *nivel, jugador_t *jugador, bool *movimiento_realizado)
{
    bool check_movimiento = chequear_movimiento(nivel, jugador, DERECHA);
    if (check_movimiento)
    {
        jugador->posicion.col++;
        jugador->movimientos_realizados++;
        restar_movimientos(jugador, 1);
        confirmar_colision(nivel, jugador);
        *movimiento_realizado = true;
    }
    else
    {
        int rand_num = rand() % 3;
        if (rand_num == 0)
        {
            printf("\nLinda pared, pero no podes pasar 0(\n");
        }
        else if (rand_num == 1)
        {
            printf("\nHay una pared, no podes pasar 0(\n");
        }
        else
        {
            printf("\nYOU SHALL NOT PASS!!! 0(\n");
        }
        detener_el_tiempo(1);
    }
}

/*
pre:
    - nivel y jugador deben estar inicializados
post:
    - resuelve el movimiento del jugador hacia la izquierda
    - actualiza el estado del jugador en caso de poder moverse
    - actualiza el estado de movimiento_realizado en caso de poder resolver correctamente el movimiento
*/
void mover_izquierda(nivel_t *nivel, jugador_t *jugador, bool *movimiento_realizado)
{
    bool check_movimiento = chequear_movimiento(nivel, jugador, IZQUIERDA);
    if (check_movimiento)
    {
        jugador->posicion.col--;
        jugador->movimientos_realizados++;
        restar_movimientos(jugador, 1);
        confirmar_colision(nivel, jugador);
        *movimiento_realizado = true;
    }
    else
    {
        int rand_num = rand() % 3;
        if (rand_num == 0)
        {
            printf("\nLinda pared, pero no podes pasar 0(\n");
        }
        else if (rand_num == 1)
        {
            printf("\nHay una pared, no podes pasar 0(\n");
        }
        else
        {
            printf("\nYOU SHALL NOT PASS!!! 0(\n");
        }
        detener_el_tiempo(1);
    }
}

/*
pre:
    - nivel debe estar inicializado
    - jugador debe estar inicializado y tener una posicion valida
post:
    - retorna TRUE en caso de que el jugador este sobre un piso, FALSE en caso contrario
*/
bool sin_piso(nivel_t *nivel, jugador_t *jugador)
{
    for (int i = 0; i < nivel->tope_paredes; i++)
    {
        if (nivel->paredes[i].col == jugador->posicion.col && nivel->paredes[i].fil == (jugador->posicion.fil + 1))
        {
            return false;
        }
    }
    return true;
}

/*
pre:
    - juego debe tener un nivel cargado y un jugador cargado
post:
    - mueve al jugador una posicion hacia abajo mientras no tenga un suelo debajo
*/
void chequear_gravedad(juego_t *juego)
{
    while (sin_piso(&juego->niveles[juego->nivel_actual - 1], &juego->jugador))
    {
        detener_el_tiempo(0.5);
        system("clear");
        juego->jugador.posicion.fil++;
        confirmar_colision(&juego->niveles[juego->nivel_actual - 1], &juego->jugador);
        imprimir_terreno(*juego);
    }
}

/*
pre:
    - movimientos > 0
    - numero_nivel debe ser un numero de nivel valido
post:
    - retorna si Randall mueve un papeleo o no
*/
bool viene_randall(int movimientos, int numero_nivel)
{
    if (movimientos % (INTERVALOS_RANDALL_POR_NIVEL[numero_nivel - 1]) == 0)
    {
        return true;
    }
    return false;
}

/*
pre:
    - nivel y coodenadas_libres deben estar inicializados
    - tope_espacios_libres debe ser un entero positivo
post:
    - asigna a los valores de espacios libres de coordenadas_libres como usados en caso de que un objeto del nivel se encuentre ahí
*/
void aniadir_objetos_espacios_libres(nivel_t *nivel, coordenada_libre_t *coordenadas_libres, int tope_espacios_libres)
{
    for (int j = 0; j < tope_espacios_libres; j++)
    {
        int fil_libre = coordenadas_libres[j].fil;
        int col_libre = coordenadas_libres[j].col;
        for (int i = 0; i < nivel->tope_obstaculos; i++)
        {
            if (nivel->obstaculos[i].posicion.col == col_libre && nivel->obstaculos[i].posicion.fil == fil_libre)
            {
                coordenadas_libres[j].usado = true;
            }
        }

        for (int i = 0; i < nivel->tope_herramientas; i++)
        {
            if (nivel->herramientas[i].posicion.col == col_libre && nivel->herramientas[i].posicion.fil == fil_libre)
            {
                coordenadas_libres[j].usado = true;
            }
        }

        for (int i = 0; i < nivel->tope_papeleos; i++)
        {
            if (nivel->papeleos[i].posicion.col == col_libre && nivel->papeleos[i].posicion.fil == fil_libre)
            {
                coordenadas_libres[j].usado = true;
            }
        }
    }
}

/*
pre:
    - nivel y jugador deben estar inicializados
    - numero_nivel debe ser un numero de nivel valido
post:
    - cambia la unibacion de un papeleo aleatorio del nivel
*/
void mover_papeleo(nivel_t *nivel, jugador_t *jugador, int numero_nivel)
{
    int tope_espacios_libres = 0;
    coordenada_libre_t espacios_libres[MAX_PAREDES];

    get_espacios_libres(nivel, espacios_libres, numero_nivel, &tope_espacios_libres, jugador->posicion.fil, jugador->posicion.col);
    aniadir_objetos_espacios_libres(nivel, espacios_libres, tope_espacios_libres);

    bool papeleo_movido = false;
    int rand_num = 0;
    if (tope_espacios_libres > 0 && !jugador->ahuyenta_randall)
    {
        do
        {
            rand_num = rand() % tope_espacios_libres;
        } while (espacios_libres[rand_num].usado);
        
        while (!papeleo_movido)
        {
            int rand_num_papeleo = rand() % nivel->tope_papeleos;
            if (nivel->papeleos[rand_num_papeleo].recolectado == false)
            {
                nivel->papeleos[rand_num_papeleo].posicion.col = espacios_libres[rand_num].col;
                nivel->papeleos[rand_num_papeleo].posicion.fil = espacios_libres[rand_num].fil;
                papeleo_movido = true;
            }
        }
    }
}

/*
pre:
    - movimientos es un entero positivo
    - numero_nivel es un numero de nivel valido
post:
    - retorna si es necesario aniadir una pared (TRUE si es necesario, FALSE si no)
*/
bool hay_que_aniadir_pared(int movimientos, int numero_nivel)
{
    if (movimientos <= MOVIMIENTOS_PAREDES_NUEVAS_POR_NIVEL[numero_nivel - 1])
    {
        return true;
    }
    return false;
}

/*
pre:
    - el nivel y el jugador deben estar inicializados
    - el numero de nivel debe ser valido
post:
    - aniade una pared al nivel correspondiente en un espacio libre
*/
void aniadir_pared(nivel_t *nivel, jugador_t *jugador, int numero_nivel)
{
    int tope_espacios_libres = 0;
    coordenada_libre_t espacios_libres[MAX_PAREDES];

    get_espacios_libres(nivel, espacios_libres, numero_nivel, &tope_espacios_libres, jugador->posicion.fil, jugador->posicion.col);
    aniadir_objetos_espacios_libres(nivel, espacios_libres, tope_espacios_libres);

    int rand_num = 0;
    if (tope_espacios_libres > 0)
    {
        do
        {
            rand_num = rand() % tope_espacios_libres;
        } while (espacios_libres[rand_num].usado);
        nivel->paredes[nivel->tope_paredes].col = espacios_libres[rand_num].col;
        nivel->paredes[nivel->tope_paredes].fil = espacios_libres[rand_num].fil;
        nivel->tope_paredes++;
    }
}

/*
pre:
post:
    - Retorna la direccion a utilizar el martillo (W, A, S, D)
*/
char pedir_accion_martillo()
{
    char accion;
    printf("\nIngrese la dirreción a martillar:\nArriba: %c.\nAbajo: %c.\nDerecha: %c.\nIzquierda: %c.\n\n", ACCION_ARRIBA, ACCION_ABAJO, ACCION_DERECHA, ACCION_IZQUIERDA);
    scanf(" %c", &accion);
    accion = (char)toupper(accion);

    while (accion != ACCION_ARRIBA && accion != ACCION_ABAJO && accion != ACCION_DERECHA && accion != ACCION_IZQUIERDA)
    {
        printf("Ingrese una direccion valida: ");
        scanf(" %c", &accion);
        accion = (char)toupper(accion);
    }
    return accion;
}

/*
pre:
    - el nivel debe estar inicializado
    - el jugador debe estar inicializado
    - la direccion debe ser una de las 4 direcciones posibles (W, A, S, D)
    - el numero de nivel debe ser valido
post:
    - si la direccion es valida, se rompe en la direccion indicada en caso de haberlo y se le resta al jugador un martillo      #AIUDA
*/
void usar_martillo(nivel_t *nivel, jugador_t *jugador, char direccion, int numero_nivel)
{
    int dimension_nivel = DIM_POR_NIVEL[numero_nivel - 1] - 1;

    int pared_a_martillar_fil = jugador->posicion.fil;
    int pared_a_martillar_col = jugador->posicion.col;

    if (direccion == ACCION_ARRIBA)
    {
        pared_a_martillar_fil = jugador->posicion.fil - 1;
        pared_a_martillar_col = jugador->posicion.col;
    }
    else if (direccion == ACCION_ABAJO)
    {
        pared_a_martillar_fil = jugador->posicion.fil + 1;
        pared_a_martillar_col = jugador->posicion.col;
    }
    else if (direccion == ACCION_DERECHA)
    {
        pared_a_martillar_fil = jugador->posicion.fil;
        pared_a_martillar_col = jugador->posicion.col + 1;
    }
    else if (direccion == ACCION_IZQUIERDA)
    {
        pared_a_martillar_fil = jugador->posicion.fil;
        pared_a_martillar_col = jugador->posicion.col - 1;
    }

    int i = 0;
    bool pared_encontrada = false;
    while (i < nivel->tope_paredes && !pared_encontrada)
    {
        if (nivel->paredes[i].fil == pared_a_martillar_fil && nivel->paredes[i].col == pared_a_martillar_col)
        {
            pared_encontrada = true;
            if (nivel->paredes[i].col == 0 || nivel->paredes[i].col == dimension_nivel || nivel->paredes[i].fil == 0 || nivel->paredes[i].fil == dimension_nivel)
            {
                printf("\nNo se puede martillar la pared de la pared. 0(\n");
            }
            else
            {
                nivel->paredes[i] = nivel->paredes[nivel->tope_paredes - 1];
                nivel->tope_paredes--;
                jugador->martillos--;
                printf("\nWREAK IT MIKE!!! >0)\n");
            }
        }
        i++;
    }
    if (!pared_encontrada)
    {
        int rand_num = rand() % 2;
        if (rand_num == 0)
        {
            printf("\nSwoooshh, no había pared ahi, 0(\n");
        }
        else if (rand_num == 1)
        {
            printf("\nNo paredes para destruir. 0(\n");
        }
        else
        {
            printf("\nNo hay una pared ahi. 0(\n");
        };
    }
    detener_el_tiempo(1);
}

/*
pre:
post:
    - Retorna la direccion a utilizar el extintor (W, A, S, D)
*/
char pedir_accion_extintor()
{
    char accion;
    printf("\nIngrese la dirreción en la que quiere apagar el fuego:\nArriba: %c.\nDerecha: %c.\nIzquierda: %c.\n\n", ACCION_ARRIBA, ACCION_DERECHA, ACCION_IZQUIERDA);
    scanf(" %c", &accion);
    accion = (char)toupper(accion);

    while (accion != ACCION_ARRIBA && accion != ACCION_DERECHA && accion != ACCION_IZQUIERDA)
    {
        printf("Ingrese una direccion valida: ");
        scanf(" %c", &accion);
        accion = (char)toupper(accion);
    }
    return accion;
}

/*
pre:
    - el nivel debe estar inicializado
    - el jugador debe estar inicializado
    - la direccion debe ser una de las 4 direcciones posibles (W, A, S, D)
post:
    - si la direccion es valida, se apaga el fuego en la direccion indicada en caso de haberlo y se le resta al jugador un extintor
*/
void usar_extintor(nivel_t *nivel, jugador_t *jugador, char direccion)
{

    int pared_a_apagar_fil = jugador->posicion.fil;
    int pared_a_apagar_col = jugador->posicion.col;

    if (direccion == ACCION_ARRIBA)
    {
        pared_a_apagar_fil = jugador->posicion.fil - 1;
        pared_a_apagar_col = jugador->posicion.col;
    }
    else if (direccion == ACCION_DERECHA)
    {
        pared_a_apagar_fil = jugador->posicion.fil;
        pared_a_apagar_col = jugador->posicion.col + 1;
    }
    else if (direccion == ACCION_IZQUIERDA)
    {
        pared_a_apagar_fil = jugador->posicion.fil;
        pared_a_apagar_col = jugador->posicion.col - 1;
    }

    int i = 0;
    bool fuego_encontrado = false;
    while (i < nivel->tope_obstaculos && !fuego_encontrado)
    {
        if (nivel->obstaculos[i].tipo == FUEGO_TIPO && nivel->obstaculos[i].posicion.fil == pared_a_apagar_fil && nivel->obstaculos[i].posicion.col == pared_a_apagar_col)
        {
            fuego_encontrado = true;
            if (jugador->extintores > 0)
            {
                nivel->obstaculos[i] = nivel->obstaculos[nivel->tope_obstaculos - 1];
                nivel->tope_obstaculos--;
                jugador->extintores--;
                printf("\nFuego apagado con exito. 0)\n");
            }
            else
            {
                printf("\nNo hay mas extintores. 0(\n");
            }
        }
        i++;
    }
    if (!fuego_encontrado)
    {
        int rand_num = rand() % 2;
        if (rand_num == 0)
        {
            printf("\nMantenlo prendido, fuego\nNo lo dejes apagar\nY grita, fuego. (no hay fuegos asi) 0(\n");
        }
        else if (rand_num == 1)
        {
            printf("\nNo veo ningun fuego para apagar. 0(\n");
        }
        else
        {
            printf("\nNo hay fuego ahi. 0(\n");
        }
    }
    detener_el_tiempo(1);
}

/*
pre:
    - el juego debe tener un nivel inicializado
    - el jugador debe estar inicializado
post:
    - resuelve la accion ingresada (cae por gravedad, hay que aniadir pared, Randall mueve un papeleo, etc.)
*/
void resolver_jugada(juego_t *juego, bool movimiento_valido)
{

    chequear_gravedad(juego);

    if (movimiento_valido && hay_que_aniadir_pared(juego->jugador.movimientos_realizados, juego->nivel_actual))
    {
        aniadir_pared(&juego->niveles[(juego->nivel_actual) - 1], &juego->jugador, juego->nivel_actual);
    }

    if (viene_randall(juego->jugador.movimientos_realizados, juego->nivel_actual))
    {
        mover_papeleo(&juego->niveles[(juego->nivel_actual) - 1], &juego->jugador, juego->nivel_actual);
    }
}

/*
pre:
    - el juego debe estar inicializado con al menos un nivel
post:
    - se resuelve la accion del jugador en el nivel actual
*/
void realizar_jugada(juego_t *juego)
{
    char accion = pedir_movimiento();
    bool movimiento_valido = false;

    if (accion == ROTAR_HORARIO)
    {
        movimiento_valido = true;
        rotar_horario(&juego->niveles[(juego->nivel_actual) - 1], &juego->jugador, juego->nivel_actual);
    }
    else if (accion == ROTAR_ANTIHORARIO)
    {
        movimiento_valido = true;
        rotar_antihorario(&juego->niveles[(juego->nivel_actual) - 1], &juego->jugador, juego->nivel_actual);
    }
    else if (accion == ACCION_DERECHA)
    {
        mover_derecha(&juego->niveles[(juego->nivel_actual) - 1], &juego->jugador, &movimiento_valido);
    }
    else if (accion == ACCION_IZQUIERDA)
    {
        mover_izquierda(&juego->niveles[(juego->nivel_actual) - 1], &juego->jugador, &movimiento_valido);
    }
    else if (accion == USAR_MARTILLO)
    {
        char direccion_martillo = pedir_accion_martillo();
        usar_martillo(&juego->niveles[(juego->nivel_actual) - 1], &juego->jugador, direccion_martillo, juego->nivel_actual);
    }
    else if (accion == USAR_EXTINTOR)
    {
        char direccion_extintor = pedir_accion_extintor();
        usar_extintor(&juego->niveles[(juego->nivel_actual) - 1], &juego->jugador, direccion_extintor);
    }

    resolver_jugada(juego, movimiento_valido);
}

/*
pre:
    - papeleos debe tener al menos un elemento
    - tope papeleos debe coincidir con el numero de papeleos del nivel
post:
    - retorna el estado del nivel, sea JUGANDO (si NO recolecto todos los papeleos) o GANADO (si recolecto todos los papeleos)
*/
int estado_nivel(papeleo_t *papeleos, int tope_papeleos)
{
    int i = 0;
    bool falta_papeleo = false;
    while (i < tope_papeleos && !falta_papeleo)
    {
        if (papeleos[i].recolectado == false)
        {
            falta_papeleo = true;
        }
        i++;
    }
    if (falta_papeleo)
    {
        return JUGANDO;
    }
    else
    {
        return GANADO;
    }
}

/*
pre:
    - juego tiene al menos un nivel bien inicializado
    - juego->nivel_actual es un numero entre 1 y juego->tope_niveles
    - jugador inicializado
post:
    - retorna el estado del juego, ya sea JUGANDO (0), GANADO (1) o PERDIDO (-1)
*/
int estado_juego(juego_t juego)
{
    int i = juego.nivel_actual - 1;
    int estado = 0;
    int niveles_ganados = 0;
    bool estado_establecido = false;
    while (i >= 0 && !estado_establecido)
    {
        if (juego.jugador.movimientos < 0)
        {
            estado = PERDIDO;
            estado_establecido = true;
            printf("TOCASTE UN FUEGO 0o\n");
        }
        else if (juego.jugador.movimientos == 0)
        {
            estado = PERDIDO;
            estado_establecido = true;
            printf("Te quedaste sin movimientos 0(\n");
        }
        else if (estado_nivel(juego.niveles[i].papeleos, juego.niveles[i].tope_papeleos) == GANADO)
        {
            niveles_ganados++;
        }
        i--;
    }
    if (niveles_ganados == MAX_NIVELES && !estado_establecido)
    {
        printf("GANASTE EL JUEGO 0)\n");
        estado = GANADO;
    }
    else if (!estado_establecido)
    {
        estado = JUGANDO;
    }
    return estado;
}