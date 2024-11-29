#include "Player.h"


Player::Player(GameMechs* thisGMRef,Food* thisFRef)
{
    foodRef = thisFRef;
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;
    playerPosList->insertHead(objPos(15,9,42));
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
    delete foodRef;
    //delete playerPosList;
    playerPosList->~objPosArrayList();
}

Player::Player(const Player &p)
{
    if (this != &p)
        {
            this->mainGameMechsRef = p.mainGameMechsRef;
            this->myDir = p.myDir;
            this->playerPosList = new objPosArrayList;
            this->playerPosList = p.playerPosList;
        }   
}

Player& Player :: operator= (const Player &p)
{
    if (this != &p)
    {
        this->mainGameMechsRef = p.mainGameMechsRef;
        this->myDir = p.myDir;
        this->playerPosList = p.playerPosList;

    }
    return *this;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic
        char input = mainGameMechsRef->getInput(); 
        Dir action = STOP;
        if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            // Add more key processing here
            case 119:
                action = UP;
                break;
            
            case 97:
                action = LEFT;
                break;

            case 100:
                action = RIGHT;
                break;
            
            case 115:
                action = DOWN;
                break;
            // Add more key processing here
            // Add more key processing here    


            default:
                break;
        }
        input = 0;
    }
    if (myDir == UP || myDir == DOWN)
    {
        if (action == LEFT)
        {
            myDir = LEFT;
        }
        else if (action == RIGHT)
        {
            myDir = RIGHT;
        }
    }
    else if (myDir == LEFT || myDir == RIGHT)
    {
        if (action == UP)
        {
            myDir = UP;
        }
        else if (action == DOWN)
        {
            myDir = DOWN;
        }
    }
    else
    {
        if (action == LEFT)
        {
            myDir = LEFT;
        }
        else if (action == RIGHT)
        {
            myDir = RIGHT;
        }
        else if (action == UP)
        {
            myDir = UP;
        }
        else if (action == DOWN)
        {
            myDir = DOWN;
        }
    }         
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    if (myDir == LEFT)
    {
        //make a new instances of the head element & update the coordinates;
        int new_x = playerPosList->getHeadElement().pos->x -1;
        int new_y = playerPosList->getHeadElement().pos->y;
        objPos newHead = playerPosList->getHeadElement();
        newHead.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        // add the new head to the list
        playerPosList->insertHead(newHead);
        // check for collision
        if(checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
        //check for consumption
        if(checkFoodConsumption()== false)
        {
            //remove tail
            mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
            playerPosList->removeTail();
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
        }
        else
        {
            //generate new food
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
            foodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
    }
    else if (myDir == RIGHT)
    {
        // generate new instances of head element
        int new_x = playerPosList->getHeadElement().pos->x +1;
        int new_y = playerPosList->getHeadElement().pos->y;
        objPos newHead = playerPosList->getHeadElement();
        newHead.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        // insert new head
        playerPosList->insertHead(newHead);
        //check for collision
        if(checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
        // check food consumption
        if(checkFoodConsumption()== false)
        {
           //remove tail
            mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
            playerPosList->removeTail();
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
        }
        else
        {
            // add score
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
            foodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
    }
    else if (myDir == UP)
    {
        // make a new instance of head element with new coordinates
        int new_x = playerPosList->getHeadElement().pos->x;
        int new_y = playerPosList->getHeadElement().pos->y-1;
        objPos newHead = playerPosList->getHeadElement();
        newHead.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        //add new head
        playerPosList->insertHead(newHead);
        // check collisiom
        if(checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
        // check food consumption
        if(checkFoodConsumption()== false)
        {
            // remove tail
            mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
            playerPosList->removeTail();
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
        }
        else
        {
            // increment score
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
            foodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
    }
    else if (myDir == DOWN)
    {
        // make new instances of head element with new coordinates
        int new_x = playerPosList->getHeadElement().pos->x;
        int new_y = playerPosList->getHeadElement().pos->y+1;
        objPos newHead = playerPosList->getHeadElement();
        newHead.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        playerPosList->insertHead(newHead);
        // check collision
        if(checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
        // check food consumption
        if(checkFoodConsumption()== false)
        {
            // remove tail
            mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
            playerPosList->removeTail();
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
        }
        else
        {
            // increment score
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
            foodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
    }
    
    if (playerPosList->getHeadElement().pos->x <= 0)
    {
        // generate new coordinate and make a new instances
        int new_x = (mainGameMechsRef->getBoardSizeX())-2;
        int new_y = playerPosList->getHeadElement().pos->y;
        objPos newSwitch = playerPosList->getHeadElement();
        newSwitch.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        // move the head position
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,35);
        playerPosList->removeHead();
        playerPosList->insertHead(newSwitch);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    else if (playerPosList->getHeadElement().pos->x >= mainGameMechsRef->getBoardSizeX()-1)
    {
        // generate new coordinate and make a new instances
        int new_x = 1;
        int new_y = playerPosList->getHeadElement().pos->y;
        objPos newSwitch = playerPosList->getHeadElement();
        newSwitch.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        // move head position
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,35);
        playerPosList->removeHead();
        playerPosList->insertHead(newSwitch);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    else if (playerPosList->getHeadElement().pos->y <= 0)
    {
        // generate new coordinate and make a new instances
        int new_x = playerPosList->getHeadElement().pos->x;
        int new_y = (mainGameMechsRef->getBoardSizeY())-2;
        objPos newSwitch = playerPosList->getHeadElement();
        newSwitch.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        // move head position
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,35);
        playerPosList->removeHead();
        playerPosList->insertHead(newSwitch);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    else if (playerPosList->getHeadElement().pos->y >= mainGameMechsRef->getBoardSizeY()-1)
    {
        // generate new coordinate and make a new instances
        int new_x = playerPosList->getHeadElement().pos->x;
        int new_y = 1;
        objPos newSwitch = playerPosList->getHeadElement();
        newSwitch.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        // move head position
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,35);
        playerPosList->removeHead();
        playerPosList->insertHead(newSwitch);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
}

// More methods to be added
bool Player::checkFoodConsumption()
{
    if (this->playerPosList->getHeadElement().pos->x == foodRef->getFoodPos().pos->x&&this->playerPosList->getHeadElement().pos->y == foodRef->getFoodPos().pos->y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Player::checkSelfCollision()
{
    for (int i =1;i<playerPosList->getSize();i++)
    {
        if (this->playerPosList->getElement(i).pos->x == this->playerPosList->getHeadElement().pos->x&&this->playerPosList->getElement(i).pos->y == this->playerPosList->getHeadElement().pos->y)
        {
            return true;
        }
    }
    return false;
    
}

