#ifndef __GAME_LOWLEVEL_H__
#define __GAME_LOWLEVEL_H__

#include "game.h"
#include "gate.h"
#include "lowlevel.h"
#include "queue.h"
#include "spaceship.h"

/**
 * draws bonus to framebuffer as heart
*/
void drawBonus(void *gameStruct, uint16_t *framebuffer);

/**
 * draws gate to framebuffer
*/
void drawGate(void *gateStruct, uint16_t*framebuffer);

/**
 * calls drawing function for all gates
*/
void drawGates(void *gameStruct, uint16_t* framebuffer);

/**
 * draws current score to top left corner of framebuffer
 */
void drawScore(void *gameStruct);

/**
 * draws spaceship to framebuffer
*/
void drawSpaceship(void *gameStruct, uint16_t* framebuffer);

/**
 * lights RGB LEDs based on current hp
*/
void showHP(void *gameStruct);

/**
 * lights yellow LEDs based on current thrust
*/
void showThrust(void *gameStruct);

#endif /* __GAME_LOWLEVEL_H__ */
