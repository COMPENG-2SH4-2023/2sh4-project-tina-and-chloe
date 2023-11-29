#include "Player.h"
#include "GameMechs.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(10, 5, '*');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    

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

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    switch(myDir)
    {
        case UP: 
            playerPos.y--;
            break;

        case DOWN: 
            playerPos.y++;
            break;

        case LEFT: 
            playerPos.x--;
            break;

        case RIGHT:
            playerPos.x++;
            break;
        
        case STOP:
            break;

        default:
            break;
    }

    switch(playerPos.x)
    {
        case 0:
            playerPos.x = boardSizeX - 2;
            break; 

        case 30:
            playerPos.x = 1;
            break;

        default:
            break;

        // case (boardSizeX - 1):
        //     playerPos.x = 1;
        //     break; 
    }

    switch(playerPos.y)
    {
        case 0:
            playerPos.y = boardSizeY - 2;
            break; 

        case 15:
            playerPos.y = 1;
            break;

        default:
            break;

        // case (boardSizeY - 1):
        //     playerPos.y = 1;
        //     break; 
    }
}

int Player::getDir()
{
    return myDir;
}