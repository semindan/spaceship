#include "game.h"

int main(int argc, char[][] argv){
    Game* game = (Game*) malloc(sizeof(Game));
    gameInit(game);

    update(game);

    freeGame(game);
}