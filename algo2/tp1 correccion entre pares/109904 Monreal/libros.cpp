#include <iostream>
#include <string>
#include <fstream>

#include "menu.h"
#include "libros.h"

using namespace std;

void leer_archivo(Biblioteca* biblioteca){

    ifstream archivo_de_libros ("libros.csv");

    string nombre, genero, puntaje;
    int cont=0;
    
    Libro** vector_de_libros = new Libro* [20];
    
    while (!archivo_de_libros.eof()){

        if (biblioteca -> cantidad_de_libros % 20 == 0) {
            agrandar_vector_de_libros(biblioteca, vector_de_libros);
            
        }
        

        getline(archivo_de_libros, nombre, ',');
        getline(archivo_de_libros, genero, ',');
        getline(archivo_de_libros, puntaje, '\n');

        Libro* libro = new Libro;

        libro -> nombre_libro = nombre;
        libro -> genero = genero[0];
        libro -> puntaje = stoi(puntaje);

        vector_de_libros[cont] = libro;
        

        cont++;

        
        
        biblioteca ->cantidad_de_libros = cont;

    }

    biblioteca -> libros = vector_de_libros;
    
}



void genero_completo(Biblioteca* biblioteca, int i){
    switch (biblioteca -> libros[i]->genero)
        {
        case 'A':
            cout<< "Aventura" << endl;
            break;
        case 'C':
            cout<< "Ciencia Ficcion" << endl;
            break;
        case 'D':
            cout<< "Didactica"<< endl;
            break;
        case 'P':
            cout<< "Policiaca"<< endl;
            break;
        case 'R':
            cout<< "Romance"<< endl;
            break;
        case 'T':
            cout<< "Terror"<< endl;
            break;
        }
}



void listar_libros_leidos (Biblioteca* biblioteca){
    
    for(int i=0; i < biblioteca -> cantidad_de_libros -1; i++){

        cout << "-----------------------" << endl;
        cout << "Nombre del libro " << i+1 << ": " << biblioteca -> libros[i] ->nombre_libro << endl;
        cout << "Genero del libro " << i+1 << ": ";
        genero_completo(biblioteca, i);
        cout << "Puntaje del libro " << i+1 << ": " << biblioteca -> libros[i] -> puntaje << endl; 
        cout << "-----------------------" << endl;
    }

}

void agrandar_vector_de_libros(Biblioteca* biblioteca,  Libro** vector_de_libros){

    int tope_viejo = biblioteca -> cantidad_de_libros;
    int tope_nuevo = tope_viejo *10;
    Libro** nuevo_vector_libros = nullptr;
    nuevo_vector_libros = new Libro*[tope_nuevo];
    biblioteca->cantidad_de_libros=tope_nuevo;

    for(int i = 0; i < tope_viejo; i++){
        nuevo_vector_libros[i] = vector_de_libros[i];

    }

    if(biblioteca->cantidad_de_libros != 0 ){
        for(int i = 0; i < tope_viejo; i++){
            delete vector_de_libros[i];
            
        }
        delete[] vector_de_libros;
        delete[] biblioteca->libros;
    }

    
    biblioteca -> libros = nuevo_vector_libros;
    
}

char pedir_y_validar_genero(){
    cout << endl << "Ingrese la inicial del genero correspondiente al libro, opciones: " 
        << endl << "Aventura (A)"
        << endl << "Ciencia Ficcion (C)"
        << endl << "Didactica (D)"
        << endl << "Policiaca (P)"
        << endl << "Romance (R)"
        << endl << "Terror (T)" << endl;
        char genero;
        cin >> genero;
        
    while(genero != 'A' || genero != 'C' || genero != 'D' || genero != 'P' || genero != 'R' || genero != 'T' ){
        cout << "La inicial ingresada no pertenece a uno de los generos validos."<< endl
        << endl << "Ingrese la inicial del genero correspondiente al libro, opciones: " 
        << endl << "Aventura (A)"
        << endl << "Ciencia Ficcion (C)"
        << endl << "Didactica (D)"
        << endl << "Policiaca (P)"
        << endl << "Romance (R)"
        << endl << "Terror (T)" << endl;
        
    }
    return genero;
}



void agregar_libro(Biblioteca* biblioteca, Libro* libros){

    if (biblioteca -> cantidad_de_libros == sizeof(biblioteca ->libros)) {
        agrandar_vector_de_libros(biblioteca, biblioteca ->libros);
        biblioteca -> cantidad_de_libros++;
    }

    cout << endl << "Ingrese nombre del libro: ";
    cin >> biblioteca ->libros[biblioteca -> cantidad_de_libros] ->nombre_libro;
    int i = validar_existancia_libro(biblioteca ->libros[biblioteca -> cantidad_de_libros] ->nombre_libro, libros, biblioteca);
    if (i == -1){

        pedir_y_validar_genero() >> biblioteca ->libros[biblioteca -> cantidad_de_libros] ->genero;
        pedir_y_validar_puntaje() >> biblioteca ->libros[biblioteca -> cantidad_de_libros] ->puntaje;

        cout << endl;
    }
}



int validar_existancia_libro(string libro_a_validar, Libro* libros, Biblioteca* biblioteca){
    for (int i=0; i<biblioteca ->cantidad_de_libros; i++){
        if (libro_a_validar == biblioteca -> libros[i] -> nombre_libro){
            cout << "Ya existe ese libro en la biblioteca!" << endl;
            return i;
        }
    }

    cout << "No existe ese libro en la biblioteca!" << endl;
    return -1;
}

int pedir_y_validar_puntaje(){
    int puntaje;
    cout << "Ingrese un nuevo puntaje entre 0 y 100: " << endl;
    cin >> puntaje;

    while (puntaje < 0 || puntaje >100){

        if (puntaje <0){
            cout << "No puede ser taaan malo el libro, el puntaje minimo es 0." << endl << "Intentalo de vuelta: " << endl;
        }

        else{
            cout << "Bueno bueno, te gusto el libro... pero el maximo puntaje es 100." << endl << "Intentalo de vuelta: " << endl;
        }
        cin >> puntaje;
    }

    cout << "El puntaje ingresado es valido!" << endl;

    return puntaje;

}

void editar_puntaje(Biblioteca* biblioteca, Libro* libros){
    string libro_a_editar;
    cout << "Ingrese el titulo del libro el cual desea editar el puntaje: " << endl;
    getline(cin >> ws, libro_a_editar);


    int i = validar_existancia_libro(libro_a_editar, libros, biblioteca);

    cout << "Ingrese el nuevo puntaje: " << endl;

    int nuevo_puntaje = pedir_y_validar_puntaje();

    biblioteca ->libros[i] ->puntaje = nuevo_puntaje;

    cout << "El cambio de puntajes se ha realizado con exito! " << endl;
    

}


void mostrar_libro_favorito(Biblioteca* biblioteca, Libro* libros){
    int mayor_puntaje = 0;

    for (int i=0; i < biblioteca ->cantidad_de_libros; i++){
        if (mayor_puntaje < biblioteca->libros[i] -> puntaje){
            mayor_puntaje = biblioteca->libros[i] -> puntaje;
        }
    }

    
    const int tope = biblioteca -> cantidad_de_libros;
    
    int* vec_libros_favoritos =new int [biblioteca -> cantidad_de_libros];


    int j=0;
    for (int i=0; i< biblioteca ->cantidad_de_libros; i++){
        if (biblioteca ->libros[i] ->puntaje == mayor_puntaje){
            vec_libros_favoritos [j] = i;
            j++;
        }
    }
    cout << "Los libros favoritos con el puntaje " << mayor_puntaje << "son: " << endl;
    
    for(int i=0; i< biblioteca->cantidad_de_libros;i++){
        cout << biblioteca->libros[vec_libros_favoritos[i]] << endl;
    }

    delete [] vec_libros_favoritos;
    
}


void ordenar_genero_mas_leido(int contador [6], int* maximo, int* posicion){
    *maximo=contador[0];
    *posicion=0;
    
    for(int i=1; i<6; i++){
        if(contador[i]> *maximo){
            *maximo=contador[i];
            *posicion = i;
        }
    }
}

void mostrar_genero(int contador [6]){
    
    int i=0, j=1;
    while (contador[i] == contador[j] && contador[j] < 6){
        switch (contador[j])
        {
            case 'A':
                cout<< "Aventura";
                break;
            case 'C':
                cout<< "Ciencia Ficcion";
                break;
            case 'D':
                cout<< "Didactica";
                break;
            case 'P':
                cout<< "Policiaca";
                break;
            case 'R':
                cout<< "Romance";
                break;
            case 'T':
                cout<< "Terror";
                break;
        }
    }
}
//hacer un vector de 6 posiciones, que cada pos represemte un genero. mas facil para ordenar.
void mostrar_genero_mas_leido(Biblioteca* biblioteca, Libro* libros){
    int contador [6] = {0,0,0,0,0,0};

    // arreglar
    for (int i=0; i< biblioteca -> cantidad_de_libros; i++){
        
        switch (biblioteca -> libros[i]->genero)
        {
        case 'A':
            contador[0]++;
            break;
        case 'C':
            contador[1]++;
            break;
        case 'D':
            contador[2]++;
            break;
        case 'P':
            contador[3]++;
            break;
        case 'R':
            contador[4]++;
            break;
        case 'T':
            contador[5]++;
            break;

        }
    }
    int *maximo, *posicion;

    ordenar_genero_mas_leido(contador, maximo, posicion); 

    cout << "Los generos mas leidos, con " << maximo << " libros leidos son: "<< endl;
    for(int i = *posicion; i<6; i++){
        if(contador[i] == *maximo){
            switch (biblioteca -> libros[i]->genero)
            {
            case 'A':
                cout << "Aventura "<< endl;
                break;
            case 'C':
                cout << "Ciencia Ficcion" << endl;
                break;
            case 'D':
                cout << "Didactica" << endl;
                break;
            case 'P':
                cout << "Policiaca" << endl;
                break;
            case 'R':
                cout << "Romance" << endl;
                break;
            case 'T':
                cout << "Terror" << endl;
                break;

            }
        }
    } 
}


void mostrar_genero_favorito(Biblioteca* biblioteca, Libro* libros){
    float promedio [6];
    int a=0 , c=0, d=0, p=0, r=0, t=0;
    float sum_a=0 , sum_c=0, sum_d=0, sum_p=0, sum_r=0, sum_t=0;
    
    for (int i=0; i< biblioteca -> cantidad_de_libros; i++){
        
        switch (biblioteca -> libros[i]->genero)
        {
        case 'A':
            a++;
            sum_a += biblioteca -> libros[i] -> puntaje;
            promedio[0] = sum_a / a ;
            break;
        case 'C':
            c++;
            sum_c += biblioteca -> libros[i] -> puntaje;
            promedio[1] = sum_c / c ;
            break;
        case 'D':
            d++;
            sum_d += biblioteca -> libros[i] -> puntaje;
            promedio[2] = sum_d / d ;
            break;
        case 'P':
            p++;
            sum_p += biblioteca -> libros[i] -> puntaje;
            promedio[3] = sum_p / p ;
            break;
        case 'R':
            r++;
            sum_r += biblioteca -> libros[i] -> puntaje;
            promedio[4] = sum_r / r ;
            break;
        case 'T':
            t++;
            sum_t += biblioteca -> libros[i] -> puntaje;
            promedio[5] = sum_t / t ;
            break;

        }
    }

    float maximo=promedio[0];
    int posicion=0;
    
    for(int i=1; i<6; i++){
        if(promedio[i]> maximo){
            maximo=promedio[i];
            posicion = i;
        }
    }

    cout << "Los generos con mayor puntaje promedio con " << maximo << ", son: "<< endl;
    for(int i = posicion; i<6; i++){
        if(promedio[i] == maximo){
            switch (biblioteca -> libros[i]->genero)
            {
            case 'A':
                cout << "Aventura "<< endl;
                break;
            case 'C':
                cout << "Ciencia Ficcion" << endl;
                break;
            case 'D':
                cout << "Didactica" << endl;
                break;
            case 'P':
                cout << "Policiaca" << endl;
                break;
            case 'R':
                cout << "Romance" << endl;
                break;
            case 'T':
                cout << "Terror" << endl;
                break;

        }
        }
    }
}

void mostrar_tres_peores_libros(Biblioteca* biblioteca, Libro* libro){
    int minimo=101;
    int posicion_peor;
    for(int i=0; i< biblioteca->cantidad_de_libros;i++){
        if(biblioteca->libros[i]->puntaje < minimo){
            minimo = biblioteca->libros[i]->puntaje;
            posicion_peor = i;
        }

    }

    cout<< "El peor libro es: " << biblioteca->libros[posicion_peor]<< "con el puntaje: " << biblioteca->libros[posicion_peor] ->puntaje << endl;

    minimo=101;
    int segundo_peor;
    for(int i=0; i< biblioteca->cantidad_de_libros;i++){
        if(biblioteca->libros[i]->puntaje < minimo && biblioteca->libros[i]->puntaje > biblioteca->libros[posicion_peor]->puntaje ){
            minimo = biblioteca->libros[i]->puntaje;
            segundo_peor = i;
        }

    }
    cout<< "El segundo peor libro es: " << biblioteca->libros[segundo_peor]<< "con el puntaje: " << biblioteca->libros[segundo_peor] ->puntaje << endl;

    minimo=101;
    int tercer_peor;
    for(int i=0; i< biblioteca->cantidad_de_libros;i++){
        if(biblioteca->libros[i]->puntaje < minimo && biblioteca->libros[i]->puntaje > biblioteca->libros[segundo_peor]->puntaje ){
            minimo = biblioteca->libros[i]->puntaje;
            tercer_peor = i;
        }
    } 

    int posibles_terceros;
    int candidato;
    for (int i=0; i< biblioteca->cantidad_de_libros;i++){
        if (biblioteca->libros[i]->puntaje == tercer_peor){
            posibles_terceros++;
            candidato = i;
        }
    }

    if(posibles_terceros == 1){
        cout<< "El tercer peor libro es: " << biblioteca->libros[tercer_peor]<< "con el puntaje: " << biblioteca->libros[tercer_peor] ->puntaje << endl;
    }
    else{
        if((biblioteca->libros[tercer_peor]->nombre_libro .compare(biblioteca->libros[candidato]->nombre_libro))<0)
            cout<< "El tercer peor libro es: " << biblioteca->libros[tercer_peor]<< "con el puntaje: " << biblioteca->libros[tercer_peor] ->puntaje << endl;
        else{
            cout<< "El tercer peor libro es: " << biblioteca->libros[candidato]<< "con el puntaje: " << biblioteca->libros[candidato] ->puntaje << endl;
        }
    
    }
}

void guardar_y_salir(Biblioteca* biblioteca, Libro* libros){
    ofstream archivo_de_libros ("libros.csv");

    for (int i=0; biblioteca->cantidad_de_libros;i++){
        archivo_de_libros<< biblioteca->libros[i]->nombre_libro << "," << biblioteca->libros[i]->genero << "," << biblioteca->libros[i]->puntaje << "\n";
        delete biblioteca ->libros[i];
        biblioteca->cantidad_de_libros--;
    }
    delete[] biblioteca->libros;
    biblioteca->libros=nullptr;
}

