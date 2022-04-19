// flags de compilacion:
// -Wall -Werror -Wconversion -std=c99 -lm
/*
-Wall: toma en cuenta todo el error
-Werror: toma el warning como error
-Wconversion: toma en cuenta los conversiones de tipo
-std=c99: toma en cuenta el uso de las nuevas funciones de C99
-lm: incluye la libreria matematica
*/

//------------------------------------------------------------------------------

typedef struct heladera {       //sin el typedef no se crea como un nuevo tipo de dato
    int kg_carne;
    int litros_lacteos;
    int litros_birra;
    int canr_huevo;
    char eficiencia;
} heladera_t;               //se le asigna un alias (el _t es una convencion de para definir el struct)


int main(){
    heladera_t heladera_namor;
    heladera_t heladera_casa;

    heladera_namor.kg_carne = 10;   //siempre va con punto

    return 0;
}