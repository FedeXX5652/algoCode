#include <iostream>
#include <fstream>
#include <string>
#include "csv_manage_link.h"
#include "functions_link.h"

using namespace std;

void read_csv(BookData* books_data, int &max_books){
    BookData temp_book;

    cout << "MAX: " << max_books << endl;

    ifstream file("data.csv");

    if (!file.is_open()){
        cout << "ERROR: File Open" << endl;
    }
    string name;
    string genre;
    string score;

    int i=0;

    while (file.good()){

        getline(file, name, ',');
        getline(file, genre, ',');
        getline(file, score, '\n');

        temp_book.name = name;
        temp_book.genre = genre[0];
        temp_book.score = stoi(score);

        if(i>=max_books){
            vector_resize(books_data, max_books);
        }
        if(i<max_books){
            books_data[i] = temp_book;
        }
        i++;
    }

    cout << sizeof(books_data) << endl;

    for(int j=0; j<max_books; j++){
        cout << "Read: ";
        cout << books_data[j].name << " - " << books_data[j].genre << " - " << books_data[j].score << " - " << books_data << endl;
    }

    file.close();
}