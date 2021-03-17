#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct TheCountry* country = NULL;
    switch (startMenu())
    {
        case 1:
            country = addNewCountry(country);
            break;
        case 2:
            free(country);
            return 0;
    }

    while (1)
    {
        switch (menu())
        {
            case (1):
                country = addNewCountry(country); //переписать на realoc
                break;
            case (2):
                outputArray(country);
                break;
            case (3):
                editing(country);
                break;
            case (4):
                search(country);
                break;
            case (5):
                printf("5");
                break;
            case (6):
                delete(country);
                break;
            case (7):
                free(country);
                return 0;
            default:
                printf("Wrong choice. Try again.");
        }
    }
}
/*
 * Написать сортировку
 * Дописать поиск по параметру
 * Написать поиск по част. парам.
 * Переписать функицию на реалок
 * Переписать изменение на реалок
 */