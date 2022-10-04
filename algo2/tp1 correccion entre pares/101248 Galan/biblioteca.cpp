#include "biblioteca.h"
#include "libro.h"
#include <iostream>
#include <fstream>
#define CANTIDAD_INICINAL 20

const std::string RUTA_LIBROS = "libros.csv";

Biblioteca* crear_biblioteca()
{
    Biblioteca* biblioteca = new Biblioteca;
    biblioteca->cantidad_de_libros = 0;
    biblioteca->lista_de_libros = new Libro* [CANTIDAD_INICINAL];
    biblioteca->limite_de_libros = CANTIDAD_INICINAL;
    return biblioteca;
};

void destruir_biblioteca(Biblioteca* biblioteca)
{
    for (size_t i = 0; i < (size_t)biblioteca->cantidad_de_libros; i++)
    {
        destruir_libro(biblioteca->lista_de_libros[i]);
    }
    delete[] biblioteca->lista_de_libros;   
    delete biblioteca;
};


void _expandir_lista(Biblioteca* biblioteca)
{   
    biblioteca->limite_de_libros = (biblioteca->limite_de_libros)*2;
    Libro** lista_de_libros_nueva = new Libro*[biblioteca->limite_de_libros];

    for (size_t i = 0; i < (size_t)biblioteca->cantidad_de_libros; i++)
    {
        lista_de_libros_nueva[i] = biblioteca->lista_de_libros[i];
    }
    delete[] biblioteca->lista_de_libros;

    biblioteca->lista_de_libros = lista_de_libros_nueva; 
};


bool _esta_libro(Biblioteca* biblioteca, string nombre) 
{
    bool libro_esta=false;
    for (size_t i = 0; i < (size_t)biblioteca->cantidad_de_libros; i++)
    {
        if(biblioteca->lista_de_libros[i]->nombre == nombre)
            libro_esta=true;
    }
    return libro_esta;
};

size_t _buscar_libro(Biblioteca * biblioteca, string nombre) 
{
    size_t i = 0;
    
    while (biblioteca->lista_de_libros[i]->nombre != nombre && i< biblioteca->cantidad_de_libros)
    {
        i++;
    
    }
    return i;
};


void agregar_libro(Biblioteca* biblioteca, Libro* libro) 
{ 
    if(libro==nullptr)
    {
        std::cout << "el libro ingresado, no es valido"<< endl;
        return;
    }
    
    if(_esta_libro(biblioteca,libro->nombre)) 
    {
        std::cout << "el libro "+libro->nombre+" ya está registrado"<< endl;
        std::cout << endl;
        delete libro; 
        return;
    }
    
    if(biblioteca->cantidad_de_libros == biblioteca->limite_de_libros)
    {
        _expandir_lista(biblioteca);
    }
    
    biblioteca->lista_de_libros[biblioteca->cantidad_de_libros] = libro;
    biblioteca->cantidad_de_libros++;

};


void imprimir_biblioteca(Biblioteca* biblioteca)
{
    if(biblioteca->cantidad_de_libros==0)
    {
        cout << "La biblioteca esta vacia, no hay libros cargados"<< endl;
        return;
    }
    for (size_t i = 0; i < (size_t)biblioteca->cantidad_de_libros; i++)
    {
        imprimir_libro(biblioteca->lista_de_libros[i]);
    }
    
}


void imprimir_libro_favorito(Biblioteca* biblioteca) 
{
     if(biblioteca->cantidad_de_libros==0)
    {
        cout << "La biblioteca esta vacia, no hay libros cargados"<< endl;
        return;
    }
    
    int maximo_puntaje=-1;
    size_t cantidad_de_maximos=0; 
    size_t* indices = new size_t[biblioteca->cantidad_de_libros]; 

    for (size_t i = 0; i < (size_t)biblioteca->cantidad_de_libros; i++) 
    {
        if (biblioteca->lista_de_libros[i]->puntaje > maximo_puntaje) 
        {
            maximo_puntaje = biblioteca->lista_de_libros[i]->puntaje;
            cantidad_de_maximos=0; 
        }
        if (biblioteca->lista_de_libros[i]->puntaje == maximo_puntaje) 
        {
            indices[cantidad_de_maximos]=i;
            cantidad_de_maximos++;
        } 
    }
    if (cantidad_de_maximos==1)
    {
        std::cout<<"El libro mejor puntuado es:"<<endl;
    }
    else
    {
        std::cout<<"Los libros mejor puntuados son:"<<endl;    
    
    }
    for (size_t i = 0; i < cantidad_de_maximos; i++)
    {
        imprimir_libro(biblioteca->lista_de_libros[indices[i]]);
    }
    delete [] indices;   

}


bool _comparar_puntajes_y_nombres(Libro* libro1, Libro* libro2)
{
    return (libro1->puntaje < libro2->puntaje ||
            (libro1->puntaje == libro2->puntaje && 
            libro1->nombre.compare(libro2->nombre) < 0 ) );
}


void imprimir_peores_libros(Biblioteca* biblioteca) 
{
    if (biblioteca->cantidad_de_libros < 3)
    {
        imprimir_biblioteca(biblioteca);
    }

    size_t inidices [3];

    int minimos_puntajes[3]={101,101,101}; 
    
    for (size_t i = 0; i < biblioteca->cantidad_de_libros; i++) 
    {
        for (size_t j = 0; j < 3; j++) 
        {
            if(minimos_puntajes[j] > 100 || _comparar_puntajes_y_nombres(biblioteca->lista_de_libros[i],biblioteca->lista_de_libros[inidices[j]])) 
            {
                for (size_t k = 2; k > j; k--)
                {
                    minimos_puntajes[k]= minimos_puntajes[k-1];
                    inidices[k] = inidices[k-1];
                }
                minimos_puntajes[j] = biblioteca->lista_de_libros[i]->puntaje; 
                inidices[j]=i;
                break;
            }
        
        }
        
    }
    std::cout<<"Los libros peor puntuados son:"<<endl;    
    for (size_t i = 0; i < 3; i++)
    {
        imprimir_libro(biblioteca->lista_de_libros[inidices[i]]);
    }

}


size_t _indice_del_valor_mas_alto(int vector[],size_t cantidad)
{
    int aux = vector[0];
    size_t indice = 0;
    for (size_t i = 0; i < cantidad; i++)
    {
        
        if (vector[i] > aux)
        {
            aux = vector[i];
            indice = i;
        }
        
    }
    return indice;

}


void mostar_genero_mas_leido(Biblioteca* biblioteca)
{
    if(biblioteca->cantidad_de_libros==0)
    {
        cout << "La biblioteca esta vacia, no hay libros cargados"<< endl;
        return;
    }

    int contadores [6]={0,0,0,0,0,0};
    size_t cantidad_de_maximos=0; 
    size_t indices[6];
    for (size_t i = 0; i < biblioteca->cantidad_de_libros; i++) // obtengo el vectro de valores
    {
        if( biblioteca->lista_de_libros[i]->genero =="A") // cambiar por case?
            contadores[AVENTURA]++;
        if( biblioteca->lista_de_libros[i]->genero =="C")
            contadores[CIENCIA_FICCION]++;
        if( biblioteca->lista_de_libros[i]->genero =="D")
            contadores[DIDACTICO]++;
        if( biblioteca->lista_de_libros[i]->genero =="P")
            contadores[POLICIACA]++;
        if( biblioteca->lista_de_libros[i]->genero =="R")
            contadores[ROMANCE]++;
        if( biblioteca->lista_de_libros[i]->genero =="T")
            contadores[TERROR]++;
    }
    //recorro el vector para ver los maximos si hay varios
    int maximo=-1;
    for (size_t i = 0; i < 6; i++)
    {
        if (contadores[i]>maximo)
        {
            maximo=contadores[i];
            cantidad_de_maximos=0;
        }
        if (contadores[i] == maximo) 
        {
            indices[cantidad_de_maximos]=i;
            cantidad_de_maximos++;
        } 
    }
    if (cantidad_de_maximos==1)
    {
        cout << "El genero más leido es: "<<endl;    
    }
    else
    {
        cout << "Los generos más leidos son: "<<endl;
    
    }
    for (size_t i = 0; i < cantidad_de_maximos; i++)
    {
        cout << generos[indices[i]] << endl;
    }
    cout << "Con "<< maximo << " libros leidos" <<endl;

};


void mostrar_genero_favorito(Biblioteca* biblioteca)
{
    if(biblioteca->cantidad_de_libros==0)
    {
        cout << "La biblioteca esta vacia, no hay libros cargados"<< endl;
        return;
    }
    int puntajes[6] = {0,0,0,0,0,0};
    float cantiadaes[6] ={0,0,0,0,0,0};
    size_t cantidad_de_maximos=0; 
    size_t indices[6];
    for (size_t i = 0; i < biblioteca->cantidad_de_libros; i++) // obtengo los valores totales 
    {
        if( biblioteca->lista_de_libros[i]->genero ==generos_inicial[AVENTURA])
        {
            puntajes[AVENTURA] +=  biblioteca->lista_de_libros[i]->puntaje;
            cantiadaes[AVENTURA]++;
        }
            
        if( biblioteca->lista_de_libros[i]->genero ==generos_inicial[CIENCIA_FICCION])
        {    
            puntajes[CIENCIA_FICCION] += biblioteca->lista_de_libros[i]->puntaje;
            cantiadaes[CIENCIA_FICCION]++;
        }
        if( biblioteca->lista_de_libros[i]->genero ==generos_inicial[DIDACTICO])
        {
            puntajes[DIDACTICO] += biblioteca->lista_de_libros[i]->puntaje;
            cantiadaes[DIDACTICO]++;
        }
        if( biblioteca->lista_de_libros[i]->genero ==generos_inicial[POLICIACA])
        {
            puntajes[POLICIACA] += biblioteca->lista_de_libros[i]->puntaje;
            cantiadaes[POLICIACA]++;
        }
            
        if( biblioteca->lista_de_libros[i]->genero ==generos_inicial[ROMANCE])
        {
            puntajes[ROMANCE] += biblioteca->lista_de_libros[i]->puntaje;
            cantiadaes[ROMANCE]++;
        }   
        if( biblioteca->lista_de_libros[i]->genero ==generos_inicial[TERROR])
        {
            puntajes[TERROR] += biblioteca->lista_de_libros[i]->puntaje;
            cantiadaes[TERROR]++;
        }    
    }
    float puntajes_promedio[6];
    for (size_t i = 0; i < 6; i++) // hago el promedio de cada genero
    {
        puntajes_promedio[i] = (float)puntajes[i]/cantiadaes[i];
    }
    
    //recorro el vector para ver los maximos si hay varios
    float maximo=-1;
    for (size_t i = 0; i < 6; i++)
    {
        if (puntajes_promedio[i] > maximo)
        {
            maximo=puntajes_promedio[i];
            cantidad_de_maximos = 0;
        }
        if (puntajes_promedio[i] == maximo) 
        {
            indices[cantidad_de_maximos] = i;
            cantidad_de_maximos++;
        } 
    }
    if (cantidad_de_maximos == 1)
    {
        cout << "El genero con mejor puntaje es: "<<endl;    
    }
    else
    {
        cout << "Los generos más puntajes son: "<<endl;
    
    }
    for (size_t i = 0; i < cantidad_de_maximos; i++)
    {
        cout << generos[indices[i]] << endl;
    }
    cout << "con un promedio de " << maximo << endl; 

};


void cargar_biblioteca(Biblioteca* biblioteca)
{
    //abro el archivo

    ifstream archivo_libros(RUTA_LIBROS); // buscar ios::in // re veer esto 
        if(!archivo_libros.is_open())
        {
        cout << "No se encontro un archivo con nombre \"" << RUTA_LIBROS << "\", se va a crear el archivo" << endl;
        archivo_libros.open(RUTA_LIBROS);
        archivo_libros.close();
        archivo_libros.open(RUTA_LIBROS);
        }

    string nombre, genero, puntaje_caracter;
    char delimitador=',';

    while(!archivo_libros.eof())
    {
        getline(archivo_libros,nombre, delimitador); 
        getline(archivo_libros,genero, delimitador); 
        getline(archivo_libros,puntaje_caracter); 
        Libro* libro = crear_libro(nombre,genero,stoi(puntaje_caracter));
        agregar_libro(biblioteca,libro);
    }

    archivo_libros.close();


};


void escribir_biblioteca(Biblioteca* biblioteca)
{
    ofstream archivo_libros(RUTA_LIBROS); 
    if(!archivo_libros.is_open())
    {
        cout << "No se encontro un archivo con nombre \"" << RUTA_LIBROS << "\", se va a crear el archivo" << endl;
        archivo_libros.open(RUTA_LIBROS);
        archivo_libros.close();
        archivo_libros.open(RUTA_LIBROS);
    }
    
    for (size_t i = 0; i < biblioteca->cantidad_de_libros-1; i++)
    {
        archivo_libros << biblioteca->lista_de_libros[i]->nombre << ',' 
                        << biblioteca->lista_de_libros[i]->genero << ',' 
                        << biblioteca->lista_de_libros[i]->puntaje << endl;
        
    }
    
    archivo_libros << biblioteca->lista_de_libros[biblioteca->cantidad_de_libros-1]->nombre << ',' 
                        << biblioteca->lista_de_libros[biblioteca->cantidad_de_libros-1]->genero << ',' 
                        << biblioteca->lista_de_libros[biblioteca->cantidad_de_libros-1]->puntaje;

        archivo_libros.close();
};


void editar_puntaje(Biblioteca* biblioteca, string nombre, int puntaje)
{
    if(biblioteca->cantidad_de_libros==0)
    {
        cout << "La biblioteca esta vacia, no hay libros cargados"<< endl;
        return;
    }
    
    while (!_esta_libro(biblioteca,nombre))
    {
        cout << "El libro no está cargado en la bibilioteca "<< endl;
        cout << "Por favor ingrese nuevamente el nombre"<< endl;
        getline(cin, nombre);    
    }

    size_t i = _buscar_libro(biblioteca,nombre);

    _cambiar_puntaje(biblioteca->lista_de_libros[i], puntaje);

}