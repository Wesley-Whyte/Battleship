#include <stdio.h>
#include <stdlib.h>
#include "Logic.h"

#define size 10

void startGame();
void setup();
void onePlayerSetup();

int main()
{
    printf("Welcome to Battle Ship\n");
    startGame();
    return 0;
}

void startGame()
{
    int input;
    printf("Start Game? Enter\n"
           "1. Yes\n"
           "2. No\n");
    scanf("%d",&input);

    while(input != 2)
    {
        switch(input)
        {
        case 1:
            clrscr();
            setup();
            break;

        case 2:
            break;

        default:
            printf("Invalid Input. Try again\n");
            printf("Start Game? Enter\n"
                   "1. Yes\n"
                   "2. No\n");
            scanf("%d",&input);
            break;
            }
        clrscr();//FOr when you come back out
        printf("Start Game? Enter\n"
               "1. Yes\n"
               "2. No\n");
        scanf("%d",&input);
      }
}

void setup()
{
    int input;
    printf("Enter\n"
           "1. 1 Player\n"
           "2. 2 Players\n"
           "0. Back\n");
    scanf("%d",&input);

    while(input != 0)
    {
        switch(input)
        {
        case 1:
            clrscr();
            onePlayerSetup();
            break;
            break;

        case 2:
            clrscr();
            twoPlayerGame();
            break;
            break;

        default:
            printf("Invalid Input. Try again\n");
            printf("Enter\n"
                   "1. 1 Player\n"
                   "2. 2 Players\n"
                   "0. Back\n");
            scanf("%d",&input);
            break;
        }
        clrscr();
        printf("Enter\n"
               "1. 1 Player\n"
               "2. 2 Players\n"
               "0. Back\n");
        scanf("%d",&input);
    }


}

void onePlayerSetup()
{
    int input;
    printf("Enter\n"
           "1. Easy\n"
           "2. Hard\n"
           "0. Back\n");
    scanf("%d",&input);

    while(input != 0)
    {
        switch(input)
        {
        case 1:
            clrscr();
            void onePlayerGame();
            break;

        case 2:
            clrscr();
            void onePlayerGame();
            break;

        default:
            printf("Invalid Input. Try again\n");
            printf("Enter\n"
                   "1. Easy\n"
                   "2. Hard\n"
                   "0. Back");
            scanf("%d",&input);
            break;
        }
    }

}

