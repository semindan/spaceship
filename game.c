
#include "game.h"

void gameInit(Game *game)
{

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

    game->previousHeadingAngle = getKnobBlueValue(game->mem_base);
    game->startingThrust = getKnobGreenValue(game->mem_base);

    game->score = 0;

    game->framebuffer = (uint16_t *)malloc(sizeof(uint16_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
}

_Bool hasCollided(Game *game)
{

    for (int i = game->gateQueue->head; i < game->gateQueue->tail; i++)
    {

        Gate *g = get_from_queue(game->gateQueue, i);

        // AABB collision
        if (SCREEN_WIDTH / 2 + game->sp->sizeX >= g->gapX && SCREEN_WIDTH / 2 <= g->gapX + g->gapW)
        {
            g->passed = true;
            if (game->spaceshipPos[1] <= g->gapY)
            {
                g->color = getColor(0, 0, 255);
                return true;
            }
            else if (game->spaceshipPos[1] + game->sp->sizeY >= g->gapY + g->gapH)
            {
                g->color = getColor(0, 0, 255);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            g->color = getColor(0, 255, 0);
        }
    }

    return false;
}
void addScore(Game *game)
{
    for (int i = game->gateQueue->head; i < game->gateQueue->tail; i++)
    {

        Gate *g = get_from_queue(game->gateQueue, i);
        
        //printf("%f    %d\n", SCREEN_WIDTH/2 - g->gapX, g->passed);
        
     
        
        if (SCREEN_WIDTH / 2 + game->sp->sizeX >= g->gapX && SCREEN_WIDTH / 2 <= g->gapX + g->gapW && !g->passed)
        {
            game->score++;
            //g->passed = true;
        }
    }
}

void drawGame(Game *game)
{

    // draw stuff to framebuffer
    drawSpaceship(game, game->framebuffer);
    showThrust(game);
    drawGates(game, game->framebuffer);
    drawScore(game);
    // render2screen
    draw(game->mem_base_lcd, game->framebuffer);
    //reset screen
    resetFrameBuffer(game->framebuffer);
}

void handleInput(Game *game)
{

    unsigned char curHeadingAngle = getKnobBlueValue(game->mem_base);
    double heading = (((double)curHeadingAngle - (double)game->previousHeadingAngle) / 255) * 360.f;
    game->previousHeadingAngle = curHeadingAngle;

    //unsigned char curThrust = getKnobGreenValue(game->mem_base);
    //double thrust =  (((double)curThrust - (double)game->startingThrust)/255) * game->sp->maxThrust;
    //
    //double thrust = (double)curThrust - (double)game->startingThrust;
    //game->startingThrust = curThrust;
    //printf("heading %f  thrust %f\n", heading, thrust);
    unsigned char curThrust = getKnobGreenValue(game->mem_base);
    double deltaThrust = (double)(curThrust - game->startingThrust)*0.1;
    game->sp->headingAngle = heading;
    //game->sp->engineThrust += (thrust / 255) * game->sp->maxThrust;
    // normalize (0-maxThrust);
// add delta to thrust
    game->sp->engineThrust += (2*deltaThrust / 255) * game->sp->maxThrust;
      if(game->sp->engineThrust > game->sp->maxThrust){
        game->sp->engineThrust = game->sp->maxThrust;
        game->startingThrust = curThrust;
    } else if(game->sp->engineThrust < 0){
        game->sp->engineThrust = 0;
        game->startingThrust = curThrust;
    }

}

bool update(Game *game)
{
    addScore(game);
    if (hasCollided(game))
    {
        game->sp->hp--;

        if (game->sp->hp <= 0)
        {
            //clean game
            resetFrameBuffer(game->framebuffer);
            draw(game->mem_base_lcd, game->framebuffer);
            gameOverScreen(game);
            //save score
            return false;
        }
        else
        {
            resetFrameBuffer(game->framebuffer);
            drawSpaceship(game, game->framebuffer);
            clean_queue(game->gateQueue);
            return true;
        }
    }

    
    spaceshipUpdate(game->sp);

    if (game->gateQueue->size < 10 && ((double)rand() / (double)RAND_MAX) > 0.9)
    {
        generateGate(game->gateQueue, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    updateGates(game->gateQueue, game->sp->engineThrust, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (game->spaceshipPos[0] + game->sp->movementVec[0] < SCREEN_WIDTH - game->sp->sizeX && game->spaceshipPos[0] + game->sp->movementVec[0] >= game->sp->sizeX)
    {
        game->spaceshipPos[0] += game->sp->movementVec[0];
    }
    else
    {
        game->spaceshipPos[0] = 0;
    }
    if (game->spaceshipPos[1] + game->sp->movementVec[1] < SCREEN_HEIGHT - game->sp->sizeY && game->spaceshipPos[1] + game->sp->movementVec[1] >= 0)
    {
        game->spaceshipPos[1] += game->sp->movementVec[1];
    }

    return true;
}

void freeGame(Game *game)
{
    free(game->sp);
    delete_queue(game->gateQueue);
    free(game);
}
void drawSpaceship(Game *game, uint16_t *framebuffer)
{

    for (int y = game->spaceshipPos[1]; y < game->spaceshipPos[1] + game->sp->sizeY; y++)
    {
        for (int x = SCREEN_WIDTH / 2; x < SCREEN_WIDTH / 2 + game->sp->sizeX; x++)
        {
            framebuffer[y * SCREEN_WIDTH + x] = getColor(255, 0, 0);
        }
    }
}
void drawGates(Game *game, uint16_t *framebuffer)
{

    for (int x = game->gateQueue->head; x < game->gateQueue->tail; x++)
    {
        Gate *gate = get_from_queue(game->gateQueue, x);
        if (gate != NULL)
        {
            drawGate(gate, framebuffer);
        }
    }
}
void drawGate(Gate *gate, uint16_t *framebuffer)
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            if (x < gate->gapX + gate->gapW && x >= gate->gapX && (y <= gate->gapY || y >= gate->gapH + gate->gapY))
            {
                framebuffer[y * SCREEN_WIDTH + x] = gate->color;
            }
        }
    }
}
void showThrust(Game *game)
{
    setLedLine(game->mem_base, round(game->sp->engineThrust/game->sp->maxThrust * 32));
}
void drawScore(Game *game)
{
    char scoreStr[100];
    sprintf(scoreStr, "%d", game->score);
    drawString(100, 0, scoreStr, game->mem_base_lcd, game->framebuffer);
}

void saveScore(int score, char *name)
{
    FILE *scores = fopen("scores.txt", "a");
    fprintf(scores, "%s %d\n", name, score);
    fclose(scores);
    // open txt
    // write name and score
}
void gameOverScreen(Game *game)
{

    //show gameoverscreen
    
    char scoreStr[100];
    sprintf(scoreStr, "%d" ,game->score);

    drawString(SCREEN_WIDTH/2, SCREEN_HEIGHT/4, "GAME OVER!", game->mem_base_lcd, game->framebuffer);
    drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "score: ", game->mem_base_lcd, game->framebuffer );
    drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, scoreStr, game->mem_base_lcd, game->framebuffer);



    draw(game->mem_base_lcd, game->framebuffer);
    while(!getKnobBlueButton(game->mem_base)){

    }
    usleep(100*1000);
    //user writes name
    char *name = getName(game);
    saveScore(game->score, name);
    free(name);
}
char *getName(Game *game)
{
    char *name = malloc(sizeof(char) * 16 + 1);
    for (int i = 0; i < 16; i++)
    {
        name[i] = ' ';
    }
    name[16] = '\0';
    int nameIdx = 0;
    unsigned char prevButton = getKnobBlueValue(game->mem_base);
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int idx = 0;

    while (nameIdx < 16)
    {
        resetFrameBuffer(game->framebuffer);
        drawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, name, game->mem_base_lcd, game->framebuffer);
        drawChar(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8, alphabet[idx], getColor(0, 255, 255), game->mem_base_lcd, game->framebuffer);

        // handle characters before letter
        for (int i = idx - 1; i >= 0; i--)
        {
            if (SCREEN_WIDTH / 2 - (idx - i) * 16 >= 8)
            {
                drawChar(SCREEN_WIDTH / 2 - (idx - i) * 16, SCREEN_HEIGHT / 8, alphabet[i], getColor(255, 255, 255), game->mem_base_lcd, game->framebuffer);
                //draw(game->mem_base_lcd, game->framebuffer);
            }
        }
        // draw chars after letter
        for (int i = idx + 1; i < 26; i++)
        {

            if (SCREEN_WIDTH / 2 + (idx - i) * 16 < SCREEN_WIDTH - 8)
            {
                drawChar(SCREEN_WIDTH / 2 + (i - idx) * 16, SCREEN_HEIGHT / 8, alphabet[i], getColor(255, 255, 255), game->mem_base_lcd, game->framebuffer);
                //draw(game->mem_base_lcd, game->framebuffer);
            }
        }

        if (getKnobBlueValue(game->mem_base) != prevButton)
        {
            unsigned char currentVal = getKnobBlueValue(game->mem_base);
            unsigned char previousVal = prevButton;
            if (currentVal - previousVal > 5)
            {
                idx++;
                prevButton = currentVal;
            }
            else if (currentVal - previousVal < -5)
            {
                idx--;
                prevButton = currentVal;
            }
        }

        if (getKnobBlueButton(game->mem_base))
        {
            name[nameIdx++] = alphabet[idx];
            usleep(100 * 1000);
            //draw(game->mem_base_lcd, game->framebuffer);
        }
        if (getKnobRedButton(game->mem_base))
        {
            usleep(100 * 1000);
            break;
        }
        draw(game->mem_base_lcd, game->framebuffer);
    }

    return name;
}