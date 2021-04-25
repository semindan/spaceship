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
 * Draw state on screen and periferies
*/
void gameLoop(Game* game){

    while(true){
        handleInput(game);

        update(game);

        drawConsole(game);
    }
}

int main(int argc, char** argv){
    Game* game = (Game*) malloc(sizeof(Game));
    gameInit(game);

    menu();
    gameLoop(game);

    freeGame(game);
}