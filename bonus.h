#ifndef __BONUS_H__
#define __BONUS_H__

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "lowLevel.h"

typedef struct{
    double posX;
    double posY;

    double width;
    double height;

    uint16_t color;
    bool passed;
} Bonus;

/**
 * generates bonus on the right edge of the screen in height y
 * returns newly generated bonus
*/
Bonus* generateBonus(int y);

/**
 * updates bonus' position and if offscreen, disposes of it
 * returns updated bonus (if disposed returns null)
*/
Bonus * updateBonus(Bonus* bonus, double engineThrust);

#endif
