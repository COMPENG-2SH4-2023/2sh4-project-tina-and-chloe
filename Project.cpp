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


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(snakeGameMech->getExitFlagStatus() == false && snakeGameMech->getLoseFlagStatus() == false)  
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
    
    snakeGameMech = new GameMechs();
    snakePlayer = new Player(snakeGameMech);
    snakePos = new objPos();
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
    
    /*
    switch (snakeGameMech->getInput())
    {
        case ' ' :
        {
            snakeGameMech->setExitTrue();
            break; 
        }
       
    }
    */
    if (snakeGameMech->getInput() == ' ')
    {
        snakeGameMech->setExitTrue();
    }
    else
    {
        snakePlayer->updatePlayerDir();
    }

    snakePlayer->movePlayer();
    snakeGameMech->incrementScore();
    if(snakeGameMech->getScore() == 20)
    {
        snakeGameMech->setLoseFlag();
    }
 
    // Below is commented out for debugging msg 
    // snakeGameMech->clearInput();
}

void DrawScreen(void)
{

    MacUILib_clearScreen();    
    int i;
    int j;
    int x = snakeGameMech->getBoardSizeX();
    int y = snakeGameMech->getBoardSizeY();    
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

    // Debugging msgs
    MacUILib_printf("Player is at (%d, %d) with symbol: %c\n", snakePos->x, snakePos->y, snakePos->symbol);
    MacUILib_printf("Command given: %c, moving: ", snakeGameMech->getInput());
    switch(snakePlayer->getDir())
    {
        case 0:
            MacUILib_printf("up\n");
            break;
        case 1:
            MacUILib_printf("down\n");
            break;
        case 2:
            MacUILib_printf("left\n");
            break;
        case 3:
            MacUILib_printf("right\n");
            break;
        case 4:
            MacUILib_printf("STOPPED\n");
            break;
    }
    MacUILib_printf("Score: %d\n", snakeGameMech->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();
    // End game processes / msgs
    if(snakeGameMech->getLoseFlagStatus() == true)
    {
        MacUILib_printf("You Lost!\n");
    }
    // else if(snakeGameMech->getExitFlagStatus() == true && snakeGameMech->getLoseFlagStatus() == false)
    // {
    //     MacUILib_printf("You Win!!!.\n");
    // }
    else if(snakeGameMech->getExitFlagStatus() == true)
    {
        MacUILib_printf("Game Exitted.\n");
    }

    delete snakePlayer;
    delete snakePos;
    delete snakeGameMech;
    MacUILib_uninit();
}
