#include <iostream>
#include "Vehiculo.h"

using namespace std;

// contructor con parametros
Vehiculo::Vehiculo(unsigned int ruedas){
    this->ruedas = ruedas;
    this->telepase = false;
}

Vehiculo::~Vehiculo(){
    cout << "DESTRUYO EL VEHICULO EN: " << this << endl;
}

void Vehiculo::verificarTelepase(bool is_telepase){
    this->telepase = is_telepase;
}

float Vehiculo::montoAPagar(int monto_por_rueda){
    return ((float)(this->ruedas)*(float)monto_por_rueda)-((float)(this->ruedas)*(float)monto_por_rueda*descuento())/100;
}



Moto::Moto(){
    this->ruedas = 2;
}

void Moto::verificarTelepase(bool telepase){
    this->telepase = false;
}

float Moto::descuento(){
    return 0;
}


Auto::Auto(){
    this->ruedas = 4;
}

void Auto::verificarTelepase(bool telepase){
    this->telepase = telepase;
}

float Auto::descuento(){
    if(this->telepase){
        return 50;
    }
    return 0;
}


Camion::Camion(unsigned int ruedas){
    this->ruedas = ruedas;
}

void Camion::verificarTelepase(bool telepase){
    this->telepase = telepase;
}

float Camion::descuento(){
    if(this->telepase){
        return 25;
    }
    return 0;
}