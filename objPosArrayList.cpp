#include "objPosArrayList.h"
#include <stdexcept>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = 200;
    listSize = 0;
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete []aList;
}

objPosArrayList::objPosArrayList(const objPosArrayList &oL)
{
    if (this != &oL)
        {
            this->arrayCapacity = oL.arrayCapacity;
            this->listSize = oL.listSize;
            aList = new objPos[arrayCapacity]; 
            for (int i =0;i<listSize;i++)
            {
                this->aList[i] = oL.aList[i];
            }
        }   
}

objPosArrayList& objPosArrayList :: operator= (const objPosArrayList &oL)
{
    if (this != &oL)
    {
        this->arrayCapacity = oL.arrayCapacity;
        this->listSize = oL.listSize;
        for (int i =0;i<listSize;i++)
        {
            this->aList[i] = oL.aList[i];
        }
    }
    return *this;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize != arrayCapacity)
    {
        for(int i=0;i<listSize;i++)
        {
            aList[listSize-i].pos->x = aList[listSize-i-1].pos->x;
            aList[listSize-i].pos->y = aList[listSize-i-1].pos->y;
            aList[listSize-i].symbol = aList[listSize-i-1].symbol;
        }
        aList[0].pos->x = thisPos.pos->x;
        aList[0].pos->y = thisPos.pos->y;
        aList[0].symbol = thisPos.symbol;    
        listSize+=1; 
    }   
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize != arrayCapacity)
    {
        aList[listSize].pos->x = thisPos.pos->x;
        aList[listSize].pos->y = thisPos.pos->y;
        aList[listSize].symbol = thisPos.symbol;    
        listSize+=1; 
    }   
}

void objPosArrayList::insertIndex(objPos thisPos,int index)
{
    if (listSize != arrayCapacity)
    {
        for(int i=0;i<index;i++)
        {
            aList[listSize-i].pos->x = aList[listSize-i-1].pos->x;
            aList[listSize-i].pos->y = aList[listSize-i-1].pos->y;
            aList[listSize-i].symbol = aList[listSize-i-1].symbol;
        }
        aList[index].pos->x = thisPos.pos->x;
        aList[index].pos->y = thisPos.pos->y;
        aList[index].symbol = thisPos.symbol;    
        listSize+=1; 
    }   
}

void objPosArrayList::removeHead()
{
    if (listSize != arrayCapacity)
    {
        for(int i=0;i<listSize;i++)
        {
            aList[i].pos->x = aList[i+1].pos->x;
            aList[i].pos->y = aList[i+1].pos->y;
            aList[i].symbol = aList[i+1].symbol;
        }
        listSize-=1; 
    }
}

void objPosArrayList::removeTail()
{
   if (listSize != 0)
    {
        aList[listSize-1].pos->x = 0;
        aList[listSize-1].pos->y = 0;
        aList[listSize-1].symbol = 0;    
        listSize-=1; 
    } 
}
void objPosArrayList::removeIndex(int index)
{
    if (listSize != arrayCapacity)
    {
        for(int i=index;i<listSize;i++)
        {
            aList[i].pos->x = aList[i+1].pos->x;
            aList[i].pos->y = aList[i+1].pos->y;
            aList[i].symbol = aList[i+1].symbol;
        }
        listSize-=1; 
    }
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    if(index<arrayCapacity)
    {
        return aList[index];
    }
    else
    {
        throw std::out_of_range("Invalid indexes.");
    }
    
}