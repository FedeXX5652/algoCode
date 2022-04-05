#include <stdio.h>

// las funciones tienen return, los procedimientos no (llevan void)

// este es un pasaje de valor por referencia (cambia las originales)
// el pasaje de valor por valor es por copia (no cambia las originales)

char* function(int* ref_n1, int* ref_n2) {      // le pasamos punteros
    printf("punteros a int: %i %i\n", *ref_n1, *ref_n2);    // accedemos a los valores de los punteros
    int n3 = (*ref_n1);
    (*ref_n1) = (*ref_n2);
    (*ref_n2) = n3;
    return "Ok";
}

int main()
{
    int nro;
    int nro2;
    char* function_response;

    printf("Ingrese un numero: ");
    scanf("%i", &nro);      // el & permite que el valor ingresado se guarde en la variable nro
    printf("Ingrese otro numero: ");
    scanf("%i", &nro2);
    
    function_response = function(&nro, &nro2);
    printf("-------------------------------------------\nLa funcion se ejecutó con: %s\n", function_response);
    printf("Nros finales intercambiados: %i, %i\n", nro, nro2);
    return 0;
}