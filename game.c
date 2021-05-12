#include "game.h"

void gameInit(Game* game){
    game->sp = (Spaceship*) malloc(sizeof(Spaceship));
    game->sp->dimensionsVec[0] = SCREEN_WIDTH / 10; //to be updated
    game->sp->dimensionsVec[1] = SCREEN_HEIGHT / 10; //to be updated according to the screen size
    spaceshipInit(game->sp);
    
    game->spaceshipPos[0] = SCREEN_WIDTH / 2;
    game->spaceshipPos[1] = SCREEN_HEIGHT / 2;
    

    game->rootGate = (Gate*) malloc(sizeof(Gate));
    gateInit(game->rootGate);
    
    game->mem_base = initHardware();
    game->mem_base_lcd = initDisplay();
    parlcd_hx8357_init(game->mem_base_lcd);

    game->framebuffer = (uint16_t*) malloc(sizeof(uint16_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
}

_Bool hasCollided(Game* game){
    Gate* g = getNearestGate(game->rootGate, game->spaceshipPos[0]);

    // AABB collision
    if( g->gapX < game->spaceshipPos[0] + game->sp->sizeX &&
        g->gapX + g->gapW > game->spaceshipPos[0] &&
        g->gapY < game->spaceshipPos[1] + game->sp->sizeY &&
        g->gapY + g->gapH > game->spaceshipPos[1]) {

        return true;
    }

    return false;
}

void drawGame(Game* game){


    // make new framebuffer
    

    // draw stuff to framebuffer
    drawSpaceship(game, game->framebuffer);
    //drawGates(game, framebuffer);

    // render2screen
    draw(game->mem_base_lcd, game->framebuffer);
    //reset screen

    for(int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++){
        game->framebuffer[i] = getColor(0,0,0);
    }

    // cleanup
    //free(framebuffer);
    //free(black);

}

void handleInput(Game* game) {
    //char inputChar = fgetc(stdin);
    
/*
    float heading = (((float)getKnobBlueValue(game->mem_base))/255) * 360.f;
    float thrust =  (((float)getKnobGreenValue(game->mem_base))/255) * game->sp->maxThrust;
    //printf("heading %f  thrust %f\n", heading, thrust);
    
    
    game->sp->headingAngle += heading;
    game->sp->engineThrust = 1;
    */
   game->sp->headingAngle = getKnobBlueValue(game->mem_base);
}

void update(Game* game) {
    /*
    if(hasCollided(game))
        game->sp->hp--;
    */
    spaceshipUpdate(game->sp);
    /*
    generateGate(game->rootGate, SCREEN_WIDTH, SCREEN_HEIGHT, game->sp->dimensionsVec);
    updateGates(game->rootGate, SCREEN_WIDTH, SCREEN_HEIGHT);
    */

    if(game->spaceshipPos[0] + game->sp->movementVec[0] < SCREEN_WIDTH-game->sp->sizeX 
    && game->spaceshipPos[0] + game->sp->movementVec[0] >= game->sp->sizeX){
            game->spaceshipPos[0] += game->sp->movementVec[0];

    }
       if(game->spaceshipPos[1] + game->sp->movementVec[1] < SCREEN_HEIGHT-game->sp->sizeY
    && game->spaceshipPos[1] + game->sp->movementVec[1] >= game->sp->sizeY){
    game->spaceshipPos[1] += game->sp->movementVec[1];

    }

}

void freeGame(Game* game) {
    free(game->sp);
    Gate *cur = game->rootGate;
    while (game->rootGate != NULL)
    {   
        cur = game->rootGate->next;
        free(game->rootGate);
        game->rootGate = cur;
    }
    
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
    return;
}