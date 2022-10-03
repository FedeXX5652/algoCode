#ifndef MENU_HPP
#define MENU_HPP

#include "libros.hpp"

const string PATH_ENTRADA = "libros.csv";
const int CANTIDAD_COMANDOS = 9;

enum ComandosDisponibles {
    MOSTRAR_AYUDA,
    MOSTRAR_LIBROS,
    AGREGAR_LIBRO,
    EDITAR_LIBRO,
    MEJOR_LIBRO,
    PEORES_LIBROS,
    GENERO_MAS_LEIDO,
    GENERO_FAVORITO,
    SALIR
};

// Muestra la ayuda al usuario.
// PRE:
// POS:
void mostrar_ayuda();

// Recibe un número de comando de parte del usuario.
// PRE:
// POS: devuelve el número de comando.
int recibir_comando();

// Valida el comando que se le pasa como parámetro. Si es inválido, lo vuelve a pedir.
// PRE:
// POS: 'comando' es cero o está entre cero y la cantidad de comandos.
void validar_comando(int comando);

// Ejecuta el comando correspondiente que se le pasa como parámetro.
// PRE: 'comando' es cero o está entre cero y la cantidad de comandos.
// POS:
void procesar_comando(int comando, lista_libros_t *mis_libros);

// Lee los libros del archivo de la biblioteca.
// PRE: 'mis_libros' debe ser una lista nueva.
// POS: 'mis_libros' tiene todos los elementos de la biblioteca.
void leer_archivo(lista_libros_t *mis_libros);

// Guarda la información (modificada o no) en el archivo de la biblioteca.
// PRE:
// POS: el archivo de la biblioteca guarda la información de 'mis_libros'. Se libera 'mis_libros'.
void escribir_archivo(lista_libros_t *mis_libros);

#endif
