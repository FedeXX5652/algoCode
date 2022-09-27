#include <iostream>
#include "Sistema.h"

using namespace std;

int main()
{
    Sistema sistema;
    sistema.cobrarPeajes();
    cout<<"El monto recaudado en el dia es de: "<<sistema.obtenerMontoRecaudado()<<" pesos "<<endl;
    return 0;
}
