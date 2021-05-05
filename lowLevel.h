#include "mzapo_regs.h"
#include "stdint.h"

/*      SETS COLOR TO FIRST OR SECOND LED       */
void setLED1Color(char red, char green, char blue);
void setLED2Color(char red, char green, char blue);

/*      RETURNS VALUE FROM SPECIFIED KNOB       */
char getKnob1Value();
char getKnob2Value();
char getKnob3Value();
