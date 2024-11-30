#include "objPosArrayList.h"
#include <stdexcept>


//initialization routine for an array of capacity 200 and a used length of 0
objPosArrayList::objPosArrayList()
{
    arrayCapacity = 200;
    listSize = 0;
    aList = new objPos[arrayCapacity];
}

//destructor routine; deletes pointer to [objPos] object created in the .h file
objPosArrayList::~objPosArrayList()
{
    delete []aList;
}

//copy constructor
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

//copy assignment operator
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

//getter for the used length of the array
int objPosArrayList::getSize() const
{
    return listSize;
}

//shifts the position of all objects in the array ahead by 1 and uses the inputted parameter [objPos] object as the first entry
//also increments the used size by 1
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

//adds the inputted parameter [objPos] object as the next entry after the last non-NULL entry
//also increments the used size by 1
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

//adds the inputted parameter [objPos] object in the index specified from the input and shifts everything after it down by 1
//also increments the used length by 1
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

//removes the first entry in the array and shifts every other entry up by 1
//also decreases the used length by 1
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

//removes the last non-NULL entry in the array by setting its position and symbol to 0,0, and NULL respectively
//also decreases the used length by 1
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

//removes the entry at the specified index in the parameter input and shifts every entry after the index up by 1
//also decreases the used length by 1
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

//getter for the first object in the array
objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

//getter for the last object in the array
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

//getter for the object in the specified index in the parameter input
objPos objPosArrayList::getElement(int index) const
{
    if(index<arrayCapacity)
    {
        return aList[index];
    }
    //catches indices that are out of the range of the array
    else
    {
        throw std::out_of_range("Invalid indexes.");
    }
    
}