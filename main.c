#include <unistd.h>

#include "game.h"
#include "menu.h"
#include "scoreboard.h"
#include "start_menu.h"

/*  handles menu render and interactions    */
int menu(){
    // wrap into functions
    unsigned char *mem_base_buttons = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    unsigned char *mem_base_lcd = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    uint16_t *framebuffer = (uint16_t*) malloc(sizeof(uint16_t) * SCREEN_HEIGHT * SCREEN_WIDTH);

    renderMenu(mem_base_lcd, framebuffer);
    return handleMenuInput(mem_base_buttons, mem_base_lcd, framebuffer);
}

/*  gameloop checks input, updates game and draws it to the display */
void gameLoop(Game* game) {

while(true)
{
    handleInput(game);
    
     if(!update(game)){
            printf("GAMEOVER\n");
            return; 
            }
    drawGame(game);
}

}


/*  manages scoreboard init, render and cleanup */
void scoreboard() {
    ScoreArray *scoreArr = loadScoreboard();
    if(scoreArr == NULL){
        return;
    }
    
    sortScoreboard(scoreArr, 0, scoreArr->count-1);
    saveScoreboard(scoreArr);
    drawScoreboard(scoreArr);
    freeScoreArray(scoreArr);
}

/*  draws starting menu for game and launches game and cleans memory afterwards */
void startMenu() {
    Game* game;
    game = (Game*) malloc(sizeof(Game));
    gameInit(game);

    setParameters(game);
    gameLoop(game);
    freeGame(game);
}

/*  main function   */
int main(int argc, char** argv) {
    // checks if file exists, if not, creates it
    if(access("scores.txt", F_OK) != 0) {
        FILE *f = fopen("scores.txt", "w");
        fclose(f);
    }
    
    while(true){  

        switch (menu()){
            case START_GAME: startMenu(); break;
            case SCOREBOARD: scoreboard(); break;
            case EXIT: return 0;
            default: break;
        }
    }
}
