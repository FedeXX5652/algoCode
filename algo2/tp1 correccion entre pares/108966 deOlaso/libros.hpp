#ifndef LIBROS_HPP
#define LIBROS_HPP

#include <string>

using namespace std;

const int CANTIDAD_GENEROS = 6;

const int ERROR = -1;
const string ERROR_STRING = "-";

typedef struct libro {
    string nombre;
    char genero;
    unsigned int puntaje;
} libro_t;

typedef struct lista_libros {
    libro_t **ls;
    int n;
} lista_libros_t;

// Libros

// Crea un nuevo libro en base a los parámetros.
// PRE: 
// POS: se crea un libro en memoria y se devuelve un puntero al libro creado.
libro_t *libro_nuevo(string nombre, char genero, unsigned int puntaje);

// Imprime el libro de la lista en la posición 'indice'.
// PRE: 'indice' debe ser cero o estar entre cero y la cantidad de libros en la lista.
// POS:
void lista_libros_mostrar_libro(lista_libros_t *mis_libros, int indice);

// Consigue información de un libro del usuario.
// PRE: 
// POS: si la información es válida, crea el libro, si no, devuelve NULL.
libro_t *recibir_nuevo_libro(lista_libros_t *mis_libros);

// Agrega un libro a una lista de libros.
// PRE: 
// POS: la lista de libros queda redimensionada y su último elemento es 'nuevo_libro'.
void lista_libros_agregar_libro(lista_libros_t *mis_libros, libro_t *nuevo_libro);

// Verifica si la lista de libros está vacía.
// PRE: la cantidad de libros de la lista debe haber sido inicializada.
// POS: 
bool lista_libros_esta_vacia(lista_libros_t *mis_libros);

// Busca un libro dentro de una lista de libros.
// PRE: 
// POS: si lo encuentra, devuelve la posición del libro en la lista de libros. Si no, devuelve un '-1'.
int buscar_libro_en_lista_libros(string nombre, lista_libros_t *mis_libros);

// Libera la memoria asociada con una lista de libros.
// PRE:
// POS: 'mis_libros' es borrada y su memoria y la de todos sus libros queda liberada.
void lista_libros_destruir(lista_libros_t *mis_libros);

// Transformaciones del genero (switches)

// Cambia el género de una letra a el nombre completo.
// PRE: 
// POS: devuelve el string asociado, o '-', en caso de error.
string genero_a_representacion(char genero);

// Cambia el número de una letra a el género asociado.
// PRE: 
// POS: devuelve el género asociado, o '-1', en caso de error.
char numero_a_genero(int numero);

// Cambia el género de una letra a el número asociado.
// PRE: 
// POS: devuelve el número asociado, o '-1', en caso de error.
int genero_a_numero(char genero);

// Comandos principales

// Imprime los libros de la biblioteca.
// PRE: 
// POS: 
void mostrar_libros(lista_libros_t *mis_libros);

// Agrega un libro a la biblioteca.
// PRE: 
// POS: si el libro ingresado no estaba antes, se inserta al final de la lista.
void agregar_libro(lista_libros_t *mis_libros);

// Edita el puntaje de un libro por título.
// PRE: 
// POS: si el libro y el puntaje ingresados son válidos, se realiza la modificación.
void editar_libro(lista_libros_t *mis_libros);

// Imprime el libro con el mejor puntaje.
// PRE: 
// POS:
void mostrar_mejor_libro(lista_libros_t *mis_libros);

// Imprime los 3 libros con los peores puntajes.
// PRE: 
// POS:
void mostrar_peores_libros(lista_libros_t *mis_libros);

// Imprime el género (o los géneros) con la mayor cantidad de libros.
// PRE: 
// POS:
void mostrar_genero_mas_leido(lista_libros_t *mis_libros);

// Imprime el género (o los géneros) con el mejor promedio de puntaje.
// PRE: 
// POS:
void mostrar_genero_favorito(lista_libros_t *mis_libros);

#endif
