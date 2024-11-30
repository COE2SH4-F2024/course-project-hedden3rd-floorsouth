#include "Food.h"
#include <stdlib.h>
#include <time.h>

//initialization routine for food generation and related logic
//takes in pointer to [gamemechs] as parameter
Food::Food(GameMechs* thisGMRef)
{
    //sets up foodPos as an [objPos] object
    this->foodPos=objPos(1,1,38);
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
        this->foodPos = F.foodPos;
        this->mainGameMechRef = F.mainGameMechRef;
    }
}

//copy assignment operator
Food& Food ::operator=(const Food &F)
{
    if (this != &F)
        {
            this->foodPos = F.foodPos;
            this->mainGameMechRef = F.mainGameMechRef;
        }
}

//setter + logic for food generation
//takes in a pointer to [objPosArrayList] object containing the position of the player snake
void Food::generateFood(objPosArrayList *blockOff)
{
    //generate food randomly except at blockOff coordinates
    bool overlap=true;
    srand(time(NULL));

    //calls GameMech to allow different board sizes to be permitted -JW
    int x=rand() % (mainGameMechRef->getBoardSizeX()-3) + 1; 
    int y=rand() % (mainGameMechRef->getBoardSizeY()-3) + 1;

    //continually tests if there is an overlap in the position of the food to be generated and blockOff coordinates
    //exits loop when there is no overlap
    while (overlap){
        overlap = false;
        for (int i = 0; i<blockOff->getSize(); i++){
            if ((x==blockOff->getElement(i).pos->x)&&(y==blockOff->getElement(i).pos->y))
            {
                srand(time(NULL));
                x=rand() % (mainGameMechRef->getBoardSizeX()-3) + 1;
                y=rand() % (mainGameMechRef->getBoardSizeY()-3) + 1;

                overlap=true;
                break;
            }
        }
    }

    //sets the coordinates of the food officially
    this->foodPos.pos->x=x;
    this->foodPos.pos->y=y;
    //use set element map for food location (GameMech class) and updates visuals to prep for draw screen -JW
    mainGameMechRef->setElementMap(this->foodPos.pos->y,this->foodPos.pos->x,this->foodPos.symbol);
}

//getter for the current position of the food
objPos Food::getFoodPos() const
{
    return foodPos;
}