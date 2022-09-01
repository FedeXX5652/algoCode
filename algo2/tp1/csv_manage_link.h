#ifndef __CSV_MANAGE_LINK_H__
#define __CSV_MANAGE_LINK_H__

using namespace std;

struct book_data{
    string name;
    char genre;
    int score;
};

bool read_csv();

#endif