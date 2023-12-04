#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"
#include "MacUILib.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;

    // Initial snake head position
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
    // Update the player's direction state based on WASD input
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
    // Track where the head currently is
    objPos newHead;
    playerPosList->getHeadElement(newHead);

    // Assign the next coordinate of the head based on the direction state
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

    // Wrap-around logic (for next head coordinate)
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

    // Snake interactions --- Food Collection & Suicide Detection
    // Variables for food collisions
    objPosArrayList* foodLocation = foodPos->getFoodPos();
    objPos collisionFood;
    objPos snakeHead;
    playerPosList->getHeadElement(snakeHead);
    int k;
    
    // Variables for suicide detection
    objPos snakeLoc;
    int snakeSize = playerPosList->getSize();

    // Suicide detection
    //   end the game if snake head overlaps with its body/tail
    for(k=2;k<snakeSize; k++)
    {
        playerPosList->getElement(snakeLoc,k);
        if (snakeHead.isPosEqual(&snakeLoc))
        {
            mainGameMechsRef->setLoseFlag();
            return;
        }
    }

    // Eat food logic
    if (foodLocation->objPosIsIn(snakeHead) && myDir != STOP) 
    {
        // Find which food it ate (symbol)
        for(int f = 0; f < foodLocation->getSize(); f++)
        {
            foodLocation->getElement(collisionFood,f);
            if(snakeHead.isPosEqual(&collisionFood))
                break;
        }

        // Decide what happens based on the symbol
        switch(collisionFood.symbol)
        {
            // Normal food, score +1, increase snake size +1
            case 'O':
                mainGameMechsRef->incrementScore();
                playerPosList->insertHead(newHead);
                break;
            // Death Food!! -> ends the game
            case 'X':
                playerPosList->insertHead(newHead);
                mainGameMechsRef->setLoseFlag();
                break;
            // SUPER Food! -> score +5, increase snake size +1
            case '$':
                mainGameMechsRef->incrementScore();
                mainGameMechsRef->incrementScore();
                mainGameMechsRef->incrementScore();
                mainGameMechsRef->incrementScore();
                mainGameMechsRef->incrementScore();
                playerPosList->insertHead(newHead);
                break;
            default:
                break;
        }

        // Regenerate all the food
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