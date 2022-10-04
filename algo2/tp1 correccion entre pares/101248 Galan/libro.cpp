#include "libro.h"
#include <fstream>
#include <iostream>

#define RUTA_DEL_ARCHIVO "libros.csv"

using namespace std;

string _caracter_a_genero(string genero_caracter)
{
    
    string genero;
    if (genero_caracter==generos_inicial[AVENTURA])
    {
        return generos[AVENTURA];
    }
    if (genero_caracter==generos_inicial[CIENCIA_FICCION])
    {
        return generos[CIENCIA_FICCION];
    }
    if (genero_caracter==generos_inicial[DIDACTICO])
    {
        return generos[DIDACTICO];
    }
    if (genero_caracter==generos_inicial[POLICIACA])
    {
        return generos[POLICIACA];
    }
    if (genero_caracter==generos_inicial[ROMANCE])
    {
        return generos[ROMANCE];
    }
    if (genero_caracter==generos_inicial[TERROR])
    {
        return generos[TERROR];
    }
    return "0";
}


Libro* crear_libro(string nombre, string genero, int puntaje) 
{

    Libro* libro = new Libro;
    libro->nombre = nombre;
    libro->genero = genero[0]; 
    libro->puntaje = puntaje; 

    return libro;
};

void destruir_libro(Libro * libro)
{
    delete libro;
    libro=nullptr;
};

string obtener_nombre(Libro* libro)
{
    return libro->nombre;
};

int obtener_puntaje(Libro* libro)
{
    return libro->puntaje;
};

string obtener_genero(Libro* libro)
{
    string genero = libro->genero;

    return _caracter_a_genero(genero);
};


void imprimir_libro(Libro *libro)
{
    std::cout<<"-------------"<<endl;
    std::cout<<"Titulo:  "  << libro->nombre<<endl;
    std::cout<<"Genero:  "  <<  _caracter_a_genero(libro->genero)<<endl;
    std::cout<<"Puntaje: "  << libro->puntaje<<endl;
    std::cout<<"-------------"<<endl;
};

void _cambiar_puntaje(Libro*libro, int puntaje) 
{
    libro->puntaje = puntaje;
}
