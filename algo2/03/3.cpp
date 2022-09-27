#include <iostream>

using namespace std;

/*
MEMORIA DINAMICA:
cada byte puede almacenar 256 valores

int a=8;
cout << (unsigned)&a << endl;   //imprime la direccion de memoria en hexa

puntero a int: int* val;
puntero a char: char* val;
puntero a float: float* val;

NO podemos asignar los espacios de memoria de forma explicita
int* val = 1120656; NO

new int crea un nuevo espacio de memoria, lo puedo guardar en el int* p
*/

int main(){
    int x;
    int *px;
    cout << "X=";
    cin >> x;
    px = &x;
    cout << "el numero ingresado fue: " << *px << endl;
    delete px;
    px = nullptr;
    cout << "pero x sigue siendo: " << x << endl;
    return 0;
}


int main(){
    int x=5, y=8;
    int *p1;
    int *p2;
    p1 = &x;
    p2 = &y;
    cout<<*p1<<" - "<<*p2<<endl;
}

typedef int* Pint;
typedef char* Pchar;

int main(){
    Pint A,C,F;
    int H;
    H=70;
    F=new int;
    (*F)=H;
    C=new int;
    A=C;
    (*A)=67;
    H++;
    cout<<(*C)<<(*A)<<(*F)<<endl;
    delete A;
    delete C;
    delete F;
    return 0;
}

int main(){
    Pint A,C,F;
    Pint *B;
    Pchar D,E;

    char G='C';
    int H=70;
    C=new int;
    A=C;
    *A=67;
    B=&A;
    F=new int;
    *F=H;
    D=(Pchar)F;
    E=(Pchar)(*B);
    **B=*A-63;
    if(*E != G){
        cout<<*A<<*D<<*C<<endl;
    }
    delete A;
    delete B;
    delete C;
    delete D;
    delete E;
}