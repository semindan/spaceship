#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "game.h"
#include "lowLevel.h"

/**
 * draw screen for Game over and manages post game 
 * returns: void
 */
void gameOverScreen(Game *game);

/**
 * manages simple UI for creating player's name and returns written name
 * returns: string of max size 16
 */
char *getName(Game *game);

#endif
