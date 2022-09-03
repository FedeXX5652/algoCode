#include <iostream>
#include <string>
#include "csv_manage_link.h"

using namespace std;

#define ACEPTED_INPUTS_MAX 8

const char ACEPTED_INPUTS[ACEPTED_INPUTS_MAX] = {'1','2','3','4','5','6','7','8'};


bool is_valid_input(char* input){
    for(int i=0; i<ACEPTED_INPUTS_MAX; i++){
        if(ACEPTED_INPUTS[i] == *input){
            return true;
        }
    }
    return false;
}

void list_read_books(){
    int x=1;
    x++;
}

void vector_resize(BookData* &books_data, int &max_books){
    int new_size = max_books*2;
    BookData* books_data_resize = new BookData[new_size];
    
    cout << "RESIZE\n";
    for(int j=0; j<max_books; j++){
        books_data_resize[j].name = books_data[j].name;
        books_data_resize[j].genre = books_data[j].genre;
        books_data_resize[j].score = books_data[j].score;
    }
    
    max_books = new_size;
    delete [] books_data;       // no se si esto deletea bien o no
    for(int j=0; j<max_books; j++){
        cout << "post resize delete: ";
        cout << books_data[j].name << " - " << books_data[j].genre << " - " << books_data[j].score << " - " << books_data << endl;
    }
    books_data = books_data_resize;
}