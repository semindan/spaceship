#include "gameover.h"

/*  draw screen for Game over and manages post game  */
void gameOverScreen(void *gameStruct){
    Game *game = (Game *) gameStruct;
    char scoreStr[100];
    sprintf(scoreStr, "%d" ,game->score);

    // show gameoverscreen
    drawRectangle(SCREEN_WIDTH/2,SCREEN_HEIGHT*3/4, strWidth("Ok"),getColor(0,255,0), game->framebuffer);
    drawString(SCREEN_WIDTH/2, SCREEN_HEIGHT*3/4, "Ok",  game->framebuffer);
    drawString(SCREEN_WIDTH/2, SCREEN_HEIGHT/4, "GAME OVER!",  game->framebuffer);
    drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "score: ",  game->framebuffer );
    drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, scoreStr,  game->framebuffer);
    draw(game->mem_base_lcd, game->framebuffer);

    // wait for input
    while(!getKnobGreenButton(game->mem_base));

    // user writes name
    char *name = getName(game);
    saveScore(game->score, name);
    free(name);
}

/*  manages simple UI for creating player's name and returns written name   */
char *getName(void *gameStruct) {
    Game *game = (Game *) gameStruct;
    char *name = malloc(sizeof(char) * 16 + 1);
    for (int i = 0; i < 16; i++) {
        name[i] = ' ';
    }
    name[16] = '\0';

    int idx = 0;
    int nameIdx = 0;
    int baseChar = 'a';
    unsigned char prevButton = getKnobBlueValue(game->mem_base);

    while (nameIdx < 16) {
        resetFrameBuffer(game->framebuffer);

        // render UI
        drawRectangle(SCREEN_WIDTH/4,SCREEN_HEIGHT*7/8, strWidth("Select"),getColor(0,0,255), game->framebuffer);
        drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT*7/8, "Select",  game->framebuffer);
        drawRectangle(SCREEN_WIDTH*3/4,SCREEN_HEIGHT*7/8, strWidth("Save"),getColor(255,0,0), game->framebuffer);
        drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT*7/8, "Save",  game->framebuffer);

        drawString(SCREEN_WIDTH/2, SCREEN_HEIGHT/4, "Enter name:", game->framebuffer);
        drawString(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, name, game->framebuffer);
        
        // render alphabet
        drawChar(SCREEN_WIDTH/2, SCREEN_HEIGHT * 3/4, baseChar + idx, getColor(0, 0, 255), game->framebuffer);
        renderAlphabet(gameStruct, idx);

        // handle user input
        if (getKnobBlueValue(game->mem_base) != prevButton){
            unsigned char currentVal = getKnobBlueValue(game->mem_base);
            unsigned char previousVal = prevButton;

            if (currentVal - previousVal > 5) {
                idx = (idx == 25) ? 0 : idx+1;
                prevButton = currentVal;
            }
            else if (currentVal - previousVal < -5) {
                idx = (idx == 0) ? 25 : idx-1;
                prevButton = currentVal;
            }
        }

        if (getKnobBlueButton(game->mem_base)) {
            name[nameIdx++] = baseChar + idx;
        }
        if (getKnobRedButton(game->mem_base)) {
            break;
        }

        draw(game->mem_base_lcd, game->framebuffer);
    }

    if(name[0] == ' '){
        strcpy(name, "unknown");
    }
    return name;
}

/*  renders previous and following letters of the alphabet  */
void renderAlphabet(void* gameStruct, int idx){
    Game *game = (Game *) gameStruct;
    int baseChar = 'a';

    // handle characters before letter
    for (int i = idx - 1; i >= 0; i--) {
        if (SCREEN_WIDTH / 2 - (idx - i) * 16 >= 8 && i >= 0) {
            drawChar(SCREEN_WIDTH / 2 - (idx - i) * 16, SCREEN_HEIGHT * 3/4, baseChar + i, getColor(255, 255, 255), game->framebuffer);
        }
    }
    // draw chars after letter
    for (int i = idx + 1; i < 26; i++) {
        if (SCREEN_WIDTH / 2 + (idx - i) * 16 < SCREEN_WIDTH - 8) {
            drawChar(SCREEN_WIDTH / 2 + (i - idx) * 16, SCREEN_HEIGHT * 3/4, baseChar + i, getColor(255, 255, 255), game->framebuffer);
        }
    }
}
