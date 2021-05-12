#ifndef __GATE_H__
#define __GATE_H__
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
#include <assert.h>
#include "queue.h"

typedef struct GateTag{
    double gapX;
    double gapY;
    double gapW;
    double gapH;
    struct GateTag *next;
} Gate;


/**
 * Generates a gate on the right side, pseudo push of a linked list(maybe we will split it later)
*/
void generateGate(queue_t *gateQueue, int screenWidth, int screenHeight);

/**
 * Deletes a gate if it's out of the screen, pseudo pop of a linked list(maybe we will split it later)
*/
void updateGates(queue_t *gateQueue, int screenWidth, int screenHeight);

/**
 * returns nearest gate to ship's x position
*/
Gate* getNearestGate(Gate* gate, int x);

/**
 * Sets gate's properties to 0
*/
void gateInit(Gate *gate);

#endif /* __GATE_H__ */
