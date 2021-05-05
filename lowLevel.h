#ifndef __LOWLEVEL_H__
#define __LOWLEVEL_H__

#include <stdint.h>

#include "mzapo_regs.h"
#include "game.h"


/*      SETS COLOR TO FIRST OR SECOND LED       */
void setLED1Color(char red, char green, char blue);
void setLED2Color(char red, char green, char blue);

/*      RETURNS VALUE FROM SPECIFIED KNOB       */
char getKnob1Value();
char getKnob2Value();
char getKnob3Value();

/*      HANDLE DISPLAY      */
void draw(char** canvas);
void draw(char** canvas, int sizeX, int sizeY);
void draw(char** canvas, int sizeX, int sizeY, int posX, int posY);

#endif /* __LOWLEVEL_H__ */
