#include "gate.h"

void generateGate(Gate *rootGate, int screenWidth, int screenHeight, int *spDimensions){
    
    srand(time(NULL));

    Gate *gate = malloc(sizeof(Gate));
    if(gate == NULL){
        printf("malloc error in gate.c\n");
        exit(100);
    }
    gateInit(gate);

    
    int spWidth = spDimensions[0];
    int spHeight = spDimensions[1];
    
    // random number in range rand() % (upper - lower + 1) + lower;
    gate->gapW = rand() % (screenWidth/10 - spWidth + 1) + spWidth;
    gate->gapH = rand() % (screenHeight - spHeight*2 + 1) + spHeight*2; 

    gate->gapX = screenWidth;
    gate->gapY = screenHeight;
    
    // pseudo push
    Gate *cur = rootGate;
    while(cur->next != NULL){
        cur =  cur->next;
    }
    cur->next = gate;

}

void updateGates(Gate *currentGate, int screenWidth, int screenHeight){
    
    // pseudo pop
    while (currentGate->gapX + currentGate->gapW < 0 || currentGate->gapX > screenWidth)
    {   
        Gate *cur = currentGate->next;
        free(currentGate);
        currentGate = cur;
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
    gate->gapH = gate->gapW = 0;
    gate->gapX = gate->gapY = 0;
    gate->next = NULL;
}