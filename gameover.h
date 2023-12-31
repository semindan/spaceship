#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "game.h"
#include "lowlevel.h"

/**
 * draw screen for Game over and manages post game 
 * returns: void
 */
void gameOverScreen(void *gameStruct);

/**
 * manages simple UI for creating player's name and returns written name
 * returns: string of max size 16
 */
char *getName(void *gameStruct);

/**
 * renders previous and following letters of the alphabet to framebuffer 
 * returns: void
 */
void renderAlphabet(void* gameStruct, int idx);

#endif /* __GAMEOVER_H__ */
