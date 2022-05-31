/*
para ordenar el vector de manera ascendente yo utilizaria el metodo por burbujeo

descrito de la siguiente manera:
- en la primera iteracion, voy a comparar el primer elemento con el segundo
- si el 1ro es mayor que el segundo, entonces compararé el 2ro con el 3do
- si el 1ro es menor que el segundo, entonces compararé el 1ro con el 3ro

en forma general, ire tomando como punto de comparacion el elemento mas pequeño encontrado
y comparando con el siguiente elemento, si el elemento actual es menor que el punto de comparacion

un ejemplo con nombres podría el siguiente:

quiero ordenar una lista de nombres: aaa, aab, abb, abc

- tomo el primer item de la lista como el punto de comparacion y comparo el primer caracter de 1er item con el primer caracter de 2do item
- si son iguales, comparo el segundo caracter de 1er item con el segundo caracter de 2do item (asi sucesivamente hasta que pueda determinar quien es mayor)
- una vez terminada la primera pasada de comparacion, habré obtenido el menor item de la lista, itercambio el 1er item con el menor item

repito este proceso hasta haber llegado al anteultimo item de la lista, donde se comparará el anteultimo item con el ultimo item
(ya que desde ese punto hacia atrás ya estan ordenados), si el anteultimo item es menor que el ultimo item, entonces intercambio los 2 ultimos items

resultado en la lista ordenada: aaa, aab, abb, abc
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NOMBRE = 20
#define MAX_ENEMIGOS 100

typedef struct enemigo{
    char nombre[MAX_NOMBRE];
    bool tiene_superpoderes;
    int veces_derrotado;
    int veces_ganadas;
} enemigo_t;


void agregar_victoria(enemigo_t enemigos[MAX_ENEMIGOS], int tope){
    bool encontrado = false;

    while(!encontrado && tope > 0){
        if(strcmp(enemigos[tope].nombre, "Mojojojo")){
            encontrado = true;
            enemigos[tope].veces_derrotado++;
        }
        else{
            tope--;
        }
    }
}