//guide for comments
//[example] denotes a class in a different .cpp file
//<example> denotes the keyboard input

#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

//importing other classes using pointers
GameMechs *gamem ;
Player *playerpt;
Food *foodpt;

//headers
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


//main
int main(void)
{
    //main loop runs through standard procedure functions
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

    //initialize relevant classes with corresponding parameters
    gamem = new GameMechs();
    foodpt = new Food(gamem);
    playerpt = new Player(gamem,foodpt);

    //set the map to be drawn with the correct starting player position, a single-block length, and generates food using its own method
    gamem->setElementMap(playerpt->getPlayerPos()->getHeadElement().pos->y,playerpt->getPlayerPos()->getHeadElement().pos->x,playerpt->getPlayerPos()->getHeadElement().symbol);
    foodpt->generateFood(playerpt->getPlayerPos());
}

void GetInput(void)
{
    //standard input detection but feeds result to [gamemechs]
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
    //gets the input entered/detected in getinput() from [gamemechs]
    if (gamem->getInput() != 0)
    {
        switch(gamem->getInput())
        {
            //sets the exit condition to true if a <space> input is detected
            case 32:
                gamem->setExitTrue();
            break;
        }
    }
    //calls function in [player] to update direction based on input
    playerpt->updatePlayerDir();
    //calls function in [player] for movement logic and associated logic
    playerpt->movePlayer();
    //gamem->clearInput();//CHECK IF THIS IS NEEDED
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   
    //prints the current game score from [gamemechs]
    MacUILib_printf("Special food: @,$\n ");
    MacUILib_printf("Your score is %d\n",gamem->getScore());
    //prints the previously set up game board
    for(int i=0; i<gamem->getBoardSizeY();i++)
    {
        for(int j=0; j<gamem->getBoardSizeX();j++)
        {
            MacUILib_printf("%c",gamem->getElementMap(i,j));
        }
        MacUILib_printf("\n");
    }
    //lose and exit conditions; print a unique message for each
    if(gamem->getExitFlagStatus()&&gamem->getLoseFlagStatus())
    {
        MacUILib_printf("You lose !\n");
    }
    else if(gamem->getExitFlagStatus())
    {
        MacUILib_printf("You win\n");
    }
    //MacUILib_clearScreen();//CHECK IF THIS IS NEEDED
     
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
