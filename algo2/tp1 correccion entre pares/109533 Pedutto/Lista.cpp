#include "Lista.hpp"
#include <fstream>
#include <string>
using namespace std;

void Cargar_Lista(Lista* Nueva_Lista){
    Nueva_Lista -> Cantidad_Libros = 0;
    Libro* Nuevo_Libro;
    string Nombre;
    char Genero;
    int Puntaje;
    fstream Archivo_Libros(PATH_LIBROS, ios::in);
    if(!Archivo_Libros.is_open()){
        cout << "\nNo se encontró el archivo " << PATH_LIBROS << endl;
        Archivo_Libros.open(PATH_LIBROS, ios::out);
        Archivo_Libros.close();
        Archivo_Libros.open(PATH_LIBROS, ios::in);
    }
    while(Archivo_Libros >> Nombre){
        Archivo_Libros >> Genero;
        Archivo_Libros >> Puntaje;
        Nuevo_Libro = new Libro;
        Nuevo_Libro -> Nombre = Nombre;
        Nuevo_Libro -> Genero = Genero;
        Nuevo_Libro -> Puntaje = Puntaje;
        Agregar_Libro(Nueva_Lista, Nuevo_Libro);
    }
    Archivo_Libros.close();
}

void Agregar_Libro(Lista* Nueva_Lista, Libro* Nuevo_Libro){
    int Tope = Nueva_Lista -> Cantidad_Libros;
    Libro** Vector_Libros = new Libro*[Tope * 2];
    for(int i = 0; i < Nueva_Lista -> Cantidad_Libros; i ++){
        Vector_Libros[i] = Nueva_Lista -> Nuevo_Libro[i];
    }
    Vector_Libros[Tope] = Nuevo_Libro;
    if(Nueva_Lista -> Cantidad_Libros != 0){
        delete[] Nueva_Lista -> Nuevo_Libro;
    }
    Nueva_Lista -> Nuevo_Libro = Vector_Libros;
    Nueva_Lista -> Cantidad_Libros ++;
}

void Listar_Libros(Lista* Nueva_Lista){
    cout << "\nLibros en la lista:\n" << endl;
    if(Nueva_Lista -> Cantidad_Libros == 0){cout << "\nLa lista está vacía" << endl;}
    for(int i = 0; i < Nueva_Lista -> Cantidad_Libros; i ++){
        Mostrar_Libro(Nueva_Lista, i);
    }
}

void Mostrar_Libro(Lista* Nueva_Lista, int Posicion){
    cout << "--------------------" << endl
         << "Libro: " << Nueva_Lista -> Nuevo_Libro[Posicion] -> Nombre << endl
         << "Género: " << Mostrar_Genero(Nueva_Lista -> Nuevo_Libro[Posicion] -> Genero) << endl
         << "Puntaje: " << Nueva_Lista -> Nuevo_Libro[Posicion] -> Puntaje << endl
         << "--------------------" << endl;
}

string Mostrar_Genero(char Genero){
    string Genero_Valido;
    switch(Genero){
        case 'A':
            Genero_Valido = "Aventura";
            break;
        case 'C':
            Genero_Valido = "Ciencia Ficción";
            break;
        case 'D':
            Genero_Valido = "Didáctica";
            break;
        case 'P':
            Genero_Valido = "Policíaca";
            break;
        case 'R':
            Genero_Valido = "Romance";
            break;
        case 'T':
            Genero_Valido = "Terror";
            break;
    }
    return Genero_Valido;
}

int Buscar_Libro(Lista* Nueva_Lista, string Nombre){
    bool Libro_Encontrado = false;
    int i = 0, Posicion = ERROR;
    while((i < Nueva_Lista -> Cantidad_Libros) && (!Libro_Encontrado)){
        if(Nueva_Lista -> Nuevo_Libro[i] -> Nombre == Nombre){
            Libro_Encontrado = true;
            Posicion = i;
        }
        i ++;
    }
    return Posicion;
}

void Cerrar_Lista(Lista* Nueva_Lista){
    ofstream Archivo_Libros(PATH_LIBROS);
    for(int i = 0; i < Nueva_Lista -> Cantidad_Libros; i ++){
        Archivo_Libros << Nueva_Lista -> Nuevo_Libro[i] -> Nombre << ' ' << Nueva_Lista -> Nuevo_Libro[i] -> Genero << ' ' << Nueva_Lista -> Nuevo_Libro[i] -> Puntaje << endl;
        delete Nueva_Lista -> Nuevo_Libro[i];
        Nueva_Lista -> Cantidad_Libros--;
    }
    delete[] Nueva_Lista -> Nuevo_Libro;
    Nueva_Lista -> Nuevo_Libro = nullptr;
}