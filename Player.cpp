#include "Player.h"


Player::Player(GameMechs* thisGMRef,Food* thisFRef)
{
    foodRef = thisFRef;
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    //playerPos = objPos(15,9,42);
    // more actions to be included
    playerPosList = new objPosArrayList;
    // playerPosList->insertHead(objPos(12,9,42));
    // playerPosList->insertTail(objPos(13,9,42));
    // playerPosList->insertTail(objPos(14,9,42));
    playerPosList->insertTail(objPos(15,9,42));
    // playerPosList->insertTail(objPos(16,9,42));
    // playerPosList->insertTail(objPos(17,9,42));
    // playerPosList->insertTail(objPos(18,9,42));
    // playerPosList->insertTail(objPos(19,9,42));
}


Player::~Player()
{
    // delete any heap members here
    delete[] mainGameMechsRef;
}

Player::Player(const Player &p)
{
    if (this != &p)
        {
            this->mainGameMechsRef = p.mainGameMechsRef;
            this->myDir = p.myDir;
            this->playerPosList = new objPosArrayList;
            // for (int i=0;i<p.playerPosList->getSize();i++)
            // {
            //     this->playerPosList[i] = p.playerPosList[i];
            // }
            this->playerPosList = p.playerPosList;
        }   
}

Player& Player :: operator= (const Player &p)
{
    if (this != &p)
    {
        this->mainGameMechsRef = p.mainGameMechsRef;
        this->myDir = p.myDir;
        // for (int i=0;i<p.playerPosList->getSize();i++)
        // {
        //     this->playerPosList[i] = p.playerPosList[i];
        // }
        this->playerPosList = p.playerPosList;

    }
    return *this;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    //return playerPos;
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
        int new_x = playerPosList->getHeadElement().pos->x -1;
        int new_y = playerPosList->getHeadElement().pos->y;
        objPos newHead = playerPosList->getHeadElement();
        newHead.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        playerPosList->insertHead(newHead);
        if(checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
        if(checkFoodConsumption()== false)
        {
            mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
            playerPosList->removeTail();
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
        }
        else
        {
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
            foodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
        // playerPosList->getHeadElement().pos->y = new_y;
        // playerPosList->getHeadElement().pos->x = new_x;
        // player.x-=1;
        // board[player.y][player.x] = player.symbol;
    }
    else if (myDir == RIGHT)
    {
        // board[player.y][player.x] = 32;
        // player.x +=1;
        // board[player.y][player.x] = player.symbol;
        int new_x = playerPosList->getHeadElement().pos->x +1;
        int new_y = playerPosList->getHeadElement().pos->y;
        objPos newHead = playerPosList->getHeadElement();
        newHead.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
        playerPosList->insertHead(newHead);
        if(checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
        if(checkFoodConsumption()== false)
        {
            mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
            playerPosList->removeTail();
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
        }
        else
        {
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
            foodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
        //playerPosList->removeTail();
        // playerPosList->getHeadElement().pos->y = new_y;
        // playerPosList->getHeadElement().pos->x = new_x;
        //mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    else if (myDir == UP)
    {
        // board[player.y][player.x] = 32;
        // player.y -=1;
        // board[player.y][player.x] = player.symbol;
        int new_x = playerPosList->getHeadElement().pos->x;
        int new_y = playerPosList->getHeadElement().pos->y-1;
        objPos newHead = playerPosList->getHeadElement();
        newHead.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
        playerPosList->insertHead(newHead);
        if(checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
        if(checkFoodConsumption()== false)
        {
            mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
            playerPosList->removeTail();
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
        }
        else
        {
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
            foodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
        //playerPosList->removeTail();
        // playerPosList->getHeadElement().pos->y = new_y;
        // playerPosList->getHeadElement().pos->x = new_x;
        //mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    else if (myDir == DOWN)
    {
        // board[player.y][player.x] = 32;
        // player.y +=1;
        // board[player.y][player.x] = player.symbol;
        int new_x = playerPosList->getHeadElement().pos->x;
        int new_y = playerPosList->getHeadElement().pos->y+1;
        objPos newHead = playerPosList->getHeadElement();
        newHead.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
        playerPosList->insertHead(newHead);
        if(checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
        if(checkFoodConsumption()== false)
        {
            mainGameMechsRef->setElementMap(playerPosList->getTailElement().pos->y,playerPosList->getTailElement().pos->x,32);
            playerPosList->removeTail();
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
        }
        else
        {
            mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
            foodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
       // playerPosList->removeTail();
        // playerPosList->getHeadElement().pos->y = new_y;
        // playerPosList->getHeadElement().pos->x = new_x;
        //mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    
    if (playerPosList->getHeadElement().pos->x <= 0)
    {
        // board[player.y][player.x] = 35;
        // player.x = 18;
        // board[player.y][player.x] = player.symbol;
        int new_x = (mainGameMechsRef->getBoardSizeX())-2;
        int new_y = playerPosList->getHeadElement().pos->y;
        objPos newSwitch = playerPosList->getHeadElement();
        newSwitch.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,35);
        //playerPosList->getHeadElement().pos->x =(mainGameMechsRef->getBoardSizeX())-2;
        playerPosList->removeHead();
        playerPosList->insertHead(newSwitch);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    else if (playerPosList->getHeadElement().pos->x >= mainGameMechsRef->getBoardSizeX()-1)
    {
        // board[player.y][player.x] = 35;
        // player.x = 1;
        // board[player.y][player.x] = player.symbol;
        int new_x = 1;
        int new_y = playerPosList->getHeadElement().pos->y;
        objPos newSwitch = playerPosList->getHeadElement();
        newSwitch.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,35);
        //playerPosList->getHeadElement().pos->x =(mainGameMechsRef->getBoardSizeX())-2;
        playerPosList->removeHead();
        playerPosList->insertHead(newSwitch);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    else if (playerPosList->getHeadElement().pos->y <= 0)
    {
        // board[player.y][player.x] = 35;
        // player.y = 8;
        // board[player.y][player.x] = player.symbol;
        int new_x = playerPosList->getHeadElement().pos->x;
        int new_y = (mainGameMechsRef->getBoardSizeY())-2;
        objPos newSwitch = playerPosList->getHeadElement();
        newSwitch.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,35);
        //playerPosList->getHeadElement().pos->x =(mainGameMechsRef->getBoardSizeX())-2;
        playerPosList->removeHead();
        playerPosList->insertHead(newSwitch);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,playerPosList->getHeadElement().symbol);
    }
    else if (playerPosList->getHeadElement().pos->y >= mainGameMechsRef->getBoardSizeY()-1)
    {
        // board[player.y][player.x] = 35;
        // player.y = 1;
        // board[player.y][player.x] = player.symbol;
        int new_x = playerPosList->getHeadElement().pos->x;
        int new_y = 1;
        objPos newSwitch = playerPosList->getHeadElement();
        newSwitch.setObjPos(new_x,new_y,playerPosList->getHeadElement().symbol);
        mainGameMechsRef->setElementMap(playerPosList->getHeadElement().pos->y,playerPosList->getHeadElement().pos->x,35);
        //playerPosList->getHeadElement().pos->x =(mainGameMechsRef->getBoardSizeX())-2;
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

