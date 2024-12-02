#include "GameMechs.h"
#include "MacUILib.h"

//initialize routine for a standard board size of 30w x 15l
GameMechs::GameMechs()
{
    boardSizeX=30;
    boardSizeY=15;
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
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

//initialization routine for a custom size game board; dimensions are specified in parameters
GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
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

//destructor routine; deletes map elements from heap
GameMechs::~GameMechs()
{
    for(int i=0;i<boardSizeY;i++)
    {
        delete[] map[i];
        map[i]=NULL;
    }
    delete [] map;
    map = NULL;
}

//getter for exit flag status
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

//getter for loss flag status
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

//getter for current input
char GameMechs::getInput() const
{
    return input;
}

//getter for current score
int GameMechs::getScore() const
{
    return score;
}

//getter for the width of the game board
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

//getter for the length of the game board
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

//setter to change the exit flag status to true
void GameMechs::setExitTrue()
{
    exitFlag=true;
}

//setter to change the loss flag status to true
void GameMechs::setLoseFlag()
{
    loseFlag=true;
}

//setter to update the input to a new one detected in [project]
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

//setter to clear the input; setting it to NULL
void GameMechs::clearInput()
{
    input = 0;
}

//setter to increase the score by 1
void GameMechs::incrementScore(int multiple)
{
    score += multiple;
}

//this is the method for the map to store the display
//getter for the 2D array for game board visuals
char GameMechs::getElementMap(int y,int x)
{
    return map[y][x];
}

//setter for a space in the 2D array for game board visuals; unique symbols can be inputted via the parameter sym
void GameMechs::setElementMap(int y,int x, char sym)
{
    map[y][x]=sym;
}