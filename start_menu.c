#include "start_menu.h"

void setupBonuses(Game* game, int idx) {
    drawRectangle(SCREEN_WIDTH/4,SCREEN_HEIGHT/4, strWidth("Bonus chance"),getColor(255,0,0),  game->framebuffer);
    drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/4, "Bonus chance",  game->framebuffer);

    switch (idx % 3) {
        case 0:
            drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "Low",  game->framebuffer);
            game->bonusChance = 0.001;
            break;
        case 1:
            drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "Normal",  game->framebuffer);
            game->bonusChance = 0.005;
            break;
        case 2:
            drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "High",  game->framebuffer);
            game->bonusChance = 0.01;
            break;
        default:
            break;
    }
}

void setupDifficulty(Game *game, int idx) {
    drawRectangle(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/4, strWidth("Difficulty"),getColor(0,255,0), game->framebuffer);
    drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/4, "Difficulty",  game->framebuffer);

    switch (idx % 3) {
        case 0:
            drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, "Easy",  game->framebuffer);
            game->gateGap = 100;
            break;
        case 1:
            drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, "Normal",  game->framebuffer);
            game->gateGap = 70;
            break;
        case 2:
            drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, "Hard",  game->framebuffer);
            game->gateGap = 40;
            break;
        default:
            printf("default\n");
            break;
    }
}

void setParameters(Game *game) {
    resetFrameBuffer(game->framebuffer);
    draw(game->mem_base_lcd,game->framebuffer);

    int idxDifficulty = 0;
    int idxBonus = 0;
    unsigned char prevRed = getKnobRedValue(game->mem_base);
    unsigned char prevGreen= getKnobGreenValue(game->mem_base);

    while(true){
        resetFrameBuffer(game->framebuffer);
        drawRectangle(SCREEN_WIDTH/2,SCREEN_HEIGHT*3/4, strWidth("Start"),getColor(0,0,255), game->framebuffer);
        drawString(SCREEN_WIDTH/2, SCREEN_HEIGHT*3/4, "Start",  game->framebuffer);
        // handle input
        if(getKnobBlueButton(game->mem_base)){
            break;
        }

        if (getKnobRedValue(game->mem_base) != prevRed){
            unsigned char currentVal = getKnobRedValue(game->mem_base);
            unsigned char previousVal = prevRed;

            if (currentVal - previousVal > 10 || currentVal - previousVal < -10) {
                idxBonus++;
                prevRed= currentVal;
            }
        }

        if (getKnobGreenValue(game->mem_base) != prevGreen){
            unsigned char currentVal = getKnobGreenValue(game->mem_base);
            unsigned char previousVal = prevGreen;
            if (currentVal - previousVal > 10 || currentVal - previousVal < -10) {
                idxDifficulty++;
                prevGreen= currentVal;
            }
        }

        // bonus UI + input
        setupBonuses(game, idxBonus);

        // difficulty UI + input
        setupDifficulty(game, idxDifficulty);
        
        draw(game->mem_base_lcd, game->framebuffer);
    }
}
