#include "lowlevel.h"

/*  maps physical addresses for LCD display */
void *initDisplay(){
    return map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
}

/*  maps physical addresses for hardware controllers */
void *initHardware(){
    return map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

/*  toggles on specified amount of LEDs  */
void setLedLine(void *mem_base, int activeLed){
    uint32_t *addr = mem_base+ SPILED_REG_LED_LINE_o;
    int result = 0;

    for(int i = 0; i < activeLed; i++){
        result = result | (1 << (32-i));
    }

    *(volatile uint32_t*)(addr) = result;
}

/*  sets all LEDs in the line to 0  */
void resetLedLine(void *mem_base){
    uint32_t *addr =  mem_base + SPILED_REG_LED_LINE_o;
    *(volatile uint32_t*)(addr)  = 0;
}

/*  sets LED1 to specified RGB color */
void setLED1Color(char red, char green, char blue,  void * mem_base){
    uint32_t x = 0;
    x |= (uint32_t)red << 16;
    x |= (uint32_t)green << 8;
    x |= (uint32_t)blue;

    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = x;
}

/*  sets LED2 to specified RGB color*/
void setLED2Color(char red, char green, char blue, void * mem_base){
    uint32_t x = 0;
    x |= (uint32_t)red << 16;
    x |= (uint32_t)green << 8;
    x |= (uint32_t)blue;

    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = x;
}

/*  resets LED1 to black color  */
void resetLED1Color(void * mem_base){
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0;
}

/*  resets LED2 to black color  */
void resetLED2Color(void * mem_base){
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0;
}

/*  returns current rotation of the Bue knob as value between 0-255*/
unsigned char getKnobBlueValue(void *mem_base){
    uint32_t *addr =  mem_base + SPILED_REG_KNOBS_8BIT_o;
    return (*addr) & 0xFF;
}

/*  returns current rotation of the Green knob as value between 0-255*/
unsigned char getKnobGreenValue(void *mem_base){
    uint32_t *addr =  mem_base + SPILED_REG_KNOBS_8BIT_o;
    return ((*addr) >> 8) & 0xFF;
}

/*  returns current rotation of the Red knob as value between 0-255*/
unsigned char getKnobRedValue(void *mem_base){
    uint32_t *addr =  mem_base + SPILED_REG_KNOBS_8BIT_o;
    return ((*addr) >> 16) & 0xFF;
}

/*  returns if Blue knob was pressed and adds latency   */
bool getKnobBlueButton(void *mem_base){
    uint32_t *addr =  mem_base+SPILED_REG_KNOBS_8BIT_o;

    if(((*addr) & 0x01000000)){
      usleep(LATENCY * 1000);
      return true;
    }
    
    return false;         
}

/*  returns if Green knob was pressed and adds latency   */
bool getKnobGreenButton(void *mem_base){
    uint32_t *addr =  mem_base+SPILED_REG_KNOBS_8BIT_o;

    if(((*addr) & 0x02000000)){
      usleep(LATENCY * 1000);
      return true;
    }
    
    return false;            
}

/*  returns if Red knob was pressed and adds latency   */
bool getKnobRedButton(void *mem_base){
    uint32_t *addr =  mem_base+SPILED_REG_KNOBS_8BIT_o;
    
    if(((*addr) & 0x04000000)){
      usleep(LATENCY * 1000);
      return true;
    }
    
    return false;         
}

/*  returns width of char in pixel based on font    */
int charWidth(int ch, font_descriptor_t *fdes) {
    int width;
    if (!fdes->width) {
        width = fdes->maxwidth;
    } else {
        width = fdes->width[ch-fdes->firstchar];
    }
    return width;
}

/*  draws char to framebuffer   */
void drawChar(int x, int y, char ch, unsigned short color,  uint16_t* framebuffer){
    font_descriptor_t *fdes = &font_rom8x16;
    
    int w = charWidth(ch, fdes);
    const font_bits_t *ptr;
    int scale = 2;

    if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
        if (fdes->offset) {
            ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
        } else {
            int bw = (fdes->maxwidth+15)/16;
            ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
        }

        int i, j;
        for (i=0; i<fdes->height; i++) {
            font_bits_t val = *ptr;
            for (j=0; j<w; j++) {
                if ((val&0x8000)!=0) {
                    drawPixelBig(x+scale*j, y+scale*i, color, framebuffer, scale);
                }
                val<<=1;
            }
            ptr++;
        }
    }
}

/*  draws framebuffer to display    */
void draw(void* lcd_addr, uint16_t* framebuffer){
    parlcd_write_cmd(lcd_addr, 0x2c);
    for(int x = 0; x < SCREEN_WIDTH * SCREEN_HEIGHT; x++){
        parlcd_write_data(lcd_addr, framebuffer[x]);
    }
}

/*  fills framebuffer with zeros    */
void resetFrameBuffer(uint16_t*framebuffer){
    for(int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++){
        framebuffer[i] = 0;
    }
}

/*  draws colored pixel to framebuffer  */
void drawPixel(int x, int y, unsigned short color, uint16_t* framebuffer) {
    if (x >=0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        framebuffer[x + SCREEN_WIDTH*y] = color;
    }
}

/*  draws colored square to framebuffer */
void drawPixelBig(int x, int y, unsigned short color,  uint16_t* framebuffer, int scale) {
    int i,j;
    for (i=0; i<scale; i++) {
        for (j=0; j<scale; j++) {
            drawPixel(x+i, y+j, color, framebuffer);
        }
    }
}

/*  draws string to framebuffer */
void drawString(int x, int y, char*str, uint16_t *framebuffer){
    int strLen = 0;
    while(str[strLen] != '\0'){
        strLen++;
    }
    
    int charX = x-(strLen/2)*16;
    int i = 0;
    while(i < strLen){
        drawChar(charX + 16*i, y, str[i], getColor(255,255,255), framebuffer);
        i++;
    }
}

/*  draws rectangle with set width to framebuffer  */
void drawRectangle(int x, int y, int len, uint16_t color, uint16_t *framebuffer){
    int width = len + 32;
    int height = 32;

    for(int imgY = 0; imgY < height; imgY++){
        for(int imgX = -width/2; imgX < width/2; imgX++){
            framebuffer[(imgY + y)*SCREEN_WIDTH + x + imgX] = color;
        }
    }
}

/*  returns RGB color as 16-bit int for the LCD display */
uint16_t getColor(unsigned char red, unsigned char green, unsigned char blue){
    return ((((red >> 3) & 0x1f) << 11) | (((green >> 2) & 0x3f) << 5) | (((blue >> 3) & 0x1f))); 
}

/*  calculates length of string */
int strWidth(char* c){
    int length = 0;
    while(c[length++] != '\0');
    return length*16;
}

