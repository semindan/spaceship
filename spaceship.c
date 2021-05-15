#include "spaceship.h"

// move someplace else
//#define M_PI   3.14159265358979323846264338327950288
double deg2rad(double degrees){
    return degrees * M_PI / 180.0;
}
double rad2deg(double radians){
    return radians * 180.0 / M_PI;
}

void spaceshipInit(Spaceship* sp){
    sp->movementVec[0] = 1.0;
    sp->movementVec[1] = 0.0;
    sp->headingAngle = 0.0;
    sp->engineThrust = 0.0;
    sp->sizeX = 23;
    sp->sizeY = 18;
    sp->hp = 3;
    sp->maxHP = 3;
    sp->maxThrust = 10;
    imageInit(sp);
}

void spaceshipUpdate(Spaceship *sp){
    sp->movementVec[0] += cos(deg2rad(sp->headingAngle)) * sp->engineThrust;
    sp->movementVec[1] += sin(deg2rad(sp->headingAngle)) * sp->engineThrust;
    //sp->movementVec[1] = //sp->headingAngle > 255/2 ? 1 : -1;//sin(deg2rad(sp->headingAngle)) * sp->engineThrust;//

}
void imageInit(Spaceship *sp){
    uint16_t spaceship[23*18] = {
    0, YELLOW, YELLOW, ORANGE, RED, BLUE, BLUE, BLUE, BLUE, BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    YELLOW, YELLOW, YELLOW, ORANGE, RED, BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, YELLOW, YELLOW, ORANGE, RED, BLUE, BLUE, BLUE, BLUE, BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, LIGHT_BLUE, LIGHT_BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, 0, 0, 0,
    0, BLUE, BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, LIGHT_BLUE, LIGHT_BLUE, BLUE, BLUE, BLUE, BLUE,
    0, BLUE, BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, LIGHT_BLUE, LIGHT_BLUE, BLUE, BLUE, BLUE, BLUE,
    0, 0, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, 0, 0, 0,
    0, 0, 0, 0, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, LIGHT_BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, LIGHT_BLUE, LIGHT_BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, YELLOW, YELLOW, ORANGE, RED, BLUE, BLUE, BLUE, BLUE, BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    YELLOW, YELLOW, YELLOW, ORANGE, RED, BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, DARK_BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, YELLOW, YELLOW, ORANGE, RED, BLUE, BLUE, BLUE, BLUE, BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    for(int i = 0; i < 18; i++){

        for(int j = 0; j < 23; j++){
                sp->image[i][j] = spaceship[i*23+j];
        }

    }

}
