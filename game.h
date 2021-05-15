#ifndef __GAME_H__
#define __GAME_H__

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "game_lowlevel.h"
#include "gameover.h"
#include "gate.h"
#include "queue.h"
#include "spaceship.h"
#include "bonus.h"

#define THRUST_INCREMENT 0.1
#define ROTATION_ANGLE 15.0

typedef struct{
    Spaceship* sp;
    queue_t *gateQueue;
    
    void *mem_base_lcd;
    void *mem_base;
    uint16_t *framebuffer;

    int spaceshipPos[2];
    double spaceshipVelocity;
    unsigned char previousHeadingAngle;
    unsigned char startingThrust;

    Bonus *bonus;

    char playerName[16];
    int generatorOffset;
    int score;
} Game;

/**
 * init all the game values and allocate structs
 * returns: void
*/
void gameInit(Game* game);

/**
 * runs through all gates and checks, if spaceship has collided using AABB collision
 * returns: bool
*/
_Bool hasCollided(Game* game);

/**
 * handles input from player, processes input, stores values to game
 * returns: void 
*/
void handleInput(Game* game);

/**
 * updates score, checks for collisions, updates components and updates spaceships position in world
 * returns: false in GAME OVER phase, else true
*/
bool update(Game* game);

/**
 * draws game components to framebuffer and sends framebuffer to render
 * returns: void
*/
void drawGame(Game* game);

/**
 * generates bonus under specific conditions
 * returns: void
*/
void createBonus(Game *game);

/**
 * player has collided with bonus
 * returns: void
*/
bool hasPickedBonus(Game *game);

/**
 * adds score to game if spaceship has passed a gate
 * returns: void
 */
void addScore(Game *game);

/**
 * appends last score to file
 * returns: void
 */
void saveScore(int score, char *name);
/**
 * destroys all current gates on the screen
 * returns: void
*/
void destroyGates(Game* game);

/**
 * turns off leds and makes screen black
 * returns: void
*/
void cleanGame(Game *game)

/**
 * frees all memory allocated for game and it's components
 * returns: void
*/
void freeGame(Game* game);

#endif  /* __GAME_H_ */
