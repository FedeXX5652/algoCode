#include <iostream>
#include <fstream>
#include <string>
#include "csv_manage_link.h"
#include "functions_link.h"

using namespace std;

void read_csv(BookData *&books_data, int &books_top, int &max_books)
{
    BookData temp_book;
    string line_content, title, genre, score, line;
    int i = 0;

    ifstream file("libros.csv");

    if (!file.is_open())
    {
        cout << "ERROR: File Open" << endl;
    }

    while (file.good())
    {
        getline(file, title, ',');
        getline(file, genre, ',');
        getline(file, score, '\n');
        temp_book.title = title;
        temp_book.genre = genre;
        temp_book.score = stoi(score);

        if (i >= max_books)
        {
            vector_resize(books_data, max_books);
        }
        if (i < max_books)
        {
            books_data[i] = temp_book;
            books_top++;
        }
        i++;
    }
    file.close();
}

void read_csv(BookData *books_data, int books_top)
{
    ofstream file("libros.csv");

    if (!file.is_open())
    {
        cout << "ERROR: File Open" << endl;
    }

    for (int i = 0; i < (books_top - 1); i++)
    {
        file << books_data[i].title << "," << books_data[i].genre << "," << books_data[i].score << "\n";
    }

    file << books_data[books_top - 1].title << "," << books_data[books_top - 1].genre << "," << books_data[books_top - 1].score;
    file.close();
}