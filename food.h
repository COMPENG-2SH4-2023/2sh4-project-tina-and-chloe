#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food
{
    private: 
        objPos foodPos;

    public: 
        Food();

        void generateFood(objPosArrayList playerBlockOff, GameMechs* mainGameMech);
        void getFoodPos(objPos &returnPos);
};

#endif