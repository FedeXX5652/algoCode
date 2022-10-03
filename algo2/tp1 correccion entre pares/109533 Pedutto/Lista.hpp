#ifndef LISTA_HPP
#define LISTA_HPP
#include <iostream>
#include <string>
using namespace std;
const string PATH_LIBROS = "Libros.csv";
const int PUNTAJE_MAXIMO = 100;
const int PUNTAJE_MINIMO = 0;
const int ERROR = -1;
struct Libro{
    string Nombre;
    char Genero;
    int Puntaje;
};
struct Lista{
    Libro** Nuevo_Libro;
    int Cantidad_Libros;
};

//Precondiciones: -
//Postcondiciones: Ejecuta el programa.
int main();

//Precondiciones: -
//Postcondiciones: Carga la lista con los datos del archivo Libros.
void Cargar_Lista(Lista* Nueva_Lista);

//Precondiciones: El libro debe estar cargado correctamente.
//Postcondiciones: Añade el libro a la lista.
void Agregar_Libro(Lista* Nueva_Lista, Libro* Nuevo_Libro);

//Precondiciones: -
//Postcondiciones: Imprime los libros que contiene la lista o un mensaje si esta vacía.
void Listar_Libros(Lista* Nueva_Lista);

//Precondiciones: La posición debe existir dentro de la lista.
//Postcondiciones: Muestra los datos del libro de la posición indicada.
void Mostrar_Libro(Lista* Nueva_Lista, int Posicion);

//Precondiciones: Recibe la inicial del género del libro.
//Postcondiciones: Devuelve el género completo del libro.
string Mostrar_Genero(char Genero);

//Precondiciones: Recibe el nombre del libro.
//Postcondiciones: Devuelve la posición del libro si es encontrado o -1 en caso contrario.
int Buscar_Libro(Lista* Nueva_Lista, string Nombre);

//Precondiciones: -
//Postcondiciones: Guarda los libros en el archivo Libros y elimina la lista.
void Cerrar_Lista(Lista* Nueva_Lista);

#endif