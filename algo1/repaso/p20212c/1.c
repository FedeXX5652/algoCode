#include <stdio.h>

#define MAX_BOTELLAS 100
#define MAX_COLOR 100

const int ERROR = -1;

typedef struct botellita {
    int contenido;
    char color_tapita[MAX_COLOR];
} botellita_t;

int botellas_hasta_litro_rec(botellita_t botellas[MAX_BOTELLAS], int litros_buscados, int tope_botellas, int posicion){
    if(litros_buscados > 0){
        if(posicion < tope_botellas){
            if(botellas[posicion].contenido >= litros_buscados){
                return posicion+1;
            }else{
                return botellas_hasta_litro_rec(botellas, litros_buscados - botellas[posicion].contenido, tope_botellas, posicion + 1);
            }
        }else{
            return ERROR;
        }
}

int botellas_hasta_litro(botellita_t botellas[MAX_BOTELLAS], int tope_botellas, int litros_buscados){
    return botellas_hasta_litro_rec(botellas, litros_buscados, tope_botellas, 0);
}

int main(){
    botellita_t botellas[MAX_BOTELLAS];
    int tope_botellas = 2;
    int litros_buscados = 5;
    int resultado;

    botellas[0].contenido = 10;
    botellas[0].color_tapita[MAX_COLOR] = "rojo";

    botellas[1].contenido = 20;
    botellas[1].color_tapita[MAX_COLOR] = "azul";


    resultado = botellas_hasta_litro(botellas, tope_botellas, litros_buscados);

    if(resultado != ERROR){
        printf("El numero de botellas que necesito para sumar %d litros es: %d\n", litros_buscados, resultado);
    }
    else{
        printf("No se puede obtener %d litros de agua\n", litros_buscados);
    }

    return 0;
}