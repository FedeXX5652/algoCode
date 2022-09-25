#ifndef __CSV_MANAGE_LINK_H__
#define __CSV_MANAGE_LINK_H__

using namespace std;

struct BookData
{
    string title;
    string genre;
    int score;
};

/*
pre:
    - books_data must be initialized
    - books_top must be initialized
    - max_books be initialized
    - the csv must have al least one book and have no blank lines
post:
    - fills books_data with the data read from the indicated csv
*/
void read_csv(BookData *&books_data, int &books_top, int &max_books);

/*
pre:
    - books_data must be initialized
    - books_top must be initialized
post:
    - saves books_data in the indicated csv
*/
void read_csv(BookData *books_data, int books_top);

#endif