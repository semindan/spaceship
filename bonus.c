#include "bonus.h"

/*  generates bonus on the right edge of the screen in height y */
Bonus *generateBonus(int y)
{
    Bonus *bonus = malloc(sizeof(Bonus));

    bonus->width = 15;
    bonus->height = 7;

    bonus->posX = SCREEN_WIDTH - bonus->width;
    bonus->posY = y;

    bonus->color = getColor(255, 0, 255);
    bonus->passed = false;

    return bonus;
}

/*  updates bonus' position and if offscreen, disposes of it    */
Bonus *updateBonus(Bonus *bonus, double engineThrust)
{
    if (bonus != NULL)
    {
        bonus->posX -= abs(engineThrust);

        if (bonus->posX + bonus->width < 0)
        {
            free(bonus);
            return NULL;
        }
    }

    return bonus;
}
