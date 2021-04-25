#include "spaceship.h"

// move someplace else
#define M_PI   3.14159265358979323846264338327950288
double deg2rad(double degrees){
    return degrees * M_PI / 180.0;
}
double rad2deg(double radians){
    return radians * 180.0 / M_PI;
}

void spaceshipInit(Spaceship* sp){
    sp->movementVec[0] = 1.0;
    sp->movementVec[1] = 0.0;
    sp->headingAngle = 90.0;
    sp->engineThrust = 0.0;

    sp->hp = 3;
    sp->speedBoost = false;
    sp->invincible = false;
}

// check if calc is correct
void spaceshipUpdate(Spaceship *sp){
    sp->movementVec[0] += cos(deg2rad(sp->headingAngle)) * sp->engineThrust;
    sp->movementVec[1] += sin(deg2rad(sp->headingAngle)) * sp->engineThrust;

}
