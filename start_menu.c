#include "start_menu.h"

void setParameters(Game *game){

        while(true){
            resetFrameBuffer(game->framebuffer);
            if(getKnobBlueButton(game->mem_base)){
                break;
            }

/*
            //difficulty
            drawRectangle(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/4, strWidth("Difficulty"),getColor(0,255,0), game->mem_base_lcd, game->framebuffer);
            drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/4, "Difficulty", game->mem_base_lcd, game->framebuffer);
            switch (getKnobGreenValue(game->mem_base)%3)
            {
            case 0:
                drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, "Easy", game->mem_base_lcd, game->framebuffer);
                game->gateGap = 100;
                break;
            case 1:
                drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, "Normal", game->mem_base_lcd, game->framebuffer);
                game->gateGap = 70;
                break;
            case 2:
                drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT/2, "Hard", game->mem_base_lcd, game->framebuffer);
                game->gateGap = 40;
                break;
            default:
                break;
            }

            drawRectangle(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/4, strWidth("Bonus chance"),getColor(255,0,0), game->mem_base_lcd, game->framebuffer);

            drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/4, "Bonus chance", game->mem_base_lcd, game->framebuffer);
            switch (getKnobBlueValue(game->mem_base)%3)
            {
            case 0:
                drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "Low", game->mem_base_lcd, game->framebuffer);
                game->bonusChance = 0.001;
                break;
            case 1:
                drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "Normal", game->mem_base_lcd, game->framebuffer);
                game->bonusChance = 0.0005;
                break;
            case 2:
                drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, "High", game->mem_base_lcd, game->framebuffer);
                game->bonusChance = 0.01;
                break;
            default:
                break;
            }




*/









            draw(game->framebuffer, game->mem_base_lcd);

        }



}