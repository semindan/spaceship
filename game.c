#include "game.h"
// debugging
#include <stdio.h>

// defines
#define THRUST_INCREMENT 0.1
#define ROTATION_ANGLE 15.0
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640

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



void draw(Game* game){
    //address magic
}

void handleInput(Game* game) {
    char inputChar = fgetc(stdin);

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

void drawConsole(Game* game) {
    fprintf(stdout, "Spaceship position: %3d %3d\n", game->spaceshipPos[0], game->spaceshipPos[1]);
    fprintf(stdout, "Spaceship is moving in direction %.2f %.2f\n", game->sp->movementVec[0], game->sp->movementVec[1]);
    fprintf(stdout, "Spaceship is heading in direction %.2f with engines on %.2f\n", game->sp->headingAngle, game->sp->engineThrust);
}
