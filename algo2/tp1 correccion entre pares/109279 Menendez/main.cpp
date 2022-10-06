#include <iostream>
#include "archivo_controllers.h"

using namespace std;

const int MAXIMO_LIBROS_INICIAL = 20;
const int ERROR = -1;
const int UNA_ACCION = 1;
const int GUARDAR_Y_SALIR = 8;

int main(){
    int maximo_libros = MAXIMO_LIBROS_INICIAL;
    Libro* libros = new Libro[maximo_libros];
    int tope_libros = 0;

    int resultado = leer_archivo(libros, tope_libros);
    if (resultado == ERROR){
        cout << "Ha habido un error al abrir el archivo. Compruebe que exista y no este corrompido y vuelva a intentarlo.";
        return ERROR;
    }

    int cantidad_acciones = UNA_ACCION;

    int opcion_elegida = abrir_menu(cantidad_acciones);
    activar_opcion_elegida(opcion_elegida, libros, tope_libros, maximo_libros);
    while(opcion_elegida != GUARDAR_Y_SALIR){
        opcion_elegida = abrir_menu(cantidad_acciones);
        activar_opcion_elegida(opcion_elegida, libros, tope_libros, maximo_libros);
    }
    imprimir_mensaje_despedida();

    delete [] libros;

    return 0;
}
