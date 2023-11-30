#include "GameMechs.h"
#include "MacUILib.h"

#include <stdlib.h>
#include <time.h>
#include "Player.h"

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0; 
    exitFlag = false; 
    loseFlag = false; 
    input = '\0'; 
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

char GameMechs::getInput()
{
    return input; 
}

void GameMechs::setInput(char this_input)
{
    input = this_input; 
}

void GameMechs::clearInput()
{
    input = 0; 
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score += 1; 
}

void GameMechs::generateFood(objPos blockOff)
{

    int i,j; 
    int match;
    int listSize = 1;
    srand(time(NULL));


    //foodPos object already exists
    for (i =0; i<listSize; i++)
    {
        do
        {
            foodPos.setObjPos((rand() %(boardSizeX-2))+1,(rand() %(boardSizeY-2))+1, '~');
            match =1;
            
            if (foodPos.isPosEqual(&blockOff))
            {
                match =0;
            }

        }while(!match); 
    }

}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}