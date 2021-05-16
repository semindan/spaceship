#ifndef __MENU_H__
#define __MENU_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "lowlevel.h"

#define START_GAME 1
#define SCOREBOARD 2
#define EXIT 3

/*  render menu to screen   */
void renderMenu(unsigned char* mem_base_lcd, uint16_t* framebuffer);

/*  handles buttons pressed in menu screen  */
int handleMenuInput(unsigned char* mem_base_buttons, unsigned char* mem_base_lcd, uint16_t* framebuffer);

#endif /* __MENU_H__ */
