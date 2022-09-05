#include <iostream>
#include <string>
#include <unistd.h>

#include "csv_manage_link.h"
#include "functions_link.h"

using namespace std;

// https://campus.fi.uba.ar/pluginfile.php/527918/mod_resource/content/1/El%20eterno%20dilema%20del%20lector.pdf
// entregar como: 109435_Galante_TP1.zip
// compilar con g++ *.cpp -Wall -Werror -Wconversion

int main()
{
    int max_books = 10;
    int books_top = 0;
    bool is_exit = false;
    char input;
    BookData *books_data = new BookData[max_books];

    read_csv(books_data, books_top, max_books);

    while (!is_exit)
    {
        cout << "\nIngrese la accion a realizar:\n1. Listar libros leidos.\n2. Agregar libro.\n3. Editar puntaje de un libro por titulo.\n4. Mostrar libro favorito.\n5. Mostrar los 3 libros con menor puntaje.\n6. Mostrar genero mas leido.\n7. Mostrar genero favorito.\n8. Guardar y salir." << endl;
        cin >> input;

        while (validate_input(&input) == false)
        {
            cout << "Ingrese una opcion valida: ";
            cin >> input;
        }

        switch (input)
        {
        case '1': // list read books
            list_read_books(books_data, books_top);
            break;
        case '2': // add book
            add_book(books_data, books_top, max_books);
            break;
        case '3': // edit score
            edit_score(books_data, books_top);
            break;
        case '4': // show favorite
            show_favorite(books_data, books_top);
            break;
        case '5': // show 3 worst
            break;
        case '6': // show most read genre
            break;
        case '7': // show favorit genre
            break;
        case '8': // save and exit
            is_exit = true;
            break;

        default:
            break;
        }
    }

    delete[] books_data;
    cout << "Cerrando app";
    return 0;
}