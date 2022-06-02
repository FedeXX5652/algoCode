#include <stdio.h>
#include "papeleo.h"

void rotar_nivel(juego_t juego, char direccion){
    printf("rotando nivel %c\n", direccion);
    printf("tope_paredes: %d\n", juego.tope_paredes);
}