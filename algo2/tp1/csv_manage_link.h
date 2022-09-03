#ifndef __CSV_MANAGE_LINK_H__
#define __CSV_MANAGE_LINK_H__

using namespace std;

struct BookData
{
    string name;
    char genre;
    int score;
};

void read_csv(BookData *&books_data, int &books_top, int &max_books);

#endif