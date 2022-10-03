#ifndef MENU_H
#define MENU_H

#include "libros.h"


//Precondiciones:
//Postcondiciones: Mostrar las opciones del menu por pantalla.
void mostrar_menu();

//Precondiciones: Que se haya mostrado el menu correctamente
//Postcondiciones: Pedir una opcion del 1 al 8
int pedir_opcion();

//Precondiciones:Que se haya pedido la opcion
//Postcondiciones: validar que dicha opcion este entre 1 y 8
void validar_opcion(int &opcion_elegida);

//Precondiciones: que la opcion este entre 1 y 8
//Postcondiciones: Se realiza la opcion elegida
void realizar_opcion_elegida(int opcion, Biblioteca* biblioteca, Libro* libros);


#endif