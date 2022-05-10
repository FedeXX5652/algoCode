#include <stdio.h>

#define MAX_VECTOR 6


void imprimir_vector(int *a, int tope_vector)
{
    int i;
    for (i = 0; i < tope_vector; i++)
        printf("\t[%d]", *(a + i));
    printf("\n");
}


void selection_sort(int *vector, int tope_vector)
{
    int actual, mas_pequeno, j, temp;

    for (actual = 0; actual < tope_vector - 1; actual++)
    {
        imprimir_vector(vector, tope_vector);
        mas_pequeno = actual;
        for (j = actual ; j < tope_vector; j++)
            if (vector[j] < vector[mas_pequeno])    // Si cambio < a >, cambia el orden final
                mas_pequeno = j;
        temp = vector[actual];
        vector[actual] = vector[mas_pequeno];
        vector[mas_pequeno] = temp;
    }
}


int main()
{
    printf("Orden por selección:\n");
    int vector[MAX_VECTOR] = {5, 3, 1, 4, 2, 6};
    int tope_vector = MAX_VECTOR;
    selection_sort(vector, tope_vector);
}