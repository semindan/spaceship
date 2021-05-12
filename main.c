#include "game.h"
#include <unistd.h>
/**
 * Handle basic menu
*/
void menu(){

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
            update(game);
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

    menu();
    gameLoop(game);

    freeGame(game);
}