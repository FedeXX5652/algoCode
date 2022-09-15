#include <iostream>
#include <cmath>
#include "punto_r2.h"

using namespace std;

// contructor sin parametros
PuntoR2::PuntoR2(){
    std::cout << "Punto creado (sin parametros) en " << this << std::endl;
    x = 0;
    y = 0;
}

// contructor con parametros
PuntoR2::PuntoR2(double x, double y){
    std::cout << "Punto creado (con parametros) en " << this << std::endl;
    this->x = x;    // crea un puntero al objeto
    this->y = y;
}

PuntoR2::~PuntoR2(){
    cout << "DESTRUYO EL OBJETO EN: " << this << endl;
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

void PuntoR2::mostrar(){
    cout << "(" << x << ", " << y << ")" << endl;
}