#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

    class Food{
        private:
            objPos foodPos;
            
            GameMechs* mainGameMechRef;

        public:
            Food(GameMechs* thisGMRef);
            ~Food();

            void generateFood(objPosArrayList *blockOff);

            objPos getFoodPos() const;
    };


#endif