#include "lowLevel.h"
#include <stdio.h>
void *initDisplay(){
    return map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
}
void *initHardware(){
    return map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

void setLED1Color(char red, char green, char blue){
    uint32_t x = 0;
    x |= (uint32_t)red << 16;
    x |= (uint32_t)green << 8;
    x |= (uint32_t)blue;

}

void setLED2Color(char red, char green, char blue, unsigned char * mem_base){
    uint32_t x = 0;
    x |= (uint32_t)red << 16;
    x |= (uint32_t)green << 8;
    x |= (uint32_t)blue;

    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = x;
}
uint16_t getColor(unsigned char red, unsigned char green, unsigned char blue){
    return ((((red>>3)&0x1f)<<11) | (((green>>2)&0x3f)<<5) | (((blue>>3)&0x1f))); 

}

unsigned char getKnobBlueValue(void *mem_base){
    uint32_t *addr =  mem_base+SPILED_REG_KNOBS_8BIT_o;
    return (*addr) & 0xFF;
}

unsigned char getKnobGreenValue(void *mem_base){
    uint32_t *addr =  mem_base+SPILED_REG_KNOBS_8BIT_o;
    return ((*addr) >> 8) & 0xFF;
}

unsigned char getKnobRedValue(void *mem_base){
    uint32_t *addr =  mem_base+SPILED_REG_KNOBS_8BIT_o;
    return ((*addr) >> 16) & 0xFF;
  
}

void draw(void* lcd_addr, uint16_t* framebuffer){
    parlcd_write_cmd(lcd_addr, 0x2c);
    for(int x = 0; x < SCREEN_WIDTH * SCREEN_HEIGHT; x++){
        parlcd_write_data(lcd_addr, framebuffer[x]);
    }
}
