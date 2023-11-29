#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    int boardSizeX = 30;
    int boardSizeY = 15;
    int score = 0; 
    bool exitFlag = false; 
    bool loseFlag = false; 
    char input = '\0'; 
    
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

char GameMechs::getInput()
{
    return input; 
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input; 
}

void GameMechs::clearInput()
{
    input = 0; 
}

void GameMechs::incrementScore()
{
    score += 1; 
}



