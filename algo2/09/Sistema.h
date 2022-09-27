#ifndef SISTEMA_H
#define SISTEMA_H

#include "Vehiculo.h"

const int MAX_VEHICULOS = 100;

class Sistema
{
private:
    Vehiculo* vehiculos[MAX_VEHICULOS];
    unsigned int cantidadDeVehiculos;
    unsigned int precioPorRueda;
    float montoRecaudado;
public:
    Sistema();
    void leerDatos();
    void cargarVehiculo(unsigned int ruedas,bool telepase);
    void cobrarPeajes();
    void cobrarMonto(float monto);
    float obtenerMontoRecaudado();

};


#endif // SISTEMA_H
