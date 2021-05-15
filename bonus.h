#include <stdio.h>
#include <math.h>
#include <time.h> 
#include <assert.h>
#include "lowLevel.h"
#include <stdlib.h>
typedef struct{
    double posX;
    double posY;
    double width;
    double height;
    uint16_t color;
    bool passed;
} Bonus;


Bonus* generateBonus(int y);
Bonus * updateBonus(Bonus* bonus, double engineThrust);