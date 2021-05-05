#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <stdbool.h>
#include <math.h>

typedef struct{
    double movementVec[2];
    int dimensionsVec[2];
    
    // normalized
    double headingAngle;
    double engineThrust;

    double sizeX;
    double sizeY;
    double maxThrust;

    int hp;
    bool speedBoost;
    bool invincible;
} Spaceship;


/*  initializes default values to spaceship  */
void spaceshipInit(Spaceship* sp);

/*  Updates spaceship movement  */
void spaceshipUpdate(Spaceship *sp);

#endif /* __SPACESHIP_H__ */
