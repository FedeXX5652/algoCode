#include <iostream>
#include <string>

#include "functions_link.h"

using namespace std;

typedef int* Pint;
typedef char* Pchar;

// https://campus.fi.uba.ar/pluginfile.php/527918/mod_resource/content/1/El%20eterno%20dilema%20del%20lector.pdf
// entregar como: 109435_Galante_TP1.zip
// compilar con g++ *.cpp -Wall -Werror -Wconversion


int main(){
    bool is_exit = false;
    while(!is_exit){
        is_exit = get_input();
    }
    return 0; 
}