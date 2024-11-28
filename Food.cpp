#include "Food.h"
#include <stdlib.h>
#include <time.h>

Food::Food(GameMechs* thisGMRef){
    this->foodPos=objPos(1,1,38);
    this->mainGameMechRef =thisGMRef;
}

Food::~Food(){
    //delete[] mainGameMechRef;
}

void Food::generateFood(objPosArrayList *blockOff){
    //generate food randomly except at blockOff coordinates
    bool overlap=true;
    srand(time(NULL));

    int x=rand() % (mainGameMechRef->getBoardSizeX()-3) + 1; //calls GameMech to allow different board sizes to be permitted -JW
    int y=rand() % (mainGameMechRef->getBoardSizeY()-3) + 1;
    //int x = 16;
    //int y = 9;
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

        // if (overlap==false){
        //     break;
        // }
    }
    this->foodPos.pos->x=x;
    this->foodPos.pos->y=y;
    //use set element map for food location (GameMech class) and updates visuals to prep for draw screen -JW
    mainGameMechRef->setElementMap(this->foodPos.pos->y,this->foodPos.pos->x,this->foodPos.symbol);
}

objPos Food::getFoodPos() const{
    //get position
    return foodPos;
}