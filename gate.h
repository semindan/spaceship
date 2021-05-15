#ifndef __GATE_H__
#define __GATE_H__
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
#include <assert.h>
#include "queue.h"
#include "lowLevel.h"
#include "game.h"

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
 * Deletes a gate if it's out of the screen, pseudo pop of a linked list(maybe we will split it later)
*/
void updateGates(queue_t *gateQueue,  double engineThrust, int screenWidth, int screenHeight);

/**
 * Sets gate's properties to 0
*/
void gateInit(Gate *gate);

#endif /* __GATE_H__ */
