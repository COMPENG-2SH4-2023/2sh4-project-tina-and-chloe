#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int sizeList;
        int sizeArray;

    public:
        // Constructors, destructor, copy constructor
        objPosArrayList();
        objPosArrayList(int maxSize);
        ~objPosArrayList();
        objPosArrayList(const objPosArrayList &l);

        // Other methods
        int getSize();
        
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        void getHeadElement(objPos &returnPos);
        void getTailElement(objPos &returnPos);
        void getElement(objPos &returnPos, int index);

        bool objPosIsIn(objPos thisPos);
};

#endif