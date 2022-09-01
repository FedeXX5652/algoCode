#include <iostream>
#include <fstream>
#include <string>
#include "csv_manage_link.h"

using namespace std;

bool read_csv(){
    book_data books[5];
    book_data temp_book;

    ifstream file("data.csv");

    if (!file.is_open()){
        cout << "ERROR: File Open" << endl;
    }
    string name;
    string genre;
    string score;

    while (file.good()){

        getline(file, name, ',');
        getline(file, genre, ',');
        getline(file, score, '\n');

        temp_book.name = name;
        temp_book.genre = genre[0];
        temp_book.score = stoi(score);
        
        cout << temp_book.name << " - " << temp_book.genre << " - " << temp_book.score << endl;
    }


    file.close();
    return false;
}