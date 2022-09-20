#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>

#include "csv_manage_link.h"
#include "functions_link.h"

using namespace std;

const int WORST_QTY = 3;

// https://campus.fi.uba.ar/pluginfile.php/527918/mod_resource/content/1/El%20eterno%20dilema%20del%20lector.pdf
// entregar como: 109435_Galante_TP1.zip
// compilar con g++ *.cpp -Wall -Werror -Wconversion

/*
pre: -
post: -
*/
int main()
{
    int max_books = 10;
    int books_top = 0;
    bool is_exit = false;
    string input;
    BookData *books_data = new BookData[max_books];

    read_csv(books_data, books_top, max_books);

    while (!is_exit)
    {
        cout << "\nIngrese la accion a realizar:\n\t1. Listar libros leidos.\n\t2. Agregar libro.\n\t3. Editar puntaje de un libro por titulo.\n\t4. Mostrar libro favorito.\n\t5. Mostrar los " << WORST_QTY << " libros con menor puntaje.\n\t6. Mostrar genero mas leido.\n\t7. Mostrar genero favorito.\n\t8. Guardar y salir." << endl;
        cin >> input;

        while (validate_input(input) == false)
        {
            cout << "Ingrese una opcion valida: ";
            cin >> input;
        }

        if (input == "1"){
            list_read_books(books_data, books_top);
        }
        else if (input == "2")
        {
            add_book(books_data, books_top, max_books);
        }
        else if (input == "3")
        {
            edit_score(books_data, books_top);
        }
        else if (input == "4")
        {
            show_favorite(books_data, books_top);
        }
        else if (input == "5")
        {
            show_worst(books_data, books_top, WORST_QTY);
        }
        else if (input == "6")
        {
            show_most_read_genre(books_data, books_top);
        }
        else if (input == "7")
        {
            show_favorite_genre(books_data, books_top);
        }
        else if (input == "8")
        {
            read_csv(books_data, books_top);
            is_exit = true;
        }
        else{
            cout << "Error: input invalida" << endl;
            is_exit = true;
        }
    }

    delete[] books_data;
    cout << "Cerrando app";
    return 0;
}