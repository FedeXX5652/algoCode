#ifndef TP1_ARCHIVO_CONTROLLERS_H
#define TP1_ARCHIVO_CONTROLLERS_H

using namespace std;

struct Libro{
    string titulo;
    char genero;
    int puntaje;
};

//Pre Debe recibir un vector de libros y su tope. Es NECESARIO que haya un archivo EXISTENTE "libros.csv" para leer en el mismo directorio que el ejecutable
//Post Lee el archivo y devuelve exito en caso de exito y error en caso de error en la apertura
int leer_archivo(Libro* libros, int &tope_libros);

//Pre Debe recibir la cantidad de acciones ejecutadas por el usuario
//Post Imprime por consola el menu de acciones para el usuario
int abrir_menu(int &cantidad_acciones);

//Pre
//Post Imprime el mensaje de despedida al usuario
void imprimir_mensaje_despedida();

//Pre Debe recibir una opcion elegida, el vector de libros, su tope inicializado y el maximo del vector
//Post Activa las debidas funciones para ejecutar al accion del usuario
void activar_opcion_elegida(int opcion_elegida, Libro* &libros, int &tope_libros, int &maximo_libros);

#endif
