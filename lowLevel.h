#ifndef __LOWLEVEL_H__
#define __LOWLEVEL_H__

#include <stdint.h>
#include <stdbool.h>
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "font_types.h"
//#include "game.h"


/*      SETS COLOR TO FIRST OR SECOND LED       */
void setLED1Color(char red, char green, char blue);
void setLED2Color(char red, char green, char blue, unsigned char* mem_base);

/*      RETURNS VALUE FROM SPECIFIED KNOB       */
unsigned char getKnobBlueValue(void *mem_base);
unsigned char getKnobGreenValue(void *mem_base);
unsigned char getKnobRedValue(void *mem_base);

bool getKnobBlueButton(void *mem_base);
bool getKnobGreenButton(void *mem_base);
bool getKnobRedButton(void *mem_base);

/*      HANDLE DISPLAY      */
void *initDisplay();
void *initHardware();
void draw(void* lcd_addr, uint16_t* framebuffer);
//void draw(char** canvas, int sizeX, int sizeY);
//void draw(char** canvas, int sizeX, int sizeY, int posX, int posY);

/* COLOR */
uint16_t getColor(unsigned char red, unsigned char green, unsigned char blue);



void drawChar(int x, int y, char ch, unsigned short color, void* lcd_addr, uint16_t* framebuffer);
void drawPixel(int x, int y, unsigned short color, uint16_t* framebuffer);
void drawPixelBig(int x, int y, unsigned short color,  uint16_t* framebuffer, int scale);
int charWidth(int ch, font_descriptor_t *fdes);
void drawString(int x, int y, char*str,  unsigned char *mem_base_lcd, uint16_t *framebuffer);
void drawRectangle(int x, int y,int len, uint16_t color,unsigned char *mem_base_lcd, uint16_t *framebuffer);
int strWidth(char* c);
void resetFrameBuffer(uint16_t*framebuffer);
void setLedLine(void *mem_base, int activeLed);
#endif /* __LOWLEVEL_H__ */
