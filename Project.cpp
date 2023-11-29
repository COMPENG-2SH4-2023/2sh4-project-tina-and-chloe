#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000


GameMechs* snakeGameMech;
Player* snakePlayer;
objPos* snakePos;
GameMechs* gameBoard;
char entered;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(snakeGameMech->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    gameBoard = new GameMechs(30,15);
    snakeGameMech = new GameMechs();
    snakePlayer = new Player(snakeGameMech);
    snakePos = new objPos();
    entered = NULL;
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        snakeGameMech->setInput(MacUILib_getChar());
    }
   
}

void RunLogic(void)
{
    entered = snakeGameMech->getInput();

    /*
    switch (entered)
    {
        case ' ' :
        {
            snakeGameMech->setExitTrue();
            break; 
        }
       
    }
    */
    if (entered == ' ')
    {
        snakeGameMech->setExitTrue();
    }
 
    
    snakeGameMech->clearInput();
}

void DrawScreen(void)
{

    MacUILib_clearScreen();    
    int i;
    int j;
    int x = gameBoard->getBoardSizeX();
    int y = gameBoard->getBoardSizeY();    
    objPos tracker;

    snakePlayer->getPlayerPos(*snakePos);
    
    for (i = 0; i < y; i++)
    {   
        for (j = 0; j < x; j++)
        {
            tracker.setObjPos( j, i,' ');
            if (tracker.isPosEqual(snakePos))
            {
                MacUILib_printf("%c", snakePos->symbol);
            }
            else if (i == 0 || i == y-1 || j == 0 || j == x-1)
            {
                MacUILib_printf("#");
            }
            else
            {
                MacUILib_printf(" "); 
            }
        }
        MacUILib_printf("\n"); 
    }

    MacUILib_printf("Player is at (%d, %d) with symbol: %c\n", snakePos->x, snakePos->y, snakePos->symbol);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete snakeGameMech;
    delete snakePlayer;
    delete snakePos;
    delete gameBoard;
    MacUILib_uninit();
}
