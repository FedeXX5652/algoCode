#include <iostream>
#include <string>
#include <cctype>
#include "csv_manage_link.h"

using namespace std;

#define ACEPTED_INPUTS_MAX 8
#define ACEPTED_GENRE_MAX 6

const char ACEPTED_INPUTS[ACEPTED_INPUTS_MAX] = {'1', '2', '3', '4', '5', '6', '7', '8'};
const char GENRE_CHAR[ACEPTED_GENRE_MAX] = {'A', 'C', 'D', 'P', 'R', 'T'};
const string GENRE_FULL_NAME[ACEPTED_GENRE_MAX] = {"Accion", "Ciencia Ficcion", "Didactico", "Policiaco", "Romance", "Terror"};

void vector_resize(BookData *&books_data, int &max_books)
{
    int new_size = max_books * 2;
    BookData *books_data_resize = new BookData[new_size];

    for (int j = 0; j < max_books; j++)
    {
        books_data_resize[j].title = books_data[j].title;
        books_data_resize[j].genre = books_data[j].genre;
        books_data_resize[j].score = books_data[j].score;
    }

    max_books = new_size;
    delete[] books_data; // no se si esto deletea bien o no
    books_data = books_data_resize;
}

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

bool validate_genre(char *genre)
{
    bool is_valid = false;
    for (int i = 0; i < ACEPTED_GENRE_MAX; i++)
    {
        if (GENRE_CHAR[i] == toupper(*genre))
        {
            is_valid = true;
        }
    }
    return is_valid;
}

void list_read_books(BookData * books_data, int books_top)
{
    bool genre_found = false;
    int genre_index = 0;
    cout << "\nEstos son tus libros:" << endl;
    for (int j = 0; j < books_top; j++)
    {
        genre_found = false;
        genre_index = 0;
        cout << "---------------------------\nNombre: " << books_data[j].title << endl;
        while (genre_found == false && genre_index < ACEPTED_GENRE_MAX)
        {
            if (GENRE_CHAR[genre_index] == books_data[j].genre)
            {
                genre_found = true;
                cout << "Genero: " << GENRE_FULL_NAME[genre_index] << endl;
            }
            genre_index++;
        }

        cout << "Puntaje: " << books_data[j].score << endl;
    }
}

void add_book(BookData *&books_data, int &books_top, int &max_books)
{
    BookData temp_book;

    bool is_valid_title = true;

    cout << "Ingrese el titulo del libro: ";
    getline(cin >> ws, temp_book.title);

    int i = 0;
    while (i < books_top && is_valid_title != false)
    {
        if (temp_book.title == books_data[i].title)
        {
            is_valid_title = false;
        }
        i++;
    }

    if (!is_valid_title)
    {
        cout << "El titulo ya esta en la lista" << endl;
    }
    else
    {
        for (int i = 0; i < (ACEPTED_GENRE_MAX - 1); i++)
        {
            cout << GENRE_CHAR[i] << ": " << GENRE_FULL_NAME[i] << " - ";
        }
        cout << GENRE_CHAR[ACEPTED_GENRE_MAX - 1] << ": " << GENRE_FULL_NAME[ACEPTED_GENRE_MAX - 1] << endl;

        cout << "Ingrese el genero del libro: ";
        cin >> temp_book.genre;
        while (validate_genre(&temp_book.genre) == false)
        {
            cout << "Ingrese un genero valido: ";
            cin >> temp_book.genre;
            temp_book.genre = (char)toupper(temp_book.genre);
        }
        cout << "Ingrese el puntaje (0-100): ";
        cin >> temp_book.score;
        while (temp_book.score > 100 || temp_book.score < 0)
        {
            cout << "Ingrese un puntaje valido: ";
            cin >> temp_book.score;
        }

        cout << temp_book.title << " - " << temp_book.genre << " - " << temp_book.score << endl;

        if (books_top >= max_books)
        {
            vector_resize(books_data, max_books);
        }
        books_data[books_top] = temp_book;

        books_top++;
    }
}

void edit_score(BookData *&books_data, int books_top){
    bool title_found = false;
    int title_index = 0;
    int new_score = 0;
    string title;

    cout << "Ingrese el titulo del libro: ";
    getline(cin >> ws, title);

    while (title_index < books_top && title_found == false)
    {
        if (title == books_data[title_index].title)
        {
            title_found = true;
        }
        else{
            title_index++;
        }
    }

    if (!title_found)
    {
        cout << "No existe el titulo '" << title << "'" << endl;
    }
    else{
        cout << "El puntaje actual es: " << books_data[title_index].score << endl;
        cout << "Ingrese el nuevo puntaje (0-100): ";
        cin >> new_score;
        while (new_score > 100 || new_score < 0)
        {
            cout << "Ingrese un puntaje valido: ";
            cin >> new_score;
        }
        books_data[title_index].score = new_score;
    }
}

void show_favorite(BookData *books_data, int books_top){
    int top_score = 0;
    int i = 0;
    bool genre_found = false;
    int genre_index = 0;

    while(i<books_top && top_score != 100){
        if(books_data[i].score > top_score){
            top_score = books_data[i].score;
        }
        i++;
    }

    cout << "Estos son tus mejores libros:" << endl;
    for(int j = 0; j < books_top; j++){
        if(books_data[j].score == top_score){
            genre_found = false;
            genre_index = 0;
            cout << "---------------------------\nNombre: " << books_data[j].title << endl;
            while (genre_found == false && genre_index < ACEPTED_GENRE_MAX)
            {
                if (GENRE_CHAR[genre_index] == books_data[j].genre)
                {
                    genre_found = true;
                    cout << "Genero: " << GENRE_FULL_NAME[genre_index] << endl;
                }
                genre_index++;
            }

            cout << "Puntaje: " << books_data[j].score << endl;
        }
    }
}