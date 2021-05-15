#ifndef __START_MENU_H__
#define __START_MENU_H__

#include "game.h"
#include "lowLevel.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

void setupBonuses(Game* game, int idx);
void setupDifficulty(Game *game, int idx);
void setParameters(Game * game);

#endif /* __START_MENU_H__ */
