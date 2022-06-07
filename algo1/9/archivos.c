#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* archivo = fopen("viejo_sabroso.txt", "w");
    
    fprintf(archivo, "eeehheeeeyy, que pasa amigos? todo bien? todo correcto? Y YO QUE ME ALEGRO\n");   // escribo en el archivo
    
    fclose(archivo);
    return 0;
}