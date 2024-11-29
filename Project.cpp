#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gamem ;
Player *playerpt;
Food *foodpt;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gamem->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gamem = new GameMechs();
    foodpt = new Food(gamem);
    playerpt = new Player(gamem,foodpt);

    gamem->setElementMap(playerpt->getPlayerPos()->getHeadElement().pos->y,playerpt->getPlayerPos()->getHeadElement().pos->x,playerpt->getPlayerPos()->getHeadElement().symbol);
    foodpt->generateFood(playerpt->getPlayerPos());
}

void GetInput(void)
{
   if (MacUILib_hasChar() != 0)
    {
        gamem->setInput( MacUILib_getChar());
    }
    else
    {
        gamem->setInput(0);
    }
}

void RunLogic(void)
{
    if (gamem->getInput() != 0)
    {
        switch(gamem->getInput())
        {
            case 32:
                gamem->setExitTrue();
            break;
        }
    }
    playerpt->updatePlayerDir();
    playerpt->movePlayer();
    //gamem->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   
    MacUILib_printf("Your score is %d\n",gamem->getScore());
    for(int i=0; i<gamem->getBoardSizeY();i++)
    {
        for(int j=0; j<gamem->getBoardSizeX();j++)
        {
            MacUILib_printf("%c",gamem->getElementMap(i,j));
        }
        MacUILib_printf("\n");
    }
    if(gamem->getExitFlagStatus()&&gamem->getLoseFlagStatus())
    {
        MacUILib_printf("You lose !\n");
    }
    else if(gamem->getExitFlagStatus())
    {
        MacUILib_printf("You win\n");
    }
    //MacUILib_clearScreen();
     
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //delete[] playerpt;
    //gamem->~GameMechs();
    //playerpt->~Player();
    //foodpt->~Food();
    //gamem->~GameMechs();
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
