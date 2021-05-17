#include "gate.h"

/*  updates position of all gates   */
void updateGates(queue_t *gateQueue, double engineThrust)
{
    int x = gateQueue->head;
    int i = gateQueue->tail;

    for (; x < i; x++)
    {
        Gate *gate = get_from_queue(gateQueue, x);
        gate->gapX -= abs(engineThrust);
    }
}
/*  generates new gate and stores it to queue   */
void generateGate(queue_t *gateQueue, int gateGap)
{
    srand(time(NULL));

    Gate *gate = malloc(sizeof(Gate));
    if (gate == NULL)
    {
        printf("malloc error in gate.c\n");
        exit(100);
    }
    gateInit(gate);

    Gate *prevGate = get_from_queue(gateQueue, gateQueue->tail - 1);
    if (prevGate != NULL)
    {
        
        int minY = (int)(prevGate->gapY - 10) < (int) SCREEN_HEIGHT/8 ? (int) SCREEN_HEIGHT/4 : (int)(prevGate->gapY - 10);
        int maxY = (int)(prevGate->gapY + 10) >= (int) SCREEN_HEIGHT*7/8 ? (int) SCREEN_HEIGHT/2 : (int)(prevGate->gapY + 10);
        int minHeight = (int)(SCREEN_HEIGHT / 10 + gateGap);
        int maxHeight = (int)(prevGate->gapH + gateGap);

        if(minY + minHeight >= SCREEN_HEIGHT){
            minY = 0;
            minHeight = 0;
        }
        if(maxY + maxHeight >= SCREEN_HEIGHT){
            maxY = (int) SCREEN_HEIGHT/2;
            maxHeight = (int) SCREEN_HEIGHT/4;
        }

        // random number in range rand() % (upper - lower + 1) + lower;
        gate->gapW = prevGate->gapW;
        gate->gapH = (rand() % (maxHeight - minHeight + 1)) + minHeight;
        gate->gapX = SCREEN_WIDTH;
        gate->gapY = rand() % (maxY - minY + 1) + minY;
    }

    

    if(!push_to_queue(gateQueue, gate)){
        popGates(gateQueue);
    }
    
}
/*  initializes gate with default values    */
void gateInit(Gate *gate)
{
    gate->gapW = 10;
    gate->gapH = SCREEN_HEIGHT / 2;

    gate->gapX = SCREEN_WIDTH;
    gate->gapY = SCREEN_HEIGHT / 4;

    gate->color = getColor(0, 255, 0);
    gate->passed = false;
}
/*     pops gates that are out of screen    */
void popGates(queue_t *gateQueue){
    
     int x = gateQueue->head;
    int i = gateQueue->tail;

    for (; x < i; x++)
    {
        Gate *gate = get_from_queue(gateQueue, x);
        // if gate isn't on screen 
        if (gate->gapX + gate->gapW <= 0)
        {
            Gate *poppedGate = pop_from_queue(gateQueue);
            if(poppedGate != NULL){
                free(poppedGate);
            }
        }
    }
    
}