#include <stdio.h>
#include "function.h"

int main()
{
    struct TheBook *books;
    books=NULL;

    switch (startMenu())
    {
        case 1:
            books = addBooks(books);
            break;
        case 2:
            return 0;
    }

    while (1)
    {
        switch (menu())
        {
            case 1:
                books = addNewBooks(books);
                break;
            case 2:
                outputArray(books);
                break;
            case 3:
                edit(books);
                break;
            case 4:
                books = del(books);
                break;
            case 5:
                search(books);
                break;
            case 6:
                sort(books);
                break;
            case 7:
                return 0;
        }
    }
}
