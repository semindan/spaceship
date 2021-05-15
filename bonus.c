#include "bonus.h"


Bonus* generateBonus(int y){
    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->posX = SCREEN_WIDTH;
    bonus->posY = SCREEN_HEIGHT;
    bonus->width = bonus->heigth = 15;
    bonus->color = getColor(255,0,0);
    bonus->passed = false;
    return bonus;
}
Bonus * updateBonus(Bonus* bonus, double engineThrust){
if(bonus != NULL){
    bonus->posX -= abs(engineThrust);
    if(bonus->posX + bonus->width < 0 ){
            free(bonus);
            return NULL;
    }
}
return bonus;

}
