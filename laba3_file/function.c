#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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
int correctChoice(int choice)
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0 || n > choice)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}
int startMenu()
{
    printf("Sele");
    return 0;
}