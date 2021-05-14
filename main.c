#include "game.h"
#include <unistd.h>

#define START_GAME 1
#define SCOREBOARD 2
#define EXIT 3
/**
 * Handle basic menu
*/
int menu(){



    // wrap into functions
    unsigned char *mem_base_buttons = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    unsigned char *mem_base_lcd = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    uint16_t *framebuffer = (uint16_t*) malloc(sizeof(uint16_t) * SCREEN_HEIGHT * SCREEN_WIDTH);

    char *startGame = "Start game";
    char *scoreBoard = "Scoreboard";
    char *exitGame = "Exit";

    drawRectangle(SCREEN_WIDTH/2, SCREEN_HEIGHT/5, strWidth(startGame), getColor(0,0,255), mem_base_lcd, framebuffer);
    drawString(SCREEN_WIDTH/2,SCREEN_HEIGHT/5,startGame,mem_base_lcd,framebuffer);

    drawRectangle(SCREEN_WIDTH/3,SCREEN_HEIGHT/2, strWidth(scoreBoard), getColor(0,255,0), mem_base_lcd, framebuffer);
    drawString(SCREEN_WIDTH/3,SCREEN_HEIGHT/2,scoreBoard,mem_base_lcd,framebuffer);

    drawRectangle(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/2, strWidth(exitGame),getColor(255,0,0), mem_base_lcd, framebuffer);
    drawString(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/2,exitGame,mem_base_lcd,framebuffer);
   
    
    draw(mem_base_lcd, framebuffer);





    //TODO
    while(true){
        if(getKnobBlueButton(mem_base_buttons)){
           resetFrameBuffer(framebuffer);
           draw(mem_base_lcd, framebuffer);
           return START_GAME;
        }
        if(getKnobGreenButton(mem_base_buttons)){
            resetFrameBuffer(framebuffer);
            draw(mem_base_lcd, framebuffer);
           //scoreboard
           return SCOREBOARD;
        }
        if(getKnobRedButton(mem_base_buttons)){
            resetFrameBuffer(framebuffer);
            draw(mem_base_lcd, framebuffer);
            return EXIT;
        }
    }
    

}



/**
 * Check if any change in input
 * 
 * Update the game (position, vectors etc.)
 * Detect collisions
 * 
 * Draw on screen and periferies
*/
void gameLoop(Game* game){
  
    while(true){
            handleInput(game);
            if(!update(game)){
                printf("GAMEOVER\n");
                return; 
            }
            drawGame(game);
    }
   
}

int main(int argc, char** argv){

    Game* game;
    while(true){

                
        switch (menu()){
            

            case START_GAME:
            game = (Game*) malloc(sizeof(Game));
            gameInit(game);
            gameLoop(game);
            freeGame(game);
            break;
            
            case SCOREBOARD:
            //scoreboard();
            break;
            
            case EXIT:
            return 0;

            default:
            break;

        }
    }
   

 
}