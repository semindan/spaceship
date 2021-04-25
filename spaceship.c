#include "spaceship.h"

void spaceshipInit(Spaceship* sp){
    sp->movementVec[0] = 1.0;
    sp->movementVec[1] = 0.0;
    sp->headingAngle = 90.0;
    sp->engineThrust = 0.0;

    sp->hp = 3;
    sp->speedBoost = false;
    sp->invincible = false;
}

void spaceshipUpdate(Spaceship *sp){
    sp->movementVec[0] += sin(sp->headingAngle) * sp->engineThrust;
    sp->movementVec[1] += cos(sp->headingAngle) * sp->engineThrust;

}
