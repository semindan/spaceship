#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define DARK_BLUE 27604
#define BLUE 33945
#define LIGHT_BLUE 32059
#define RED 62639
#define ORANGE 64880
#define YELLOW 65459

typedef struct{
    double movementVec[2];
    int dimensionsVec[2];
    
    double headingAngle;
    double engineThrust;
    double maxThrust;

    double sizeX;
    double sizeY;

    int hp;
    int maxHP;

    uint16_t image[18][25];
} Spaceship;

/*  initializes default values to spaceship  */
void spaceshipInit(Spaceship* sp);

/*  Updates spaceship movement  */
void spaceshipUpdate(Spaceship *sp);

/*  loads image graphic to memory from array   */
void imageInit(Spaceship *sp);

#endif /* __SPACESHIP_H__ */
