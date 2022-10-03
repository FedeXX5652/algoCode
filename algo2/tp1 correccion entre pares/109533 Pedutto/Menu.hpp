#ifndef MENU_HPP
#define MENU_HPP
#include "Lista.hpp"
#include <string>
using namespace std;
const int POSICION_INVALIDA = -1;
const int LIBROS_MENOR_PUNTAJE = 3;
const int TOTAL_GENEROS = 6;
enum Menu{
    LISTAR_LIBROS = 1,
    AGREGAR_LIBRO,
    EDITAR_PUNTAJE,
    MOSTRAR_LIBRO_FAVORITO,
    MOSTRAR_LIBROS_MENOR_PUNTAJE,
    MOSTRAR_GENERO_MAS_LEIDO,
    MOSTRAR_GENERO_FAVORITO,
    SALIR,
    CANTIDAD_DE_OPCIONES
};

//Precondiciones: -
//Postcondiciones: Muestra el menú.
void Mostrar_Menu();

//Precondiciones: -
//Postcondiciones: Solicita la opción a realizar.
int Pedir_Opcion();

//Precondiciones: Recibe una opción a realizar.
//Postcondiciones: Verifica que la opción sea un número entre 0 y el valor de CANTIDAD_DE_OPCIONES, y si no lo es, solicita otra opción.
void Validar_Opcion(int &Opcion);

//Precondiciones: Recibe una opción válida.
//Postcondiciones: Realiza la acción indicada.
void Procesar_Opcion(Lista* Nueva_Lista, int Opcion);

//Precondiciones: -
//Postcondiciones: Solicita los datos del libro.
Libro* Pedir_Libro();

//Precondiciones: -
//Postcondiciones: Solicita el nombre del libro.
string Pedir_Nombre();

//Precondiciones: -
//Postcondiciones: Solicita el género del libro.
char Pedir_Genero();

//Precondiciones: Recibe el género a validar.
//Postcondiciones: Devuelve true si el género es válido y false en caso contrario.
bool Validar_Genero(string Genero);

//Precondiciones: -
//Postcondiciones: Solicita el puntaje del libro.
int Pedir_Puntaje();

//Precondiciones: Recibe el puntaje a validar.
//Postcondiciones: Devuelve true si el puntaje es válido y false en caso contrario.
bool Validar_Puntaje(string Puntaje);

//Precondiciones: -
//Postcondiciones: Devuelve el mayor puntaje de la lista.
int Buscar_Mayor_Puntaje(Lista* Nueva_Lista);

//Precondiciones: Recibe el mayor puntaje de la lista.
//Postcondiciones: Devuelve el libro con mayor puntaje.
void Mostrar_Libro_Favorito(Lista* Nueva_Lista, int Puntaje);

//Precondiciones: -
//Postcondiciones: Devuelve un vector con los puntajes más bajos de la lista (La cantidad de elementos del vector es igual a LIBROS_MENOR_PUNTAJE).
int Buscar_Menor_Puntaje(Lista* Nueva_Lista);

//Precondiciones: Recibe el vector con los puntajes más bajos de la lista.
//Postcondiciones: Devuelve los libros con los puntajes más bajos de la lista.
void Mostrar_Libros_Menor_Puntaje(Lista* Nueva_Lista, int Vector[]);

//Precondiciones: Recibe el tercer menor puntaje de la lista.
//Postcondiciones: Devuelve un vector con los nombres de los libros con el tercer menor puntaje de la lista.
string Buscar_Nombres(Lista* Nueva_Lista, int Menor_Puntaje);

//Precondiciones: Recibe el vector con los nombres de los libros con el tercer menor puntaje de la lista.
//Postcondiciones: Ordena ascendentemente el vector recibido.
void Ordenar_Nombres(Lista* Nueva_Lista, string Vector[]);

//Precondiciones: Recibe el vector con los nombres ordenados ascendentemente de los libros con el tercer menor puntaje de la lista.
//Postcondiciones: Devuelve la posición del libro con el tercer menor puntaje de la lista.
int Posicion_Libro_Menor_Puntaje(Lista* Nueva_Lista, string Vector[]);

//Precondiciones: -
//Postcondiciones: Devuelve un vector con todas las apariciones de cada género (La cantidad de elementos del vector es igual a TOTAL_GENEROS).
int Contar_Generos(Lista* Nueva_Lista);

//Precondiciones: Recibe el vector con todas las apariciones de cada género.
//Postcondiciones: Devuelve el mayor valor del vector con todas las apariciones de cada género.
int Buscar_Mayor_Aparicion(int Vector[]);

//Precondiciones: Recibe el vector con todas las apariciones de cada género y el mayor valor de dicho vector.
//Postcondiciones: Devuelve el género que cumpla con la condición.
void Genero_Mas_Leido(int Vector[], int Mayor);

//Precondiciones: -
//Postcondiciones: Devuelve un vector con todos los puntajes de cada género (La cantidad de elementos del vector es igual a TOTAL_GENEROS).
int Sumar_Puntajes_Generos(Lista* Nueva_Lista);

//Precondiciones: Recibe los vectores con todas las apariciones y todos los puntajes de cada género.
//Postcondiciones: Devuelve un vector con todos los promedios de cada género.
float Promediar_Generos(Lista* Nueva_Lista, int Vector_Generos[], int Vector_Puntajes[]);

//Precondiciones: Recibe el vector con todos los promedios de cada género.
//Postcondiciones: Devuelve el mayor valor del vector con todos los promedios de cada género.
float Buscar_Mayor_Promedio(float Vector[]);

//Precondiciones: Recibe el vector con todos los promedios de cada género y el mayor valor de dicho vector.
//Postcondiciones: Devuelve el género que cumpla con la condición.
void Genero_Favorito(float Vector[], float Mayor);

#endif