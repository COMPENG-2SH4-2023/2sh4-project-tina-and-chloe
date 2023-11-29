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
objPos snakePos;
GameMechs* gameBoard;


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
    char entered = snakeGameMech->getInput();

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
    //tracker.setObjPos(4,2,'*');
   

    objPos player;
    player.setObjPos(4,2,'*');
    
    for (i=0; i<y; i++)
    {   
        for (j=0;j<x; j++)
        {
            tracker.setObjPos(i,j,' ');
            if (tracker.isPosEqual(&player))
            {
                MacUILib_printf("*");
            }
            else if (i>=1 && i<=y-2 && j >=1 && j <= x-2)
            {
                MacUILib_printf(" ");
            }
            else
            {
                MacUILib_printf("#"); 
            }
            
        }
        MacUILib_printf("\n"); 
 
    }



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
    MacUILib_uninit();
}
