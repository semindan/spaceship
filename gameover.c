#include "gameover.h"

/*  draw screen for Game over and manages post game  */
void gameOverScreen(Game *game){
    char scoreStr[100];
    sprintf(scoreStr, "%d" ,game->score);

    // show gameoverscreen
    drawString(SCREEN_WIDTH/2, SCREEN_HEIGHT/4, "GAME OVER!", game->mem_base_lcd, game->framebuffer);
    drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "score: ", game->mem_base_lcd, game->framebuffer );
    drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, scoreStr, game->mem_base_lcd, game->framebuffer);
    draw(game->mem_base_lcd, game->framebuffer);

    // wait for input
    while(!getKnobRedButton(game->mem_base));

    // user writes name
    char *name = getName(game);
    saveScore(game->score, name);
    free(name);
}

/*  manages simple UI for creating player's name and returns written name   */
char *getName(Game *game) {
    char *name = malloc(sizeof(char) * 16 + 1);
    for (int i = 0; i < 16; i++) {
        name[i] = ' ';
    }
    name[16] = '\0';

    int idx = 0;
    int nameIdx = 0;
    //char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    unsigned char prevButton = getKnobBlueValue(game->mem_base);

    while (nameIdx < 16) {
        resetFrameBuffer(game->framebuffer);
        drawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, name, game->mem_base_lcd, game->framebuffer);
        drawChar(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8, 'a' + idx, getColor(0, 255, 255), game->mem_base_lcd, game->framebuffer);

        // handle characters before letter
        for (int i = idx - 1; i >= 0; i--) {
            if (SCREEN_WIDTH / 2 - (idx - i) * 16 >= 8 && i >= 0) {
                drawChar(SCREEN_WIDTH / 2 - (idx - i) * 16, SCREEN_HEIGHT / 8, 'a' + i, getColor(255, 255, 255), game->mem_base_lcd, game->framebuffer);
            }
        }
        // draw chars after letter
        for (int i = idx + 1; i < 26; i++) {
            if (SCREEN_WIDTH / 2 + (idx - i) * 16 < SCREEN_WIDTH - 8) {
                drawChar(SCREEN_WIDTH / 2 + (i - idx) * 16, SCREEN_HEIGHT / 8, 'a' + i, getColor(255, 255, 255), game->mem_base_lcd, game->framebuffer);
            }
        }

        // handle user input
        if (getKnobBlueValue(game->mem_base) != prevButton){
            unsigned char currentVal = getKnobBlueValue(game->mem_base);
            unsigned char previousVal = prevButton;
            if (currentVal - previousVal > 5) {
                idx++;
                prevButton = currentVal;
            }
            else if (currentVal - previousVal < -5) {
                idx--;
                prevButton = currentVal;
            }
        }

        if (getKnobBlueButton(game->mem_base)) {
            name[nameIdx++] = 'a' + idx;
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