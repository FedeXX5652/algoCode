#include <iostream>

using namespace std;


void cargar_vec(int vec[], int n){
    for(int i=0; i<n; i++){
        vec[i] = (i+1)*(i+1);
    }
}

void mostrar_vec(int vec[], int n){
    cout << "VECTOR:\n[";
    for(int i=0; i<n-1; i++){
        cout << vec[i];
        cout << ", ";
    }
    cout << vec[n-1] << "]" << endl;
}