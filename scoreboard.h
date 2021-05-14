#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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

ScoreArray* loadScoreBoard();
ScoreArray* sortScoreBoard(ScoreArray* scores, int low, int high);
int makePartitionArray(ScoreArray*scores, int low, int high);
void drawScoreBoard(ScoreArray* scores);
void saveScoreBoard(ScoreArray* sa);
void freeScoreArray(ScoreArray* sa);