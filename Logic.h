#ifndef LOGIC_H
#define LOGIC_H

#include "GridPoint.h"

struct player
{
    char* name;
    struct gridpoint View[10][10];
    struct gridpoint Heur[10][10];
    struct gridpoint Board[10][10];
    int Ships[10];
};

void breaker();
void clrscr();
void chooseColumn();

void playerInit(struct player* aBoard);
void displayBoard(struct gridpoint board[][10]);

void onePlayerGame();
void twoPlayerGame();

int horizontalValidation(struct gridpoint heur[][10],int row,int col,int shipLenght);
int verticalValidation(struct gridpoint heur[][10],int row,int col,int shipLenght);

void horizontalPlacement(struct gridpoint game[][10],struct gridpoint heur[][10],int row,int col,int shipLenght,int shipid);
void vericalPlacement(struct gridpoint game[][10],struct gridpoint heur[][10],int row,int col,int shipLenght, int shipid);

void placeBattleShips(struct gridpoint board[][10],struct gridpoint heur[][10],int shipLenght,int shipid,char* playerName);
void autoPlaceBattleShips(struct gridpoint board[][10],struct gridpoint heur[][10],int shipLenght,int shipid,char* playerName);

int runTurn(struct player* main,struct player* second);//returns 0 for game over
                                                       //        1 for game on
int autoRunTurn(struct player* main,struct player* second);//returns 0 for game over
                                                       //        1 for game on

#endif

