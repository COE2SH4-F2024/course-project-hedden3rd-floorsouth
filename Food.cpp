#include "Food.h"
#include <stdlib.h>
#include <time.h>

//initialization routine for food generation and related logic
//takes in pointer to [gamemechs] as parameter
Food::Food(GameMechs* thisGMRef)
{
    //sets up foodBucket as an [objPosArrayList] array object
    foodBucket=new objPosArrayList;
    for(int i=0;i<5;i++)
    {
        this->foodBucket->insertTail(objPos(0,0,38));
    }

    //links [gamemechs] to local variable thisGMRef
    this->mainGameMechRef =thisGMRef;
}

//destructor routine
Food::~Food()
{
    delete foodBucket;
}

//copy constructor
Food::Food(const Food &F)
{
    if (this != &F)
    {
        this->foodBucket = new objPosArrayList;
        this->foodBucket = F.foodBucket;
        this->mainGameMechRef = F.mainGameMechRef;
    }
}

//copy assignment operator
Food& Food ::operator=(const Food &F)
{
    if (this != &F)
    {
        this->foodBucket = F.foodBucket;
        this->mainGameMechRef = F.mainGameMechRef;
    }
    return *this;
}

//setter + logic for food generation
//takes in a pointer to [objPosArrayList] object containing the position of the player snake
void Food::generateFood(objPosArrayList *blockOff)
{
    //delete old food
    for (int i=0; i<5; i++)
    {
        mainGameMechRef->setElementMap(foodBucket->getHeadElement().pos->y,foodBucket->getHeadElement().pos->x,32);
        this->foodBucket->removeHead();
    }
    //generate new food items
    srand(time(NULL));
    int x=0;
    int y=0;
    for(int i=0;i<5;i++)
    {
        bool overlap=true;
        while(overlap)
        {
            overlap = false;
            x=rand() % (mainGameMechRef->getBoardSizeX()-3) + 1; 
            y=rand() % (mainGameMechRef->getBoardSizeY()-3) + 1;
            // check has it generate before
            for(int j=0;j<i;j++)
            {
                if(foodBucket->getElement(j).pos->x==x&&foodBucket->getElement(j).pos->y==y)
                {
                    overlap== true;
                    break;
                }
            }
            if(overlap==false)
            {
                // check did it crash the location of the player
                for(int k=0;k<blockOff->getSize();k++)
                {
                    if(blockOff->getElement(k).getObjPos().pos->x==x &&blockOff->getElement(k).getObjPos().pos->y==y)
                    {
                        overlap = true;
                        break;
                    }
                }
            }
        }
        // insert to the list with specific details & update board
        // first 2 is 2 different special food, others are normal food
        if (i==0)
        {
            this->foodBucket->insertTail(objPos(x,y,36));
            mainGameMechRef->setElementMap(y,x,36);
        }
        else if(i==1)
        {
            this->foodBucket->insertTail(objPos(x,y,64));
            mainGameMechRef->setElementMap(y,x,64);
        }
        else
        {
            this->foodBucket->insertTail(objPos(x,y,38));
            mainGameMechRef->setElementMap(y,x,38);
        }
    }
}

//getter for the current position of the food
objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}