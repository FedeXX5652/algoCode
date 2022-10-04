#include "menu.h"
#include "biblioteca.h"
#include <iostream>

using namespace std;



void mostrar_menu()
{
    cout << endl << endl << endl;
    cout << "=================== MENU ===================" << endl
    << "    " << "1. Listar libros leidos." << endl
    << "    " << "2. Agregar libro." << endl
    << "    " << "3. Editar puntaje de un libro por título." << endl
    << "    " << "4. Mostar libro favorito. " << endl
    << "    " << "5. Mostar los 3 libros con menor puntaje." << endl
    << "    " << "6. Mostar género más leído." << endl
    << "    " << "7. Mostar  género favorito." << endl
    << "    " << "8. Guardar y salir." << endl
    <<"============================================"<< endl;
    cout << endl << endl << endl;
};


int ingreso_de_opcion()
{
    string opcion_cadena;

    getline(cin,opcion_cadena);

    int opcion = stoi(opcion_cadena);

    return opcion;
}

int _validar_puntaje(int puntaje)
{
    string puntaje_cadena;
    while (puntaje<0 || puntaje>100)
    {
        cout << "El puntaje ingresado no es valido."<<endl; 
        cout << "Por favor ingrese un puntaje entre 0 y 100"<<endl; 
        getline(cin,puntaje_cadena);
        puntaje = stoi(puntaje_cadena);
    }
    
    return puntaje;
};

string _validar_genero(string genero)
{
    
    while ( (genero != generos[AVENTURA]) && (genero != generos[CIENCIA_FICCION]) && (genero != generos[DIDACTICO]) && 
    (genero != generos[POLICIACA]) &&  (genero != generos[ROMANCE]) && (genero != generos[TERROR]))  
    {
        cout << "El genero, " << genero << " ingresado no es valido."<<endl; 
        cout << "Por favor ingrese uno de los siguientes generos: Aventura, Ciencia_Ficcion, Didactica, Policiaca, Romance, Terror" <<endl; 
        getline(cin, genero);
    
    }

    return genero;
};


void procesar_opcion(Biblioteca* biblioteca ,int opcion)
{
    string nombre,genero,puntaje_cadena;
    int puntaje;
    switch (opcion)
    {
        case(LISTA_DE_LIBROS):
        {
            cout << "=================== LISTA DE LIBROS ===================" << endl;
                imprimir_biblioteca(biblioteca);
            break;
        
        }
        case(AGREGAR_LIBRO):
        {   
            cout << "=================== AGREGAR LIBRO ===================" << endl;
            cout << "Por favor ingrese los datos del libro a agregar"<<endl;
            cout << "Nombre:";
            getline(cin, nombre); 
            cout << endl;
            
            cout << "Ingrese el género del libro entre los siguientes o solo su inicial:"<<endl; 
            cout << "Aventura, Ciencia Ficción, Didáctico, Romance, Terror o Policíaca"<< endl;
            cout << "Incluidos acentos y mayusculas."<< endl;

            cout << "Genero: ";
            getline(cin, genero);
            cout << endl;
            genero = _validar_genero(genero);

            cout << "Para el puntaje ingrese un número entre 0 y 100 inclusive"<< endl;
            cout << "Puntaje: ";
            getline(cin, puntaje_cadena);
            cout << endl;
            puntaje = stoi(puntaje_cadena);            
            puntaje = _validar_puntaje(puntaje);

            Libro* libro = crear_libro(nombre,genero,puntaje);
            agregar_libro(biblioteca,libro);
            cout << "Se a agregado el libro correctametne."; 
        }
        break;

        case(EDITAR_PUNTAJE):
        {
            cout << "=================== EDITAR PUNTAJE ===================" << endl;
            imprimir_biblioteca(biblioteca);
            cout << "Ingrese el nombre del libro que quiere modifica el puntaje"<<endl;
            cout << "Respetando mayusculas y acentos: "<<endl;
            cout <<"Nombre: ";
            getline(cin, nombre);
            cout << "Ingrese el puntaje que quiere poner: "<<endl;
            cout <<"Puntaje: ";
            getline(cin, puntaje_cadena);
            cout << endl;
            puntaje = stoi(puntaje_cadena);
            puntaje = _validar_puntaje(puntaje);
            editar_puntaje(biblioteca, nombre, puntaje);
            cout<< "El puntaje del libro " << nombre <<" ahora es "<< puntaje;
        }
        break;
        
        case(FAVORITO):
        {
            cout << "=================== FAVORITO ===================" << endl;
            imprimir_libro_favorito(biblioteca); 
        }
        break;

        case(PEORES):
        {
            cout << "=================== PEORES ===================" << endl;
            imprimir_peores_libros(biblioteca);
        
        }
        break;

        case(GENERO_MAS_LEIDO):
        {
            cout << "=================== GENERO MAS LEIDO ===================" << endl;
            mostar_genero_mas_leido(biblioteca);
        }
        break;

        case(GENERO_FAVORITO):
        {
            cout << "=================== GENERO FAVORITO ===================" << endl;
            mostrar_genero_favorito(biblioteca);
        }
        break;

    case(GUARDAR_Y_SALIR):
    {
        escribir_biblioteca(biblioteca);
        cout << "Se a guardado la lista de libros en el archivo libros.csv" << endl;

    }
    break;
    
    default:
    cout << "La opcion ingresada no es valida, por favor ingrese un número del 1 al 8"<<endl;
        break;
    }

};