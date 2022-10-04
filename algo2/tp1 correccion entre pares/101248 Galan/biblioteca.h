#ifndef _BIBLIOTECA_
#define _BIBLIOTECA_
#include "libro.h"

using namespace std;

struct Biblioteca
{
    Libro** lista_de_libros;
    size_t cantidad_de_libros;
    size_t limite_de_libros;
};

//PRE:--
//POST: Crea una bibilioteca vacia inicializando los valores de cantidad de libros en 0 y el limite en 20
Biblioteca* crear_biblioteca();


//PRE:La biblioteca fue creada anteriormente
//POST:Libera la memoria asocida a la biblioteca
void destruir_biblioteca(Biblioteca* biblioteca);


//PRE: El libro  tiene sus paramtros validados y no debe estar ya incluido(la comparacion de hace por nombre)
//POST:Agrega el libro al final de la lista, llama a _expadir_listo si se necesita mas memoria. 
void agregar_libro(Biblioteca* biblioteca,Libro* libro);


//PRE: el campo "cantiadad de libros" y "limite de libros" debe ser igual
//POST: amplia el vector dianamico y cambia el limite de libros
void _expandir_lista(Biblioteca* biblioteca); 


//PRE:La biblioteca fue creada y tiene al menos un libro
//POST: devuelve true si el libro esta y false si no esta
bool _esta_libro(Biblioteca* biblioteca, string nombre);


//PRE:La biblioteca fue creada y tiene al menos un libro
//POST:Impirme todos los libros que se encuentren cargados
void imprimir_biblioteca(Biblioteca* biblioteca); 


//PRE:La biblioteca tiene que tener al menos un libro
//POST: muestra todos los libros que compartan el puntaje maximo  
void imprimir_libro_favorito(Biblioteca* biblioteca);


//PRE: La biblioteca tiene que tener al menos un libro
//POST:Si la biblioteca tiene 3 libros o menos, muestra todos, si tiene mas muestra los 3 peores. 
//En caso de empate se decide por orden alfabetico
void imprimir_peores_libros(Biblioteca* biblioteca);


//PRE:La biblioteca tiene que tener al menos un libro
//POST:Muestra por terminal el/los generos mas leidos y la cantidad de libros.
void mostar_genero_mas_leido(Biblioteca* biblioteca);


//PRE: Los datos a cargar deben estar en formato CSV nombre,genero,puntaje. el genero es solamente la inicial (A para Aventura)
//POST: crea una estructura libro para cada renglon y los agrega en la biblioteca.
void cargar_biblioteca(Biblioteca* biblioteca);


//PRE: La biblioteca tiene que tener al menos un libro
//POST: Edita o crea un archivo llamado "libros.csv" y escrbribe la informacion de cada libro en el siguiente orden
// nombre,genero,puntaje. Solo se escribe la inicial del genero 
void escribir_biblioteca(Biblioteca* biblioteca); //tiene que escribir la inicial nomas


//PRE:--
//POST: devuevle la ubicación del maximo de un vector
size_t _indice_del_valor_mas_alto(int vector[],size_t cantidad);


//PRE:La biblioteca tiene que tener al menos un libro
//POST: Muestra por terminal el o los generos favoritos con el promedio de puntajes de ese genero.
void mostrar_genero_favorito(Biblioteca* biblioteca);


//PRE: El nombre ingresado corresponde a un libro que fue agregado
//POST: Cambia el puntaje del libro
void editar_puntaje(Biblioteca* biblioteca, string nombre, int puntaje);


//PRE:La biblioteca tiene que tener al menos un libro
//POST: devuelve la poscion del libro ingresado.
size_t _buscar_libro(Biblioteca * biblioteca, string nombre);
#endif