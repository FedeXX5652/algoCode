#include <stdio.h>

#define N 5

void mostrarLista(int *);
int main(int argc, char **argv)
{
    int arreglo[N] = {5, 2, 4, 1, 3};
    int i, clave, j;
    // Recorrer el arreglo
    for (i = 1; i < N; i++)
    {
        clave = *(arreglo + i);
        j = i - 1;
        // Comparar el valor selecionado con todos los valores anteriores
        while (j >= 0 && *(arreglo + j) > clave)
        {
            // Insertar el valor donde corresponda
            *(arreglo + j + 1) = *(arreglo + j);
            j = j - 1;
        }
        *(arreglo + j + 1) = clave;
        mostrarLista(arreglo);
    }
    mostrarLista(arreglo);
    return 0;
}
// Función para mostrar estado de la lista
void mostrarLista(int *lista)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("\t[%d]", *(lista + i));
    }
    printf("\n");
    ;
}