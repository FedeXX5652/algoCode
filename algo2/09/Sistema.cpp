#include "Sistema.h"
#include "Vehiculo.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const string PATH = "vehiculos.txt";
const int PRECIO_POR_RUEDA = 10;

Sistema::Sistema()
{
    this->cantidadDeVehiculos = 0;
    this->precioPorRueda = PRECIO_POR_RUEDA;
    this->leerDatos();
}

void Sistema::leerDatos()
{
    ifstream archivo;
    archivo.open(PATH.c_str());
    unsigned int ruedas;
    bool telepase;

    if(!archivo)
    {
        cout<<"No se pudo leer el archivo: "<<PATH<<endl;
        exit(1);
    }

    while(archivo>>ruedas>>telepase)
    {
        this->cargarVehiculo(ruedas,telepase);
    }

    archivo.close();

}

void Sistema::cargarVehiculo(unsigned int ruedas, bool telepase)
{
    if(ruedas == 2){
        this->vehiculos[cantidadDeVehiculos] = new Moto();
    }
    else if(ruedas == 4){
        this->vehiculos[cantidadDeVehiculos] = new Auto();
    }
    else{
        this->vehiculos[cantidadDeVehiculos] = new Camion(ruedas);
    }
	

    this->vehiculos[cantidadDeVehiculos]->verificarTelepase(telepase);

    cantidadDeVehiculos++;
}

void Sistema::cobrarPeajes()
{
    for(unsigned int i = 0; i < cantidadDeVehiculos; i++)
    {
        cobrarMonto(vehiculos[i]->montoAPagar(PRECIO_POR_RUEDA));
    }
}

void Sistema::cobrarMonto(float monto)
{
    montoRecaudado = montoRecaudado + monto;
}

float Sistema::obtenerMontoRecaudado()
{
    return this->montoRecaudado;
}
