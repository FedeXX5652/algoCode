#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 

using namespace std;

void read_csv(){
    // ifstream f("data.csv")   //lectura
    // ofstream f("data.csv")   //escritura

    // fstream f("data.csv", tipo) //ambas, en el tipo va si es escritura o lectura

    ifstream f("data.csv");
    if(f.is_open()){
        cout<<"ARCHIVO ABIERTO para leer :>"<<endl;
        string line;
        while(getline(f, line, '\0')){
            cout<<line<<endl;
        }
    }
    f.close();
    
    // ofstream f2("data.csv");
    // if(f2.is_open()){
    //     cout<<"ARCHIVO ABIERTO para escribir :>"<<endl;
    // }
    // f2.close();
}

int main(){
    read_csv();
    return 0;
}