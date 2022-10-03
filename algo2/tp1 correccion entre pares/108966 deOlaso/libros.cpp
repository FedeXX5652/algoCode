#include "libros.hpp"

#include <iostream>

// Libros

libro_t *libro_nuevo(string nombre, char genero, unsigned int puntaje)
{
    libro_t *l = new libro_t;
    l -> nombre = nombre;
    l -> genero = genero;
    l -> puntaje = puntaje;
    return l;
}

void lista_libros_mostrar_libro(lista_libros_t *mis_libros, int indice)
{
    libro_t *mi_libro = mis_libros -> ls[indice];
    cout << "|   #" << indice + 1 << " - '"
         << mi_libro -> nombre << "', " 
         << genero_a_representacion(mi_libro -> genero) << ", " 
         << mi_libro -> puntaje << endl;
}

libro_t *recibir_nuevo_libro(lista_libros_t *mis_libros)
{
    string nuevo_nombre = "";
    string nuevo_genero;
    string nuevo_puntaje;

    // Nombre
    cout << "|   Ingresa un nombre para tu nuevo libro:" << endl;

    while(nuevo_nombre == "")
    {
        cin.ignore();
        getline(cin, nuevo_nombre);
    }

    if(buscar_libro_en_lista_libros(nuevo_nombre, mis_libros) != ERROR)
    {
        cout << "|   No se ha podido agregar el libro ya que uno con el mismo nombre ya existe en la lista." << endl;
        return NULL;
    }

    // Género
    cout << "|   Ingresa un género para tu nuevo libro:" << endl
         << "|   (A -> Aventura, C -> Ciencia Ficción, D -> Didáctica, P -> Policíaca, R -> Romance, T -> Terror)" << endl;

    cin >> nuevo_genero;
    char nuevo_genero_c = (char) toupper(nuevo_genero.c_str()[0]);

    if(genero_a_representacion(nuevo_genero_c) == ERROR_STRING)
    {
        cout << "|   Ingresaste un género inválido. Podes ver los géneros disponibles con '0'." << endl;
        return NULL;
    }

    // Puntaje
    cout << "|   Ingresa un puntaje para tu nuevo libro:" << endl;

    cin >> nuevo_puntaje;
    unsigned int nuevo_puntaje_uint = (unsigned int) stoi(nuevo_puntaje);

    if(nuevo_puntaje_uint > 100)
    {
        cout << "|   Ingresaste un puntaje inválido. Los valores de puntajes van de 0 a 100 inclusive." << endl;
        return NULL;
    }

    return libro_nuevo(nuevo_nombre, nuevo_genero_c, nuevo_puntaje_uint);
}

void lista_libros_agregar_libro(lista_libros_t *mis_libros, libro_t *nuevo_libro)
{
    libro_t **aux = new libro_t*[mis_libros -> n + 1];

    for(int i = 0; i < mis_libros -> n; i++)
        aux[i] = mis_libros -> ls[i];
    aux[mis_libros -> n] = nuevo_libro;

    if(mis_libros -> n != 0)
        delete[] mis_libros -> ls;

    mis_libros -> ls = aux;
    mis_libros -> n++;
}

bool lista_libros_esta_vacia(lista_libros_t *mis_libros)
{
    if(mis_libros -> n)
        return false;

    cout << "|   Tu biblioteca está vacía." << endl;
    return true;
}

int buscar_libro_en_lista_libros(string nombre, lista_libros_t *mis_libros)
{
    int i = 0;
    int indice = ERROR;
    bool encontrado = false;

    while(i < mis_libros -> n && !encontrado)
    {
        if(nombre == mis_libros -> ls[i] -> nombre)
        {
            indice = i;
            encontrado = true;
        }
        i++;
    }

    return indice;
}

void lista_libros_destruir(lista_libros_t *mis_libros)
{
    if(lista_libros_esta_vacia(mis_libros))
    {
        delete mis_libros;
        return;
    }

    for(int i = 0; i < mis_libros -> n; i++)
        delete mis_libros -> ls[i];

    delete[] mis_libros -> ls;
    delete mis_libros;
}

// Transformaciones del género

string genero_a_representacion(char genero)
{
    string representacion;
    switch(genero)
    {
        case 'A': representacion = "Aventura"; break;
        case 'C': representacion = "Ciencia Ficción"; break;
        case 'D': representacion = "Didáctica"; break;
        case 'P': representacion = "Policíaca"; break;
        case 'R': representacion = "Romance"; break;
        case 'T': representacion = "Terror"; break;
        default: representacion = ERROR_STRING;
    }
    return representacion;
}

char numero_a_genero(int numero)
{
    char genero;
    switch(numero)
    {
        case 0: genero = 'A'; break;
        case 1: genero = 'C'; break;
        case 2: genero = 'D'; break;
        case 3: genero = 'P'; break;
        case 4: genero = 'R'; break;
        case 5: genero = 'T'; break;
        default: genero = ERROR;
    }
    return genero;
}

int genero_a_numero(char genero)
{
    int numero;
    switch(genero)
    {
        case 'A': numero = 0; break;
        case 'C': numero = 1; break;
        case 'D': numero = 2; break;
        case 'P': numero = 3; break;
        case 'R': numero = 4; break;
        case 'T': numero = 5; break;
        default: numero = ERROR;
    }
    return numero;
}

// Comandos principales 

void mostrar_libros(lista_libros_t *mis_libros)
{
    if(lista_libros_esta_vacia(mis_libros))
        return;

    cout << "|   Lista de tus " << mis_libros -> n << " libros:" << endl;
    for(int i = 0; i < mis_libros -> n; i++)
        lista_libros_mostrar_libro(mis_libros, i);
}

void agregar_libro(lista_libros_t *mis_libros)
{
    libro_t *nuevo_libro = recibir_nuevo_libro(mis_libros);
    if(nuevo_libro == NULL)
        return;

    lista_libros_agregar_libro(mis_libros, nuevo_libro);

    cout << "|   Libro agregado exitosamente." << endl;
}

void editar_libro(lista_libros_t *mis_libros)
{
    string nombre;
    string nuevo_puntaje;

    cout << "|   Ingresa el nombre del libro a modificar:" << endl;
    
    cin.ignore();
    getline(cin, nombre);

    int indice = buscar_libro_en_lista_libros(nombre, mis_libros);
    if(indice == ERROR)
    {
        cout << "|   No se ha podido agregar el libro ya que su nombre no existe en la biblioteca." << endl;
        return;
    }

    cout << "|   Ingresa el nuevo puntaje de '" << nombre << "':" << endl;

    cin >> nuevo_puntaje;
    unsigned int nuevo_puntaje_uint = (unsigned int)stoi(nuevo_puntaje);

    if(nuevo_puntaje_uint > 100)
    {
        cout << "|   Ingresaste un puntaje inválido. Los valores de puntajes van de 0 a 100 inclusive." << endl;
        return;
    }

    mis_libros -> ls[indice] -> puntaje = nuevo_puntaje_uint;

    cout << "|   Libro modificado exitosamente." << endl;
}

void mostrar_mejor_libro(lista_libros_t *mis_libros)
{
    if(lista_libros_esta_vacia(mis_libros))
        return;

    unsigned int puntaje_mas_alto = 0;
    int indice_favorito = 0;

    for(int i = 0; i < mis_libros -> n; i++)
    {
        if(mis_libros -> ls[i] -> puntaje > puntaje_mas_alto)
        {
            puntaje_mas_alto = mis_libros -> ls[i] -> puntaje;
            indice_favorito = i;
        }
    }

    cout << "|   Tu libro favorito es:" << endl;
    lista_libros_mostrar_libro(mis_libros, indice_favorito);
}

void mostrar_peores_libros(lista_libros_t *mis_libros)
{
    if(lista_libros_esta_vacia(mis_libros))
        return;

    if(mis_libros -> n <= 3)
    {
        int j;
        int peores_indices[mis_libros -> n];
        unsigned int puntaje_actual;

        // Mini ordenamiento por inserción
        for(int i = 0; i < mis_libros -> n; i++)
        {
            j = i;
            puntaje_actual = mis_libros -> ls[i] -> puntaje;
            while(j > 0 && puntaje_actual < mis_libros -> ls[j - 1] -> puntaje)
            {
                peores_indices[j] = peores_indices[j - 1];
                j--;
            }
            peores_indices[j] = i;
        }

        cout << "|   Tus peores libros son:" << endl;
        for(int i = 0; i < mis_libros -> n; i++)
            lista_libros_mostrar_libro(mis_libros, peores_indices[i]);

        return;
    }

    int j;
    int peores_indices[3];
    unsigned int puntaje_actual;

    // Mini ordenamiento por inserción inicial
    for(int i = 0; i < 3; i++)
    {
        j = i;
        puntaje_actual = mis_libros -> ls[i] -> puntaje;
        while(j > 0 && puntaje_actual < (mis_libros -> ls[peores_indices[j - 1]] -> puntaje))
        {
            peores_indices[j] = peores_indices[j - 1];
            j--;
        }
        peores_indices[j] = i;
    }

    // Ordenamiento por inserción posta
    for(int i = 3; i < mis_libros -> n; i++)
    {
        puntaje_actual = mis_libros -> ls[i] -> puntaje;
        j = 2;

        // Si el puntaje actual es menor al más grande de los peores, entra
        if(puntaje_actual < mis_libros -> ls[peores_indices[j]] -> puntaje)
        {
            // Vemos en qué posicion entra, exactamente
            while(j > 0 && puntaje_actual < (mis_libros -> ls[peores_indices[j - 1]] -> puntaje))
            {
                peores_indices[j] = peores_indices[j - 1];
                j--;
            }
            peores_indices[j] = i;
        }
    }

    cout << "|   Tus peores libros son:" << endl;
    for(int i = 0; i < 3; i++)
        lista_libros_mostrar_libro(mis_libros, peores_indices[i]);
}

void mostrar_genero_mas_leido(lista_libros_t *mis_libros)
{
    if(lista_libros_esta_vacia(mis_libros))
        return;

    // Por cada ítem de la lista de libros, veo su género,
    // lo convierto a un número y hago ++ en el indice
    // apropiado de 'contador'.
    //                                A  C  D  P  R  T
    int contador[CANTIDAD_GENEROS] = {0, 0, 0, 0, 0, 0};
    for(int i = 0; i < mis_libros -> n; i++)
        contador[genero_a_numero(mis_libros -> ls[i] -> genero)]++;

    int cuenta_max = 0;
    for(int i = 0; i < CANTIDAD_GENEROS; i++)
    {
        if(contador[i] > cuenta_max)
            cuenta_max = contador[i];
    }

    cout << "|   Tu/s género/s mas leído/s:" << endl;
    for(int i = 0; i < CANTIDAD_GENEROS; i++)
    {
        if(contador[i] == cuenta_max)
            cout << "|   " << genero_a_representacion(numero_a_genero(i)) << endl;
    }
    cout << "|   Con una cantidad de " << cuenta_max << " libros leídos!" << endl;
}

void mostrar_genero_favorito(lista_libros_t *mis_libros)
{
    if(lista_libros_esta_vacia(mis_libros))
        return;

    // Por cada ítem de la lista de libros, veo su género,
    // lo convierto a un número y hago ++ en el índice
    // apropiado de 'contador'. También sumo su puntaje
    // en el índice apropiado de 'puntajes'.
    //                                A  C  D  P  R  T
    int contador[CANTIDAD_GENEROS] = {0, 0, 0, 0, 0, 0};
    int puntajes[CANTIDAD_GENEROS] = {0, 0, 0, 0, 0, 0};
    float promedios[CANTIDAD_GENEROS];

    for(int i = 0; i < mis_libros -> n; i++)
    {
        int j = genero_a_numero(mis_libros -> ls[i] -> genero);
        contador[j]++;
        puntajes[j] += mis_libros -> ls[i] -> puntaje;
    }

    float promedio_max = 0;
    for(int i = 0; i < CANTIDAD_GENEROS; i++)
    {
        if(contador[i] != 0)
            promedios[i] = (float) puntajes[i] / (float) contador[i];
        else
            promedios[i] = 0;

        if(promedios[i] > promedio_max)
            promedio_max = promedios[i];
    }

    cout << "|   Tu/s género/s favorito/s:" << endl;
    for(int i = 0; i < CANTIDAD_GENEROS; i++)
    {
        if(promedios[i] == promedio_max)
            cout << "|   " << genero_a_representacion(numero_a_genero(i)) << endl;
    }
    cout << "|   Con un promedio de " << promedio_max << " puntos!" << endl;
}
