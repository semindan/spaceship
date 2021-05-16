#include "menu.h"

/*  render menu to screen   */
void renderMenu(unsigned char* mem_base_lcd, uint16_t* framebuffer) {
    char *startGame = "Start game";
    char *scoreBoard = "Scoreboard";
    char *exitGame = "Exit";

    drawRectangle(SCREEN_WIDTH/2, SCREEN_HEIGHT/5, strWidth(startGame), getColor(0,0,255),  framebuffer);
    drawString(SCREEN_WIDTH/2,SCREEN_HEIGHT/5,startGame,framebuffer);

    drawRectangle(SCREEN_WIDTH/3,SCREEN_HEIGHT/2, strWidth(scoreBoard), getColor(0,255,0),  framebuffer);
    drawString(SCREEN_WIDTH/3,SCREEN_HEIGHT/2,scoreBoard,framebuffer);

    drawRectangle(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/2, strWidth(exitGame),getColor(255,0,0),framebuffer);
    drawString(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/2,exitGame,framebuffer);
   
    draw(mem_base_lcd, framebuffer);
}

/*  handles buttons pressed in menu screen  */
int handleMenuInput(unsigned char* mem_base_buttons, unsigned char* mem_base_lcd, uint16_t* framebuffer){
    while(true){
        if(getKnobBlueButton(mem_base_buttons)){
           resetFrameBuffer(framebuffer);
           draw(mem_base_lcd, framebuffer);
           free(framebuffer);
           return START_GAME;
        }

        if(getKnobGreenButton(mem_base_buttons)){
            resetFrameBuffer(framebuffer);
            draw(mem_base_lcd, framebuffer);
            free(framebuffer);
            return SCOREBOARD;
        }
        
        if(getKnobRedButton(mem_base_buttons)){
            resetFrameBuffer(framebuffer);
            draw(mem_base_lcd, framebuffer);
            free(framebuffer);
            return EXIT;
        }
    }
}
