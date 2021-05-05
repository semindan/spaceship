#include "lowLevel.h"

void setLED1Color(char red, char green, char blue){
    uint32_t x = 0;
    x |= (uint32_t)red << 16;
    x |= (uint32_t)green << 8;
    x |= (uint32_t)blue;

    uint32_t* addr = SPILED_REG_BASE_PHYS + SPILED_REG_LED_RGB1_o;
    (*addr) = x;
}

void setLED2Color(char red, char green, char blue){
    uint32_t x = 0;
    x |= (uint32_t)red << 16;
    x |= (uint32_t)green << 8;
    x |= (uint32_t)blue;

    uint32_t* addr = SPILED_REG_BASE_PHYS + SPILED_REG_LED_RGB2_o;
    (*addr) = x;
}

char getKnob1Value(){
    uint32_t* addr = SPILED_REG_BASE_PHYS + SPILED_REG_KNOBS_8BIT_o;
    return ((*addr) >> 16) & 0xFF;
}

char getKnob2Value(){
    uint32_t* addr = SPILED_REG_BASE_PHYS + SPILED_REG_KNOBS_8BIT_o;
    return ((*addr) >> 8) & 0xFF;
}

char getKnob3Value(){
    uint32_t* addr = SPILED_REG_BASE_PHYS + SPILED_REG_KNOBS_8BIT_o;
    return (*addr) & 0xFF;
}

void draw(char** canvas){
    uint32_t* addr = PARLCD_REG_BASE_PHYS;
    for(int x = 0; x < SCREEN_WIDTH; x++){
        for(int y = 0; y < SCREEN_HEIGTH; y++){
            // write to address
        
        }
    }
}
