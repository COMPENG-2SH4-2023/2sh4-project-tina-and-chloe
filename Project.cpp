#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

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
    int i;
    int j;

    objPos tracker;
    //tracker.setObjPos(4,2,'*');
   

    objPos player;
    player.setObjPos(4,2,'*');
    
    for (i=0; i<10; i++)
    {   
        for (j=0;j<20; j++)
        {
            tracker.setObjPos(i,j,' ');
            if (tracker.isPosEqual(&player))
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
  
    MacUILib_uninit();
}
