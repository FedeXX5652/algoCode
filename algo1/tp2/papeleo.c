#include <stdio.h>

int imprimir_terreno(char terreno[][10]){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            printf("%c", terreno[i][j]);
        }
        printf("\n");
    }
    return 0;
}