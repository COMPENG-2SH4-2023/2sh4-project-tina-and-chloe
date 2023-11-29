#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
GameMechs* snakeGameMech;
Player* snakePlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
    snakeGameMech = new GameMechs();
    snakePlayer = new Player(snakeGameMech);
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    int i, j;

    objPos tracker;
    objPos player;
    player.setObjPos(4,2,'*');
    
    for (i=0; i<10; i++)
    {   
        for (j=0;j<20; j++)
        {
            tracker.setObjPos(i,j,' ');
            if (tracker.isPosEqual(&snakePlayer))
            {
                MacUILib_printf("*");
            }
            else if (i>=1 && i<=8 && j >=1 && j <= 18)
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
