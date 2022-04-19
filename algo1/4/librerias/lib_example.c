#include <stdio.h>
#include "calculator.h"

// LE GUSTA QUE LE DIGAN BIBLIOTECA Y NO LIBRERIA
/*
    Toda funcion que no esté en el .h no se puede usar fuera de la biblioteca (es una funcion privada de calculator.c)
    Ej:
        la funcion pot() no se puede usar en otro archivo que no sea calculator.c (lib_example.c no puede usarla)
*/

int main(){
    int a, b;
    char op;
    scanf("%d %c %d", &a, &op, &b);
    switch(op){
        case '+':
            printf("%d\n", add(a, b));
            break;
        case '-':
            printf("%d\n", sub(a, b));
            break;
        case '*':
            printf("%d\n", mul(a, b));
            break;
        case '/':
            printf("%d\n", div(a, b));
            break;
        default:
            printf("Invalid operator\n");
            break;
    }
    return 0;
}

// gcc lib_example.c calculator.c -o bibliotecas -Wall -Werror -Wconversion -std=c99