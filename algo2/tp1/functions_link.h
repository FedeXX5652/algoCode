#ifndef __FUNCTIONS_LINK_H__
#define __FUNCTIONS_LINK_H__

bool is_valid_input(char *input);

void list_read_books(BookData *&books_data, int &books_top);

void vector_resize(BookData *&books_data, int &max_books);

#endif