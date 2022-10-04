#ifndef _LIBRO_
#define _LIBRO_
#include <string>
using namespace std;

enum Genero 
{
    AVENTURA, 
    CIENCIA_FICCION, 
    DIDACTICO,
    POLICIACA,
    ROMANCE,
    TERROR
};

const string generos[6]= {"Aventura","Ciencia Ficción","Didáctico","Policiaca","Romance","Terror"};

const string generos_inicial[6]= {"A","C","D","P","R","T"};

struct Libro
{
    string nombre;
    string genero;
    int puntaje;
};


//PRE:El genero deber ser: Aventura, Ciencia Ficción, Didactico, Policiaca, Romance o Terror.
//POST: Devuevle un puntero al libro creado. 
Libro * crear_libro(string nombre, string genero, int puntaje);


//PRE: El libro fue creado anteriormente
//POST:Libera la memoria asociada al libro.
void destruir_libro(Libro* libro); 


//PRE: El libro fue creado anteriormente
//POST:Devuelve el genero  
string obtener_nombre(Libro* libro);



//PRE:El libro fue creado anteriormente
//POST:Muestra por terminal el nombre, genero y puntaje. 
void imprimir_libro(Libro *libro);



//PRE: El puntaje debe estar entre 0 y 100 inclusive. El libro fue creado anteriormente
//POST: Cambia el puntaje del libro especficado
void _cambiar_puntaje(Libro*libro, int puntaje); 


//PRE: EL genero_caracter debe ser: A C D P R T
//POST: Deuvelve Aventura, Cienca ficcion, Didactica, Policiaca Romance o Terror 
// respectivamente.
string _caracter_a_genero(string genero_caracter);


#endif
