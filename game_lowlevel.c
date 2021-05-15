#include "game_lowlevel.h"

/*  draws bonus to framebuffer as heart  */
void drawBonus(void *gameStruct, uint16_t *framebuffer) {
    Game *game = (Game *) gameStruct;
    if(game->bonus == NULL){
        return;
    }

    const char heart[] = " $$$$$   $$$$$ "  
                         "$$$$$$$ $$$$$$$"
                         "$$$$$$$$$$$$$$$"
                         " $$$$$$$$$$$$$ "
                         "  $$$$$$$$$$$  "
                         "    $$$$$$$    "
                         "      $$$      ";
    
    for (int y = game->bonus->posY; y < game->bonus->posY+game->bonus->height; y++) {
        for (int x = game->bonus->posX; x < game->bonus->posX+game->bonus->width; x++) {
           
            if(heart[(int)((y-game->bonus->posY)*game->bonus->width) + (int)x-(int)game->bonus->posX] == '$'){
                
                game->framebuffer[y * SCREEN_WIDTH + x] = game->bonus->color;
            }
        }
    }
        
}


/*  draws gate to framebuffer  */
void drawGate(void *gateStruct, uint16_t *framebuffer) {
    Gate *gate = (Gate *) gateStruct;
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (x < gate->gapX + gate->gapW && x >= gate->gapX && (
                y <= gate->gapY || y >= gate->gapH + gate->gapY)){

                    framebuffer[y * SCREEN_WIDTH + x] = gate->color;
            }
        }
    }
}

/*  calls drawing function for all gates  */
void drawGates(void *gameStruct, uint16_t *framebuffer) {
    Game *game = (Game *) gameStruct;
    for (int x = game->gateQueue->head; x < game->gateQueue->tail; x++) {
        Gate *gate = get_from_queue(game->gateQueue, x);
        
        if (gate != NULL) {
            drawGate(gate, framebuffer);
        }
    }
}

/*  draws current score to top left corner of framebuffer   */
void drawScore(void *gameStruct) {
    Game *game = (Game *) gameStruct;
    char scoreStr[100];
    sprintf(scoreStr, "%d", game->score);
    drawString(100, 0, scoreStr,  game->framebuffer);
}

/*  draws spaceship to framebuffer  */
void drawSpaceship(void *gameStruct, uint16_t *framebuffer) {
    Game *game = (Game *) gameStruct;
    for (int y = game->spaceshipPos[1]; y < game->spaceshipPos[1] + game->sp->sizeY; y++) {
        for (int x = SCREEN_WIDTH / 2; x < SCREEN_WIDTH / 2 + game->sp->sizeX; x++) {
            framebuffer[y * SCREEN_WIDTH + x] = game->sp->image[(int)y-game->spaceshipPos[1]][(int) x-SCREEN_WIDTH/2];
        }
    }
}

/*  lights LED based on current hp  */
void showHP(void *gameStruct){
    Game *game = (Game *) gameStruct;
    switch(game->sp->hp){
        case 0: setLED1Color(0,0,0, game->mem_base);    break;
        case 1: setLED1Color(255,0,0, game->mem_base);  break;
        case 2: setLED1Color(255,165,0, game->mem_base);break;
        default:setLED1Color(0,255,0, game->mem_base);  break;
    }
}

/*  lights LEDs based on current thrust */
void showThrust(void *gameStruct) {
    Game *game = (Game *) gameStruct;
    setLedLine(game->mem_base, round(game->sp->engineThrust/game->sp->maxThrust * 32));
}
