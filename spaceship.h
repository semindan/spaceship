#include <stdbool.h>
#include <math.h>

typedef struct{
    double movementVec[2];
    
    // normalized
    double headingAngle;
    double engineThrust;

    int hp;
    bool speedBoost;
    bool invincible;
} Spaceship;


/*  initializes default values to spaceship  */
void spaceshipInit(Spaceship* sp);

/*  Updates spaceship movement  */
void spaceshipUpdate(Spaceship *sp);
