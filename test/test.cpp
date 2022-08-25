#include <iostream>

using namespace std;

void cargar(int mat[][6], int fil, int col){
    for(int f=0; f<fil; f++){
        for(int c=0; c<col; c++){
            mat[f][c] = (f+1)*(c+1);
        }
    }
}

void mostrar(int mat[][6], int fil, int col)
{
    for(int f=0; f<fil; f++){
        for(int i=0; i<col; i++){
        if(i==0){
            cout << "[";
        }
        cout << mat[f][i];
        if(i+1 != col){
            cout << ", ";
        }
        else{
            cout << "]" << endl;
        }
    }
    }
}

int main()
{
    int fil = 2;
    int col = 6;
    int mat[2][6];
    cargar(mat, fil, col);
    cout << "---" << endl;
    mostrar(mat, fil, col);
}