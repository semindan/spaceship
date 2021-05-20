#ifndef __LOWLEVEL_H__
#define __LOWLEVEL_H__

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "font_types.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#define LATENCY 150

/*  maps physical addresses for LCD display */
void *initDisplay();

/*  maps physical addresses for hardware controllers */
void *initHardware();


/*  toggles on specified amount of LEDs  */
void setLedLine(void *mem_base, int activeLed);

/*  sets all LEDs in the line to 0  */
void resetLedLine(void *mem_base);

/*  sets LED to specified RGB color */
void setLED1Color(char red, char green, char blue,  void * mem_base);
void setLED2Color(char red, char green, char blue, void* mem_base);

/*  resets LED to black color  */
void resetLED1Color(void * mem_base);
void resetLED2Color(void * mem_base);

/*  gets knob rotation in (0-255) range */
unsigned char getKnobBlueValue(void *mem_base);
unsigned char getKnobGreenValue(void *mem_base);
unsigned char getKnobRedValue(void *mem_base);

/*  returns if knob was pressed and adds latency (LATENCY in miliseconds) */
bool getKnobBlueButton(void *mem_base);
bool getKnobGreenButton(void *mem_base);
bool getKnobRedButton(void *mem_base);


/*  functions for font drawing  */
int charWidth(int ch, font_descriptor_t *fdes);
void drawChar(int x, int y, char ch, unsigned short color,  uint16_t* framebuffer);

/*  draws framebuffer to display    */
void draw(void* lcd_addr, uint16_t* framebuffer);

/*  fills framebuffer with zeros    */
void resetFrameBuffer(uint16_t*framebuffer);

/*  draws colored pixel to framebuffer  */
void drawPixel(int x, int y, unsigned short color, uint16_t* framebuffer);

/*  draws colored square to framebuffer */
void drawPixelBig(int x, int y, unsigned short color,  uint16_t* framebuffer, int scale);

/*  draws string to framebuffer */
void drawString(int x, int y, char*str,  uint16_t *framebuffer);

/*  draws rectangle with set height to framebuffer  */
void drawRectangle(int x, int y,int len, uint16_t color, uint16_t *framebuffer);


/*  returns RGB color as 16-bit int for the LCD display */
uint16_t getColor(unsigned char red, unsigned char green, unsigned char blue);

/*  calculates length of string */
int strWidth(char* c);

#endif /* __LOWLEVEL_H__ */
