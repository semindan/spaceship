#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lowLevel.h"

typedef struct {
    char* name;
    int value;
} Score;

typedef struct{
    Score** scores;
    int count;
    int capacity;
} ScoreArray;

/** 
 * loads scoreboard from "scores.txt"
 * returns: ScoreArray, null on missing file 
 */
ScoreArray* loadScoreboard();

/** 
 * sorts Scoreboard by highest score
 * returns: void, changes the passed ScoreArray
 */
void sortScoreboard(ScoreArray* scores, int low, int high);

/** 
 * support function for quicksort in sortScoreboard();
 * returns: int pivot
 */
int makePartitionArray(ScoreArray*scores, int low, int high);

/** 
 * handles drawing of Scoreboard on the screen
 * draws 5 or less names and scores and handles user controls
 * returns: void 
 */
void drawScoreboard(ScoreArray* scores);

/** 
 * saves scoreboard to "scores.txt" using "w"
 * returns: void 
 */
void saveScoreboard(ScoreArray* sa);

/** 
 * free allocated memory for ScoreArray
 * returns: void 
 */
void freeScoreArray(ScoreArray* sa);

#endif /* __SCOREBOARD_H__ */
