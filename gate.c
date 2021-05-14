#include "gate.h"

void generateGate(queue_t* gateQueue, int screenWidth, int screenHeight){
    
    srand(time(NULL));

    Gate *gate = malloc(sizeof(Gate));
    if(gate == NULL){
        printf("malloc error in gate.c\n");
        exit(100);
    }
    gateInit(gate);

    //TODO: randomize gates

    //int spWidth = spDimensions[0];
    //int spHeight = spDimensions[1];
    
    // random number in range rand() % (upper - lower + 1) + lower;
    gate->gapW = rand() % (screenWidth/20 - screenWidth/30 + 1) + screenWidth/30;
    gate->gapH = rand() % (screenHeight - screenHeight/30 + 1) + screenHeight/30; 

    gate->gapX = screenWidth;//screenWidth;
    gate->gapY = screenHeight/5;//screenHeight;
    
    if(!push_to_queue(gateQueue, gate)){
        printf("FULL\n");
    }
}

void updateGates(queue_t *gateQueue,double engineThrust, int screenWidth, int screenHeight){

    int x = gateQueue->head;
    int i = gateQueue->tail;
    for(; x < i; x++){
        Gate * gate = get_from_queue(gateQueue, x);
        gate->gapX -= abs(engineThrust);
        if(gate->gapX + gate->gapW < 0 || gate->gapX > screenWidth){
            Gate *gatePopped = pop_from_queue(gateQueue);
        }
        
    }

    
}

Gate* getNearestGate(Gate* gate, int x){
    if(gate->next == NULL){
        return gate;
    }

    double distA = fabs(gate->gapX - x);
    double distB = fabs(gate->next->gapX - x);
    
    if(distA < distB){
        return gate;
    } else {
        return getNearestGate(gate->next, x);
    }
}

void gateInit(Gate *gate){
    gate->gapH = gate->gapW = 10;
    gate->gapX = gate->gapY = 10;
    gate->color = getColor(0,255,0);
    gate->passed = false;
}