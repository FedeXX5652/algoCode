#include <iostream>
#include "punto_r2.h"

using namespace std;

// contructor
PuntoR2::PuntoR2(){
    x = 0;
    y = 0;
}


void PuntoR2::asignar_x(double cx){
    x = cx;
}


void PuntoR2::asignar_y(double cy){
    y = cy;
}


double PuntoR2::obtener_x(){
    return x;
}


double PuntoR2::obtener_y(){
    return y;
}