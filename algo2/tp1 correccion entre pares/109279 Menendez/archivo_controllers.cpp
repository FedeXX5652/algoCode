#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAXIMO_LIBROS_INICIAL = 20;
const int AMPLIACION_DE_VECTOR = 10;
const int LIMITE_DE_PRECAUCION = 1;

const char AVENTURA = 'A';
const char TERROR = 'T';
const char ROMANCE = 'R';
const char CIENCIA_FICCION = 'C';
const char DIDACTICA = 'D';
const char POLICIACA = 'P';

const int POSICION_AVENTURA = 1;
const int POSICION_TERROR = 4;
const int POSICION_CIENCIA_FICCION = 2;
const int POSICION_POLICIACA = 0;
const int POSICION_DIDACTICA = 3;
const int POSICION_ROMANCE = 5;

const int PUNTAJE_MINIMO = 0;
const int PUNTAJE_MAXIMO = 100;

const int UNA_ACCION = 1;
const int NO_ENCONTRADO = -1;
const int DOS_DIGITOS = 2;
const int UN_GENERO = 1;
const int PRIMER_GENERO_FAVORITO = 0;
const int MAX_GENEROS = 6;
const int MARGEN_DE_PRECAUCION = 5;
const string NOMBRE_DEL_ARCHIVO = "libros.csv";
const string ERROR_APERTURA_ARCHIVO = "Ha habido un error al abrir el archivo.";
const int ERROR = -1;
const int DESFAZAJE_CANTIDAD_LIBROS = 1;
const int EXITO = 0;
const int LISTAR_LIBROS = 1;
const int AGREGAR_LIBRO = 2;
const int EDITAR_PUNTAJE = 3;
const int MOSTRAR_LIBRO_FAVORITO = 4;
const int MOSTRAR_LIBROS_DE_MENOR_PUNTAJE = 5;
const int MOSTRAR_GENERO_MAS_LEIDO = 6;
const int MOSTRAR_GENERO_FAVORITO = 7;
const int GUARDAR_Y_SALIR = 8;
const int CANTIDAD_DE_CARACTERES_A_IGNORAR = 100;

const int CANTIDAD_DE_LIBROS_A_LISTAR = 3;
const int UN_LIBRO = 1;
const int PRIMER_LIBRO_FAVORITO = 0;
const int TERCERA_POSICION = 2;
const int PRIMER_CARACTER = 0;
const int INTERCAMBIO = 1;
const int NO_INTERCAMBIO = 0;
const int SIN_APARICIONES = 0;

struct Libro{
    string titulo;
    char genero;
    int puntaje;
};

struct Genero {
    string nombre;
    int cantidad_de_apariciones;
    int puntaje_total;
    int promedio_puntaje_apariciones;
};

//Pre Debe recibir el vector de libros vacio, su tope por referencia (ya inicializado en 0) y el archivo abierto para leer
//Post Inicializa el vector de libros con lo leido del archivo.
void inicializar_libros(Libro* libros, int &tope_libros, fstream &archivo_libros){
    string linea;

    while(getline (archivo_libros, linea)){

        char vector_linea[linea.length()];
        strcpy(vector_linea, linea.c_str());

        char* partes = strtok(vector_linea, ",");
        if(partes) libros[tope_libros].titulo = partes;

        partes = strtok(nullptr, ",");
        if(partes) libros[tope_libros].genero = *partes;

        partes = strtok(nullptr, ",");
        if(partes) libros[tope_libros].puntaje = stoi(partes);

        tope_libros++;
    }
}

int leer_archivo(Libro* libros, int &tope_libros){
    fstream archivo_libros;
    archivo_libros.open(NOMBRE_DEL_ARCHIVO, ios::in);

    if(archivo_libros.is_open()){
        inicializar_libros(libros, tope_libros, archivo_libros);
    }else {
        cout << ERROR_APERTURA_ARCHIVO;
        return ERROR;
    }

    archivo_libros.close();
    return EXITO;
}

bool respuesta_es_valida(int respuesta){
    return(respuesta == LISTAR_LIBROS || respuesta == AGREGAR_LIBRO || respuesta == EDITAR_PUNTAJE || respuesta == MOSTRAR_LIBRO_FAVORITO || respuesta == MOSTRAR_LIBROS_DE_MENOR_PUNTAJE || respuesta == MOSTRAR_GENERO_MAS_LEIDO || respuesta == MOSTRAR_GENERO_FAVORITO || respuesta == GUARDAR_Y_SALIR);
}

//Pre Debe recibir la cantidad de acciones ejecutadas por el usuario
//Post Imprime por consola el menu de acciones para el usuario
int abrir_menu(int &cantidad_acciones){
    int respuesta;

    cout << endl;

    if(cantidad_acciones == UNA_ACCION){
        cout << "Bienvenido al gestor de libros leidos. Elija una opcion:" << endl;
    } else {
        cout << "Elija una opcion:" << endl;
    }

    cout << "Ingrese 1 para listar libros leidos" << endl;
    cout << "Ingrese 2 para agregar un nuevo libro leido" << endl;
    cout << "Ingrese 3 para editar el puntaje de un libro" << endl;
    cout << "Ingrese 4 para mostrar el libro favorito" << endl;
    cout << "Ingrese 5 para listar los 3 libros de menor puntaje" << endl;
    cout << "Ingrese 6 para mostrar el genero mas leido" << endl;
    cout << "Ingrese 7 para mostrar el genero favorito" << endl;
    cout << "Ingrese 8 para guardar y salir" << endl;
    cout << "Porfavor, seleccione una opcion:  ";
    cin >> respuesta;
    cout << endl;

    while(!respuesta_es_valida(respuesta)){
        cout << "El valor ingresado es invalido. Porfavor seleccione una opcion dentro de las dadas:  ";
        cin.clear();
        cin.ignore(CANTIDAD_DE_CARACTERES_A_IGNORAR, '\n');
        cin >> respuesta;
        cout << endl;
    }

    cantidad_acciones++;
    return respuesta;
}

//Pre Debe recibir el vector de libros y su tope
//Post Lista los libros leidos por consola
void listar_libros(Libro* libros, int tope_libros){
    cout << "Listado de libros leidos:" << endl;
    cout << endl;
    for(int i = 0; i < tope_libros; ++i){
        cout << i+DESFAZAJE_CANTIDAD_LIBROS << ". Titulo: " << libros[i].titulo << " - ";

        switch(libros[i].genero){
            case AVENTURA:
                cout << "Genero: " << "Aventura - ";
                break;

            case CIENCIA_FICCION:
                cout << "Genero: " << "Ciencia ficcion - ";
                break;

            case DIDACTICA:
                cout << "Genero: " << "Didactica - ";
                break;

            case POLICIACA:
                cout << "Genero: " << "Policiaca - ";
                break;

            case ROMANCE:
                cout << "Genero: " << "Romance - ";
                break;

            case TERROR:
                cout << "Genero: " << "Terror - ";
                break;
        }

        cout << "Puntaje: " << libros[i].puntaje << endl;
    }
}

//Pre Debe recibir el vector de libros, su tope, un vector de libros favoritos y su tope por referencia
//Post Calcula los libros favoritos y los incluye en el vector de libros favoritos
void calcular_libros_favoritos(Libro* libros, int tope_libros, Libro libros_favoritos[], int &tope_libros_favoritos){
    int mayor_puntaje = 0;

    for(int i = 0; i < tope_libros; ++i){
        if(libros[i].puntaje > mayor_puntaje) {
            mayor_puntaje = libros[i].puntaje;
            libros_favoritos[PRIMER_LIBRO_FAVORITO] = (libros)[i];
            tope_libros_favoritos = UN_LIBRO;
        } else if(libros[i].puntaje == mayor_puntaje){
            cout << i;
            libros_favoritos[tope_libros_favoritos] = (libros)[i];
            tope_libros_favoritos++;
        }
    }
}

//Pre Debe recibir el vector de libros y su tope.
//Post Muestra por pantalla los libros favoritos
void mostrar_libros_favoritos(Libro* libros, int tope_libros){
    Libro libros_favoritos[tope_libros];
    int tope_libros_favoritos = 0;

    calcular_libros_favoritos(libros, tope_libros, libros_favoritos, tope_libros_favoritos);

    if (tope_libros_favoritos == UN_LIBRO){
        cout << "El libro favorito es " << libros_favoritos[PRIMER_LIBRO_FAVORITO].titulo <<  " con un puntaje de " << libros_favoritos[PRIMER_LIBRO_FAVORITO].puntaje << endl;
    } else {
        cout << "Con un puntaje de " << libros_favoritos[PRIMER_LIBRO_FAVORITO].puntaje << ", los libros favoritos son:" << endl;
        for(int i = 0; i < tope_libros_favoritos; ++i){
            cout << i+DESFAZAJE_CANTIDAD_LIBROS << ". Titulo: " << libros_favoritos[i].titulo << endl;
        }
    }
}

//Pre Debe recibir dos libros por referencia
//Post Intercambia de lugar los dos libros recibidos
void intercambiar(Libro &primer_libro, Libro &segundo_libro){
    Libro libro_auxiliar = primer_libro;
    primer_libro = segundo_libro;
    segundo_libro = libro_auxiliar;

}

//Pre Debe recibir dos libros y el contador del for
//Post Devuelve el resulado de la comparacion. Es decir si hay que intercambiar los libros o no
int comparacion_de_puntajes(int contador, Libro primer_libro, Libro segundo_libro){
    int resultado = NO_INTERCAMBIO;

    if(primer_libro.puntaje > segundo_libro.puntaje) resultado = INTERCAMBIO;
    if(contador == TERCERA_POSICION && primer_libro.puntaje == segundo_libro.puntaje && primer_libro.titulo[PRIMER_CARACTER] > segundo_libro.titulo[PRIMER_CARACTER]) resultado = INTERCAMBIO;

    return resultado;
}

//Pre Debe recibir el vector de libros, su tope, un vector de libros ordenados por menor puntaje y su tope por referencia
//Post Ordena los libros por menor puntaje
void ordenar_libros_por_menor_puntaje(Libro* libros, int tope_libros, Libro libros_ordenados_menor_puntaje[], int &tope_libros_ordenados_menor_puntaje){
    for(int i = 0; i < tope_libros; ++i){
        libros_ordenados_menor_puntaje[i] = (libros)[i];
    }
    tope_libros_ordenados_menor_puntaje = tope_libros;


    for(int i = 0; i < tope_libros_ordenados_menor_puntaje; i++){
        for(int j = 0; j < (tope_libros_ordenados_menor_puntaje - DESFAZAJE_CANTIDAD_LIBROS); j++){
            int resultado_comparacion = comparacion_de_puntajes(j, libros_ordenados_menor_puntaje[j], libros_ordenados_menor_puntaje[j+1]);
            if(resultado_comparacion == INTERCAMBIO){
                intercambiar(libros_ordenados_menor_puntaje[j], libros_ordenados_menor_puntaje[j+1]);
            }
        }
    }
}

//Pre Debe recibir el vecto de libros y su tope
//Post Muestra por pantalla los 3 libros de menor puntaje
void mostrar_libros_de_menor_puntaje(Libro* libros, int tope_libros){
    Libro libros_ordenados_menor_puntaje[tope_libros + MARGEN_DE_PRECAUCION];
    int tope_libros_ordenados_menor_puntaje = 0;

    ordenar_libros_por_menor_puntaje(libros, tope_libros, libros_ordenados_menor_puntaje, tope_libros_ordenados_menor_puntaje);

    int contador = 0;
    cout << "Los libros de menor puntaje son: " << endl;
    while(contador < CANTIDAD_DE_LIBROS_A_LISTAR && contador <= tope_libros_ordenados_menor_puntaje - DESFAZAJE_CANTIDAD_LIBROS){
        cout << contador + DESFAZAJE_CANTIDAD_LIBROS << ". Titulo: " << libros_ordenados_menor_puntaje[contador].titulo << " - Puntaje: " << libros_ordenados_menor_puntaje[contador].puntaje << endl;
        contador++;
    }
}

//Pre Debe recibir un vector de generos no inicializado y su tope por referencia
//Post Inicializa el vector de generos
void inicializar_generos(Genero generos[], int &tope_generos){
    generos[POSICION_POLICIACA].nombre = "Policiaco";
    generos[POSICION_AVENTURA].nombre = "Aventura";
    generos[POSICION_CIENCIA_FICCION].nombre = "Ciencia ficcion";
    generos[POSICION_DIDACTICA].nombre = "Didactica";
    generos[POSICION_TERROR].nombre = "Terror";
    generos[POSICION_ROMANCE].nombre = "Romance";

    tope_generos = MAX_GENEROS;

    for(int i = 0; i < tope_generos; ++i){
        generos[i].cantidad_de_apariciones = 0;
        generos[i].puntaje_total = 0;
        generos[i].promedio_puntaje_apariciones = 0;
    }
}

//Pre Debe recibir el vector de libros, su tope y el vector de generos
//Post Setea la cantidad de apariciones de cada genero
void calcular_apariciones_generos(Libro* libros, int tope_libros, Genero generos[]){
    for(int i = 0; i < tope_libros; ++i){
        switch(libros[i].genero){
            case POLICIACA:
                generos[POSICION_POLICIACA].cantidad_de_apariciones++;
                break;

            case AVENTURA:
                generos[POSICION_AVENTURA].cantidad_de_apariciones++;
                break;

            case CIENCIA_FICCION:
                generos[POSICION_CIENCIA_FICCION].cantidad_de_apariciones++;
                break;

            case DIDACTICA:
                generos[POSICION_DIDACTICA].cantidad_de_apariciones++;
                break;

            case TERROR:
                generos[POSICION_TERROR].cantidad_de_apariciones++;
                break;

            case ROMANCE:
                generos[POSICION_ROMANCE].cantidad_de_apariciones++;
                break;
        }
    }
}

//Pre Debe recibir el vector de libros, junto a su tope, el vector de generos y su tope
//Post Define cual es el genero con mas apariciones y devuelve el num de apariciones.
int calcular_maximo_apariciones(Libro* libros, int tope_libros, Genero generos[], int tope_generos){
    calcular_apariciones_generos(libros, tope_libros, generos);
    int maximo_apariciones = 0;

    for(int j = 0; j < tope_generos; ++j){
        if(generos[j].cantidad_de_apariciones > maximo_apariciones){
            maximo_apariciones = generos[j].cantidad_de_apariciones;
        }
    }

    return maximo_apariciones;
}

//Pre Debe recibir el vector de libros y su tope
//Post Muestra por pantalla el/los generos mas leidos
void mostrar_genero_mas_leido(Libro* libros, int tope_libros){
    Genero generos[MAX_GENEROS + MARGEN_DE_PRECAUCION];
    int tope_generos;
    inicializar_generos(generos, tope_generos);
    int maximo_apariciones = calcular_maximo_apariciones(libros, tope_libros, generos, tope_generos);

    cout << "Con " << maximo_apariciones <<" apariciones cada, el/los generos mas leidos son: " << endl;
    for(int i = 0; i < tope_generos; ++i){
        if(generos[i].cantidad_de_apariciones == maximo_apariciones){
            cout << generos[i].nombre << endl;
        }
    }
}

//Pre Debe recibir el vector de libros, su tope y un vector de generos
//Post Setea los puntajes totales de cada genero.
void calcular_puntaje_generos(Libro* libros, int tope_libros, Genero generos[]){
    for(int i = 0; i < tope_libros; ++i){
        switch(libros[i].genero){
            case POLICIACA:
                generos[POSICION_POLICIACA].puntaje_total = generos[POSICION_POLICIACA].puntaje_total + libros[i].puntaje;
                break;

            case AVENTURA:
                generos[POSICION_AVENTURA].puntaje_total = generos[POSICION_AVENTURA].puntaje_total + libros[i].puntaje;
                break;

            case CIENCIA_FICCION:
                generos[POSICION_CIENCIA_FICCION].puntaje_total = generos[POSICION_CIENCIA_FICCION].puntaje_total + libros[i].puntaje;
                break;

            case DIDACTICA:
                generos[POSICION_DIDACTICA].puntaje_total = generos[POSICION_DIDACTICA].puntaje_total + libros[i].puntaje;
                break;

            case TERROR:
                generos[POSICION_TERROR].puntaje_total = generos[POSICION_TERROR].puntaje_total + libros[i].puntaje;
                break;

            case ROMANCE:
                generos[POSICION_ROMANCE].puntaje_total = generos[POSICION_ROMANCE].puntaje_total + libros[i].puntaje;
                break;
        }
    }
}

//Pre Debe recibir el vector de generos y su tope
//Post Setea el promedio de cada genero
void calcular_promedio_generos(Genero generos[], int tope_generos){
    for(int i = 0; i < tope_generos; ++i){
        if(generos[i].cantidad_de_apariciones != SIN_APARICIONES) generos[i].promedio_puntaje_apariciones = (generos[i].puntaje_total / generos[i].cantidad_de_apariciones);
    }
}

//Pre Debe recibir el vector de generos, su tope, el vector de generos favoritos y su tope por referencia
//Post Calcula los generos favoritos entre los libros incluidos y los incluye al vector de generos favoritos
void calcular_generos_favoritos(Genero generos[], int tope_generos, Genero generos_favoritos[], int &tope_generos_favoritos){
    int mayor_promedio = 0;

    for(int i = 0; i < tope_generos; ++i){
        if(generos[i].promedio_puntaje_apariciones > mayor_promedio){
            mayor_promedio = generos[i].promedio_puntaje_apariciones;
            generos_favoritos[PRIMER_GENERO_FAVORITO] = generos[i];
            tope_generos_favoritos = UN_GENERO;
        } else if(generos[i].promedio_puntaje_apariciones == mayor_promedio){
            generos_favoritos[tope_generos_favoritos] = generos[i];
            tope_generos_favoritos++;
        }
    }
}

//Pre De recibir el vector de libros y su tope
//Post Muestra por consola el genero o los generos favoritos
void mostrar_genero_favorito(Libro* libros, int tope_libros){
    Genero generos[MAX_GENEROS + MARGEN_DE_PRECAUCION];
    int tope_generos;
    inicializar_generos(generos, tope_generos);
    Genero generos_favoritos[MAX_GENEROS + MARGEN_DE_PRECAUCION];
    int tope_generos_favoritos = 0;

    calcular_apariciones_generos(libros, tope_libros, generos);
    calcular_puntaje_generos(libros, tope_libros, generos);
    calcular_promedio_generos(generos, tope_generos);
    calcular_generos_favoritos(generos, tope_generos, generos_favoritos, tope_generos_favoritos);

    cout << "El/los generos favoritos son:" << endl;
    for(int i = 0; i < tope_generos_favoritos; ++i){
        cout << generos_favoritos[i].nombre << endl;
    }
}

//Pre Debe recibir un titulo, el vector de libros y su tope
//Post Devuelve false si el titulo todavia no esta incluido y true en caso contrario
bool libro_ya_esta_incluido(string titulo, Libro* libros,int tope_libros){
    bool esta_incluido = false;

    for(int i = 0; i < tope_libros; ++i){
        if(libros[i].titulo == titulo) esta_incluido = true;
    }

    return esta_incluido;
}

//Pre Debe recibir el vector de libros y su tope.
//Post Pide el titulo de un libro nuevo y luego lo devuelve
string pedir_titulo_de_libro(Libro* libros,int tope_libros){
    string titulo;

    cout << "Porfavor, ingrese el titulo del nuevo libro que desea ingresar: ";
    getline(cin >> ws, titulo);

    while(libro_ya_esta_incluido(titulo, libros, tope_libros)){
        cout << "Usted ha ingresado un libro que ya existe dentro del listado. Porfavor, ingrese uno diferente: ";
        getline(cin >> ws, titulo);
    }

    return titulo;
}

//Pre Debe recibir un puntaje
//Post Devuelve false si es puntaje es valido y true si no es valido
bool puntaje_no_valido(string puntaje){
    bool no_valido = false;

    if(puntaje.length() > DOS_DIGITOS){
        no_valido = true;
    } else {
        for(int i = 0; i < puntaje.length(); ++i){
            if(!isdigit(puntaje[i])) no_valido = true;
        }
    }

    if(!no_valido) no_valido = (stoi(puntaje) < PUNTAJE_MINIMO || stoi(puntaje) > PUNTAJE_MAXIMO);

    return no_valido;
}

//Pre
//Post Pide un puntaje de libro al usuario y lo devuelve
int pedir_puntaje_de_libro(){
    string puntaje;

    cout << "Porfavor, ingrese el puntaje del libro: ";
    cin >> puntaje;

    while(puntaje_no_valido(puntaje)){
        cout << "Usted ha ingresado un puntaje invalido. Porfavor, ingrese uno dentro del rango 0-100: ";
        cin >> puntaje;
    }

    return stoi(puntaje);
}

//Pre debe recibir un string correspondiente a un genero
//Post Devuelve true en caso de que sea un genero valido y false en caso contrario
bool genero_valido(string genero){
    return (genero == "R" || genero == "A" || genero == "T" || genero == "C" || genero == "D" || genero == "P" || genero == "Ciencia ficcion" || genero == "Terror" || genero ==
                                                                                                                                                                       "Didactica" || genero == "Aventura" || genero == "Romance" || genero == "Policiaca");
}

//Pre
//Post Pide un genero al usuario y se asegura que sea valido, para luego devolver solo el primer caracter.
char pedir_genero_de_libro(){
    string genero;
    cout << "Para el genero del libro, usted puede ingresar la forma completa (Romance) o abreviada (R). Porfavor, asegurese que su primera letra SIEMPRE este en mayuscula y de cumplir "
            "con los generos permitidos." <<
         endl;
    cout << "Porfavor, ingrese el genero del nuevo libro que desea ingresar: ";
    getline(cin >> ws, genero);

    while(!genero_valido(genero)){
        cout << "Usted a ingresado un genero invalido. Porfavor, ingrese uno valido: ";
        getline(cin >> ws, genero);
    }

    return genero[PRIMER_CARACTER];
}

//Pre Debe recibir el puntero del vector libros po referencia, su tope y el maximo del vector por referencia
//Post Amplia el tamaño maximo del vector
void ampliar_tamanio_vector(Libro* &libros, int tope_libros, int &maximo_libros){
    maximo_libros += AMPLIACION_DE_VECTOR;
    Libro* nuevos_libros = new Libro[maximo_libros];

    for(int i = 0; i < tope_libros; ++i){
        nuevos_libros[i] = libros[i];
    }

    delete [] libros;
    libros = nuevos_libros;
}

//Pre Debe recibir el putero de libros por referencia, junto a su tope tambien por referencia y el maximo del vector de libros, tambien por referencia
//Post Agrega un libro ingresado por el usuario al vector
void agregar_libro(Libro*  &libros,int &tope_libros, int &maximo_libros){
    Libro nuevo_libro;
    nuevo_libro.titulo = pedir_titulo_de_libro(libros, tope_libros);
    nuevo_libro.puntaje = pedir_puntaje_de_libro();
    nuevo_libro.genero = pedir_genero_de_libro();

    libros[tope_libros] = nuevo_libro;
    tope_libros++;

    if(tope_libros == maximo_libros - LIMITE_DE_PRECAUCION) ampliar_tamanio_vector(libros, tope_libros, maximo_libros);
}

//Pre Debe recibir el titulo ingresado por el usuario (siendo este un titulo valido), el vector de libros y su tope
//Post Devuelve la posicion en el vector de libros del libro buscado
int encontrar_posicion_libro(string titulo, Libro libros[], int tope_libros){
    int posicion = NO_ENCONTRADO;

    for(int i = 0; i < tope_libros; ++i){
        if(libros[i].titulo == titulo) posicion = i;
    }

    return posicion;
}

//Pre Debe recibir el vector de libros y su tope
//Post Devuelve la posicion del libro que el usuario desea editar
int pedir_titulo_libro_a_editar(Libro libros[], int tope_libros){
    string titulo;
    cout << "Porfavor, ingrese el titulo del libro al que desea editar el puntaje: ";
    getline(cin >> ws, titulo);


    int posicion = encontrar_posicion_libro(titulo, libros, tope_libros);
    while(posicion == NO_ENCONTRADO){
        posicion = encontrar_posicion_libro(titulo, libros, tope_libros);
        cout << "Usted a ingresado un titulo de un libro inexistente en el listado. Porfavor, ingrese un titulo valido:  ";
        getline(cin >> ws, titulo);
    }

    return posicion;
}

//Pre Debe recibir el vector de libros y su tope
//Post Edita el puntaje del libro que el usuario busca modificar
void editar_puntaje_libro(Libro libros[], int tope_libros){
    int posicion_del_libro_buscado = pedir_titulo_libro_a_editar(libros, tope_libros);
    libros[posicion_del_libro_buscado].puntaje = pedir_puntaje_de_libro();
}

//Pre debe recibir el vector de libros y su tope
//Post sobreescribe el archivo con los cambios hechos.
void guardar_y_salir(Libro libros[], int tope_libros){
    ofstream libros_file("libros.csv");

    for(int i = 0; i < tope_libros; ++i){
        libros_file << libros[i].titulo << "," <<libros[i].genero << "," << libros[i].puntaje << "\n";
    }

    libros_file.close();
}

//Pre Debe recibir una opcion elegida, el vector de libros, su tope inicializado y el maximo del vector
//Post Activa las debidas funciones para ejecutar al accion del usuario
void activar_opcion_elegida(int opcion_elegida, Libro* &libros, int &tope_libros, int &maximo_libros){
    switch(opcion_elegida){
        case LISTAR_LIBROS:
            listar_libros(libros, tope_libros);
            break;

        case AGREGAR_LIBRO:
            agregar_libro(libros, tope_libros, maximo_libros);
            break;

        case EDITAR_PUNTAJE:
            editar_puntaje_libro(libros, tope_libros);
            break;

        case MOSTRAR_LIBRO_FAVORITO:
            mostrar_libros_favoritos(libros, tope_libros);
            break;

        case MOSTRAR_LIBROS_DE_MENOR_PUNTAJE:
            mostrar_libros_de_menor_puntaje(libros, tope_libros);
            break;

        case MOSTRAR_GENERO_MAS_LEIDO:
            mostrar_genero_mas_leido(libros, tope_libros);
            break;

        case MOSTRAR_GENERO_FAVORITO:
            mostrar_genero_favorito(libros, tope_libros);
            break;

        case GUARDAR_Y_SALIR:
            guardar_y_salir(libros, tope_libros);
            break;
    }
}

//Pre
//Post Imprime el mensaje de despedida al usuario
void imprimir_mensaje_despedida(){
    cout << "Guardando y saliendo..." << endl;
}
