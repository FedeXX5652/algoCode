#include <iostream>
#include <string>
#include "csv_manage_link.h"

using namespace std;

#define ACEPTED_INPUTS_MAX 8

const char ACEPTED_INPUTS[ACEPTED_INPUTS_MAX] = {'1', '2', '3', '4', '5', '6', '7', '8'};

bool is_valid_input(char *input)
{
    for (int i = 0; i < ACEPTED_INPUTS_MAX; i++)
    {
        if (ACEPTED_INPUTS[i] == *input)
        {
            return true;
        }
    }
    return false;
}

void list_read_books(BookData *&books_data, int &books_top)
{
    cout << "\nEstos son tus libros:" << endl;
    for (int j = 0; j < books_top; j++)
    {
        cout << "---------------------------\n" << "Nombre: " << books_data[j].name << endl;
        switch (books_data[j].genre)
        {
        case 'A':
            cout << "Genero: Aventura" << endl;
            break;
        case 'C':
            cout << "Genero: Ciencia Ficcion" << endl;
            break;
        case 'D':
            cout << "Genero: Didactica" << endl;
            break;
        case 'P':
            cout << "Genero: Policiaca" << endl;
            break;
        case 'R':
            cout << "Genero: Romance" << endl;
            break;
        case 'T':
            cout << "Genero: Terror" << endl;
            break;
        default:
            cout << "Genero: Invalido" << endl;
            break;
        }
        cout << "Puntaje: " << books_data[j].score << endl;
    }
}

void vector_resize(BookData *&books_data, int &max_books)
{
    int new_size = max_books * 2;
    BookData *books_data_resize = new BookData[new_size];

    for (int j = 0; j < max_books; j++)
    {
        books_data_resize[j].name = books_data[j].name;
        books_data_resize[j].genre = books_data[j].genre;
        books_data_resize[j].score = books_data[j].score;
    }

    max_books = new_size;
    delete[] books_data; // no se si esto deletea bien o no
    books_data = books_data_resize;
}