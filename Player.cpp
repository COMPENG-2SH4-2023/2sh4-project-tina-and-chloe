#include "Player.h"


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

    // switch(mainGameMechsRef.getInput())
    // {
    //     case 'W':
    //     case 'w':
    //         if(myDir != DOWN && myDir != UP)
    //         {
    //             myDir = UP;
    //         }
    //         break; 

    //     case 'A':
    //     case 'a':
    //         if(myDir != RIGHT && myDir != LEFT)
    //         {
    //             myDir = LEFT;
    //         }
    //         break;

    //     case 'S':
    //     case 's':
    //         if(myDir != UP && myDir != DOWN)
    //         {
    //             myDir = DOWN;
    //         }
    //         break;

    //     case 'D':
    //     case 'd':
    //         if(myDir != LEFT && myDir != RIGHT)
    //         { 
    //             myDir = RIGHT;
    //         }
    //         break;

    //     default:
    //         break;
    // }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
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

    // switch(playerPos.x)
    // {
    //     case 0:
    //         playerPos.x = mainGameMechsRef.getBoardSizeX() - 2;
    //         break; 

    //     case (mainGameMechsRef.getBoardSizeX() - 1):
    //         playerPos.x = 1;
    //         break; 
    // }

    // switch(playerPos.y)
    // {
    //     case 0:
    //         playerPos.y = mainGameMechsRef.getBoardSizeY() - 2;
    //         break; 

    //     case (mainGameMechsRef.getBoardSizeY() - 1):
    //         playerPos.y = 1;
    //         break; 
    //}
}

