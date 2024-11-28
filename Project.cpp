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
//char** map;
// char input;

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

    gamem = new GameMechs(30,15);
    foodpt = new Food(gamem);
    playerpt = new Player(gamem,foodpt);
    // map=new char*[15];
    // for (int i =0; i<15;i++)
    // {
    //     map[i] = new char[30];
    //     for (int j=0; j<30;j++)
    //     {
    //         if(i==0 || i==14)
    //         {
    //             map[i][j] = 35;
    //         }
    //         else if (j==0 || j==29)
    //         {
    //             map[i][j] = 35;
    //         }
    //         else
    //         {
    //             map[i][j] = 32;
    //         }
    //     }
    // }
    //map[playerpt->getPlayerPos().pos->y][playerpt->getPlayerPos().pos->x] = 42;
    for (int i=0;i<playerpt->getPlayerPos()->getSize();i++)
    {
        gamem->setElementMap(playerpt->getPlayerPos()->getElement(i).pos->y,playerpt->getPlayerPos()->getElement(i).pos->x,playerpt->getPlayerPos()->getElement(i).symbol);
    }
    
    foodpt->generateFood(playerpt->getPlayerPos());
    gamem->setElementMap(foodpt->getFoodPos().pos->y,foodpt->getFoodPos().pos->x,foodpt->getFoodPos().symbol);
}

void GetInput(void)
{
   if (MacUILib_hasChar() != 0)
    {
        gamem->setInput( MacUILib_getChar());
        //input = MacUILib_getChar();
    }
    else
    {
        gamem->setInput(0);
        //input = 0;
    }
}

void RunLogic(void)
{
    //foodpt->generateFood(playerpt->getPlayerPos());
    gamem->setElementMap(foodpt->getFoodPos().pos->y,foodpt->getFoodPos().pos->x,foodpt->getFoodPos().symbol);

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
    for(int i=0; i<15;i++)
    {
        for(int j=0; j<30;j++)
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
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
