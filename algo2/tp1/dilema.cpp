#include <iostream>
#include <string>

#include "functions_link.h"

using namespace std;

typedef int* Pint;
typedef char* Pchar;

// https://campus.fi.uba.ar/pluginfile.php/527918/mod_resource/content/1/El%20eterno%20dilema%20del%20lector.pdf
// entregar como: 109435_Galante_TP1.zip


int main(){
    bool exit = false;
    int input;
    cout<<"Ingrese la accion a realizar:\n1. Listar libros leídos.\n2. Agregar libro.\n3. Editar puntaje de un libro por título.\n4. Mostrar libro favorito.\n5. Mostrar los 3 libros con menor puntaje.\n6. Mostrar género más leído.\n7. Mostrar género favorito.\n8. Guardar y salir."<<endl;
    cin>>input;
    while (is_valid_input(&input) == false){
        cout<<"Ingrese una opción valida: ";
        cin>>input;
    }
    cout<<"ingresaste: "<<input<<endl;
    return 0; 
}