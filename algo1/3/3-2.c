#include <stdio.h>

int function(int nro, int nro2)
{
    printf("La suma de %d y %d es: %d\n", nro, nro2, (nro+nro2));
    return 0;
}

int main()
{

    int nro;
    int nro2;
    printf("Ingrese un numero: ");
    scanf("%i", &nro);
    printf("Ingrese otro numero: ");
    scanf("%i", &nro2);
    
    function(nro, nro2);
    return 0;

}