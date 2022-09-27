#include <iostream>
#include "circulo.h"

Circulo::Circulo(double r){
    std::cout << "Circulo creado en " << this << std::endl;
    radio = r;
}

void Circulo::mostrar(){
    std::cout << "Circulo de radio " << radio << ", centrado en ";
    centro.mostrar();
}