
#include <stdio.h>

#define CINCUENTA 50

typedef struct casa
{
    char direccion[CINCUENTA];
    int anio_construccion;
} casa_t;

casa_t casa_mas_antigua(casa_t casas[MAX_CASAS], int t){
    int anio_mas_antigua = 2000;
    casa_t mas_antigua;
    for (i = 1; i < t; i++)
    {
        if (casas[i].anio_construccion < anio_mas_antigua)
        {
            anio_mas_antigua = casas[i].anio_construccion;
            mas_antigua = casas[i];
        }
        i++;
    }
    return mas_antigua;
}

/*
no se entiende el define de CINCUENTA, habría que poner algo mas descriptivo como MAX_DIRECCIONES
no esta declarada la variable i
no se entiende a que refiere la variable t, se le puede cambiar el nombre a tope
no tiene pre y post condiciones, no explica que es lo que requiere la funcion, t puede ser cualquier numero??
MAX_CASAS no esta definido
en el for se utiliza un i++, pero esto no es necesario al estar usando una estructura for
el ciclo for arranca en 1, deberia arrancar en 0

*/