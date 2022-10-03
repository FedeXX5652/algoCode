#include "Menu.hpp"
#include "Lista.hpp"
#include <iostream>
#include <string>
using namespace std;

void Mostrar_Menu(){
    cout << "\nMenú:\n" << endl
         << "1) Ver todos los libros" << endl
         << "2) Agregar un libro" << endl
         << "3) Editar puntaje de un libro" << endl
         << "4) Mostrar libro favorito" << endl
         << "5) Mostrar libros con menor puntaje" << endl
         << "6) Mostrar género más leído" << endl
         << "7) Mostrar género favorito" << endl
         << "8) Guardar cambios y salir" << endl;
}

int Pedir_Opcion(){
    int Opcion;
    cout << "\nIngrese la acción a realizar: ";
    cin >> Opcion;
    return Opcion;
}

void Validar_Opcion(int &Opcion){
    bool Opcion_Valida = (Opcion>0) && (Opcion  <= CANTIDAD_DE_OPCIONES);
    while(!Opcion_Valida){
        cout << "La opción elegida no es válida. Ingrese la acción a realizar: ";
        cin >> Opcion;
        Opcion_Valida = (Opcion>0) && (Opcion  <= CANTIDAD_DE_OPCIONES);
    }
}

void Procesar_Opcion(Lista* Nueva_Lista, int Opcion){
    Libro* Nuevo_Libro = nullptr;
    string Nombre;
    int Posicion, Puntaje, Vector_Puntajes, Vector_Generos, Apariciones;
    float Vector_Promedios, Promedio;
    switch(Opcion){
        case LISTAR_LIBROS:
            Listar_Libros(Nueva_Lista);
            break;
        case AGREGAR_LIBRO:
            Nombre = Pedir_Nombre();
            Posicion = Buscar_Libro(Nueva_Lista, Nombre);
            if(Posicion != POSICION_INVALIDA){
                cout << "\nEl libro " << Nombre << " ya está en la lista." << endl;
            }
            else{
                cout << "\nEl libro " << Nombre << " no está en la lista." << endl;
                Nuevo_Libro = Pedir_Libro();
                Agregar_Libro(Nueva_Lista, Nuevo_Libro);
                cout << "\nLibro listado correctamente." << endl;
            }
            break;
        case EDITAR_PUNTAJE:
            Nombre = Pedir_Nombre();
            Posicion = Buscar_Libro(Nueva_Lista, Nombre);
            if(Posicion == POSICION_INVALIDA){
                cout << "\nEl libro " << Nombre << " no está en la lista." << endl;
            }
            else{
                Puntaje = Pedir_Puntaje();
                Nueva_Lista -> Nuevo_Libro[Posicion] -> Puntaje = Puntaje;
                cout << "\nPuntaje cambiado correctamente." << endl;
            }
            break;
        case MOSTRAR_LIBRO_FAVORITO:
            Puntaje = Buscar_Mayor_Puntaje(Nueva_Lista);
            cout << "\nLos libros con mayor puntaje son:\n" << endl;
            Mostrar_Libro_Favorito(Nueva_Lista, Puntaje);
            break;
        case MOSTRAR_LIBROS_MENOR_PUNTAJE:
            Vector_Puntajes = Buscar_Menor_Puntaje(Nueva_Lista);
            cout << "\nLos 3 libros con menor puntaje son:\n" << endl;
            Mostrar_Libros_Menor_Puntaje(Nueva_Lista, &Vector_Puntajes);
            break;
        case MOSTRAR_GENERO_MAS_LEIDO:
            Vector_Generos = Contar_Generos(Nueva_Lista);
            Apariciones = Buscar_Mayor_Aparicion(&Vector_Generos);
            cout << "\nLos géneros más leídos son:\n" << endl;
            Genero_Mas_Leido(&Vector_Generos, Apariciones);
            break;
        case MOSTRAR_GENERO_FAVORITO:
            Vector_Generos = Contar_Generos(Nueva_Lista);
            Vector_Puntajes = Sumar_Puntajes_Generos(Nueva_Lista);
            Vector_Promedios = Promediar_Generos(Nueva_Lista, &Vector_Generos, &Vector_Puntajes);
            Promedio = Buscar_Mayor_Promedio(&Vector_Promedios);
            cout << "\nLos géneros favoritos son:\n" << endl;
            Genero_Favorito(&Vector_Promedios, Promedio);
            break;
    }
}

Libro* Pedir_Libro(){
    Libro* Nuevo_Libro = new Libro;
    string Nombre = Pedir_Nombre();
    char Genero = Pedir_Genero();
    int Puntaje = Pedir_Puntaje();
    Nuevo_Libro -> Nombre = Nombre;
    Nuevo_Libro -> Genero = Genero;
    Nuevo_Libro -> Puntaje = Puntaje;
    return Nuevo_Libro;
}

string Pedir_Nombre(){
    string Nombre;
    cout << "\nIngrese el nombre del libro: ";
    fflush(stdin);
    getline(cin >> ws, Nombre);
    return Nombre;
}

char Pedir_Genero(){
    string Genero;
    cout << "\nGéneros:\n" << endl
         << "Aventura" << endl
         << "Ciencia Ficción" << endl
         << "Didáctica" << endl
         << "Policíaca" << endl
         << "Romance" << endl
         << "Terror" << endl
         << "\nIngrese el género del libro: ";
    fflush(stdin);
    getline(cin >> ws, Genero);
    while(!Validar_Genero(Genero)){
        cout << "El género ingresado es inválido. Ingrese el género del libro: ";
        fflush(stdin);
        getline(cin >> ws, Genero);
    }
    return Genero[0];
}

bool Validar_Genero(string Genero){
    bool Genero_Valido = false;
    if((Genero == "Aventura")||(Genero == "Ciencia Ficción")||(Genero == "Didáctica")||(Genero == "Policíaca")||(Genero == "Romance")||(Genero == "Terror")){
        Genero_Valido = true;
    }
    return Genero_Valido;
}

int Pedir_Puntaje(){
    string Puntaje;
    cout << "\nIngrese el puntaje del libro: ";
    cin >> Puntaje;
    while(!Validar_Puntaje(Puntaje)){
        cout << "El puntaje ingresado tiene un formato inválido. Ingrese el puntaje del libro: ";
        cin >> Puntaje;
    }
    return stol(Puntaje);
}

bool Validar_Puntaje(string Puntaje){
    bool Puntaje_Valido = false;
    int i = 0;
    while(Puntaje_Valido && (i < Puntaje.length())){
        Puntaje_Valido = isdigit(Puntaje[i]);
        i ++;
    }
    if((stol(Puntaje) >= PUNTAJE_MINIMO) && (stol(Puntaje) <= PUNTAJE_MAXIMO)){
        Puntaje_Valido = true;
    }
    return Puntaje_Valido;
}

int Buscar_Mayor_Puntaje(Lista* Nueva_Lista){
    int i = 0, Puntaje = 0;
    while(i < Nueva_Lista -> Cantidad_Libros){
        if(Puntaje < Nueva_Lista -> Nuevo_Libro[i] -> Puntaje){
            Puntaje = Nueva_Lista -> Nuevo_Libro[i] -> Puntaje;
        }
        i ++;
    }
    return Puntaje;
}

void Mostrar_Libro_Favorito(Lista* Nueva_Lista, int Puntaje){
    int i = 0;
    while(i < Nueva_Lista -> Cantidad_Libros){
        if(Puntaje == Nueva_Lista -> Nuevo_Libro[i] -> Puntaje){
            cout << Nueva_Lista -> Nuevo_Libro[i] -> Nombre << endl;
        }
        i ++;
    }
}

int Buscar_Menor_Puntaje(Lista* Nueva_Lista){
    int i = 0, Primer_Puntaje = 100, Segundo_Puntaje = 90, Tercer_Puntaje = 80, Vector[LIBROS_MENOR_PUNTAJE] = {Primer_Puntaje, Segundo_Puntaje, Tercer_Puntaje};
    while(i < Nueva_Lista -> Cantidad_Libros){
        if(Primer_Puntaje > Nueva_Lista -> Nuevo_Libro[i] -> Puntaje){
            Tercer_Puntaje = Segundo_Puntaje;
            Segundo_Puntaje = Primer_Puntaje;
            Primer_Puntaje = Nueva_Lista -> Nuevo_Libro[i] -> Puntaje;
        }
        i ++;
    }
    return Vector[LIBROS_MENOR_PUNTAJE];
}

void Mostrar_Libros_Menor_Puntaje(Lista* Nueva_Lista, int Vector[]){
    int i = 0, j, Posicion;
    string Vector_Nombres;
    while(i < LIBROS_MENOR_PUNTAJE - 1){
        for(j = 0; j < Nueva_Lista -> Cantidad_Libros; j ++){
            if(Vector[i] == Nueva_Lista -> Nuevo_Libro[j] -> Puntaje){
                cout << Nueva_Lista -> Nuevo_Libro[j] -> Nombre << endl;
            }
        }
        i ++;
    }
    if(Vector[LIBROS_MENOR_PUNTAJE]){
        Vector_Nombres = Buscar_Nombres(Nueva_Lista, Vector[LIBROS_MENOR_PUNTAJE]);
        Ordenar_Nombres(Nueva_Lista, &Vector_Nombres);
        Posicion = Posicion_Libro_Menor_Puntaje(Nueva_Lista, &Vector_Nombres);
        cout << Nueva_Lista -> Nuevo_Libro[Posicion] -> Nombre << endl;
    }
}

string Buscar_Nombres(Lista* Nueva_Lista, int Menor_Puntaje){
    int i = 0, j = 0;
    string Vector[j];
    while(i < Nueva_Lista -> Cantidad_Libros){
        if(Menor_Puntaje == Nueva_Lista -> Nuevo_Libro[i] -> Puntaje){
            Vector[j] = Nueva_Lista -> Nuevo_Libro[i] -> Nombre;
            j ++;
        }
        i ++;
    }
    return Vector[j];
}

void Ordenar_Nombres(Lista* Nueva_Lista, string Vector[]){
    int i, j;
    string Auxiliar;
    for(i = 1; i < Nueva_Lista -> Cantidad_Libros; i ++){
        for(j = 0; j < Nueva_Lista -> Cantidad_Libros - i; j ++){
            if(Vector[j] > Vector[j + 1]){
                Auxiliar = Vector[j];
                Vector[j] = Vector[j + 1];
                Vector[j + 1] = Auxiliar;
            }
        }
    }
}

int Posicion_Libro_Menor_Puntaje(Lista* Nueva_Lista, string Vector[]){
    bool Libro_Encontrado = false;
    int i = 0, Posicion = ERROR;
    while((i < Nueva_Lista -> Cantidad_Libros) && (!Libro_Encontrado)){
        if(Nueva_Lista -> Nuevo_Libro[i] -> Nombre == Vector[0]){
            Libro_Encontrado = true;
            Posicion = i;
        }
        i ++;
    }
    return Posicion;
}

int Contar_Generos(Lista* Nueva_Lista){
    int i = 0, Total_A = 0, Total_C = 0, Total_D = 0, Total_P = 0, Total_R = 0, Total_T = 0, Vector[TOTAL_GENEROS] = {Total_A, Total_C, Total_D, Total_P, Total_R, Total_T};
    while(i < Nueva_Lista -> Cantidad_Libros){
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'A'){Total_A ++;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'C'){Total_C ++;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'D'){Total_D ++;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'P'){Total_P ++;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'R'){Total_R ++;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'T'){Total_T ++;}
        i ++;
    }
    return Vector[TOTAL_GENEROS];
}

int Buscar_Mayor_Aparicion(int Vector[]){
    int i = 0, Mayor = 0;
    while(i < TOTAL_GENEROS){
        if(Vector[i] > Mayor){
            Mayor = Vector[i];
        }
        i ++;
    }
    return Mayor;
}

void Genero_Mas_Leido(int Vector[], int Mayor){
    int i = 0;
    while(i < TOTAL_GENEROS){
        if(Vector[i] == Mayor){
            if(i == 0){Mostrar_Genero('A');}
            if(i == 1){Mostrar_Genero('C');}
            if(i == 2){Mostrar_Genero('D');}
            if(i == 3){Mostrar_Genero('P');}
            if(i == 4){Mostrar_Genero('R');}
            if(i == 5){Mostrar_Genero('T');}
        }
        i ++;
    }
}

int Sumar_Puntajes_Generos(Lista* Nueva_Lista){
    int i = 0, Puntaje_A = 0, Puntaje_C = 0, Puntaje_D = 0, Puntaje_P = 0, Puntaje_R = 0, Puntaje_T = 0, Vector[TOTAL_GENEROS] = {Puntaje_A, Puntaje_C, Puntaje_D, Puntaje_P, Puntaje_R, Puntaje_T};
    while(i < Nueva_Lista -> Cantidad_Libros){
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'A'){Puntaje_A += Nueva_Lista -> Nuevo_Libro[i] -> Puntaje;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'C'){Puntaje_C += Nueva_Lista -> Nuevo_Libro[i] -> Puntaje;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'D'){Puntaje_D += Nueva_Lista -> Nuevo_Libro[i] -> Puntaje;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'P'){Puntaje_P += Nueva_Lista -> Nuevo_Libro[i] -> Puntaje;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'R'){Puntaje_R += Nueva_Lista -> Nuevo_Libro[i] -> Puntaje;}
        if(Nueva_Lista -> Nuevo_Libro[i] -> Genero = 'T'){Puntaje_T += Nueva_Lista -> Nuevo_Libro[i] -> Puntaje;}
        i ++;
    }
    return Vector[TOTAL_GENEROS];
}

float Promediar_Generos(Lista* Nueva_Lista, int Vector_Generos[], int Vector_Puntajes[]){
    int i = 0;
    float Vector_Promedios[TOTAL_GENEROS];
    while(i < TOTAL_GENEROS){
        Vector_Promedios[i] = (float) Vector_Puntajes[i] / Vector_Generos[i];
        i ++;
    }
    return Vector_Promedios[TOTAL_GENEROS];
}

float Buscar_Mayor_Promedio(float Vector[]){
    int i = 0;
    float Mayor = 0;
    while(i < TOTAL_GENEROS){
        if(Vector[i] > Mayor){
            Mayor = Vector[i];
        }
        i ++;
    }
    return Mayor;
}

void Genero_Favorito(float Vector[], float Mayor){
    int i = 0;
    while(i < TOTAL_GENEROS){
        if(Vector[i] == Mayor){
            if(i == 0){Mostrar_Genero('A');}
            if(i == 1){Mostrar_Genero('C');}
            if(i == 2){Mostrar_Genero('D');}
            if(i == 3){Mostrar_Genero('P');}
            if(i == 4){Mostrar_Genero('R');}
            if(i == 5){Mostrar_Genero('T');}
        }
        i ++;
    }
}