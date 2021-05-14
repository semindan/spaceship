
#ifndef __GAME_H__
#define __GAME_H__

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "queue.h"
#include "spaceship.h"
#include "gate.h"
#include "lowLevel.h"

// defines
#define THRUST_INCREMENT 0.1
#define ROTATION_ANGLE 15.0


typedef struct{
    Spaceship* sp;
    int spaceshipPos[2];
    double spaceshipVelocity;
    unsigned char previousHeadingAngle;
    unsigned char startingThrust;
    queue_t *gateQueue;
    int gateCount;
    void *mem_base_lcd;
    void *mem_base;
    uint16_t *framebuffer;
    int score;
    char playerName[16];
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
void drawGame(Game* game);

/**
 * Sem se potom daji vsechny registry na potenciometry, kteryma se to bude ovladat
*/
void handleInput(Game* game);

/**
 * Hlavni gameloop
*/
bool update(Game* game);

/**
 * Uvolneni veskere pameti
*/
void freeGame(Game* game);

void drawSpaceship(Game *game, uint16_t* framebuffer);
void drawGates(Game *game, uint16_t* framebuffer);
void drawGate(Gate *gate, uint16_t*framebuffer);
void resetFrameBuffer(uint16_t*framebuffer);
void addScore(Game *game);
void drawScore(Game* game);
void saveScore(int score, char *name);
void gameOverScreen(Game *game);
char *getName(Game *game);
void showThrust(Game *game);
void createBonus(Game *game);
void drawBonus(Game *game, uint16_t *framebuffer);
#endif  /* __GAME_H_ */
