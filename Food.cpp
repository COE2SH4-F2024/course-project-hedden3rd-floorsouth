#include "Food.h"
#include <stdlib.h>
#include <time.h>

//initialization routine for food generation and related logic
//takes in pointer to [gamemechs] as parameter
Food::Food(GameMechs* thisGMRef)
{
    //sets up foodBucket as an [objPosArrayList] array object
    foodBucket=new objPosArrayList;

    //links [gamemechs] to local variable thisGMRef
    this->mainGameMechRef =thisGMRef;
}

//destructor routine; deletes the pointer to [gamemechs]
Food::~Food()
{
    delete mainGameMechRef;
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
    //generate food randomly except at blockOff coordinates
    bool overlap=true;
    int x[8]={};
    int y[8]={};

    //if (index==999){
        for (int i=0; i<5; i++){
            srand(time(NULL)+i*29);

            //calls GameMech to allow different board sizes to be permitted -JW
            x[i]=rand() % (mainGameMechRef->getBoardSizeX()-3) + 1; 
            y[i]=rand() % (mainGameMechRef->getBoardSizeY()-3) + 1;
        }
    //}
    /*else{
        srand(time(NULL));

        x[index]=rand() % (mainGameMechRef->getBoardSizeX()-3) + 1;
        y[index]=rand() % (mainGameMechRef->getBoardSizeY()-3) + 1;
    }*/


    //continually tests if there is an overlap in the position of the food to be generated and blockOff coordinates
    //exits loop when there is no overlap
    while (overlap){
        overlap = false;
        for (int i=0; i<5; i++){
            for (int j = 0; j<blockOff->getSize(); j++){
                if ((x[i]==blockOff->getElement(j).pos->x)&&(y[i]==blockOff->getElement(j).pos->y)){
                    srand(time(NULL)+i*j*7);
                    x[i]=rand() % (mainGameMechRef->getBoardSizeX()-3) + 1;
                    y[i]=rand() % (mainGameMechRef->getBoardSizeY()-3) + 1;

                    overlap=true;
                    break;
                }
            }

            for (int k=1; k<(5-i); k++){
                if ((x[i]==x[i+k])&&(y[i]==y[i+k])){
                    srand(time(NULL)+i*23);
                    x[i]=rand() % (mainGameMechRef->getBoardSizeX()-3) + 1;
                    y[i]=rand() % (mainGameMechRef->getBoardSizeY()-3) + 1;

                    overlap=true;
                    break;
                }
            }

            if (overlap){
                break;
            }
        }
    }

    for (int i=0; i<5; i++){
        mainGameMechRef->setElementMap(foodBucket->getElement(i).pos->x,foodBucket->getElement(i).pos->y,32);
    }
    //sets the coordinates of the food officially
    for (int i=0; i<5; i++){
        foodBucket->insertIndex(objPos(x[i],y[i],38),i);
        //use set element map for food location (GameMech class) and updates visuals to prep for draw screen -JW
        mainGameMechRef->setElementMap(y[i],x[i],38);
    }
  
}

//getter for the current position of the food
objPos Food::getFoodPos(int index) const
{
    return foodBucket->getElement(index);
}