#include <iostream>
#include "punto_r2.h"
#include "circulo.h"

using namespace std;

int main(){
    PuntoR2* pA;
    PuntoR2 B(2.4, 4.1);
    pA = new PuntoR2;
    
    cout << "A = ";      //utiliza los valores del constructor
    pA->mostrar();
    delete pA;  // deletea el puntero y llama al destructor
    cout << "B = ";      //utiliza los valores ingresados
    B.mostrar();

    Circulo c(2.0);

    c.mostrar();

    return 0;
}