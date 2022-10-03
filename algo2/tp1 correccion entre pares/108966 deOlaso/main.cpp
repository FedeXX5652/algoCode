#include "menu.hpp"

#include <iostream>

using namespace std;

int main(void)
{
    lista_libros_t *mis_libros = new lista_libros_t;

    leer_archivo(mis_libros);

    int comando;

    comando = recibir_comando();

    while(comando != SALIR)
    {
        validar_comando(comando);
        procesar_comando(comando, mis_libros);
        comando = recibir_comando();
    }

    escribir_archivo(mis_libros);
    lista_libros_destruir(mis_libros);
    
    return 0;
}
