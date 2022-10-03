#include <iostream>
#include <string>
#include <fstream>

#include "menu.h"
#include "libros.h"

using namespace std;

void mostrar_menu(){
    cout << endl << "MENU" << endl
    << '\t' << "1. Listar libros leídos." << endl
    << '\t' << "2. Agregar libro." << endl
    << '\t' << "3. Editar puntaje de un libro por título." << endl
    << '\t' << "4. Mostrar libro favorito." << endl
    << '\t' << "5. Mostrar los 3 libros con menor puntaje." << endl
    << '\t' << "6. Mostrar género más leído." << endl
    << '\t' << "7. Mostrar género favorito." << endl
    << '\t' << "8. Guardar y salir." << endl;

}

int pedir_opcion(){
    int opcion_elegida;
    cout << endl << "Ingrese el número de su acción elegida : ";
    cin >> opcion_elegida;

    return opcion_elegida;
}

void validar_opcion (int &opcion_elegida){
    bool opcion_valida = opcion_elegida > 0 && opcion_elegida <= 8;
    //agregar const
    while (!opcion_valida){
        cout << "Esa no es una opcion valida. Por favor ingrese la opcion deseada: " << endl;
        cin >> opcion_elegida;
        opcion_valida = opcion_elegida > 0 && opcion_elegida <= 8;
    }

}

void realizar_opcion_elegida(int opcion, Biblioteca* biblioteca, Libro* libros){
    switch (opcion){
        case 1:
            listar_libros_leidos(biblioteca);
            break;
        case 2:
            agregar_libro(biblioteca, libros);
            break;
        case 3:
            editar_puntaje(biblioteca, libros);
            break;
        case 4:
            mostrar_libro_favorito( biblioteca,  libros);
            break;
        case 5:
            mostrar_tres_menor_libros(biblioteca, libros);
            break;
        case 6:
            mostrar_genero_mas_leido( biblioteca,  libros);
            break;
        case 7:
            mostrar_genero_favorito (biblioteca, libros);
            break;
        case 8:
            guardar_y_salir(biblioteca, libros);
            break;

    }
    
}