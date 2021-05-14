#include "scoreboard.h"

ScoreArray* loadScoreBoard(){
  FILE *f = fopen("scores.txt", "r");
  if(f == NULL){
      fprintf(stderr, "Error while opening\n");
  }
  ScoreArray* sa = (ScoreArray*) malloc(sizeof(ScoreArray));
  sa->capacity = 5;
  sa->count = 0;
  sa->scores = (Score**) malloc(sizeof(Score*)*sa->capacity);
  char str[16];
  int integer;
  while(fscanf(f,"%s %d\n", str, &integer) != EOF){
      printf("LINE\n");
      if(sa->count >= sa->capacity){
          sa->capacity *= 2;
          sa = realloc(sa, sizeof(Score)*sa->capacity);
      }
      
      Score *score = (Score*) malloc(sizeof(Score));
      score->name = malloc(17);
      memcpy(score->name, str, 16);
      score->value = integer;
      sa->scores[sa->count] = score;
      sa->count++;

  }
  fclose(f);
  
  return sa;
}

ScoreArray* sortScoreBoard(ScoreArray* scores);

void saveScoreBoard(ScoreArray* sa){
  FILE *f = fopen("scores.txt", "w");
  fscanf(f,"%d\n", &sa->count);
  for(int i = 0; i < sa->count; i++){
    fprintf(f,"%s %d\n", sa->scores[i]->name, sa->scores[i]->value);
  }
  fclose(f);
}

void drawScoreBoard(ScoreArray* scores){
    
    unsigned char *mem_base_lcd = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    unsigned char *mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

    uint16_t *framebuffer = (uint16_t*) malloc(sizeof(uint16_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
    unsigned char prevKnobVal = getKnobBlueValue(mem_base);
    
    
    int len = 5;
    int ind = 0;
    
    
    
    while(true){
        resetFrameBuffer(framebuffer);
        
        for(int i = 0; i < len; i++){
        drawString(SCREEN_WIDTH/4, SCREEN_HEIGHT*(i+1)/(len+1), scores->scores[i+ind]->name, mem_base_lcd,framebuffer);
        char scoreVal[100];
        sprintf(scoreVal,"%d", scores->scores[i+ind]->value);
        drawString(SCREEN_WIDTH*3/4, SCREEN_HEIGHT*(i+1)/(len+1), scoreVal, mem_base_lcd,framebuffer);
        
        }

     if (getKnobBlueValue(mem_base) != prevKnobVal)
        {
            unsigned char currentVal = getKnobBlueValue(mem_base);
            unsigned char previousVal = prevKnobVal;
            if (currentVal - previousVal > 5)
            {
                ind += (ind == scores->count) ? 0 : 1;
                prevKnobVal = currentVal;
            }
            else if (currentVal - previousVal < -5)
            {
                ind -= (ind == 0) ? 0 : 1;
                prevKnobVal = currentVal;
            }
        }
        if (getKnobRedButton(mem_base))
        {
            usleep(100 * 1000);
            break;
        }
        draw(mem_base_lcd, framebuffer);
    }
    
}



void freeScoreArray(ScoreArray* sa){
  free(sa->scores);
  free(sa);
}