#ifndef __GATE_H__
#define __GATE_H__

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "lowLevel.h"
#include "queue.h"

typedef struct GateTag{
    double gapX;
    double gapY;

    double gapW;
    double gapH;

    struct GateTag *next;

    uint16_t color;

    bool passed;
} Gate;

/**
 * deletes a gate if it's out of the screen, pops it from the queue(maybe we will split it later)
*/
void updateGates(queue_t *gateQueue,  double engineThrust, int screenWidth, int screenHeight);

/**
 * initializes gate with default values 
*/
void gateInit(Gate *gate);

#endif /* __GATE_H__ */
