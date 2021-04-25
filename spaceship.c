#include "spaceship.h"

void spaceshipInit(Spaceship* sp){
    sp->movementVec = {0.0, 0.0};
    sp->headingVec = {1.0, 0.0};
    sp->engineThrust = 0;

    sp->hp = 3;
    sp->speedBoost = false;
    sp->invincible = false;
}

void spaceshipUpdate(Spaceship *sp){
    sp->movementVec[0] = sp->movementVec[0] + sp->headingVec[0]*sp->engineThrust;
    sp->movementVec[1] = sp->movementVec[1] + sp->headingVec[1]*sp->engineThrust;


}
