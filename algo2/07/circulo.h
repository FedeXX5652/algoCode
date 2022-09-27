#ifndef CIRCULO_H_INCLUDED
#define CIRCULO_H_INCLUDED

#include "punto_r2.h"

class Circulo{
    private:
        double radio;
        PuntoR2 centro;

    public:
        Circulo(double r);

        void mostrar();
};

#endif