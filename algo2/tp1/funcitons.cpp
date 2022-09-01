#include <iostream>
#include <string>
#include "csv_manage_link.h"

using namespace std;

#define ACEPTED_INPUTS_MAX 8

const char ACEPTED_INPUTS[ACEPTED_INPUTS_MAX] = {'1','2','3','4','5','6','7','8'};


bool is_valid_input(char* input){
    for(int i=0; i<ACEPTED_INPUTS_MAX; i++){
        if(ACEPTED_INPUTS[i] == *input){
            return true;
        }
    }
    return false;
}

void list_read_books(){
    read_csv();
}

bool get_input(){
    bool is_exit = false;
    char input;

    cout<<"\nIngrese la accion a realizar:\n1. Listar libros leidos.\n2. Agregar libro.\n3. Editar puntaje de un libro por titulo.\n4. Mostrar libro favorito.\n5. Mostrar los 3 libros con menor puntaje.\n6. Mostrar genero mas leido.\n7. Mostrar genero favorito.\n8. Guardar y salir."<<endl;
    cin>>input;

    while (is_valid_input(&input) == false){
        cout<<"Ingrese una opcion valida: ";
        cin>>input;
    }

    switch(input)
    {
    case '1':   // list read books
        list_read_books();
        break;
    case '2':   // add book
        break;
    case '3':   // edit score
        break;
    case '4':   // show favorite
        break;
    case '5':   // show 3 worst
        break;
    case '6':   // show most read genre
        break;
    case '7':   // show favorit genre
        break;
    case '8':   // save and exit
        is_exit = true;
        break;
    
    default:
        break;
    }

    return is_exit;
}