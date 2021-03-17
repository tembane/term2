#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
int arraySize;
struct TheBook{
    int pages;
    char*name;
    int flag;
    union AuthorAndToms{
        char author[100];
        int volume;
    } info;
};
struct TheBook* addBooks(struct TheBook* pointer)
{
    printf("Enter the number of books\n");
    arraySize = inputValidationInt();
    if(!(pointer = (struct TheBook*)calloc(arraySize, sizeof(struct TheBook)))) return 0;
    for (int i = 0; i < arraySize; ++i)
    {
        if(!(pointer[i].name=(char*)calloc(100, sizeof(char)))) return 0;
    }

    for (int i = 0; i < arraySize; ++i)
    {
        printf("Note #%d\n", i+1);
        printf("Enter book name\n");
        rewind(stdin);
        gets(pointer[i].name);
        printf("Enter the number of pages in the book\n");
        pointer[i].pages=inputValidationInt();
        switch (unionMenu())
        {
            case 1:
                printf("Enter author name\n");
                rewind (stdin);
                gets(pointer[i].info.author);
                pointer[i].flag = 0;
                break;
            case 2:
                printf("Enter the number if vol.\n");
                pointer[i].info.volume=inputValidationInt();
                pointer[i].flag = 1;
                break;
        }
    }
    return pointer;
}
struct TheBook * addNewBooks(struct TheBook * pointer)
{
    printf("How many books do you want to add?\n");
    int newArraySize = inputValidationInt();

    if(!(pointer = (struct TheBook*)realloc(pointer,
                                            (arraySize+newArraySize)* sizeof(struct TheBook)))) return 0;
    for (int i = arraySize; i < arraySize+newArraySize; ++i)
    {
        if(!(pointer[i].name=(char*)calloc(100, sizeof(char)))) return 0;
    }

    for (int i = arraySize; i < arraySize+newArraySize; ++i)
    {
        printf("Note #%d\n", i+1);
        printf("Enter book name\n");
        rewind(stdin);
        gets(pointer[i].name);
        printf("Enter the number of pages in the book\n");
        pointer[i].pages=inputValidationInt();
        switch (unionMenu())
        {
            case 1:
                printf("Enter author name\n");
                rewind (stdin);
                gets(pointer[i].info.author);
                pointer[i].flag = 0;
                break;
            case 2:
                printf("Enter the number if vol.\n");
                pointer[i].info.volume=inputValidationInt();
                pointer[i].flag = 1;
                break;
        }
    }
    arraySize += newArraySize;
    return pointer;
}
struct TheBook* del (struct TheBook* pointer)
{
    printf("Make a choice\n");
    printf("1)  Delete a specific notes\n");
    printf("2)  Delete by a given parameter\n");
    printf("3)  Delete all notes\n");
    printf("4)  Exit\n");
    int choice = correctChoice(4);
    switch (choice)
    {
        case 1:
            printf("Enter the record number\n");
            int recordNumber = correctChoice(arraySize);
            for (int i = recordNumber; i < arraySize; ++i)
            {
                pointer[i]=pointer[i+1];
            }
            arraySize --;
            pointer = (struct TheBook*)realloc(pointer, arraySize* sizeof(struct TheBook));
            printf("The note was successfully deleted\n");
            break;
        case  2:
            pointer = delGivenParam(pointer);
            printf("The note was successfully deleted\n");
            break;
        case 3:
            free(pointer);
            printf("All notes was successfully deleted\n");
            break;
        case 4:
            break;
    }
    return pointer;
}
struct TheBook* delGivenParam(struct TheBook* pointer)
{
    switch (paramEditMenu())
    {
        case 1:
            printf("Enter the title of the book\n");
            char bookTitle[100];
            rewind(stdin);
            gets(bookTitle);
            rightRegister(bookTitle, 100);
            for (int i = 0; i < arraySize; ++i)
            {
                rightRegister(pointer[i].name, 100);
                if(strcmp(bookTitle, pointer[i].name) == 0)
                {
                    for (int j = i; j < arraySize; ++j)
                        pointer[j] = pointer[j + 1];
                    arraySize--;
                }
            }
            pointer = (struct TheBook*)realloc(pointer, arraySize* sizeof(struct TheBook));
            break;
        case 2:
            printf("Enter the number of pages\n");
            int numberOfPages = inputValidationInt();
            for (int i = 0; i < arraySize; ++i)
            {
                if(numberOfPages == pointer[i].pages)
                {
                    for (int j = i; j <arraySize; ++j)
                        pointer[j]=pointer[j+1];
                    arraySize--;
                }
            }
            pointer = (struct TheBook*)realloc(pointer, arraySize* sizeof(struct TheBook));
            break;
        case 3:
            printf("Enter the author's name\n");
            rewind(stdin);
            char authorName[100];
            gets(authorName);
            rightRegister(authorName, 100);
            for (int i = 0; i < arraySize; ++i)
            {
                rightRegister(pointer[i].info.author, 100);
                if(strcmp(pointer[i].info.author, authorName) == 0)
                {
                    for (int j = i; j < arraySize; ++j)
                        pointer[j] = pointer[j + 1];
                    arraySize--;
                }
            }
            pointer = (struct TheBook*)realloc(pointer, arraySize* sizeof(struct TheBook));
            break;
        case 4:
            printf("Enter the number of vol.\n");
            int numberOfVol = inputValidationInt();
            for (int i = 0; i < arraySize; ++i)
            {
                if(numberOfVol == pointer[i].info.volume)
                {
                    for (int j = i; j <arraySize; ++j)
                        pointer[j]=pointer[j+1];
                    arraySize--;
                }
            }
            pointer = (struct TheBook*)realloc(pointer, arraySize* sizeof(struct TheBook));
            break;
        case 5:
            break;
    }
    return pointer;
}
int inputValidationInt()
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}
int correctChoice(int k)
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0 || n > k)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}
int startMenu()
{
    printf("1)  Add new book\n");
    printf("2)  Exit\n");
    int choice = correctChoice(2);
    return choice;
}
int menu()
{
    printf("1)   Add new books\n");
    printf("2)   Output\n");
    printf("3)   Edit\n");
    printf("4)   Delete\n");
    printf("5)   Search\n");
    printf("6)   Sort\n");
    printf("7)   Exit\n");
    int choice = correctChoice(7);
    return choice;
}
int unionMenu()
{
    printf("Make a choice\n");
    printf("1)  Add author\n");
    printf("2)  Add the number if vol.\n");
    int choice = correctChoice(2);
    return choice;
}
int paramEditMenu()
{
    printf("1)  Removal by the title of the book\n");
    printf("2)  Delete by the number of pages\n");
    printf("3)  Removal by the author's name\n");
    printf("4)  Removal by volume\n");
    printf("5)  Exit\n");
    int choice = correctChoice(5);
    return choice;
}
void lines()
{
    int i = 0;
    while (i < 105)
    {
        printf("-");
        i++;
    }
    printf("\n");
}
void headline()
{
    char headline[] = "BOOKS";
    lines();
    printf("|%-51c%-52s|\n", ' ', headline);
    lines();
    printf("|\t%c\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\n",
           '#', "Book", "Pages", "Author", "Vol.");
}
void outputArray(struct TheBook * pointer)
{
    printf("Make a choice\n");
    printf("1)  All notes\n");
    printf("2)  One note\n");
    printf("3)  Exit\n");
    int choice = correctChoice(3);
    switch (choice)
    {
        case 1:
            headline();
            lines();
            for (int i = 0; i < arraySize; ++i) {
                printf("|\t%d\t|\t%s\t|\t%d\t|",i+1,pointer[i].name,pointer[i].pages);
                if(pointer[i].flag == 0)
                {
                    printf("\t%s\t|\t%c\t|\n", pointer[i].info.author, '-');
                }else
                    printf("\t%c\t|\t%d\t|\n",'-', pointer[i].info.volume);
                lines();
            }
            break;
        case 2:

            printf("Enter book number\n");
            int bookNumber = correctChoice(arraySize);
            bookNumber--;
            headline();
            lines();
            printf("|\t%d\t|\t%s\t|\t%d\t|",bookNumber+1,pointer[bookNumber].name,pointer[bookNumber].pages);
            if(pointer[bookNumber].flag == 0)
            {
                printf("\t%s\t|\t%c\t|\n", pointer[bookNumber].info.author, '-');
            }else
                printf("\t%c\t|\t%d\t|\n",'-', pointer[bookNumber].info.volume);
            lines();
            break;
        case 3:
            break;

    }
}
void edit(struct TheBook * pointer)
{
    printf("Make a choice:\n");
    printf("1)  Edit one note\n");
    printf("2)  Edit part of note\n");
    printf("3)  Exit\n");
    int choice = correctChoice(3);
    switch (choice)
    {
        case 1:
            editOneNote(pointer);
            break;
        case 2:
            partEdit(pointer);
            break;
        case 3:
            break;
    }

}
void editOneNote (struct TheBook *pointer)
{
    printf("Enter book number\n");
    int bookNumber = correctChoice(arraySize);
    bookNumber--;

    printf("Enter new book name\n");
    rewind(stdin);
    gets(pointer[bookNumber].name);

    printf("Enter new number of page\n");
    pointer[bookNumber].pages = inputValidationInt();

    if(pointer[bookNumber].flag == 0)
    {
        printf("Make a choice\n");
        printf("1)  Change the author's name\n");
        printf("2)  Change the field from the author's name to the number of volumes\n");
        int choice = correctChoice(2);
        switch (choice)
        {
            case 1:
                printf("Enter the author's new name\n");
                rewind(stdin);
                gets(pointer[bookNumber].info.author);
                //break;
                return;
            case 2:
                printf("Enter the number of volumes\n");
                pointer[bookNumber].info.volume = inputValidationInt();
                pointer[bookNumber].flag = 1;
                //break;
                return;
        }
    }
    if(pointer[bookNumber].flag == 1)
    {
        printf("Make choice\n");
        printf("1)  Change the number of volumes\n");
        printf("2)  Change the field from the number of volumes to the author's name\n");
        int choice = correctChoice(2);
        switch (choice)
        {
            case 1:
                printf("Enter the number of volumes\n");
                pointer[bookNumber].info.volume = inputValidationInt();
                //break;
                return;
            case 2:
                printf("Enter the author's new name\n");
                rewind(stdin);
                gets(pointer[bookNumber].info.author);
                pointer[bookNumber].flag = 0;
                //break;
                return;
        }
    }
}
void partEdit(struct TheBook *pointer)
{
    printf("Enter book number\n");
    int bookNumber = correctChoice(arraySize);
    bookNumber--;
    printf("Make a choice\n");
    printf("1)  edit book name\n");
    printf("2)  Edit the number of page\n");
    printf("3)  Edit author\n");
    printf("4)  Edit the number of vol.\n");
    int choice = correctChoice(4);
    switch(choice)
    {
        case 1:
            printf("Enter new book name\n");
            rewind(stdin);
            gets(pointer[bookNumber].name);
            break;
        case 2:
            printf("Enter new number of page\n");
            pointer[bookNumber].pages = inputValidationInt();
            break;
        case 3:
            if(pointer[bookNumber].flag == 0)
            {
                printf("Enter the author's new name\n");
                rewind(stdin);
                gets(pointer[bookNumber].info.author);
            }
            if(pointer[bookNumber].flag == 1)
            {
                printf("Oops... There is no data on the author's name in this record\n");
                printf("If you change this value, you will no longer be able to store the number of volumes\n");
                printf("Do you want to make changes?\n");
                printf("1)No\n2)Yes\n");
                int editChoice = correctChoice(2);
                switch (editChoice)
                {
                    case 1:
                        break;
                    case 2:
                        printf("Enter the author's name\n");
                        rewind(stdin);
                        gets(pointer[bookNumber].info.author);
                        pointer[bookNumber].flag = 0;
                }
            }
            break;
        case 4:
            if(pointer[bookNumber].flag == 1)
            {
                printf("Enter the number of volumes\n");
                pointer[bookNumber].info.volume = inputValidationInt();
            }
            if(pointer[bookNumber].flag == 0)
            {
                printf("Oops... There is no data on the number of volumes in this record\n");
                printf("If you change this value, you will no longer be able to store the author's name\n");
                printf("Do you want to make changes?\n");
                printf("1)No\n2)Yes\n");
                int editChoice = correctChoice(2);
                switch (editChoice)
                {
                    case 1:
                        break;
                    case 2:
                        printf("Enter the number of volumes\n");
                        pointer[bookNumber].info.volume = inputValidationInt();
                        pointer[bookNumber].flag = 1;
                }
            }
            break;
    }
}
void search (struct TheBook* pointer)
{
    int bookNumber = 0;
    printf("Make a choice\n");
    printf("1)  Search by the name of the book\n"
           "2)  Search by number of pages\n"
           "3)  Search by the author's name\n"
           "4)  Search by volumes\n"
           "5)  Exit\n");
    int choice = correctChoice(4);
    switch (choice)
    {
        case 1:
            printf("Enter the title of the book\n");
            rewind(stdin);
            char bookTitle[100];
            gets(bookTitle);
            rightRegister(bookTitle, 100);
            bookNumber = 0;
            headline();
            for (int i = 0; i < arraySize; ++i)
            {
                rightRegister(pointer[i].name, 100);
                if(strcmp(bookTitle, pointer[i].name) == 0)
                {
                    headline();
                    searchOutput(pointer, bookNumber);
                    bookNumber++;
                }
            }
            break;
        case 2:
            printf("Enter the number of pages\n");
            int numberPage = inputValidationInt();
            bookNumber = 0;
            headline();
            for (int i = 0; i < arraySize; ++i)
            {
                if(numberPage == pointer[i].pages)
                {
                    headline();
                    searchOutput(pointer, bookNumber);
                    bookNumber++;
                }
            }
            break;
        case 3:
            printf("Enter the author's name\n");
            rewind(stdin);
            char authorName[100];
            gets(authorName);
            rightRegister(authorName, 100);
            bookNumber = 0;
            headline();
            for (int i = 0; i < arraySize; ++i)
            {
                rightRegister(pointer[i].info.author, 100);
                if(strcmp(authorName, pointer[i].info.author) == 0)
                {

                    searchOutput(pointer, bookNumber);
                    bookNumber++;
                }
            }
            rewind(stdin);
            break;
        case 4:
            printf("Enter the number of vol.\n");
            int numberOfVol = inputValidationInt();
            headline();
            for (int i = 0; i < arraySize; ++i)
            {
                if(numberOfVol == pointer[i].info.volume)
                {
                    searchOutput(pointer, bookNumber);
                    bookNumber++;
                }
            }
            break;
        case 5:
            break;
    }

}
void searchOutput (struct TheBook *pointer, int bookNumber)
{
    lines();
    printf("|\t%d\t|\t%s\t|\t%d\t|",bookNumber+1,pointer[bookNumber].name,pointer[bookNumber].pages);
    if(pointer[bookNumber].flag == 0)
    {
        printf("\t%s\t|\t%c\t|\n", pointer[bookNumber].info.author, '-');
    }else
        printf("\t%c\t|\t%d\t|\n",'-', pointer[bookNumber].info.volume);
    lines();
}
void rightRegister(char*string, int stringSize)
{
    if ((string[0] >= 'a') && (string[0] <= 'z'))
        string[0] -= 32;
    for (int i = 1; i < stringSize; i++)
    {
        if ((string[i] >= 'A') && (string[i] <= 'Z'))
            string[i] += 32;
    }
    for (int i = 1; i < stringSize; i++)
    {
        if ((string[i] >= 'a') && (string[i] <= 'z') &&
            (((string[i - 1]) == '-') || ((string[i - 1]) == ' ')))
            string[i] -= 32;
    }
}

void sort(struct TheBook* pointer)
{
    printf("Make a choice\n");
    printf("1)  Sort alphabetically\n");
    printf("2)  Sort by descending\n");
    printf("3)  Sort by ascending\n");
    printf("4)  Exit\n");
    int choice = correctChoice(4);
    switch (choice)
    {
        case 1:
            alphabeticallySort(pointer);
            break;
        case 2:
            descendingSort(pointer);
            break;
        case 3:
            ascendingSort(pointer);
            break;
        case 4:
            break;

    }
}

void alphabeticallySort(struct TheBook * pointer)
{
    printf("Make a choice\n");
    printf("1)  Sort the title of the books\n"
           "2)   Sort the names of the authors\n");
    struct TheBook temp;
    int choice = correctChoice(2);
    switch (choice)
    {
        case 1:
            for (int i = 0; i < arraySize; ++i) {
                for (int j = 0; j < arraySize-1; ++j) {
                    if (strcmp(pointer[j].name, pointer[j+1].name)>0)
                    {
                        temp = pointer[j];
                        pointer[j] = pointer[j+1];
                        pointer[j+1] = temp;
                    }
                }
            }
            break;
        case 2:
            for (int i = 0; i < arraySize; ++i) {
                for (int j = 0; j < arraySize-1; ++j) {
                    if (strcmp(pointer[j].info.author, pointer[j+1].info.author)>0)
                    {
                        temp = pointer[j];
                        pointer[j] = pointer[j+1];
                        pointer[j+1] = temp;
                    }
                }
            }
            break;
    }
}

void descendingSort (struct TheBook *pointer) //по убыванию
{
    printf("Make a choice\n");
    printf("1)  Sort by number of pages\n"
           "2)  Sort by number of volumes\n");
    struct TheBook temp;
    int choice = correctChoice(2);
    switch (choice)
    {
        case 1:
            for (int i = 0; i < arraySize; ++i)
            {
                for (int j = 0; j < arraySize; ++j)
                {
                    if (pointer[j].pages > pointer[j+1].pages)
                    {
                        temp = pointer[j];
                        pointer[j] = pointer[j+1];
                        pointer[j+1] = temp;
                    }
                }
            }
            break;
        case 2:
            for (int i = 0; i < arraySize; ++i)
            {
                for (int j = 0; j < arraySize; ++j)
                {
                    if (pointer[j].info.volume > pointer[j+1].info.volume)
                    {
                        temp = pointer[j];
                        pointer[j] = pointer[j+1];
                        pointer[j+1] = temp;
                    }
                }
            }
            break;
    }
}

void ascendingSort (struct TheBook *pointer) //по возрастанию
{
    printf("Make a choice\n");
    printf("1)  Sort by number of pages\n"
           "2)  Sort by number of volumes\n");
    struct TheBook temp;
    int choice = correctChoice(2);
    switch (choice)
    {
        case 1:
            for (int i = 0; i < arraySize; ++i)
            {
                for (int j = 0; j < arraySize; ++j)
                {
                    if (pointer[j].pages < pointer[j+1].pages)
                    {
                        temp = pointer[j];
                        pointer[j] = pointer[j+1];
                        pointer[j+1] = temp;
                    }
                }
            }
            break;
        case 2:
            for (int i = 0; i < arraySize; ++i)
            {
                for (int j = 0; j < arraySize; ++j)
                {
                    if (pointer[j].info.volume < pointer[j+1].info.volume)
                    {
                        temp = pointer[j];
                        pointer[j] = pointer[j+1];
                        pointer[j+1] = temp;
                    }
                }
            }
            break;
    }
}
