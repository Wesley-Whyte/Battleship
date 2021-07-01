#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Logic.h"
#include "GridPoint.h"
#define size 10

///
///Simulates a one player game
///
void onePlayerGame()
{
    typedef struct player Player;
    Player player1;
    Player player2;

    int turntracker = 1;//Player 1 goes first
                        //1. for player 1's turn
                        //2. for player 2's turn
    int turn;//set to
             //1. to keep turn
             //2. to switch turns
             //0.to end game


    playerInit(&player1);
    playerInit(&player2);
    char p1[10] = "Player 1";
    char p2[10] = "Computer";
    player1.name = p1;
    player2.name = p2;

    //let player one set his battleships
      //Give prompt to set battleships
      //Start with largest and go down
    for(int i = size - 1;i >= 0;i--)
    {
        placeBattleShips(player1.Board,player1.Heur,player1.Ships[i],i,player1.name);
    }
    clrscr();
    printf("%s has placed his battleships\n",player1.name);
    displayBoard(player1.Board);
    breaker();
    //let computer set his battleships
    for(int i = size - 1;i >= 0;i--)
    {
        autoPlaceBattleShips(player2.Board,player2.Heur,player2.Ships[i],i,player2.name);
    }
    clrscr();
    printf("%s has placed his battleships\n",player2.name);
    breaker();

    //take turns playing
    if(turntracker == 1)
    {
        turn = runTurn(&player1,&player2);
    }
    else if(turntracker == 2)
    {
        turn = autoRunTurn(&player2,&player1);
    }

    while(turn != 0)
    {
        switch(turn)
        {
        case 1://Depending on whose turn it was before they'll play again
            if(turntracker == 1)
            {
                turn = runTurn(&player1,&player2);
            }
            else if(turntracker == 2)
            {
                turn = autoRunTurn(&player2,&player1);
            }

            break;

        case 2://First switch turns
            if(turntracker == 1)
            {
                turntracker = 2;
            }
            else if(turntracker == 2)
            {
                turntracker = 1;
            }
            //Then let the next person play their turn
            if(turntracker == 1)
            {
                turn = runTurn(&player1,&player2);
            }
            else if(turntracker == 2)
            {
                turn = autoRunTurn(&player2,&player1);
            }

            break;
        }
    }
    printf("Game over.\n");
    if(turntracker == 1)
    {
        printf("%s wins",player1.name);
    }
    else if(turntracker == 2)
    {
        printf("%s wins",player2.name);
    }
    breaker();

}
///
///Simulates a two player game
///
void twoPlayerGame()
{
    typedef struct player Player;
    Player player1;
    Player player2;
    int turntracker = 1;//Player 1 goes first
                        //1. for player 1's turn
                        //2. for player 2's turn
    int turn;//set to
             //1. to keep turn
             //2. to switch turns
             //0.to end game


    playerInit(&player1);
    playerInit(&player2);
    char p1[10] = "Player 1";
    char p2[10] = "Player 2";
    player1.name = p1;
    player2.name = p2;

    //let player one set his battleships
      //Give prompt to set battleships
      //Start with largest and go down
    for(int i = size - 1;i >= 0;i--)
    {
        placeBattleShips(player1.Board,player1.Heur,player1.Ships[i],i,player1.name);
    }
    clrscr();
    printf("%s has placed his battleships\n",player1.name);
    displayBoard(player1.Board);
    breaker();
    //let player two set his battleships
    for(int i = size - 1;i >= 0;i--)
    {
        placeBattleShips(player2.Board,player2.Heur,player2.Ships[i],i,player2.name);
    }
    clrscr();
    printf("%s has placed his battleships\n",player2.name);
    displayBoard(player2.Board);
    breaker();

    //take turns playing
    if(turntracker == 1)
    {
        turn = runTurn(&player1,&player2);
    }
    else if(turntracker == 2)
    {
        turn = runTurn(&player2,&player1);
    }

    while(turn != 0)
    {
        switch(turn)
        {
        case 1://Depending on whose turn it was before they'll play again
            if(turntracker == 1)
            {
                turn = runTurn(&player1,&player2);
            }
            else if(turntracker == 2)
            {
                turn = runTurn(&player2,&player1);
            }

            break;

        case 2://First switch turns
            if(turntracker == 1)
            {
                turntracker = 2;
            }
            else if(turntracker == 2)
            {
                turntracker = 1;
            }
            //Then let the next person play their turn
            if(turntracker == 1)
            {
                turn = runTurn(&player1,&player2);
            }
            else if(turntracker == 2)
            {
                turn = runTurn(&player2,&player1);
            }

            break;
        }
    }
    printf("Game over.\n");
    if(turntracker == 1)
    {
        printf("%s wins",player1.name);
    }
    else if(turntracker == 2)
    {
        printf("%s wins",player2.name);
    }
    breaker();
}
///
/// Runs a turn of the game
///
int runTurn(struct player* main,struct player* second)
{
    //main guesses a point
    int column;
    int row;
    int failsafe = 1;
    int game = 0;//0 for game over
                 //1 keep turn
                 //2 switch turns

    clrscr();
    printf("%s's Turn\n",main->name);
    displayBoard(main->View);



        while(failsafe != 0)//to make sure they select a valid column
        {
            printf("Choose location\n");
            chooseColumn();

            scanf("%d",&column);
            if(column >= 1 && column  <= 10)
            {
                column = column - 1;
                failsafe = 0;
            }
            else
            {
                printf("Invalid choice. Try again\n");
            }
        }

        failsafe = 1;
        while(failsafe != 0)//to make sure they select a valid row
        {
            printf("Select row\n");
            scanf("%d",&row);
            if(row >= 1 && row  <= 10)
            {
                row = row - 1;
                failsafe = 0;
            }
            else
            {
                printf("Invalid choice. Try again\n");
            }
        }

        if((second->Board[row][column].battleshipid) >= 1 && (second->Board[row][column].battleshipid) <= 10)//Theres a ship there
        {
            //Change main view display into a H
            main->View[row][column].display = 'H';
            clrscr();
            printf("%s's Turn\n",main->name);
            displayBoard(main->View);
            printf("That was a Hit\n");
            //Change second board symbol into a X
            second->Board[row][column].display = 'X';
            //Reduce the length of the ship with that id
            second->Ships[(second->Board[row][column].battleshipid) - 1]--;
            //Check to see if ship is completely destroyed
            if(second->Ships[(second->Board[row][column].battleshipid) - 1] == 0)
            {
                printf("%s sunk a battleship\n",main->name);
            }
            //Change second board id to 11
            second->Board[row][column].battleshipid = 11;
            //Check to see if game is over
            for(int i = 0;i < size;i++)
            {
                if(second->Ships[i] != 0)
                {
                    game = 1;
                    //The game is still on
                }
            }
            breaker();
            return game;

        }
        else if((second->Board[row][column].battleshipid) == 11)//The selected place has already been searched
        {
            printf("This spot has already been selected\n"
                   "Try again\n");
            breaker();
            game = 1;
            return game;
        }
        else//Theres no ship there
        {
            //Change main view display into a M
            main->View[row][column].display = 'M';
            //Change second board id to 11
            second->Board[row][column].battleshipid = 11;

            clrscr();
            printf("%s's Turn\n",main->name);
            displayBoard(main->View);
            printf("That was a miss\n");
            breaker();
            game = 2;
            return game;
        }



}
///
///Automatically done turn
///
int autoRunTurn(struct player* main,struct player* second)
{
    srand(time(NULL));
    //main guesses a point
    int column;
    int row;
    int game = 0;//0 for game over
                 //1 keep turn
                 //2 switch turns

        game = 0;
        column = rand()%10;

        row = rand()%10;

        if((second->Board[row][column].battleshipid) >= 1 && (second->Board[row][column].battleshipid) <= 10)//Theres a ship there
        {
            //Change main view display into a H
            main->View[row][column].display = 'H';
            //Change second board symbol into a X
            second->Board[row][column].display = 'X';
            clrscr();
            printf("%s's Turn\n",main->name);
            displayBoard(second->Board);
            printf("That was a Hit\n");
            //Reduce the length of the ship with that id
            second->Ships[(second->Board[row][column].battleshipid) - 1]--;
            //Check to see if ship is completely destroyed
            if(second->Ships[(second->Board[row][column].battleshipid) - 1] == 0)
            {
                printf("%s sunk a battleship\n",main->name);
            }
            //Change second board id to 11
            second->Board[row][column].battleshipid = 11;
            //Check to see if game is over
            for(int i = 0;i < size;i++)
            {
                if(second->Ships[i] != 0)
                {
                    game = 1;
                    //The game is still on
                }
            }
            breaker();
            return game;

        }
        else if((second->Board[row][column].battleshipid) == 11)//The selected place has already been searched
        {
            game = 1;
            return game;
        }
        else//Theres no ship there
        {
            //Change main view display into a M
            main->View[row][column].display = 'M';
            second->Board[row][column].display = 'O';
            //Change second board id to 11
            second->Board[row][column].battleshipid = 11;

            clrscr();
            printf("%s's Turn\n",main->name);
            displayBoard(second->Board);
            printf("That was a miss\n");
            breaker();
            game = 2;
            return game;
        }


    return 1;//game continues
}
///
///Let's a player set his battleships
///
void placeBattleShips(struct gridpoint board[][10],struct gridpoint heur[][10],int shipLenght,int shipid,char* playerName)
{
    const char *ships[10] = {"Destroyer","Destroyer","Destroyer","Destroyer","Submarine","Submarine","Submarine","Cruiser","Cruiser","Carrier"};
    //pick starting location
          int column;
          int row;
          int choice;
          int failsafe = 1;
          int verify = 1;

          clrscr();
          printf("%s\n",playerName);
          displayBoard(board);

          while(verify != 0)
          {
              while(failsafe != 0)//to make sure they select a valid column
              {
                  printf("Place your battleship\n");
                  printf("This %s has %d cells\n",ships[shipid],shipLenght);
                  printf("Choose location\n");
                  chooseColumn();

                  scanf("%d",&column);
                  if(column >= 1 && column  <= 10)
                  {
                      column = column - 1;
                      failsafe = 0;
                  }
                  else
                  {
                      printf("Invalid choice. Try again\n");
                  }
              }

              failsafe = 1;
              while(failsafe != 0)//to make sure they select a valid row
              {
                  printf("Select row\n");
                  scanf("%d",&row);
                  if(row >= 1 && row  <= 10)
                  {
                      row = row - 1;
                      failsafe = 0;
                  }
                  else
                  {
                      printf("Invalid choice. Try again\n");
                  }
              }

              failsafe = 1;
              while(failsafe != 0)//to make sure they select a valid orientation
              {
                  //Prompt to pick 1.horizontal or 2.vertical
                  printf("Enter\n"
                         "1. To place Horizontally\n"
                         "2. To place Vertically\n");
                  scanf("%d",&choice);

                  if(choice >= 1 && choice <= 2)
                  {
                      failsafe = 0;
                  }
                  else
                  {
                      printf("Invalid choice. Try again\n");
                  }

              }

              switch(choice)
              {
              case 1:
                //Check horizontal validity
                if((horizontalValidation(heur,row,column,shipLenght)) == 1)
                {
                    //Place ship
                    horizontalPlacement(board,heur,row,column,shipLenght,shipid);
                    verify = 0;
                }
                else
                {
                    clrscr();
                    printf("%s\n",playerName);
                    displayBoard(board);
                    printf("Invalid placement. Try again\n");
                    failsafe = 1;
                }
                break;

              case 2:
                //check vertical validity
                if((verticalValidation(heur,row,column,shipLenght)) == 1)
                {
                      //Place ship

                      vericalPlacement(board,heur,row,column,shipLenght,shipid);
                      verify = 0;
                }
                else
                {
                    clrscr();
                    printf("%s\n",playerName);
                    displayBoard(board);
                    printf("Invalid placement. Try again\n");
                    failsafe = 1;
                }
                break;

              default:
                break;
             }
          }
}
///
///Randomly places battleships
///
void autoPlaceBattleShips(struct gridpoint board[][10],struct gridpoint heur[][10],int shipLenght,int shipid,char* playerName)
{
    srand(time(NULL));
    //pick starting location
          int column;
          int row;
          int choice;
          int failsafe = 1;
          int verify = 1;

          while(verify != 0)
          {
              column = rand()%10;

              row = rand()%10;

              failsafe = 1;
              while(failsafe != 0)//to make sure they select a valid orientation
              {
                  //Prompt to pick 1.horizontal or 2.vertical
                  choice = rand()%3;
                  if(choice >= 1 && choice <= 2)
                  {
                      failsafe = 0;
                  }

              }

              switch(choice)
              {
              case 1:
                //Check horizontal validity
                if((horizontalValidation(heur,row,column,shipLenght)) == 1)
                {
                    //Place ship
                    horizontalPlacement(board,heur,row,column,shipLenght,shipid);
                    verify = 0;
                }
                else
                {
                    failsafe = 1;
                }
                break;

              case 2:
                //check vertical validity
                if((verticalValidation(heur,row,column,shipLenght)) == 1)
                {
                      //Place ship

                      vericalPlacement(board,heur,row,column,shipLenght,shipid);
                      verify = 0;
                }
                else
                {
                    failsafe = 1;
                }
                break;

              default:
                break;
             }
          }
}
///
/// Places a battleship vertically on a board
///
void vericalPlacement(struct gridpoint game[][size],struct gridpoint heur[][size],int row,int col,int shipLenght, int shipid)
{
    //Change game board
    for(int i = 0;i < shipLenght;i++)
    {
        game[row + i][col].display = 'S';
        game[row + i][col].battleshipid = shipid + 1;
    }

    //change hueristic board
    for(int i = 0;i < shipLenght;i++)
    {
        int place = row + i;
        heur[place][col].battleshipid = 1;
        //mark points around this point
        //above
        if(place - 1 >= 0 && place - 1 <= 9)
        {
            heur[place - 1][col].battleshipid = 1;
        }
        //below
        if(place + 1 >= 0 && place + 1 <= 9)
        {
            heur[place + 1][col].battleshipid = 1;
        }
        //left
        if(col - 1 >= 0 && col - 1 <= 9)
        {
            heur[place][col - 1].battleshipid = 1;
        }
        //right
        if(col + 1 >= 0 && col + 1 <= 9)
        {
            heur[place][col + 1].battleshipid = 1;
        }
    }
}
///
/// places a battleship horizontally on a board
///
void horizontalPlacement(struct gridpoint game[][size],struct gridpoint heur[][size],int row,int col,int shipLenght,int shipid)
{
    //Change game board
    for(int i = 0;i < shipLenght;i++)
    {
        game[row][col + i].display = 'S';
        game[row][col + i].battleshipid = shipid + 1;
    }
    //change hueristic board
    for(int i = 0;i < shipLenght;i++)
    {
        int place = col + i;
        heur[row][place].battleshipid = 1;
        //mark points around this point
        //above
        if(row - 1 >= 0 && row - 1 <= 9)
        {
            heur[row - 1][place].battleshipid = 1;
        }
        //below
        if(row + 1 >= 0 && row + 1 <= 9)
        {
            heur[row + 1][place].battleshipid = 1;
        }
        //left
        if(place - 1 >= 0 && place - 1 <= 9)
        {
            heur[row][place - 1].battleshipid = 1;
        }
        //right
        if(place - 1 >= 0 && place - 1 <= 9)
        {
            heur[row][place + 1].battleshipid = 1;
        }
    }
}
///
/// Makes sure a battleship can fit vertically on a board
///
int verticalValidation(struct gridpoint heur[][size],int row,int col,int shipLenght)
{
    int output = 1;
    //make sure it fits
    if((row + shipLenght) > size)
    {
        output = 0;
    }
    //validate gridpoints
    for(int i = 0;i < shipLenght;i++)
    {

        if((validateGridPoint(&heur[row + i][col])) != 1)
        {
            output = 0;
        }

    }
    return output;
}
///
/// Makes sure a battleship can fit vertically on a board
///
int horizontalValidation(struct gridpoint heur[][size],int row,int col,int shipLenght)
{
    int output = 1;
    //validate starting point
    //make sure it fits
    if((col + shipLenght) > size)
    {

        output = 0;
    }
    //validate gridpoints
    for(int i = 0;i < shipLenght;i++)
    {
        if((validateGridPoint(&heur[row][col + i])) != 1)
        {
            output = 0;
        }

    }
    return output;
}
///
/// Initializes a board
///
void playerInit(struct player* aBoard)
{
    for(int i = 0;i < size;i++)
    {
        for(int j = 0;j < size;j++)
        {
            aBoard->View[i][j].display = '*';
            aBoard->View[i][j].battleshipid = 0;
        }
    }

    for(int i = 0;i < size;i++)
    {
        for(int j = 0;j < size;j++)
        {
            aBoard->Heur[i][j].battleshipid = 0;
        }
    }

    for(int i = 0;i < size;i++)
    {
        for(int j = 0;j < size;j++)
        {
            aBoard->Board[i][j].display = '*';
            aBoard->Board[i][j].battleshipid = 0;
        }
    }

    aBoard->Ships[0] = 2;
    aBoard->Ships[1] = 2;
    aBoard->Ships[2] = 2;
    aBoard->Ships[3] = 2;
    aBoard->Ships[4] = 3;
    aBoard->Ships[5] = 3;
    aBoard->Ships[6] = 3;
    aBoard->Ships[7] = 4;
    aBoard->Ships[8] = 4;
    aBoard->Ships[9] = 5;
}
///
/// Displays a board
///
void displayBoard(struct gridpoint board[][10])
{
    printf(" . A B C D E F G H I J\n");
    for(int i = 1;i <= size;i++)
    {
        printf("%2d ",i);

        for(int j = 1;j <= size;j++)
        {
            printf("%c ",board[i - 1][j - 1].display);
            if(j == size)
            {
                printf("\n");
            }
        }
    }
    printf("\n\n");
}
///
///Prints prompt to choose column
///
void chooseColumn()
{
    printf("Choose column\n");
    printf("Enter\n"
           "1. A\t"
            "2. B\t"
            "3. C\t"
            "4. D\t"
            "5. E\t"
            "6. F\t"
            "7. G\t"
            "8. H\t"
            "9. I\t"
            "10. J\n");

}
///
/// Clears the screen
///
void clrscr()
{
    system("@cls||clear");
}
///
///To pause the program
///
void breaker()
{
    char breaker[3];
    printf("Enter any key to continue\n");
    scanf("%2s",breaker);
}
