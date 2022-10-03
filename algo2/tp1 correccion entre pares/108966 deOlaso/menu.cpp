#include "menu.hpp"
#include "libros.hpp"

#include <fstream>
#include <iostream>

void mostrar_ayuda()
{
    cout << "|   Comandos disponibles:" << endl <<
            "|   0. Mostrar ayuda." << endl <<
            "|   1. Listar libros leídos." << endl <<
            "|   2. Agregar libro." << endl <<
            "|   3. Editar puntaje de un libro por título." << endl <<
            "|   4. Mostrar libro favorito." << endl <<
            "|   5. Mostrar los 3 peores libros." << endl <<
            "|   6. Mostrar género/s más leído/s." << endl <<
            "|   7. Mostrar género/s favorito/s." << endl <<
            "|   8. Guardar y salir. " << endl;
}

int recibir_comando()
{
    int comando;

    cout << "Ingresa un número de comando:" << endl;
    cin >> comando;

    return comando;
}

void validar_comando(int comando)
{
    bool es_valido = comando >= 0 && comando < CANTIDAD_COMANDOS;

    while(!es_valido)
    {
        cout << "|   El comando ingresado no es válido." << endl;
        comando = recibir_comando();
    }
}

void procesar_comando(int comando, lista_libros_t *mis_libros)
{
    switch(comando)
    {
        case MOSTRAR_AYUDA:
            mostrar_ayuda(); break;

        case MOSTRAR_LIBROS: 
            mostrar_libros(mis_libros); break;

        case AGREGAR_LIBRO:
            agregar_libro(mis_libros); break;

        case EDITAR_LIBRO:
            editar_libro(mis_libros); break;

        case MEJOR_LIBRO:
            mostrar_mejor_libro(mis_libros); break;

        case PEORES_LIBROS:
            mostrar_peores_libros(mis_libros); break;

        case GENERO_MAS_LEIDO:
            mostrar_genero_mas_leido(mis_libros); break;
        
        case GENERO_FAVORITO:
            mostrar_genero_favorito(mis_libros); break;

        default:;
    }
}

void leer_archivo(lista_libros_t *mis_libros)
{
    cout << "|   Bienvenido a tu biblioteca digital! Ingresa '0' para ver los comandos disponibles." << endl;

    mis_libros -> n = 0;

    ifstream archivo_entrada(PATH_ENTRADA);
    if(!archivo_entrada.is_open())
    {
        cout << "|   El archivo '" << PATH_ENTRADA << "' no existe en la carpeta de tu biblioteca." << endl
             << "|   Este archivo se creará al salir." << endl;
        archivo_entrada.open(PATH_ENTRADA, ios::out);
        archivo_entrada.close();
        archivo_entrada.open(PATH_ENTRADA, ios::in);
        return;
    }

    string nuevo_nombre, nuevo_genero, nuevo_puntaje;
    libro_t* nuevo_libro;

    while(getline(archivo_entrada, nuevo_nombre, ','))
    {
          getline(archivo_entrada, nuevo_genero, ',');
          getline(archivo_entrada, nuevo_puntaje);

        nuevo_libro = libro_nuevo(nuevo_nombre, nuevo_genero.c_str()[0], stoi(nuevo_puntaje));

        lista_libros_agregar_libro(mis_libros, nuevo_libro);
    }

    archivo_entrada.close();
}

void escribir_archivo(lista_libros_t *mis_libros)
{
    ofstream archivo_salida(PATH_ENTRADA);

    if(lista_libros_esta_vacia(mis_libros))
    {
        archivo_salida.close();
        return;
    }

    for(int i = 0; i < mis_libros -> n; i++)
    {
        archivo_salida << mis_libros -> ls[i] -> nombre << ","
                       << mis_libros -> ls[i] -> genero << ","
                       << mis_libros -> ls[i] -> puntaje << endl;
    }

    archivo_salida.close();
    cout << "|   Biblioteca guardada exitosamente." << endl;
}
