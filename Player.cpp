#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos = objPos(15,9,42);
}


Player::~Player()
{
    // delete any heap members here
    delete[] mainGameMechsRef;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
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
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,32);
        playerPos.pos->x -=1;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,playerPos.symbol);
        // player.x-=1;
        // board[player.y][player.x] = player.symbol;
    }
    else if (myDir == RIGHT)
    {
        // board[player.y][player.x] = 32;
        // player.x +=1;
        // board[player.y][player.x] = player.symbol;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,32);
        playerPos.pos->x +=1;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,playerPos.symbol);
    }
    else if (myDir == UP)
    {
        // board[player.y][player.x] = 32;
        // player.y -=1;
        // board[player.y][player.x] = player.symbol;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,32);
        playerPos.pos->y -=1;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,playerPos.symbol);
    }
    else if (myDir == DOWN)
    {
        // board[player.y][player.x] = 32;
        // player.y +=1;
        // board[player.y][player.x] = player.symbol;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,32);
        playerPos.pos->y +=1;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,playerPos.symbol);
    }

    if (playerPos.pos->x <= 0)
    {
        // board[player.y][player.x] = 35;
        // player.x = 18;
        // board[player.y][player.x] = player.symbol;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,35);
        playerPos.pos->x =(mainGameMechsRef->getBoardSizeX())-2;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,playerPos.symbol);
    }
    else if (playerPos.pos->x >= 29)
    {
        // board[player.y][player.x] = 35;
        // player.x = 1;
        // board[player.y][player.x] = player.symbol;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,35);
        playerPos.pos->x =1;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,playerPos.symbol);
    }
    else if (playerPos.pos->y <= 0)
    {
        // board[player.y][player.x] = 35;
        // player.y = 8;
        // board[player.y][player.x] = player.symbol;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,35);
        playerPos.pos->y =(mainGameMechsRef->getBoardSizeY())-2;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,playerPos.symbol);
    }
    else if (playerPos.pos->y >= 14)
    {
        // board[player.y][player.x] = 35;
        // player.y = 1;
        // board[player.y][player.x] = player.symbol;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,35);
        playerPos.pos->y =1;
        mainGameMechsRef->setElementMap(playerPos.pos->y,playerPos.pos->x,playerPos.symbol);
    }
}

// More methods to be added