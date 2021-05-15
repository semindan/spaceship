#ifndef __GAME_LOWLEVEL_H__
#define __GAME_LOWLEVEL_H__

#include "game.h"
#include "gate.h"
#include "lowLevel.h"
#include "queue.h"
#include "spaceship.h"

/**
 * draws bonus to framebuffer as heart
*/
void drawBonus(Game *game, uint16_t *framebuffer);

/**
 * draws gate to framebuffer
*/
void drawGate(Gate *gate, uint16_t*framebuffer);

/**
 * calls drawing function for all gates
*/
void drawGates(Game *game, uint16_t* framebuffer);

/**
 * draws current score to top left corner of framebuffer
 */
void drawScore(Game* game);

/**
 * draws spaceship to framebuffer
*/
void drawSpaceship(Game *game, uint16_t* framebuffer);

/**
 * lights yellow LEDs based on current thrust
*/
void showThrust(Game *game);

#endif
