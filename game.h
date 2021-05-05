#ifndef __GAME_H__
#define __GAME_H__

#include <math.h>
#include <stdlib.h>

#include "spaceship.h"
#include "gate.h"
#include "lowLevel.h"

// defines
#define THRUST_INCREMENT 0.1
#define ROTATION_ANGLE 15.0
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640

typedef struct{
    Spaceship* sp;
    int spaceshipPos[2];
    double spaceshipVelocity;
    Gate *rootGate;
} Game;

/**
 * Inicializace vsech podsoucasti hry
*/
void gameInit(Game* game);

/**
 * Update arraye, tzn generovani novych prekazek
*/
void updateArray(Game* game);

/**
 * Detects collision between spaceship and gate
*/
_Bool hasCollided(Game* game);

/**
 * Tady bude core vykreslovani na display a LEDky
*/
void draw(Game* game);

/**
 * Sem se potom daji vsechny registry na potenciometry, kteryma se to bude ovladat
*/
void handleInput(Game* game);

/**
 * Hlavni gameloop
*/
void update(Game* game);

/**
 * Uvolneni veskere pameti
*/
void freeGame(Game* game);

// debug pro console use
void drawConsole(Game* game);

#endif  /* __GAME_H_ */
