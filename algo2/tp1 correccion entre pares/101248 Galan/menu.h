#ifndef MENU
#define MENU
#include "biblioteca.h"
using namespace std;

enum Opcion 
{
    LISTA_DE_LIBROS=1, 
    AGREGAR_LIBRO, 
    EDITAR_PUNTAJE,
    FAVORITO,
    PEORES,
    GENERO_MAS_LEIDO,
    GENERO_FAVORITO,
    GUARDAR_Y_SALIR
};


//PRE:--
//POST: Muestra por terminal un menu con las opcciones para usar el programa 
void mostrar_menu();

//PRE:El ingresado por terminal debe estar entre 1 y 8
//POST: Devuelve un valor que corresponde a una de las opciones listadas por la función "mostrar_menu"
int ingreso_de_opcion();

//PRE: el valor de opcion debe estar entre 1 y 8
//POST: ejecuta distitnas funciones en base a la opción ingresada.
// Si el valor recivido está fuera del rango 1-8 se vuelve a preguntar por una opcion. 
void procesar_opcion(Biblioteca* biblioteca ,int opcion);

//PRE:verifica que el string ingresado es uno entre: Aventura, Ciencia_ficion, Terror, Didactico, Romance,Policíaca
//POST: Devulve uno de los generos validos.
string _validar_genero(string genero);

//PRE: Verifica que el puntaje ingresado es un valor entre 0 y 100
//POST: devulve un valor valido de puntaje.
int _validar_puntaje(int puntaje);



#endif