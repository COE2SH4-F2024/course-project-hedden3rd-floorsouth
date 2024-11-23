#include "GameMechs.h"

GameMechs::GameMechs()
{
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    // i implemented this for check iteration 1A
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
    
}

bool GameMechs::getExitFlagStatus() const
{

}

bool GameMechs::getLoseFlagStatus() const
{

}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{

}

void GameMechs::incrementScore()
{
    
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

}

void GameMechs::setLoseFlag()
{
    
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