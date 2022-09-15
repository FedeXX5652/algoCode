#include <iostream>
#include "punto_r2.h"

using namespace std;

int main(){
    PuntoR2 A;
    cout << "Antes de asignar: (" << A.obtener_x() << "," << A.obtener_y() << ")" << endl;      //utiliza el defaul de la clase
    A.asignar_x(2.3);
    A.asignar_y(5.8);
    cout << "Despues de asignar: (" << A.obtener_x() << "," << A.obtener_y() << ")" << endl;    //utiliza el valor seteado en asignar_x y asignar_y
    return 0;
}