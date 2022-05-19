#include <stdio.h>

const int MAX_NOMBRE = 20;
const int MAX_COLOR = 20;
const int MAX_COLORES = 10;


typedef struct gato {
    int edad;
    char colores[MAX_COLORES][MAX_COLOR];
    char nombre[MAX_NOMBRE];
    bool esta_eliminado;        // esto se usa en eliminacion logica
} gato_t;


int main(){

    return 0;
}