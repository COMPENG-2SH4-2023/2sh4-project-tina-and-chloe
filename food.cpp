#include "Food.h"
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

Food::Food()
{
    foodBucket = new objPosArrayList(foodQuantity);
}

Food::~Food()
{
    delete[] foodBucket;
}

Food::Food(const Food &l)
{
    foodBucket = l.foodBucket;
}

void Food::generateFood(objPosArrayList playerBlockOff, GameMechs* mainGameMech)
{
    int i, j, k; 
    int match; // flag to check if new food has been generated somewhere it shouldn't be
    int snakeLength = playerBlockOff.getSize();
    objPos foodPos, check;
    char customSym; // sets the different food symbols

    // Randomize by time
    srand(time(NULL));

    // First remove all the food in the list
    for(i = 0; i < foodQuantity; i++)
    {
        foodBucket->removeHead();
    }
    
    // Randomly generate food to fill the list
    for(i = 0; i < foodQuantity; i++)
    {
        do
        {
            match = 1;
            
            if(i == 0)
                customSym = 'O';
            else if(i == 1)
                customSym = '$';
            else if (i == 2)
                customSym = 'X';

            // Generate a food position
            foodPos.setObjPos((rand() %(mainGameMech->getBoardSizeX()-2))+1,(rand() %(mainGameMech->getBoardSizeY()-2))+1, customSym);

            // Check if new foodPos coordinates already exists somewhere the snake is occupying
            for (k = 0; k < snakeLength; k++)
            {
                playerBlockOff.getElement(check,k);
                if (foodPos.isPosEqual(&check))
                {
                    match = 0;
                }
            }

            // Check if new foodPos coordinates already exist as other food in the list
            // (checks from end of list, backwards)
            for(j = i-1; j >= 0; j--)
            {
                foodBucket->getElement(check,j);
                if(foodPos.isPosEqual(&check))
                {
                    match = 0;
                }
            }
        }while(!match); 

        // If all the checks pass, add the foodPos to the list
        foodBucket->insertTail(foodPos);
    }
}

objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
}