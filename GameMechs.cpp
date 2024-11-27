#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    boardSizeX=30;
    boardSizeY=15;
    input = 0;
    exitFlag = false;
    loseFlag = false;
    // implement food later
    map=new char*[boardSizeY];
    for (int i =0; i<boardSizeY;i++)
    {
        map[i] = new char[boardSizeX];
        for (int j=0; j<boardSizeX;j++)
        {
            if(i==0 || i==boardSizeY-1)
            {
                map[i][j] = 35;
            }
            else if (j==0 || j==boardSizeX-1)
            {
                map[i][j] = 35;
            }
            else
            {
                map[i][j] = 32;
            }
        }
    }
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    input = 0;
    exitFlag = false;
    loseFlag = false;
    // implement food later
    map=new char*[boardSizeY];
    for (int i =0; i<boardSizeY;i++)
    {
        map[i] = new char[boardSizeX];
        for (int j=0; j<boardSizeX;j++)
        {
            if(i==0 || i==boardSizeY-1)
            {
                map[i][j] = 35;
            }
            else if (j==0 || j==boardSizeX-1)
            {
                map[i][j] = 35;
            }
            else
            {
                map[i][j] = 32;
            }
        }
    }
}

// do you need a destructor?
// yes
GameMechs::~GameMechs()
{
    //for Part 2B, keep blank for now -JW
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    //implement after Part 2B as food is needed to increase score -JW
}

void GameMechs::incrementScore()
{
    //same as above -JW
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag=true;
}

void GameMechs::setLoseFlag()
{
    loseFlag=true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
// this is the method for the map to store the display
char GameMechs::getElementMap(int y,int x)
{
    return map[y][x];
}
void GameMechs::setElementMap(int y,int x, char sym)
{
    map[y][x]=sym;
}