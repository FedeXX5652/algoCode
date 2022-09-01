#include <iostream>

struct Empleado{
    int legajo;
    string nombre;
    float sueldo;
}

void f(int &p){     // permite modificar el valor de x
    p=8;
    cout << p;  // imprime 5
}

void f2(int* vec) // tambien vale void f2(int vec[])

int main(){
    int x=5;
    cout << x;  // imprime 5
    f(x);
    cout << x;  // imprime 8

    int vec[10];
    int* p;
    p[0]; // accede a la 1ra pos
    p[1]; // accede a la 2da pos

    Empleado* pe = new Empleado;

    pe->legajo = 145;
    pe->sueldo = 123456;

    Empleado* empleados = new Empleados[100]; // vector de structs creado en forma dinamica
}

//------------------------------------------------

int ** mat;
mat = new int*[4];      // creo el vec de filas
for(int i=0; i<4; i++){
    mat[i] = new int[5]     // creo el vec de columnas
}

for(int i=0; i<4; i++){     // para borrar la mat tengo que primero borrar cada fila y despues la columna principal
    delete [] mat[i];
}
delete [] mat;