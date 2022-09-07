#include <iostream>
#include <fstream>
#include <string>
#include "csv_manage_link.h"
#include "functions_link.h"

using namespace std;

/*
pre:
    - books_data must be initialized
    - books_top must be initialized
    - max_books be initialized
post:
    - fills books_data with the data read from the indicated csv
*/
void read_csv(BookData *&books_data, int &books_top, int &max_books)
{
    BookData temp_book;
    string line_content, title, genre, score;
    int i = 0;

    ifstream file("data.csv");

    if (!file.is_open())
    {
        cout << "ERROR: File Open" << endl;
    }


    while (file.good())
    {
        getline(file, line_content, '\n');
        if(line_content != ""){
            getline(file, title, ',');
            getline(file, genre, ',');
            getline(file, score, '\n');       
            temp_book.title = title;
            temp_book.genre = genre[0];
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
    }
    file.close();
}


/*
pre:
    - books_data must be initialized
    - books_top must be initialized
post:
    - saves books_data in the indicated csv
*/
void read_csv(BookData *books_data, int books_top){
    ofstream file("data.csv");
    
    if (!file.is_open())
    {
        cout << "ERROR: File Open" << endl;
    }

    for(int i = 0; i<books_top; i++){
        file << books_data[i].title << "," << (char)toupper(books_data[i].genre) << "," << books_data[i].score << "\n";
    }
    file.close();
}