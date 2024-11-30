#include "objPos.h"

//initialization routine for a new standard object with a position of 0,0 and a NULL character
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

//initialization routine or a new object with custom position and symbol; input via parameters
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//destructor routine; deletes pointer to struct Pos
objPos :: ~objPos()
{
    delete pos;
}

//copy constructor
objPos::objPos(const objPos &oP)
{
    pos = new Pos;
    this->pos->x = oP.pos->x;
    this->pos->y = oP.pos->y;
    this->symbol = oP.symbol;
}

//copy assignment operator
objPos& objPos :: operator=(const objPos &oP)
{
    if(this != &oP)
    {
        //delete this->pos;//CHECK IF THIS IS NECESSARY
        //this->pos = new Pos;//CHECK IF THIS IS NECESSARY
        this->pos->x = oP.pos->x;
        this->pos->y = oP.pos->y;
        this->symbol = oP.symbol;
    }
    return *this;
}

//setter from an object inputted via parameter
void objPos::setObjPos(objPos o)
{
    //takes the position and symbol values of the object o and sets them to the current object
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

//setter from custom input position and symbol values
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//getter for the current object as an [objPos] object; making a copy of the current object
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

//getter for the symbol of the object
char objPos::getSymbol() const
{
    return symbol;
}

//tests if an object inputted via parameter is equal position wise to the current object
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
