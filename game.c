#include "game.h"

/*  initializes all game values and components  */
void gameInit(Game *game) {
    game->mem_base = initHardware();
    game->mem_base_lcd = initDisplay();
    parlcd_hx8357_init(game->mem_base_lcd);

    game->sp = (Spaceship *)malloc(sizeof(Spaceship));
    game->sp->dimensionsVec[0] = SCREEN_WIDTH / 10;  //to be updated
    game->sp->dimensionsVec[1] = SCREEN_HEIGHT / 10; //to be updated according to the screen size
    spaceshipInit(game->sp);

    game->spaceshipPos[0] = 0;
    game->spaceshipPos[1] = SCREEN_HEIGHT / 2;

    game->gateCount = 0;
    game->gateQueue = create_queue(50);
    Gate *rootGate = malloc(sizeof(Gate));
    gateInit(rootGate);
    push_to_queue(game->gateQueue, rootGate);
    game->bonus = NULL;

    game->previousHeadingAngle = getKnobBlueValue(game->mem_base);
    game->startingThrust = getKnobGreenValue(game->mem_base);

    game->score = 0;

    game->framebuffer = (uint16_t *)malloc(sizeof(uint16_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
}

/*  runs through all gates and checks, if spaceship has collided using AABB collision   */
_Bool hasCollided(Game *game) {
    for (int i = game->gateQueue->head; i < game->gateQueue->tail; i++) {
        Gate *g = get_from_queue(game->gateQueue, i);

        // AABB collision
        if (SCREEN_WIDTH / 2 + game->sp->sizeX >= g->gapX && SCREEN_WIDTH / 2 <= g->gapX + g->gapW) {
            g->passed = true;
            if (game->spaceshipPos[1] <= g->gapY) {
                g->color = getColor(0, 0, 255);
                return true;
            }
            else if (game->spaceshipPos[1] + game->sp->sizeY >= g->gapY + g->gapH) {
                g->color = getColor(0, 0, 255);
                return true;
            }
            else {
                return false;
            }
        } else {
            g->color = getColor(0, 255, 0);
        }
    }

    return false;
}

/*  handles input from player, processes input, stores values to game   */
void handleInput(Game *game) {
    unsigned char curHeadingAngle = getKnobBlueValue(game->mem_base);
    double heading = (((double)curHeadingAngle - (double)game->previousHeadingAngle) / 255) * 360.f;
    game->previousHeadingAngle = curHeadingAngle;

    unsigned char curThrust = getKnobGreenValue(game->mem_base);
    double deltaThrust = (double)(curThrust - game->startingThrust)*0.1;
    game->sp->headingAngle = heading;
   
    // add delta to thrust
    game->sp->engineThrust += (2*deltaThrust / 255) * game->sp->maxThrust;
    if(game->sp->engineThrust > game->sp->maxThrust){
        game->sp->engineThrust = game->sp->maxThrust;
        game->startingThrust = curThrust;
    } 
    else if(game->sp->engineThrust < 0){
        game->sp->engineThrust = 0;
        game->startingThrust = curThrust;
    }
}

/*   updates score, checks for collisions, updates components and updates spaceships position in world  */
bool update(Game *game) {
    addScore(game);

    if (hasCollided(game)) {
        game->sp->hp--;

        if (game->sp->hp <= 0) {
            // cleanup of game
            resetFrameBuffer(game->framebuffer);
            draw(game->mem_base_lcd, game->framebuffer);
            resetLedLine(game->mem_base);
            resetLED1Color(game->mem_base);
            // switch to gameOverScreen()
            gameOverScreen(game);
            return false;

        } else {
            resetFrameBuffer(game->framebuffer);
            drawSpaceship(game, game->framebuffer);
            clean_queue(game->gateQueue);
            return true;
        }
    }
    
    spaceshipUpdate(game->sp);
    
    if (game->gateQueue->size < 10 && ((double)rand() / (double)RAND_MAX) > 0.9) {
        generateGate(game->gateQueue, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    updateGates(game->gateQueue, game->sp->engineThrust, SCREEN_WIDTH, SCREEN_HEIGHT);
    createBonus(game);

    if(hasPickedBonus(game)){
        if(game->sp->hp < game->sp->maxHP){
        game->sp->hp++;
        }
    }
    game->bonus = updateBonus(game->bonus, game->sp->engineThrust);
    // keep spaceship within world
    if (game->spaceshipPos[0] + game->sp->movementVec[0] < SCREEN_WIDTH - game->sp->sizeX && 
        game->spaceshipPos[0] + game->sp->movementVec[0] >= game->sp->sizeX) {
            game->spaceshipPos[0] += game->sp->movementVec[0];
    } else {
        game->spaceshipPos[0] = 0;
    }

    if (game->spaceshipPos[1] + game->sp->movementVec[1] < SCREEN_HEIGHT - game->sp->sizeY && 
        game->spaceshipPos[1] + game->sp->movementVec[1] >= 0) {
            game->spaceshipPos[1] += game->sp->movementVec[1];
    }

    return true;
}

/*  draws game components to framebuffer and sends framebuffer to render    */
void drawGame(Game *game){
    // draw stuff to framebuffer
    drawBonus(game, game->framebuffer);
    drawSpaceship(game, game->framebuffer);
    drawGates(game, game->framebuffer);
    drawScore(game);
    
    // draw on hardware
    showHP(game);
    showThrust(game);
    draw(game->mem_base_lcd, game->framebuffer);
    
    //reset screen
    resetFrameBuffer(game->framebuffer);
}

/*  generates bonus under specific conditions   */
void createBonus(Game *game) {
    if(game->bonus == NULL){
        game->bonus =  generateBonus(SCREEN_HEIGHT/2);
    }
}
bool hasPickedBonus(Game *game) {

        // AABB collision
        if (SCREEN_WIDTH / 2 + game->sp->sizeX >= game->bonus->posX \
        && SCREEN_WIDTH / 2 <= game->bonus->posX + game->bonus->width && !game->bonus->passed) {
            game->bonus->passed = true;

            if(game->spaceshipPos[1] + game->sp->sizeY >= game->bonus->posY\
            && game->spaceshipPos[1] <= game->bonus->posY + game->bonus->heigth){
                 game->bonus->color = getColor(0, 0, 0);
                return true;
            }
        
        }

    return false;
}
/*  adds score to game if spaceship has passed a gate   */
void addScore(Game *game) {
    for (int i = game->gateQueue->head; i < game->gateQueue->tail; i++) {
        Gate *g = get_from_queue(game->gateQueue, i);
        
        if (SCREEN_WIDTH / 2 + game->sp->sizeX >= g->gapX && SCREEN_WIDTH / 2 <= g->gapX + g->gapW && !g->passed) {
            game->score++;
        }
    }
}

/*  appends last score to file  */
void saveScore(int score, char *name) {
    FILE *scores = fopen("scores.txt", "a");
    if(scores == NULL)
        return;

    fprintf(scores, "%s %d\n", name, score);
    fclose(scores);
}

/*  free allocated memory   */
void freeGame(Game *game) {
    free(game->sp);
    delete_queue(game->gateQueue);
    free(game);
}
