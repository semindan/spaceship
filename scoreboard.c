#include "scoreboard.h"

/* loads scoreboard from "scores.txt" to ScoreArray */
ScoreArray *loadScoreboard()
{
    FILE *f = fopen("scores.txt", "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error while opening\n");
        return NULL;
    }

    ScoreArray *sa = (ScoreArray *)malloc(sizeof(ScoreArray));
    sa->capacity = 5;
    sa->count = 0;
    sa->scores = (Score **)malloc(sizeof(Score *) * sa->capacity);

    char str[16];
    int integer;
    while (fscanf(f, "%s %d\n", str, &integer) != EOF)
    {
        if (sa->count >= sa->capacity)
        {
            sa->capacity *= 2;
            sa->scores = realloc(sa->scores, sizeof(Score *) * sa->capacity);
        }

        Score *score = (Score *)malloc(sizeof(Score));
        score->name = malloc(17);
        strcpy(score->name, str);
        score->value = integer;
        sa->scores[sa->count] = score;
        sa->count++;
    }
    fclose(f);

    return sa;
}

/* sorts Scoreboard by highest score */
void sortScoreboard(ScoreArray *scores, int low, int high)
{
    if (low < high)
    {
        int p = makePartitionArray(scores, low, high);
        sortScoreboard(scores, low, p - 1);
        sortScoreboard(scores, p + 1, high);
    }
}

/* support function for quicksort in sortScoreboard() */
int makePartitionArray(ScoreArray *scores, int low, int high)
{
    int pivot = scores->scores[high]->value;
    int i = low;

    for (int j = low; j < high; j++)
    {
        if (scores->scores[j]->value > pivot)
        {
            Score *temp = scores->scores[i];
            scores->scores[i] = scores->scores[j];
            scores->scores[j] = temp;
            i++;
        }
    }

    Score *temp = scores->scores[i];
    scores->scores[i] = scores->scores[high];
    scores->scores[high] = temp;
    return i;
}

/* handles drawing of Scoreboard on the screen
 * draws 5 or less names and scores and handles user controls */
void drawScoreboard(ScoreArray *scores)
{

    unsigned char *mem_base_lcd = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    unsigned char *mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    uint16_t *framebuffer = (uint16_t *)malloc(sizeof(uint16_t) * SCREEN_HEIGHT * SCREEN_WIDTH);

    unsigned char prevKnobVal = getKnobBlueValue(mem_base);
    int len = scores->count > 5 ? 5 : scores->count;
    int ind = 0;

    while (true)
    {
        resetFrameBuffer(framebuffer);
        

        for (int i = 0; i < len; i++)
        {
            drawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT * (i + 1) / (len + 1), scores->scores[i + ind]->name, framebuffer);

            char scoreVal[100];
            sprintf(scoreVal, "%d", scores->scores[i + ind]->value);

            drawString(SCREEN_WIDTH * 5 / 6, SCREEN_HEIGHT * (i + 1) / (len + 1), scoreVal, framebuffer);
        }

        if (getKnobBlueValue(mem_base) != prevKnobVal)
        {
            unsigned char currentVal = getKnobBlueValue(mem_base);
            unsigned char previousVal = prevKnobVal;

            if (currentVal - previousVal > 5)
            {
                ind += (ind == scores->count - len) ? 0 : 1;
                prevKnobVal = currentVal;
            }
            else if (currentVal - previousVal < -5)
            {
                ind -= (ind == 0) ? 0 : 1;
                prevKnobVal = currentVal;
            }
        }

        drawRectangle(SCREEN_WIDTH/2,SCREEN_HEIGHT*7/8, strWidth("Back"),getColor(255,0,0), framebuffer);
        drawString(SCREEN_WIDTH/2, SCREEN_HEIGHT*7/8, "Back",  framebuffer);

        if (getKnobRedButton(mem_base))
        {
            break;
        }

        draw(mem_base_lcd, framebuffer);
    }
}

/* saves scoreboard to "scores.txt" */
void saveScoreboard(ScoreArray *sa)
{
    FILE *f = fopen("scores.txt", "w");
    if (f == NULL)
        return;

    for (int i = 0; i < sa->count; i++)
    {
        fprintf(f, "%s %d\n", sa->scores[i]->name, sa->scores[i]->value);
    }

    fclose(f);
}

/* free allocated memory for ScoreArray */
void freeScoreArray(ScoreArray *sa)
{
    for (int i = 0; i < sa->count; i++)
    {
        free(sa->scores[i]->name);
        free(sa->scores[i]);
    }
    free(sa->scores);
    free(sa);
}
