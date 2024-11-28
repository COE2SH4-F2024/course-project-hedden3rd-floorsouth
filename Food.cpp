#include "Food.h"
#include <stdlib.h>
#include <time.h>

Food::Food(){
    foodPos=objPos();
}

Food::~Food(){
    delete[] mainGameMechRef;
}

void Food::generateFood(objPosArrayList *blockOff){
    //generate food randomly except at blockOff coordinates
    bool overlap=false;
    srand(time(NULL));

    this->foodPos.pos->x=rand() % (mainGameMechRef->getBoardSizeX()-1) + 1; //calls GameMech to allow different board sizes to be permitted -JW
    this->foodPos.pos->y=rand() % (mainGameMechRef->getBoardSizeY()-1) + 1;

    while (true){
        for (int i; i<blockOff->getSize(); i++){
            if (this->foodPos.pos==blockOff->getElement(i).pos){
                srand(time(NULL));
                this->foodPos.pos->x=rand() % (mainGameMechRef->getBoardSizeX()-1) + 1;
                this->foodPos.pos->y=rand() % (mainGameMechRef->getBoardSizeY()-1) + 1;

                overlap=true;
                break;
            }
        }

        if (overlap==false){
            break;
        }
    }

    mainGameMechRef->setElementMap(this->foodPos.pos->y,this->foodPos.pos->x,38);
    //use set element map for food location (GameMech class) and updates visuals to prep for draw screen -JW
}

objPos Food::getFoodPos() const{
    //get position
    return foodPos;
}