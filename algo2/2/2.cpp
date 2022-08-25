#include <iostream>
#include <string>

using namespace std;

/*
funciones:
    - tipo_de_retorno nombre_funcion (parametros){
        
    }
*/

int minimo(int& x, int& y){     // pasaje por referencia
    int min = x;
    if(x>y){
        min = y;
    }
    return min;
}

void cargar_vec(int vec[], int n){      // los vectores ya se pasan por referencia, no requieren return ni &
    for(int i=0; i<n; i++){
        vec[i] = (i+1)*(i+1);
    }
}

void mostrar_vec(int vec[], int n){
    for(int i=0; i<n; i++){
        if(i==0){
            cout << "[";
        }
        cout << vec[i];
        if(i+1 != n){
            cout << ", ";
        }
        else{
            cout << "]" << endl;
        }
    }
}

void cargar_mat(int mat[][5], int fil, int col){        // se requiere que la cantidad de filas se indique al pasar la matriz
    for(int f=0; f<fil; f++){                           // (para poder ubicar donde se almacena el valor)
        for(int c=0; c<col; c++){
            // cin >> mat[f][c];
            mat[f][c] = (f+1)*(c+1);
        }
    }
}

void mostrar_mat(int mat[][5], int fil, int col){
    for(int f=0; f<fil; f++){
        mostrar_vec(mat[f], col);
    }
}

int main(){
    int x = 5, y=8;
    cout << "start: "<< x << " | " << y << endl;

    int min = minimo(x,y);

    cout << "min: " << min << endl;

    //-------------------------------- vector

    int vector[5];
    cout << "\nVECTOR:"<< endl;
    cargar_vec(vector, 5);
    mostrar_vec(vector, 5);

    //-------------------------------- matrix

    int mat[3][5];
    cout << "\nMATRIX:"<< endl;
    cargar_mat(mat, 3, 5);
    mostrar_mat(mat, 3, 5);

    //-------------------------------- string

    cout << "\nSTRING:"<< endl;
    string name = "Federico";
    string surname = "Galante";

    string full_name = name + " " + surname;
    cout << full_name << endl;

    //-------------------------------- 

    /*
    proceso de compilacion:
        -preprocesamiento:  (reemplazar una cosa por otra, reeplaza las directivas por lo indicado)
            *directivas:
                +include    (reeplaza los include por el paquete, copia y pega el codigo de lo incluido)
                +define (evitarlo)
                +ifndef
                +endif
            *proceso:
                +
        -copmilador:
            *tranduce cada linea a codigo de maquina
        -linkeditor:
            *si hay varios archivos los une a todos en un ejecutable

    declaracion vs definicion:
        void cargar(int vec[], int n);  // declaracion (las manod al .h, creando el link, reemplazo por el #include "wasd.h")

        int main(){
            ...
        }

        int cargar(){   // definicion (las definiciones lo correcto es mandarlas a otro archivo .cpp, crear una lib)
            ...
        }
    */

    return 0;
}