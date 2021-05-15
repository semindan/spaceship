#include "gate.h"

void generateGate(queue_t* gateQueue, int screenWidth, int screenHeight){
    
    srand(time(NULL));

    Gate *gate = malloc(sizeof(Gate));
    if(gate == NULL){
        printf("malloc error in gate.c\n");
        exit(100);
    }
    gateInit(gate);
    

    
    Gate *prevGate = get_from_queue( gateQueue,  gateQueue->tail-1);
    
    
   
    int minHeight = (int) (SCREEN_HEIGHT/10);
    int maxHeight = (int)( prevGate->gapH+100);
    int minY = SCREEN_HEIGHT/4;
    int maxY = (int)( prevGate->gapY+10);

    // random number in range rand() % (upper - lower + 1) + lower;
    gate->gapW = prevGate->gapW;
    gate->gapH = (rand() % ( maxHeight - minHeight + 1)) + minHeight; 

    gate->gapX = screenWidth;
    gate->gapY =  rand() % (maxY - minY + 1) + minY; 
    

    push_to_queue(gateQueue, gate);
}

void updateGates(queue_t *gateQueue,double engineThrust, int screenWidth, int screenHeight){

    int x = gateQueue->head;
    int i = gateQueue->tail;
    for(; x < i; x++){
        Gate * gate = get_from_queue(gateQueue, x);
        gate->gapX -= abs(engineThrust);
        if(gate->gapX + gate->gapW <= 0){
            Gate *gatePopped = pop_from_queue(gateQueue);
        }
        
    }

    
}



void gateInit(Gate *gate){
    gate->gapW = 10;
    gate->gapH = SCREEN_HEIGHT/2;
    
    
    gate->gapX = SCREEN_WIDTH;
    gate->gapY = SCREEN_HEIGHT/4;
    gate->color = getColor(0,255,0);
    gate->passed = false;
}