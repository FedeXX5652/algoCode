#include <iostream>
#include <string>
#include <fstream>
#include "menu.h"
#include "libros.h"


using namespace std;


int main (){
    
    Biblioteca* biblioteca = new Biblioteca;
    Libro* libros;
    leer_archivo(biblioteca);
      
    mostrar_menu();
    int opcion = pedir_opcion();
    validar_opcion (opcion);
    realizar_opcion_elegida(opcion, biblioteca, libros);
    
    delete biblioteca;

    return 0;
}

