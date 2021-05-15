#include "spaceship.h"
/*  support functions   */
double deg2rad(double degrees){
    return degrees * M_PI / 180.0;
}
double rad2deg(double radians){
    return radians * 180.0 / M_PI;
}

/*  initializes basic values    */
void spaceshipInit(Spaceship* sp){
    sp->movementVec[0] = 1.0;
    sp->movementVec[1] = 0.0;
    
    sp->headingAngle = 0.0;
    sp->engineThrust = 0.0;
    sp->maxThrust = 10;

    sp->sizeX = 23;
    sp->sizeY = 18;

    sp->hp = 3;
    sp->maxHP = 3;

    imageInit(sp);
}

/*  updates spaceship movement  */
void spaceshipUpdate(Spaceship *sp){
    sp->movementVec[0] += cos(deg2rad(sp->headingAngle)) * sp->engineThrust;
    sp->movementVec[1] += sin(deg2rad(sp->headingAngle)) * sp->engineThrust;
}

/*  loads image graphic to memory from array    */
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
