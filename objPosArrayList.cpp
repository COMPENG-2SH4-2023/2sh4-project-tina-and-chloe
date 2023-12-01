#include "objPosArrayList.h"
#include "objPos.h"

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeList == sizeArray)
    {
        return;
    }

    for(int i = sizeList; i > 0; i--)
        aList[i] = aList[i-1];

    aList[0] = thisPos;
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList == sizeArray)
    {
        return;
    }

    aList[sizeList] = thisPos;
    sizeList++;
}

void objPosArrayList::removeHead()
{
    if(sizeList == 0)
    {
        return;
    }

    for(int i = 0; i < sizeList-1; i++)
    {
        aList[i] = aList[i+1];
    }

    sizeList--;
}

void objPosArrayList::removeTail()
{
    if(sizeList == 0)
    {
        return;
    }

    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(sizeList == 0)
    {
        return;
    }

    returnPos.setObjPos(aList[0].x, aList[0].y, aList[0].symbol);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if(sizeList == 0)
    {
        return;
    }

    returnPos.setObjPos(aList[sizeList-1].x, aList[sizeList-1].y, aList[sizeList-1].symbol);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index].x, aList[index].y, aList[index].symbol);
}

bool objPosArrayList::objPosIsIn(objPos thisPos)
{
    for(int i = 0; i < sizeList; i++)
    {
        if(aList[i].isPosEqual(&thisPos))
        {
            return true;
        }
    }

    return false;
}