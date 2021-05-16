#include "gate.h"

/*  updates position of all gates   */
void updateGates(queue_t *gateQueue, double engineThrust, int screenWidth, int screenHeight) {
    int x = gateQueue->head;
    int i = gateQueue->tail;

    for(; x < i; x++){
        Gate * gate = get_from_queue(gateQueue, x);
        gate->gapX -= abs(engineThrust);
        
        if(gate->gapX + gate->gapW <= 0){
            pop_from_queue(gateQueue);
        }
        
    }
}

/*  initializes gate with default values    */
void gateInit(Gate *gate) {
    gate->gapW = 10;
    gate->gapH = SCREEN_HEIGHT/2;
    
    gate->gapX = SCREEN_WIDTH;
    gate->gapY = SCREEN_HEIGHT/4;

    gate->color = getColor(0,255,0);
    gate->passed = false;
}
