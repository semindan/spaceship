#include "game.h"

/**
 * Handle basic menu
*/
void menu(){

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
    unsigned char *base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    parlcd_hx8357_init(base);
   

    unsigned char *buff = malloc(sizeof(unsigned char) * 480 * 320 * 2);
    unsigned char r = 0;
    unsigned char g = 255;
    unsigned char b = 0;
    uint16_t rgb565 = ((((r>>3)&0x1f)<<11) | (((g>>2)&0x3f)<<5) | (((b>>3)&0x1f))); 

     parlcd_write_cmd(base, 0x2c);
    for(int x = 0; x < 480*320; x++){
        parlcd_write_data(base, rgb565);
    }

    
    printf("HI\n");
    free(buff);
        //update(game);
        //drawGame(game);
        //drawConsole(game);
  
}

int main(int argc, char** argv){
    Game* game = (Game*) malloc(sizeof(Game));
    gameInit(game);

    menu();
    gameLoop(game);

    freeGame(game);
}