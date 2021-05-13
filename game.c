#include "game.h"

void gameInit(Game* game){

    game->mem_base = initHardware();
    game->mem_base_lcd = initDisplay();
    parlcd_hx8357_init(game->mem_base_lcd);


    game->sp = (Spaceship*) malloc(sizeof(Spaceship));
    game->sp->dimensionsVec[0] = SCREEN_WIDTH / 10; //to be updated
    game->sp->dimensionsVec[1] = SCREEN_HEIGHT / 10; //to be updated according to the screen size
    spaceshipInit(game->sp);
    
    game->spaceshipPos[0] = 0;
    game->spaceshipPos[1] = SCREEN_HEIGHT / 2;
    
    game->gateCount = 0;
    game->gateQueue = create_queue(50);
    
    game->previousHeadingAngle = getKnobBlueValue(game->mem_base);
    game->startingThrust = getKnobGreenValue(game->mem_base);
    

    game->framebuffer = (uint16_t*) malloc(sizeof(uint16_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
}

_Bool hasCollided(Game* game){
        
    for(int i = game->gateQueue->head; i < game->gateQueue->tail; i++ ){
        
        Gate* g = get_from_queue(game->gateQueue, i);
        
        // AABB collision
        if(SCREEN_WIDTH/2 + game->sp->sizeX >= g->gapX
        && SCREEN_WIDTH/2 <= g->gapX + g->gapW
        && (game->spaceshipPos[1] <= g->gapY 
        || game->spaceshipPos[1] + game->sp->sizeY >= g->gapY + g->gapH)){
        
            g->color = getColor(0,0,255);
            return true;
        }
        else{
            g->color = getColor(0,255,0);
        }


        /*
                  |_|
                +
                   _
                  | |
        */
        /*
        if( g->gapX < game->spaceshipPos[0] + game->sp->sizeX &&
            g->gapX + g->gapW > game->spaceshipPos[0] &&
            g->gapY < game->spaceshipPos[1] + game->sp->sizeY &&
            g->gapY + g->gapH > game->spaceshipPos[1]) {

            return true;
        }
        */
    }
    
    return false;
}

void drawGame(Game* game){


    // make new framebuffer
    

    // draw stuff to framebuffer
    drawSpaceship(game, game->framebuffer);
    drawGates(game, game->framebuffer);

    // render2screen
    draw(game->mem_base_lcd, game->framebuffer);
    //reset screen
    resetScreen(game->framebuffer);
    

    // cleanup
    //free(framebuffer);
    //free(black);

}

void handleInput(Game* game) {
    
    unsigned char curHeadingAngle = getKnobBlueValue(game->mem_base);
    double heading = (((double)curHeadingAngle - (double)game->previousHeadingAngle)/255) * 360.f;
    game->previousHeadingAngle = curHeadingAngle;

    unsigned char curThrust = getKnobGreenValue(game->mem_base);
    //double thrust =  (((double)curThrust - (double)game->startingThrust)/255) * game->sp->maxThrust;
    //
    double thrust =  (double)curThrust - (double)game->startingThrust;

    printf("heading %f  thrust %f\n", heading, thrust);
    
    
    game->sp->headingAngle = heading;
    game->sp->engineThrust = (thrust/255)  * game->sp->maxThrust;
  
}

bool update(Game* game) {
    
    

    if(hasCollided(game)){
         game->sp->hp--;

         if(game->sp->hp <= 0){
            return false;
         }
         else{
             resetScreen(game->framebuffer);
             drawSpaceship(game, game->framebuffer);
             clean_queue(game->gateQueue);
             return true;
         }
    }
    
    spaceshipUpdate(game->sp);
    /*
    if(game->gateQueue->size < 10 && ((double)rand()/(double)RAND_MAX) > 0.9){
           generateGate(game->gateQueue, SCREEN_WIDTH, SCREEN_HEIGHT);     
    }
    updateGates(game->gateQueue, SCREEN_WIDTH, SCREEN_HEIGHT);
    */
    if(game->spaceshipPos[0] + game->sp->movementVec[0] < SCREEN_WIDTH-game->sp->sizeX 
    && game->spaceshipPos[0] + game->sp->movementVec[0] >= game->sp->sizeX){
            game->spaceshipPos[0] += game->sp->movementVec[0];
    }
    else{
        game->spaceshipPos[0] = 0;
    }
       if(game->spaceshipPos[1] + game->sp->movementVec[1] < SCREEN_HEIGHT-game->sp->sizeY
    && game->spaceshipPos[1] + game->sp->movementVec[1] >= game->sp->sizeY){
    game->spaceshipPos[1] += game->sp->movementVec[1];
    }
   
    return true;
}

void freeGame(Game* game) {
    free(game->sp);
    delete_queue(game->gateQueue);
    free(game);
}
void drawSpaceship(Game *game, uint16_t* framebuffer){
    
    int imgStartX = SCREEN_WIDTH/2 - game->sp->sizeX;
    int imgStartY = game->spaceshipPos[1] - game->sp->sizeY;
    
    for(int y = 0; y < game->sp->sizeY; y++){
        for(int x = 0; x < game->sp->sizeX; x++){
            framebuffer[(imgStartY + y) * SCREEN_WIDTH + imgStartX + x] = getColor(255,0,0);
        }
    }
    
  
  
}
void drawGates(Game *game, uint16_t* framebuffer){
    
    for(int x = game->gateQueue->head; x < game->gateQueue->tail; x++){
        Gate * gate = get_from_queue(game->gateQueue, x);
        if(gate != NULL){
            drawGate(gate, framebuffer);
        }
        
    }
        
      
    
}
void drawGate(Gate *gate, uint16_t*framebuffer){
    for(int y = 0; y < SCREEN_HEIGHT; y++){
        for(int x = 0; x < SCREEN_WIDTH; x++){
            if(x <  gate->gapX + gate->gapW && x >= gate->gapX && (y <= gate->gapY || y >= gate->gapH+gate->gapY)){
                framebuffer[y*SCREEN_WIDTH+x] = gate->color;  
            }

        }
    }

}
void resetScreen(uint16_t*framebuffer){
    
    for(int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++){
        framebuffer[i] = getColor(0,0,0);
    }

}
