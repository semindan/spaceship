#include "spaceship.h"


typedef struct{
    Spaceship* sp;
    int spaceshipPos[2];
    double spaceshipVelocity;

    int gateSpaces[16];
} Game;

/**
 * Inicializace vsech podsoucasti hry
*/
void gameInit(Game* game);

/**
 * Update arraye, tzn generovani novych prekazek
*/
void updateArray(Game* game);

/**
 * Tady bude core vykreslovani na display a LEDky
*/
void draw(Game* game);

/**
 * Sem se potom daji vsechny registry na potenciometry, kteryma se to bude ovladat
*/
void handleInput(Game* game);

/**
 * Hlavni gameloop
*/
void update(Game* game);

/**
 * Uvolneni veskere pameti
*/
void freeGame(Game* game);

// debug pro console use
void drawConsole(Game* game);
