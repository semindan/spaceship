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
    
    
    game->mem_base_lcd = initDisplay();
    parlcd_hx8357_init(game->mem_base_lcd);
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


    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 255;
    uint16_t rgb565 = ((((r>>3)&0x1f)<<11) | (((g>>2)&0x3f)<<5) | (((b>>3)&0x1f))); 


     parlcd_write_cmd(game->mem_base_lcd, 0x2c);
    for(int x = 0; x < SCREEN_WIDTH*SCREEN_HEIGHT; x++){
        parlcd_write_data(game->mem_base_lcd, rgb565);
    }
}

void handleInput(Game* game) {
    //char inputChar = fgetc(stdin);
    char inputChar = 'f';
    //float heading = (getKnob1Value()/255) * 360.f;
    //float thrust =  (getKnob2Value()/255) * game->sp->maxThrust;

    
    
    if(inputChar == 'q'){
        game->sp->headingAngle += ROTATION_ANGLE;
        game->sp->headingAngle += (game->sp->headingAngle > 360.0 - ROTATION_ANGLE) ? -360.0 + ROTATION_ANGLE :   ROTATION_ANGLE;
    }

    if(inputChar == 'e'){
        game->sp->headingAngle -= ROTATION_ANGLE;
        game->sp->headingAngle += (game->sp->headingAngle < ROTATION_ANGLE) ? 360.0 - ROTATION_ANGLE :   (-1) * ROTATION_ANGLE;
    }

    if(inputChar == 'w'){
        game->sp->engineThrust = (game->sp->engineThrust < 1.0) ? game->sp->engineThrust + THRUST_INCREMENT : 1.0;
    }

    if(inputChar == 's'){
        game->sp->engineThrust = (game->sp->engineThrust > 0.0) ? game->sp->engineThrust - THRUST_INCREMENT : 0.0;
    }

}

void update(Game* game) {
    if(hasCollided(game))
        game->sp->hp--;
    
    spaceshipUpdate(game->sp);
    generateGate(game->rootGate, SCREEN_WIDTH, SCREEN_HEIGHT, game->sp->dimensionsVec);
    updateGates(game->rootGate, SCREEN_WIDTH, SCREEN_HEIGHT);


    game->spaceshipPos[0] += game->sp->movementVec[0];
    game->spaceshipPos[1] += game->sp->movementVec[1];

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
