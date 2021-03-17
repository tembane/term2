#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arraySize = 0;

struct TheCountry {
    char name[25];
    char capital[30];
    /*    char dimensionOfPopulation[80];
        char dimensionOfSquare[80];*/
    float population;
    float square;
};
int startMenu()
{
    int temp;
    printf("    1)Add new country\n");
    printf("    2)Exit\n");
    temp = correctChoice(2);
    return temp;
}
int menu() {
    int temp;
    printf("\nChoose what action to perform:\n");
    printf("    1)  Add state\n");
    printf("    2)  List states\n");
    printf("    3)  Change the last entry\n");
    printf("    4)  Find states\n");
    printf("    5)  Sort the list\n");
    printf("    6)  Delete state\n");
    printf("    7)  Exit\n");
    temp = inputValidationInt();
    return temp;
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
float inputValidationFloat()
{
    float n;
    while (scanf("%f", &n) != 1 || n <= 0.0)
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
    char headline[] = "COUNTRY";
    lines();
    printf("|%-51c%-52s|\n", ' ', headline);
    lines();
    printf("|\t%c\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\n",
           '#', "The Country", "The Capital", "Population", "Square");
}
int editingMenu()
{
    int temp;
    printf("    1)  Edit country name\n");
    printf("    2)  Edit capital name\n");
    printf("    3)  Edit population\n");
    printf("    4)  Edit square\n");
    temp = correctChoice(4);
    rewind(stdin);
    return temp;
}
int searchMenu()
{
    int temp;
    printf("Select option to search\n");
    printf("    1)  Note number\n");
    printf("    2)  Country name\n");
    printf("    3)  Capital name\n");
    printf("    4)  Population\n");
    printf("    5)  square\n");
    temp = correctChoice(5);
    rewind(stdin);
    return temp;
}
struct TheCountry* addNewCountry(struct TheCountry* country)
{
    int numberOfRecords = 0;
    printf("How many countries do you want to enter?\n");
    arraySize = inputValidationInt();

    country = (struct TheCountry*)calloc(arraySize, sizeof(struct TheCountry));

    for (int i = 0; i < arraySize; ++i)
    {
        printf("Note # %d\n", numberOfRecords + 1);
        printf("Enter country name:\n");
        rewind(stdin);
        gets(country[i].name);
        printf("Enter the name of the capital:\n");
        rewind(stdin);
        gets(country[i].capital);
        printf("Enter the population of this country:\n");
        rewind(stdin);
        country[i].population = inputValidationFloat();
        printf("Enter country area:\n");
        country[i].square = inputValidationFloat();
        numberOfRecords++;
    }
    return country;
}
void outputArray(struct TheCountry* country)
{
    printf("Select an action\n");
    printf("    1)Output all countries\n    2)Output one country\n");
    int choice = correctChoice(2);

    switch (choice)
    {
        case 1:
            outputAllNotes(country);
            break;

        case 2:
            outputOneNote(country);
            break;
        default:
            printf("Wrong choice. Try again.");
    }
}
void outputAllNotes(struct TheCountry* country)
{
    headline();
    lines();
    for (int i = 0; i < arraySize; ++i)
    {
        printf("|\t%d\t|\t%s\t|\t%s\t|\t%.2f\t|\t%.2f\t|\n",
               i + 1, country[i].name, country[i].capital, country[i].population, country[i].square);
        lines();
    }

}
void outputOneNote(struct TheCountry* country)
{
    printf("Enter note number:\n");
    int countryNumber = correctChoice(arraySize);
    countryNumber--;

    headline();
    lines();

    printf("|\t%d\t|\t%s\t|\t%s\t|\t%.2f\t|\t%.2f\t|\n",
           countryNumber + 1, country[countryNumber].name, country[countryNumber].capital,
           country[countryNumber].population, country[countryNumber].square);
    rewind(stdin);
    lines();
}
void editing(struct TheCountry* country)
{
    printf("What do you want to do\n");
    printf("    1)  Change entire record\n");
    printf("    2)  Change an individual part in a record:\n");
    printf("    3)  Exit\n");
    int recordNumber;
    int choice = correctChoice(3);
    switch (choice)
    {
        case 1:
            printf("Enter record number\n");
            recordNumber = correctChoice(arraySize);
            recordNumber--;
            printf("Enter country name:\n");
            rewind(stdin);
            gets(country[recordNumber].name);
            printf("Enter the name of the capital:\n");
            rewind(stdin);
            gets(country[recordNumber].capital);
            printf("Enter the population of this country:\n");
            rewind(stdin);
            country[recordNumber].population = inputValidationFloat();
            printf("Enter country area:\n");
            country[recordNumber].square = inputValidationFloat();
            break;
        case 2:
            printf("Enter record number");
            recordNumber = correctChoice(arraySize);
            recordNumber--;
            rewind(stdin);

            switch (editingMenu())
            {
                case 1:
                    printf("Enter new country name\n");
                    gets(country[recordNumber].name);
                    rewind(stdin);
                    break;
                case 2:
                    printf("Enter new capital name\n");
                    gets(country[recordNumber].capital);
                    rewind(stdin);
                    break;
                case 3:
                    printf("Enter new population\n");
                    country[recordNumber].population = inputValidationFloat();
                    break;
                case 4:
                    printf("Enter new square\n");
                    country[recordNumber].square = inputValidationFloat();
                    break;
                default:
                    printf("Wrong choice. Try again.");
            }
        case 3:
            break;
    }
}
void delete(struct TheCountry* country)
{
    printf("    1)  Delete all notes\n");
    printf("    2)  Delete 1 note\n");
    printf("    3)  Exit\n");
    int choice = correctChoice(3);

    switch (choice)
    {
        case 1:
            free(country);
            printf("All notes were deleted successfully\n");
            break;
        case 2:
            printf("Enter note number\n");
            int noteNumber = correctChoice(arraySize) - 1;
            for (int i = noteNumber; i < arraySize; i++)
                country[i] = country[i + 1];
            arraySize--;
            printf("The note was successfully deleted\n");
            break;
        case 3:
            break;
    }
}
void search(struct TheCountry* country)
{
    printf("    1)  Search by a given parameter\n");
    printf("    2)  Search by partial match of a given parameter\n");
    printf("    3)  Exit\n");
    int choice = correctChoice(3);

    switch (choice)
    {
        case 1:
            searchGivenParam(country);
            break;
        case 2:
            //partSearch(country);
            break;
        case 3:
            break;
    }
}
void searchGivenParam(struct TheCountry* country)
{
    char temp[30];
    switch (searchMenu())
    {
        case 1:
            outputOneNote(country);
            break;
        case 2:
            printf("Enter country name\n");
            gets(temp);
            for (int i = 0; i < arraySize; ++i)
            {
                if(country[i].name==temp)
                {
                    printf("13123123 %s\n", country[i].name);
                }else
                    continue;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;

    }
}
