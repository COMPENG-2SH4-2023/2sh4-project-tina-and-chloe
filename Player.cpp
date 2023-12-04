#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"
#include "MacUILib.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPosList = new objPosArrayList;

    objPos playerHead;
    int startX = (mainGameMechsRef->getBoardSizeX()) / 2;
    int startY = (mainGameMechsRef->getBoardSizeY()) / 2;
    playerHead.setObjPos(startX, startY, '*');
    playerPosList->insertHead(playerHead);
}


Player::~Player()
{
    delete[] playerPosList;
}

Player::Player(const Player &l)
{
    myDir = l.myDir;
    mainGameMechsRef = l.mainGameMechsRef;
    playerPosList = l.playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    switch(mainGameMechsRef->getInput())
    {
        case 'W':
        case 'w':
            if(myDir != DOWN && myDir != UP)
            {
                myDir = UP;
            }
            break; 

        case 'A':
        case 'a':
            if(myDir != RIGHT && myDir != LEFT)
            {
                myDir = LEFT;
            }
            break;

        case 'S':
        case 's':
            if(myDir != UP && myDir != DOWN)
            {
                myDir = DOWN;
            }
            break;

        case 'D':
        case 'd':
            if(myDir != LEFT && myDir != RIGHT)
            { 
                myDir = RIGHT;
            }
            break;

        default:
            break;
    }
}

void Player::movePlayer(Food* foodPos)
{
    // PPA3 Finite State Machine logic
    objPos newHead;
    playerPosList->getHeadElement(newHead);

    switch(myDir)
    {
        case UP: 
            newHead.y--;
            break;

        case DOWN: 
            newHead.y++;
            break;

        case LEFT: 
            newHead.x--;
            break;

        case RIGHT:
            newHead.x++;
            break;
        
        case STOP:
            break;

        default:
            break;
    }

    // Wrap-around logic
    if(newHead.x == 0)
    {
        newHead.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if(newHead.x == mainGameMechsRef->getBoardSizeX() - 1)
    {
        newHead.x = 1;
    }

    if(newHead.y == 0)
    {
        newHead.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if(newHead.y == mainGameMechsRef->getBoardSizeY() - 1)
    {
        newHead.y = 1;
    }

    // Snake interactions 
    // Variables for food collisions
    objPos foodLocation;
    objPos snakeHead;
    playerPosList->getHeadElement(snakeHead);
    foodPos->getFoodPos(foodLocation);
    int k;
    
    // Variables for suicide detection
    objPos snakeLoc;
    int snakeSize = playerPosList->getSize();

    // Suicide detection
    for(k=2;k<snakeSize; k++)
    {
        playerPosList->getElement(snakeLoc,k);
        if (snakeHead.isPosEqual(&snakeLoc))
        {
            mainGameMechsRef->setLoseFlag();
            return;
        }
    }

    // Eat foor logic
    if (foodLocation.isPosEqual(&snakeHead) && myDir != STOP) 
    {
        // Increment score
        mainGameMechsRef->incrementScore();
        // Insert head, but not remove tail
        playerPosList->insertHead(newHead);
        // Regenerate food
        foodPos->generateFood(*playerPosList, mainGameMechsRef);
    }
    else if (myDir != STOP)
    {
        // Insert head, remove tail (aka move)
        playerPosList->insertHead(newHead);
        playerPosList->removeTail();
    } 
}


int Player::getDir()
{
    return myDir;
}