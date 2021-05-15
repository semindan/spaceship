#include "game_lowlevel.h"

/*  draws bonus to framebuffer as heart  */
void drawBonus(Game *game, uint16_t *framebuffer) {
    for(int i = game->gateQueue->head; i < game->gateQueue->tail; i++){
        Gate * gate = get_from_queue(game->gateQueue, i);
        if(gate->isBonus){
            const char heart[] = 
                                 " $$$$$   $$$$$ "  
                                 "$$$$$$$ $$$$$$$"
                                 "$$$$$$$$$$$$$$$"
                                 " $$$$$$$$$$$$$ "
                                 "  $$$$$$$$$$$  "
                                 "    $$$$$$$    "
                                 "      $$$      ";
            for (int y = gate->gapY; y < gate->gapY+gate->gapH; y++) {
                for (int x = gate->gapX; x < gate->gapX+gate->gapW; x++) {
                    if(heart[(int)((y-gate->gapY)*gate->gapW) + (int)x- (int)gate->gapX] == '$'){
                        game->framebuffer[y * SCREEN_WIDTH + x] = gate->color;
                    }
                }
            }
        }
    }
}

/*  draws gate to framebuffer  */
void drawGate(Gate *gate, uint16_t *framebuffer) {
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
void drawGates(Game *game, uint16_t *framebuffer) {
    for (int x = game->gateQueue->head; x < game->gateQueue->tail; x++) {
        Gate *gate = get_from_queue(game->gateQueue, x);
        
        if (gate != NULL && !gate->isBonus) {
            drawGate(gate, framebuffer);
        }
    }
}

/*  draws current score to top left corner of framebuffer   */
void drawScore(Game *game) {
    char scoreStr[100];
    sprintf(scoreStr, "%d", game->score);
    drawString(100, 0, scoreStr, game->mem_base_lcd, game->framebuffer);
}

/*  draws spaceship to framebuffer  */
void drawSpaceship(Game *game, uint16_t *framebuffer) {
    for (int y = game->spaceshipPos[1]; y < game->spaceshipPos[1] + game->sp->sizeY; y++) {
        for (int x = SCREEN_WIDTH / 2; x < SCREEN_WIDTH / 2 + game->sp->sizeX; x++) {
            framebuffer[y * SCREEN_WIDTH + x] = getColor(255, 0, 0);
        }
    }
}

/*  lights LEDs based on current thrust */
void showThrust(Game *game) {
    setLedLine(game->mem_base, round(game->sp->engineThrust/game->sp->maxThrust * 32));
}
