#include <iostream>
#include <string>
#include <cctype>
#include "csv_manage_link.h"

using namespace std;

#define ACEPTED_INPUTS_MAX 8
#define ACEPTED_GENRE_MAX 6

const char ACEPTED_INPUTS[ACEPTED_INPUTS_MAX] = {'1', '2', '3', '4', '5', '6', '7', '8'};
const char ACEPTED_GENRE[ACEPTED_GENRE_MAX] = {'A', 'C', 'D', 'P', 'R', 'T'};

bool validate_input(char *input)
{
    bool is_valid = false;
    for (int i = 0; i < ACEPTED_INPUTS_MAX; i++)
    {
        if (ACEPTED_INPUTS[i] == *input)
        {
            is_valid = true;
        }
    }
    return is_valid;
}

bool validate_genre(char *genre){
    bool is_valid = false;
    for (int i = 0; i < ACEPTED_GENRE_MAX; i++)
    {
        if (ACEPTED_GENRE[i] == toupper(*genre))
        {
            is_valid = true;
        }
    }
    return is_valid;
}

void list_read_books(BookData *&books_data, int &books_top)
{
    cout << "\nEstos son tus libros:" << endl;
    for (int j = 0; j < books_top; j++)
    {
        cout << "---------------------------\n"
             << "Nombre: " << books_data[j].name << endl;
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

void add_book(BookData *&books_data, int &books_top, int &max_books)
{
    string title;
    char genre;
    int score;

    bool is_valid_title = true;

    cout << "Ingrese el titulo del libro: ";
    getline(cin >> ws, title);
    
    int i = 0;
    while(i < books_top && is_valid_title != false){
        if(title == books_data[i].name){
            is_valid_title = false;
        }
        i++;
    }

    if(!is_valid_title){
        cout << "El titulo ya esta en la lista" << endl;
    }
    else{
        cout << "A: Aventura - C: Ciencia Ficcion - D: Didactica - P: Policiaca - R: Romance - T: Terror\nIngrese el genero del libro: ";
        cin >> genre;
        while(validate_genre(&genre) == false){
            cout << "Ingrese un genero valido: ";
            cin >> genre;
        }
        cout << "Ingrese el puntaje (0-100): ";
        cin >> score;
        while(score > 100 || score < 0){
            cout << "Ingrese un puntaje valido: ";
            cin >> score;
        }

        cout << title << " - " << (char)toupper(genre) << " - " << score << endl;
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