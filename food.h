#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

#define foodQuantity 3

class Food
{
    private: 
        objPosArrayList* foodBucket;

    public: 
        // Constructor, destructor, copy constructor
        Food();
        ~Food();
        Food(const Food &l);

        // Other methods
        void generateFood(objPosArrayList playerBlockOff, GameMechs* mainGameMech);
        objPosArrayList* getFoodPos();
};

#endif