#include <iostream>
#include <string>

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
}

void vector_resize(BookData* books_data, int &max_books){
    cout << max_books << endl;
    for(int j=0; j<max_books; j++){
        cout << books_data[j].name << " - " << books_data[j].genre << " - " << books_data[j].score << endl;
    }
}