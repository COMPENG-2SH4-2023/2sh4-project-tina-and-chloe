#include "Food.h"
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

Food::Food()
{
    foodPos.setObjPos(0,0,'O');
}

void Food::generateFood(objPosArrayList playerBlockOff, GameMechs* mainGameMech)
{
    int i,j,k; 
    int match;
    int snakeLength = playerBlockOff.getSize();
    objPos check;

    srand(time(NULL));

    // Check if foodPos coordinates already exists somewhere the snake is occupying
    do
    {
        foodPos.setObjPos((rand() %(mainGameMech->getBoardSizeX()-2))+1,(rand() %(mainGameMech->getBoardSizeY()-2))+1, 'O');
        match = 1;
        for (k = 0; k < snakeLength; k++)
        {
            playerBlockOff.getElement(check,k);
            if (foodPos.isPosEqual(&check))
            {
                match = 0;
            }
        }
    }while(!match); 
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}