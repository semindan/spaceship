#include "game.h"
#include <unistd.h>
/**
 * Handle basic menu
*/
void menu(Game* game){



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
           return;
        }
        if(getKnobGreenButton(mem_base_buttons)){
           //scoreboard
           return;
        }
        if(getKnobRedButton(mem_base_buttons)){
            return;
        }
    }
    

}
  double clockToMilliseconds(clock_t ticks){
    // units/(units/time) => time (seconds) * 1000 = milliseconds
    return (ticks/(double)CLOCKS_PER_SEC)*1000.0;
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
    
    float FPS = 20;
    float frameMS = 1000/FPS;
    float delayMS = 0;
    while(true){
        /*
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        */
        //printf("start %d\n", start.tv_nsec);
            handleInput(game);
            // save score
            if(!update(game)){
                printf("GAMEOVER\n");
            }
            drawGame(game);
        /*
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        //printf("end %d\n", end.tv_nsec);
        delayMS = frameMS - ((float)(end.tv_nsec - start.tv_nsec)/1000000);
        if(delayMS > 0){
               // usleep(delayMS*1000);
                parlcd_delay(delayMS);
        }
        */
        //parlcd_delay(delayMS);
       // printf("%f\n", delayMS);
    }
      
        //drawConsole(game);
    

    
     
 
   
}

int main(int argc, char** argv){
    Game* game = (Game*) malloc(sizeof(Game));
    gameInit(game);

    menu(game);
    gameLoop(game);

    freeGame(game);
}