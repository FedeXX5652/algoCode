#include <iostream>
#include "punto_r2.h"

using namespace std;

int main(){
    PuntoR2 A(4.9, 8.8);
    cout << "Antes de asignar: (" << A.obtener_x() << "," << A.obtener_y() << ")" << endl;      //utiliza los valores del constructor
    A.asignar_x(2.3);
    A.asignar_y(5.8);
    cout << "Despues de asignar: (" << A.obtener_x() << "," << A.obtener_y() << ")" << endl;    //utiliza el valor seteado en asignar_x y asignar_y
    return 0;
}