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
    //address magic
}

void handleInput(Game* game) {
    char inputChar = fgetc(stdin);

    float heading = (getKnob1Value()/255) * 360.f;
    float thrust =  (getKnob2Value()/255) * game->sp->maxThrust;
    
    setLED2Color(getKnob1Value(), getKnob1Value(), getKnob1Value());
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
