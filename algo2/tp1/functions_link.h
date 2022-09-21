#ifndef __FUNCTIONS_LINK_H__
#define __FUNCTIONS_LINK_H__


/*
pre:
    - books_data vector has to be initialized
    - max_books must be a positive int
post:
    - changes the books_data pointer to a bigger vector (double the max_data size)
*/
void vector_resize(BookData *&books_data, int &max_books);


/*
pre:
    - book_data must be initialized
post:
    - prints the data of the book (title, genre, score)
*/
bool validate_input(string input);


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - prints all the books with their data
*/
void list_read_books(BookData *books_data, int books_top);


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
    - max_books must be a positive int
post:
    - adds the new book to the last position of the books_data vector
*/
void add_book(BookData *&books_data, int &books_top, int &max_books);


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - changes the score of the selected title
*/
void edit_score(BookData *&books_data, int books_top);


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - prints the best rated book
*/
void show_favorite(BookData *books_data, int books_top);


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
    - worst_qty must be a positive int
post:
    - prints the worst rated books up to worst_qty
*/
void show_worst(BookData *books_data, int books_top, int worst_qty);


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - prints the most read genre
*/
void show_most_read_genre(BookData *books_data, int books_top);


/*
pre:
    - books_data must be initialized
    - books_top must be a positive int
post:
    - prints the highest average genre
*/
void show_favorite_genre(BookData *books_data, int books_top);

#endif