/*
-C esta contenido en C++ (C++ es un superset de C)
-estandares: ANSI C++ / ISO C++

Compilador:
    -Eclipse
    -Code::Blocks
    -Dev C++

Variables:
    -tipo nombre;
    -tipo nombre = valor;
    -ej:
        int x, y;
        int x = 5, y;
    -int sueldo_bruto V int sueldoBruto

Constantes:
    -const tipo NOMBRE = valor;
    -const int IVA = 21;
    -NO usar #define

entrada/salida:
    #indlue <iostream>

    Cin
        int valor;
        std::cin >> valor;
    Cout
        char valor = 'J'
        std::cout << "Hello World" << valor << std::endl;

tipos de datos derivados:
    int vec[10];    // arrancan en 0

    struct Empleados{
        int legajo;
        float sueldo;
    };

    Empleados empleado_nuevo;
    empleado_nuevo.legajo = 325;
    empleado_nuevo.sueldo = 402000.30;

    enum Estado{
        NO_COMENZADO;
        INICIADO;
        FINALIZADO;
    }

    Estado partido;
    partido = NO_COMENZADO
    if (partido == INICIADO){
        consultar_puntuacion();
    }

    int matrix[8][9];

division float:
    int x=8, y=9;
    double z = (double)x/y;
*/


#include <iostream>     // canal de entrada-salida

using namespace std;    // si no se indica, usa por default el espacio de nombres std

int main(){
    cout << "Hello World" << endl;     // imprime lo que hay dsps del cout <<

    char c = 'A';
    cout << (int)c << endl;     // casting

    c++;

    cout << c;

    return 0;
}