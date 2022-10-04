#include <iostream>
#include "libro.h"
#include "biblioteca.h"
#include "menu.h"
using namespace std;

int main()
{ 
    
    Biblioteca* biblioteca = crear_biblioteca();
    cargar_biblioteca(biblioteca);

    
        int opcion = 0;
        
        while (opcion != GUARDAR_Y_SALIR)
        {
            mostrar_menu();
            opcion = ingreso_de_opcion();
            procesar_opcion(biblioteca , opcion);
            
        }
        
        destruir_biblioteca(biblioteca);
    

    return 0;
}