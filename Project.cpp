#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* snakeGameMech;
Player* snakePlayer;
Food* snakeFood;

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
    
    // Initialize heap elements
    snakeGameMech = new GameMechs();
    snakePlayer = new Player(snakeGameMech);
    snakeFood = new Food();

    // Generate initial food
    objPosArrayList *snakeWholePos;
    snakeWholePos = snakePlayer->getPlayerPos();
    snakeFood->generateFood(*snakeWholePos, snakeGameMech);
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
    // Spacebar will exit the game otherwise, input is used
    // to update player movement state
    if (snakeGameMech->getInput() == ' ')
    {
        snakeGameMech->setExitTrue();
    }
    else
    {
        snakePlayer->updatePlayerDir();
    }

    // Move the player based on the state
    snakePlayer->movePlayer(snakeFood);
 
    // Below is commented out for debugging msg 
    // Clear the input
    // snakeGameMech->clearInput();
}

void DrawScreen(void)
{

    MacUILib_clearScreen();    
    // Variables for iterating through grid
    int i;
    int j;
    int x = snakeGameMech->getBoardSizeX();
    int y = snakeGameMech->getBoardSizeY(); 
    objPos tracker;
    // Variables for iterating through "snake list"   
    int s;
    int snakeList = (snakePlayer->getPlayerPos())->getSize();
    objPosArrayList* listPtr = snakePlayer->getPlayerPos();
    objPos snakePos;
    // Variable for holding food position
    objPos foodPos;
    snakeFood->getFoodPos(foodPos);
    
    
    for (i = 0; i < y; i++)
    {   
        for (j = 0; j < x; j++)
        {
            tracker.setObjPos( j, i,' ');
            // Print the border
            if (!listPtr->objPosIsIn(tracker) && (i == 0 || i == y-1 || j == 0 || j == x-1))
            {
                MacUILib_printf("#");
            }
            // Print the snake
            else if(listPtr->objPosIsIn(tracker))
            {
                for(s = 0; s < snakeList; s++)
                {
                    listPtr->getElement(snakePos,s);
                    if(tracker.isPosEqual(&snakePos))
                    {
                        MacUILib_printf("%c", snakePos.symbol);
                        break;
                    }
                }
            }
            // Print the food(s)
            else if(!listPtr->objPosIsIn(tracker) && tracker.isPosEqual(&foodPos))
            {
                MacUILib_printf("%c", foodPos.symbol);
            }
            // Print whitespaces
            else
            {
                MacUILib_printf(" "); 
            }
        }
        MacUILib_printf("\n"); 
    }

    // Debugging msgs
    objPos thisPos;
    for(int k = 0; k<5; k++)
    {
        listPtr->getElement(thisPos,k);
        MacUILib_printf("Obj %d is at (%d, %d) with sym: %c\n", k, thisPos.x, thisPos.y, thisPos.symbol);
    }
    MacUILib_printf("List size: %d\n", snakeList);
    listPtr->getHeadElement(thisPos);
    MacUILib_printf("Player Head is at (%d, %d) with symbol: %c\n", thisPos.x, thisPos.y, thisPos.symbol);
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
    MacUILib_printf("food is at (%d, %d) with symbol: %c\n", foodPos.x, foodPos.y, foodPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    // End game messages
    if(snakeGameMech->getLoseFlagStatus() == true)
    {
        MacUILib_printf("You Lost!\nYour score was: %d.", snakeGameMech->getScore());
    }
    else if(snakeGameMech->getExitFlagStatus() == true)
    {
        MacUILib_printf("Game Exitted.\nYour score was: %d.", snakeGameMech->getScore());
    }

    // End game processes
    delete snakePlayer;
    delete snakeFood;
    delete snakeGameMech;
    MacUILib_uninit();
}