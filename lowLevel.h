#ifndef __LOWLEVEL_H__
#define __LOWLEVEL_H__

#include <stdint.h>

#include "mzapo_regs.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
//#include "game.h"


/*      SETS COLOR TO FIRST OR SECOND LED       */
void setLED1Color(char red, char green, char blue);
void setLED2Color(char red, char green, char blue, unsigned char* mem_base);

/*      RETURNS VALUE FROM SPECIFIED KNOB       */
unsigned char getKnobBlueValue(void *mem_base);
unsigned char getKnobGreenValue(void *mem_base);
unsigned char getKnobRedValue(void *mem_base);

/*      HANDLE DISPLAY      */
void *initDisplay();
void *initHardware();
void draw(void* lcd_addr, uint16_t* framebuffer);
//void draw(char** canvas, int sizeX, int sizeY);
//void draw(char** canvas, int sizeX, int sizeY, int posX, int posY);

/* COLOR */
uint16_t getColor(unsigned char red, unsigned char green, unsigned char blue);
#endif /* __LOWLEVEL_H__ */
