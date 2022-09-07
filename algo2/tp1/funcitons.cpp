#include <iostream>
#include <string>
#include <cctype>
#include "csv_manage_link.h"

using namespace std;

#define ACEPTED_INPUTS_MAX 8
#define ACEPTED_GENRE_MAX 6

const int MAX_SCORE = 100;
const int MIN_SCORE = 0;
const char ACEPTED_INPUTS[ACEPTED_INPUTS_MAX] = {'1', '2', '3', '4', '5', '6', '7', '8'};
const char GENRE_CHAR[ACEPTED_GENRE_MAX] = {'A', 'C', 'D', 'P', 'R', 'T'};
const string GENRE_FULL_NAME[ACEPTED_GENRE_MAX] = {"Accion", "Ciencia Ficcion", "Didactico", "Policiaco", "Romance", "Terror"};


/*
pre:
    - books_data vector has to be initialized
    - max_books must be a positive int
post:
    - changes the books_data pointer to a bigger vector (double the max_data size)
*/
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


/*
pre:
    - input must be a char
post:
    - returns true if input is in ACEPTED_INPUTS, false otherwise
*/
bool validate_input(char input)
{
    bool is_valid = false;
    for (int i = 0; i < ACEPTED_INPUTS_MAX; i++)
    {
        if (ACEPTED_INPUTS[i] == input)
        {
            is_valid = true;
        }
    }
    return is_valid;
}


/*
pre:
    - genre must be a char
post:
    - returns true if genre is in GENRE_CHAR, false otherwise
*/
bool validate_genre(char genre)
{
    bool is_valid = false;
    for (int i = 0; i < ACEPTED_GENRE_MAX; i++)
    {
        if (GENRE_CHAR[i] == toupper(genre))
        {
            is_valid = true;
        }
    }
    return is_valid;
}


/*
pre:
    - book_data must be initialized
post:
    - prints the data of the book (title, genre, score)
*/
void print_book(BookData book_data){
    bool genre_found = false;
    int genre_index = 0;
    cout << "---------------------------\nNombre: " << book_data.title << endl;
    while (genre_found == false && genre_index < ACEPTED_GENRE_MAX)
    {
        if (GENRE_CHAR[genre_index] == book_data.genre)
        {
            genre_found = true;
            cout << "Genero: " << GENRE_FULL_NAME[genre_index] << endl;
        }
        genre_index++;
    }

    cout << "Puntaje: " << book_data.score << endl;
}


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - prints all the books with their data
*/
void list_read_books(BookData * books_data, int books_top)
{
    cout << "\nEstos son tus libros:" << endl;
    for (int j = 0; j < books_top; j++)
    {
        print_book(books_data[j]);
    }
}


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
    - max_books must be a positive int
post:
    - adds the new book to the last position of the books_data vector
*/
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
        temp_book.genre = (char)toupper(temp_book.genre);
        while (validate_genre(temp_book.genre) == false)
        {
            cout << "Ingrese un genero valido: ";
            cin >> temp_book.genre;
            temp_book.genre = (char)toupper(temp_book.genre);
        }
        cout << "Ingrese el puntaje (0-100): ";
        cin >> temp_book.score;
        while (temp_book.score > MAX_SCORE || temp_book.score < MIN_SCORE)
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


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - changes the score of the selected title
*/
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
        while (new_score > MAX_SCORE || new_score < MIN_SCORE)
        {
            cout << "Ingrese un puntaje valido: ";
            cin >> new_score;
        }
        books_data[title_index].score = new_score;
    }
}


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - prints the best rated book
*/
void show_favorite(BookData *books_data, int books_top){
    int top_score = 0;
    int i = 0;

    while(i<books_top && top_score != MAX_SCORE){
        if(books_data[i].score > top_score){
            top_score = books_data[i].score;
        }
        i++;
    }

    cout << "Estos son tus mejores libros:" << endl;
    for(int j = 0; j < books_top; j++){
        if(books_data[j].score == top_score){
            print_book(books_data[j]);
        }
    }
}


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
    - worst_qty must be a positive int
post:
    - prints the worst rated books up to worst_qty
*/
void show_worst(BookData *books_data, int books_top, int worst_qty){        // FALTA TERMINAR
    int worst_indexs[worst_qty];
    int j=0;
    bool new_lowest_found = false;

    for(int i = 0; i < worst_qty; i++){
        worst_indexs[i] = -1;
    }

    for(int i = 0; i < books_top; i++){
        j=0;
        new_lowest_found = false;
        while(j < worst_qty && !new_lowest_found){
            if(worst_indexs[j] == -1 || books_data[i].score < books_data[worst_indexs[j]].score){
                for(int k = worst_qty; k > j; k--){     // inserts the new lowest score index at the indicated position and moves the rest of the scores back
                    worst_indexs[k] = worst_indexs[k-1];
                }
                worst_indexs[j] = i;
                new_lowest_found = true;
            }
            else if(j+1==worst_qty && books_data[i].score == books_data[worst_indexs[j]].score){      // if tie between last index and comparing index, take the alphabetically first
                new_lowest_found = true;
                if((books_data[i].title).compare(books_data[worst_indexs[j]].title) < 0){
                    worst_indexs[j] = i;
                }
            }
            j++;
        }
    }

    cout << "Estos son tus peores " << worst_qty << " libros:" << endl;
    for(int i = 0; i < worst_qty; i++){
        print_book(books_data[worst_indexs[i]]);
    }
}


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - prints the most read genre
*/
void show_most_read_genre(BookData *books_data, int books_top){
    bool genre_found = false;
    int j=0, most_read_genre_count = 0;
    int genre_read_count[ACEPTED_GENRE_MAX];

    for(int i=0; i<ACEPTED_GENRE_MAX; i++){
        genre_read_count[i] = 0;
    }

    for(int i=0; i<books_top; i++){
        j=0;
        while(!genre_found && j<ACEPTED_GENRE_MAX){
            if(GENRE_CHAR[j] == books_data[i].genre){
                genre_read_count[j]++;
            }
            j++;
        }
    }

    for(int i=0; i<ACEPTED_GENRE_MAX; i++){
        if(genre_read_count[i] > most_read_genre_count){
            most_read_genre_count = genre_read_count[i];
        }
    }

    cout << "Estos son tus generos mas leidos:" << endl;
    for(int i=0; i<ACEPTED_GENRE_MAX; i++){
        if(genre_read_count[i] == most_read_genre_count){
            cout << "\t- " << GENRE_FULL_NAME[i] << endl;
        }
    }
    cout << "con " << most_read_genre_count << " libros leidos" << endl;
}


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - prints the highest average genre
*/
void show_favorite_genre(BookData *books_data, int books_top){
    bool genre_found = false;
    int j=0;
    float highest_genre_score_average = 0, average = 0;
    int genre_read_count[ACEPTED_GENRE_MAX];
    int genre_read_score_sum[ACEPTED_GENRE_MAX];

    for(int i=0; i<ACEPTED_GENRE_MAX; i++){
        genre_read_count[i] = 0;
        genre_read_score_sum[i] = 0;
    }

    for(int i=0; i<books_top; i++){
        j=0;
        while(!genre_found && j<ACEPTED_GENRE_MAX){
            if(GENRE_CHAR[j] == books_data[i].genre){
                genre_read_count[j]++;
                genre_read_score_sum[j]+=books_data[i].score;
            }
            j++;
        }
    }

    for(int i=0; i<ACEPTED_GENRE_MAX; i++){
        average = (float)genre_read_score_sum[i]/(float)genre_read_count[i];
        if(average > highest_genre_score_average){
            highest_genre_score_average = average;
        }
    }

    cout << "Estos son tus generos favoritos:" << endl;
    for(int i=0; i<ACEPTED_GENRE_MAX; i++){
        average = (float)genre_read_score_sum[i]/(float)genre_read_count[i];
        if(average == highest_genre_score_average){
            cout << "\t- " << GENRE_FULL_NAME[i] << endl;
        }
    }
    cout << "con un puntaje promedio de " << highest_genre_score_average << endl;
}