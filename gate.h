#ifndef __GATE_H__
#define __GATE_H__

#include <math.h>
#include <stdlib.h>
#include <time.h>


#include "lowlevel.h"
#include "queue.h"

typedef struct{
    double gapX;
    double gapY;

    double gapW;
    double gapH;

    uint16_t color;

    bool passed;
} Gate;

/**
 * deletes a gate if it's out of the screen, pops it from the queue(maybe we will split it later)
*/
void updateGates(queue_t *gateQueue,  double engineThrust);
/**
 * Generates a gate on the right side, pushes it to gate queue(maybe we will split it later)
*/
void generateGate(queue_t *gateQueue, int gateGap);
/**
 * Pops gates that are out of screen
*/
void popGates(queue_t *gateQueue);
/**
 * initializes gate with default values 
*/
void gateInit(Gate *gate);

#endif /* __GATE_H__ */
