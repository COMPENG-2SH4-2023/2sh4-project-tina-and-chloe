#include "objPosArrayList.h"
#include "objPos.h"

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

// Constructor for specified maximum list size
objPosArrayList::objPosArrayList(int maxSize)
{
    aList = new objPos[maxSize];
    sizeList = 0;
    sizeArray = maxSize;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

objPosArrayList::objPosArrayList(const objPosArrayList &l)
{
    sizeList = l.sizeList;
    sizeArray = l.sizeArray;
    aList = new objPos[ARRAY_MAX_CAP];
    for(int i = 0; i < sizeList; i++)
    {
        aList[i] = l.aList[i];
    }
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Do nothing if list is at its max size (= array size)
    if(sizeList == sizeArray)
    {
        return;
    }

    // Shuffle all the list elements "back" by one
    for(int i = sizeList; i > 0; i--)
        aList[i] = aList[i-1];

    // Insert the new head element, increase the list size
    aList[0] = thisPos;
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Do nothing if list is at its max size (= array size)
    if(sizeList == sizeArray)
    {
        return;
    }

    // Insert the new tail element, increase the list size
    aList[sizeList] = thisPos;
    sizeList++;
}

void objPosArrayList::removeHead()
{
    // Do nothing if list is empty
    if(sizeList == 0)
    {
        return;
    }

    // Shuffle all the elements "forward"
    for(int i = 0; i < sizeList-1; i++)
    {
        aList[i] = aList[i+1];
    }

    // Decrease the list size (so the old tail is inaccessible)
    sizeList--;
}

void objPosArrayList::removeTail()
{
    // Do nothing if list is empty
    if(sizeList == 0)
    {
        return;
    }

    // Decrease the list size (so the old tail is inaccessible)
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    // Do nothing if list is empty
    if(sizeList == 0)
    {
        return;
    }

    returnPos.setObjPos(aList[0].x, aList[0].y, aList[0].symbol);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    // Do nothing if list is empty
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
    // Iterate through the list, see if any of the coordinates match with
    //   the argument thisPos' coordinates
    for(int i = 0; i < sizeList; i++)
    {
        if(aList[i].isPosEqual(&thisPos))
        {
            return true;
        }
    }

    return false;
}