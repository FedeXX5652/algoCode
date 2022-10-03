#ifndef LIBROS_H
#define LIBROS_H

#include <iostream>
#include <string>
using namespace std;

struct Libro{
    string nombre_libro;
    char genero;
    int puntaje;

};

struct Biblioteca{
    Libro** libros;
    int cantidad_de_libros;
};



//Precondiciones: El vector llega a su maxima capacidad.
//Postcondiciones: Duplica el tamanio del vector
void agrandar_vector_de_libros(Biblioteca* biblioteca, Libro** vector_de_libros);

//Precondiciones: Debe existir el archivo .csv
//Postcondiciones: Lee el archivo y lo guarda.
void leer_archivo(Biblioteca* biblioteca);

//Precondiciones: Que sea un libro valido con genero
//Postcondiciones: Transforma la inicial del genero en la palabra completa.
void genero_completo(Biblioteca* biblioteca, int i);

//Precondiciones: Tener los libros cargados
//Postcondiciones: Mostrar los libros por pantalla
void listar_libros_leidos(Biblioteca* biblioteca);

//Precondiciones: Que exista Biblioteca
//Postcondiciones: -
void agregar_libro(Biblioteca* biblioteca, Libro* libros);

//Precondiciones: Querer agregar un libro
//Postcondiciones: -
char pedir_y_validar_genero();

//Precondiciones: Querer agregar un libro
//Postcondiciones: -
int validar_existancia_libro(string libro_a_editar, Libro* libros);

//Precondiciones: Querer agregar un libro
//Postcondiciones: -
int pedir_y_validar_puntaje();

//Precondiciones: Que el libro ya este cargado
//Postcondiciones: editar el puntaje de dicho libro
void editar_puntaje(Biblioteca* biblioteca, Libro* libros);

//Precondiciones: Ya deben estar todos los libros correctamente guardados
//Postcondiciones: Mostrar a el/los libro/s con mayor puntaje por pantalla
void mostrar_libro_favorito(Biblioteca* biblioteca, Libro* libros);

//Precondiciones: Ya deben estar todos los libros correctamente guardados
//Postcondiciones: Mostrar los 3 peores libros segun su puntaje.
void mostrar_tres_menor_libros(Biblioteca* biblioteca, Libro* libro);

//Precondiciones: Ya deben estar todos los libros correctamente guardados
//Postcondiciones: Saber cual fue el genero mas leido, y cuanto se leyo.
void ordenar_genero_mas_leido(int contador [6], int* maximo, int* posicion);

//Precondiciones: Ya deben estar todos los libros correctamente guardados
//Postcondiciones: Mostrar a el genero cque mas se repite por pantalla
void mostrar_genero_mas_leido(Biblioteca* biblioteca, Libro* libros);

//Precondiciones: Ya deben estar todos los libros correctamente guardados
//Postcondiciones: Mostrar a el genero con mayor puntaje por pantalla
void mostrar_genero_favorito(Biblioteca* biblioteca, Libro* libros);

//Precondiciones: - 
//Postcondiciones: Se debe actualizar el archivo correctamente y cerrar.
void guardar_y_salir(Biblioteca* biblioteca, Libro* libros);





#endif