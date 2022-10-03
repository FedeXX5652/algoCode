#include "Menu.hpp"
#include "Lista.hpp"
#include <iostream>
using namespace std;

int main(){
    Lista* Nueva_Lista = new Lista;
    int Opcion = 0;
    Cargar_Lista(Nueva_Lista);
    Mostrar_Menu();
    Opcion = Pedir_Opcion();
    Validar_Opcion(Opcion);
    while(Opcion != SALIR){
        Procesar_Opcion(Nueva_Lista, Opcion);
        Mostrar_Menu();
        Opcion = Pedir_Opcion();
        Validar_Opcion(Opcion);
    }
    Cerrar_Lista(Nueva_Lista);
    delete Nueva_Lista;
    return 0;
}