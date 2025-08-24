/*
 * Project Name: SSD1306_GRAPH
 * File: SSD1306OLED.c
 * Description: OLED SSD1306  I2C library c file
 * Author: Gavin Lyons.
 * Complier: xc8 v2.10 compiler
 * PIC: PIC18F47K42
 * IDE:  MPLAB X v5.30
 * Created Sep 2020
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_PIC18F47K42_projects
 */

// ************ Libs ****************
#include "SSD1306OLED.h"
#include "string.h"
#include "mcc_generated_files/mcc.h"


// *********** Private Variables ***********
typedef struct _Selected_Font_s
{
  const uint8_t *font;        // Fonts Stored are Const
  uint8_t x_size;
  uint8_t y_size;
  uint8_t offset;
  uint8_t numchars;
  uint8_t inverted;
} Selected_Font_s;


static Selected_Font_s sfont;

uint8_t _rotation=0; // 0-3
int16_t _width, _height; // Display w/h as modified by current rotation 
        


// ************** Memory Buffer Display ****
static uint8_t buffer[SSD1306_HEIGHT * SSD1306_WIDTH / 8] ={
    // block 1
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

    //block 2
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#if (SSD1306_HEIGHT * SSD1306_WIDTH > 96*16)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
#if (SSD1306_HEIGHT == 64)
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
#endif
#endif
};

// *********** Private Function Prototypes ****************
static void ssd1306_command(uint8_t command);
static void ssd1306_data(uint8_t value);
static uint8_t width(void);
static uint8_t height(void);

// ************ Function Space ****************

/*
 * Desc: SSD1306_Init
 * Initialize OLED
 */
void SSD1306_Init(void) {
    __delay_ms(100);
    ssd1306_command(SSD1306_DISPLAY_OFF);
    ssd1306_command(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    ssd1306_command(0x80);
    ssd1306_command(SSD1306_SET_MULTIPLEX_RATIO);
    ssd1306_command(SSD1306_HEIGHT - 1);
    ssd1306_command(SSD1306_SET_DISPLAY_OFFSET);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_SET_START_LINE | 0x00);
    ssd1306_command(SSD1306_CHARGE_PUMP);
    ssd1306_command(0x14);
    ssd1306_command(SSD1306_MEMORY_ADDR_MODE);
    ssd1306_command(0x00); //Horizontal Addressing Mode is Used
    ssd1306_command(SSD1306_SET_SEGMENT_REMAP | 0x01);
    ssd1306_command(SSD1306_COM_SCAN_DIR_DEC);

#if defined SSD1306_128_32
    ssd1306_command(SSD1306_SET_COM_PINS);
    ssd1306_command(0x02);
    ssd1306_command(SSD1306_SET_CONTRAST_CONTROL);
    ssd1306_command(0x8F);

#elif defined SSD1306_128_64
    ssd1306_command(SSD1306_SET_COM_PINS);
    ssd1306_command(0x12);
    ssd1306_command(SSD1306_SET_CONTRAST_CONTROL);
    ssd1306_command(0xCF);

#elif defined SSD1306_96_16 // Not tested , no part.
    ssd1306_command(SSD1306_SET_COM_PINS);
    ssd1306_command(0x2); // ?
    ssd1306_command(SSD1306_SET_CONTRAST_CONTROL);
    ssd1306_command(0xAF);
#endif

    ssd1306_command(SSD1306_SET_PRECHARGE_PERIOD);
    ssd1306_command(0xF1);
    ssd1306_command(SSD1306_SET_VCOM_DESELECT);
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_DISPLAY_ALL_ON_RESUME);
    ssd1306_command(SSD1306_NORMAL_DISPLAY);
    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
    ssd1306_command(SSD1306_DISPLAY_ON);

    __delay_ms(100);
    SSD1306_UpdateDisplay();
}


/*
 * Desc: SSD1306_SetFont
 * Param1:  font: Select this font, pass PICO or UNO or MEGA
 */
void SSD1306_SetFont(const uint8_t *font) {
    sfont.font = font;
    sfont.x_size = *(font + 0);
    sfont.y_size = *(font + 1);
    sfont.offset = *(font + 2);
    sfont.numchars = *(font + 3);
    sfont.inverted = false;
}

// Desc: Turns On Display
// Param1: bits,  1  on , 0 off

void SSD1306_DisplayEnable(uint8_t bits) {
    bits ? ssd1306_command(SSD1306_DISPLAY_ON) : ssd1306_command(SSD1306_DISPLAY_OFF);
}

/*
 * Desc: SSD1306_InvertFont
 * Invert the font
 * Param1: true or false
 */
void SSD1306_InvertFont(bool invert_status) {
    invert_status ? (sfont.inverted = true) : (sfont.inverted = false);
}

/*
 * Desc: SSD1306_UpdateDisplay
 * Update the OLED Buffer on the actual display
 */
void SSD1306_UpdateDisplay(void) {
    uint16_t i = 0;
    uint8_t x = 0;
    ssd1306_command(SSD1306_SET_COLUMN_ADDR);
    ssd1306_command(0); // Column start address (0 = reset)
    ssd1306_command(SSD1306_WIDTH - 1); // Column end address (127 = reset)

    ssd1306_command(SSD1306_SET_PAGE_ADDR);
    ssd1306_command(0); // Page start address (0 = reset)
#if SSD1306_HEIGHT == 64
    ssd1306_command(7); // Page end address
#endif
#if SSD1306_HEIGHT == 32
    ssd1306_command(3); // Page end address
#endif
#if SSD1306_HEIGHT == 16
    ssd1306_command(1); // Page end address
#endif

    for (i = 0; i < (SSD1306_WIDTH * SSD1306_HEIGHT / 8); i++) {
        // Send data for Transmission
        for (x = 0; x < 16; x++) {
            ssd1306_data(buffer[i]);
            i++;
        }
        i--;
    }
}

/*
 * Desc: SSD1306_Contrast.
 * Set the OLED display contrast.
 * Param1:  contrast: contrast value: 0x00 to 0xFF
 */
void SSD1306_Contrast(uint8_t contrast) {
    ssd1306_command(SSD1306_SET_CONTRAST_CONTROL);
    ssd1306_command(contrast);
}

/*
 * Desc: SSD1306_FillBUffer
 * Fill the OLED Buffer.
 *  Param1:  contrast:  Fill value,
 *  pass 0x00 to clear , 0xFF to fill (normal mode)
 */
void SSD1306_FillBuffer(uint8_t pattern) {
    memset(buffer, pattern, (SSD1306_WIDTH * SSD1306_HEIGHT / 8));
}

/*
 * Desc: SSD1306_InvertDisplay.
 * Invert the Display based on the parameters
 * Param1:  value: If True invert the display
 */
void SSD1306_InvertDisplay(bool value) {
    if (value) {
        ssd1306_command(SSD1306_INVERT_DISPLAY);
    } else {
        ssd1306_command(SSD1306_NORMAL_DISPLAY);
    }
}

/**
 * Desc: SSD1306_SetPixel.
 * Draws a pixel on OLED by using the specified parameters.
 * Param1:  x: x coordinate with valid 
 * Param2:  y: y coordinate with valid 
 * Param3:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_SetPixel(int16_t x, int16_t y, uint8_t color) {
    if ((x < 0) || (x >= SSD1306_WIDTH) || (y < 0) || (y >= SSD1306_HEIGHT))
        return;
    int16_t temp;
    switch (_rotation) {
        case 1:
            temp = x;
            x = SSD1306_WIDTH - 1 - y;
            y = temp;
            break;
        case 2:
            x = SSD1306_WIDTH - 1 - x;
            y = SSD1306_HEIGHT - 1 - y;
            break;
        case 3:
            temp = x;
            x = y;
            y = SSD1306_HEIGHT - 1 - temp;
            break;
    }

    switch (color) {
        case SSD1306_WHITE: buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y & 7));
            break;
        case SSD1306_BLACK: buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y & 7));
            break;
        case SSD1306_INVERSE: buffer[x + (y / 8) * SSD1306_WIDTH] ^= (1 << (y & 7));
            break;
    }
}

/**
 * Desc: Draws a line on OLED.
 * Draws a line on OLED by using the specified parameters.
 * <a href="https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm">
 * Algorithm Used</a>
 * Param1:  x_start: x coordinate of start point. Valid values: 0..127
 * Param2:  y_start: x coordinate of start point. Valid values: 0..63
 * Param3:  x_end: x coordinate of end point. Valid values: 0..127
 * Param4:  y_end: y coordinate of end point. Valid values: 0..63
 * Param5:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_Line(int16_t x_start, int16_t y_start, int16_t x_end, int16_t y_end, uint8_t color) {
    int16_t x, y, addx, addy, dx, dy;
    int32_t P;
    int16_t i;
    dx = abs((int16_t) (x_end - x_start));
    dy = abs((int16_t) (y_end - y_start));
    x = x_start;
    y = y_start;

    if (x_start > x_end)
        addx = -1;
    else
        addx = 1;

    if (y_start > y_end)
        addy = -1;
    else
        addy = 1;

    if (dx >= dy) {
        P = 2 * dy - dx;

        for (i = 0; i <= dx; ++i) {
            SSD1306_SetPixel(x, y, color);
            if (P < 0) {
                P += 2 * dy;
                x += addx;
            } else {
                P += 2 * dy - 2 * dx;
                x += addx;
                y += addy;
            }
        }
    } else {
        P = 2 * dx - dy;
        for (i = 0; i <= dy; ++i) {
            SSD1306_SetPixel(x, y, color);

            if (P < 0) {
                P += 2 * dx;
                y += addy;
            } else {
                P += 2 * dx - 2 * dy;
                x += addx;
                y += addy;
            }
        }
    }
}

// Desc: Draws a Vertical line of height h 
void SSD1306_V_Line(int16_t x, int16_t y,
        int16_t h, uint8_t color) {
    SSD1306_Line(x, y, x, y + h - 1, color);
}

// Desc: Draws a Horizontal line of width w 
void SSD1306_H_Line(int16_t x, int16_t y,
        int16_t w, uint8_t color) {
    SSD1306_Line(x, y, x + w - 1, y, color);
}

/*
 * Desc: Draws a rectangle on OLED.
 * Draws a rectangle on OLED by using the specified parameters.
 * Param1:  x: x coordinate of the upper left rectangle corner.
 * Param2:  y: y coordinate of the upper left rectangle corner.
 * Param3:  w: width
 * Param4:  h: height
 * Param5:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_Rectangle(int16_t x, int16_t y,
        int16_t w, int16_t h, uint8_t color) {
    SSD1306_H_Line(x, y, w, color);
    SSD1306_H_Line(x, y + h - 1, w, color);
    SSD1306_V_Line(x, y, h, color);
    SSD1306_V_Line(x + w - 1, y, h, color);
}

/*
 * Desc: SSD1306_FillRectangle
 * Draws a rectangle on OLED by using the specified parameters with filling.
 * Param1:  x: x coordinate of the upper left rectangle corner.
 * Param2:  1: y coordinate of the upper left rectangle corner.
 * Param3:  w: width
 * Param4:  h: height
 * Param5:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_FillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color) {
    for (int16_t i = x; i < x + w; i++) {
        SSD1306_V_Line(i, y, h, color);
    }
}

/*
 * Desc: SSD1306_Triangle
 * Draw a Triangle based on the coordinates
 * Param1:  x0: x0 coordinate
 * Param2:  y0: y0 coordinate
 * Param3:  x1: x1 coordinate
 * Param4:  y1: y1 coordinate
 * Param5:  x2: x2 coordinate
 * Param6:  y2: y2 coordinate
 * Param7:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color) {
    SSD1306_Line(x0, y0, x1, y1, color);
    SSD1306_Line(x1, y1, x2, y2, color);
    SSD1306_Line(x2, y2, x0, y0, color);
}

// Fill a triangle
void SSD1306_FillTriangle(int16_t x0, int16_t y0,
        int16_t x1, int16_t y1,
        int16_t x2, int16_t y2, uint8_t color) {

    int16_t a, b, y, last;

    if (y0 > y1) {
        SSD1306_swap(y0, y1);
        SSD1306_swap(x0, x1);
    }
    if (y1 > y2) {
        SSD1306_swap(y2, y1);
        SSD1306_swap(x2, x1);
    }
    if (y0 > y1) {
        SSD1306_swap(y0, y1);
        SSD1306_swap(x0, x1);
    }

    if (y0 == y2) {
        a = b = x0;
        if (x1 < a) a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a) a = x2;
        else if (x2 > b) b = x2;
        SSD1306_H_Line(a, y0, b - a + 1, color);
        return;
    }

    int16_t
    dx01 = x1 - x0,
            dy01 = y1 - y0,
            dx02 = x2 - x0,
            dy02 = y2 - y0,
            dx12 = x2 - x1,
            dy12 = y2 - y1;
    int32_t
    sa = 0,
            sb = 0;

    if (y1 == y2) last = y1; 
    else last = y1 - 1; 

    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
  
        if (a > b) SSD1306_swap(a, b);
        SSD1306_H_Line(a, y, b - a + 1, color);
    }

     sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if (a > b) SSD1306_swap(a, b);
        SSD1306_H_Line(a, y, b - a + 1, color);
    }
}

// Desc called from inside DrawRoundRect
void SSD1306_DrawCircleHelper(int16_t x0, int16_t y0,
        int16_t r, uint8_t cornername, uint8_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x4) {
            SSD1306_SetPixel(x0 + x, y0 + y, color);
            SSD1306_SetPixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
            SSD1306_SetPixel(x0 + x, y0 - y, color);
            SSD1306_SetPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            SSD1306_SetPixel(x0 - y, y0 + x, color);
            SSD1306_SetPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            SSD1306_SetPixel(x0 - y, y0 - x, color);
            SSD1306_SetPixel(x0 - x, y0 - y, color);
        }
    }
}

// Draw a rounded corner rectangle
void SSD1306_DrawRoundRect(int16_t x, int16_t y, int16_t w,
        int16_t h, int16_t r, uint8_t color) {
    SSD1306_H_Line(x + r, y, w - 2 * r, color); // Top
    SSD1306_H_Line(x + r, y + h - 1, w - 2 * r, color); // Bottom
    SSD1306_V_Line(x, y + r, h - 2 * r, color); // Left
    SSD1306_V_Line(x + w - 1, y + r, h - 2 * r, color); // Right
    // draw four corners
    SSD1306_DrawCircleHelper(x + r, y + r, r, 1, color);
    SSD1306_DrawCircleHelper(x + w - r - 1, y + r, r, 2, color);
    SSD1306_DrawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
    SSD1306_DrawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

// Fill a rounded corner rectangle
void SSD1306_FillRoundRect(int16_t x, int16_t y, int16_t w,
        int16_t h, int16_t r, uint8_t color) {
    SSD1306_FillRectangle(x + r, y, w - 2 * r, h, color);
    SSD1306_FillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
    SSD1306_FillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}

/*
 * Desc: OLED Image.
 * Displays bitmap image on OLED.
 * Param1:  *image: image to be displayed. Bitmap array must be located in code
 * memory. DATA vertical addressed Use https://javl.github.io/image2cpp/
 * NOTES Writes to SCREEN  NOT BUFFER , FULL SCREEN BITMAP ONLY 
 */
void SSD1306_Bitmap(const uint8_t *image) {
    uint16_t i;
    for (i = 0; i < (SSD1306_WIDTH * SSD1306_HEIGHT / 8); i++) {
        buffer[i] = *(image + i);
    }
}

/*
   Function Desc:    Draw a  image at the specified (x,y) position,
              using the specified foreground color 
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    bitmap  byte array with monochrome bitmap HORIZONTALY ADDRESSED DATA
    Param4:    w   Width of bitmap in pixels
    Param5:    h   Height of bitmap in pixels
    Param6:    color
 * NOTES Writes to BUFFER NOT SCREEN 
 */
void SSD1306_BitmapBuffer(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h,
        uint8_t color) {

    uint16_t byteWidth = (w + 7) / 8; 
    uint8_t _byte = 0;
    uint16_t i, j;

    for (j = 0; j < h; j++, y++) {
        for (i = 0; i < w; i++) {
            if (i & 7) _byte <<= 1;
            else _byte = bitmap[j * byteWidth + i / 8];
            if (_byte & 0x80)
                SSD1306_SetPixel(x + i, y, color);
        }
    }
}

/*
 * Desc: Draws a Circle on OLED.
 * Draws a Circle on OLED by using the specified parameters.
 * <a href="https://en.wikipedia.org/wiki/Midpoint_circle_algorithm">
 * Mid Point Circle Algorithm Weblink</a>
 * Param1:  x_center: x coordinate of the circle center. Valid values: 0..127
 * Param2:  y_center: y coordinate of the circle center. Valid values: 0..63
 * Param3:  radius: radius of the circle.
 * Param4:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_Circle(int16_t x0, int16_t y0, int16_t r, uint8_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    SSD1306_SetPixel(x0, y0 + r, color);
    SSD1306_SetPixel(x0, y0 - r, color);
    SSD1306_SetPixel(x0 + r, y0, color);
    SSD1306_SetPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        SSD1306_SetPixel(x0 + x, y0 + y, color);
        SSD1306_SetPixel(x0 - x, y0 + y, color);
        SSD1306_SetPixel(x0 + x, y0 - y, color);
        SSD1306_SetPixel(x0 - x, y0 - y, color);
        SSD1306_SetPixel(x0 + y, y0 + x, color);
        SSD1306_SetPixel(x0 - y, y0 + x, color);
        SSD1306_SetPixel(x0 + y, y0 - x, color);
        SSD1306_SetPixel(x0 - y, y0 - x, color);
    }
}

void SSD1306_FillCircle(int16_t x0, int16_t y0, int16_t r,
        uint8_t color) {
    SSD1306_V_Line(x0, y0 - r, 2 * r + 1, color);
    SSD1306_FillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and round rects
void SSD1306_FillCircleHelper(int16_t x0, int16_t y0, int16_t r,
        uint8_t cornername, int16_t delta, uint8_t color) {

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x1) {
            SSD1306_V_Line(x0 + x, y0 - y, 2 * y + 1 + delta, color);
            SSD1306_V_Line(x0 + y, y0 - x, 2 * x + 1 + delta, color);
        }
        if (cornername & 0x2) {
            SSD1306_V_Line(x0 - x, y0 - y, 2 * y + 1 + delta, color);
            SSD1306_V_Line(x0 - y, y0 - x, 2 * x + 1 + delta, color);
        }
    }
}

/*
 * Desc: Write character on OLED.
 * Param1:  x: character starting position on x-axis. Valid values: 0..127
 * Param2:  y: character starting position on y-axis. Valid values: 0..63
 * Param3:  value: Character to be written.
 */
void SSD1306_Write(int16_t x, int16_t y, char value) {
    uint16_t font_idx = 0;
    uint16_t rowcount = 0;
    uint16_t count = 0;
    uint8_t index;
    uint16_t temp = 0;

    int16_t cbyte, cx, cy;
    int16_t cbit;

    if (sfont.y_size % 8 == 0) {
        font_idx = ((value - sfont.offset)*(sfont.x_size * (sfont.y_size / 8))) + 4;
        for (rowcount = 0; rowcount < (sfont.y_size / 8); rowcount++) {
            for (count = 0; count < sfont.x_size; count++) {
                temp = *(sfont.font + font_idx + count + (rowcount * sfont.x_size));
                for (index = 0; index < 8; index++) {
                    if (temp & (1 << index)) {
                        if (sfont.inverted == false)
                            SSD1306_SetPixel(x + count, y + (rowcount * 8) + index, true);
                        else
                            SSD1306_SetPixel(x + count, y + (rowcount * 8) + index, false);
                    } else {
                        if (sfont.inverted == false)
                            SSD1306_SetPixel(x + count, y + (rowcount * 8) + index, false);
                        else
                            SSD1306_SetPixel(x + count, y + (rowcount * 8) + index, true);
                    }
                }
            }
        }
    } else {
        font_idx = ((value - sfont.offset)*((sfont.x_size * sfont.y_size) / 8)) + 4;
        cbyte = *(sfont.font + font_idx);
        cbit = 7;
        for (cx = 0; cx < sfont.x_size; cx++) {
            for (cy = 0; cy < sfont.y_size; cy++) {
                if ((cbyte & (1 << cbit)) != 0) {
                    if (sfont.inverted == false)
                        SSD1306_SetPixel(x + cx, y + cy, true);
                    else
                        SSD1306_SetPixel(x + cx, y + cy, false);
                } else {
                    if (sfont.inverted == false)
                        SSD1306_SetPixel(x + cx, y + cy, false);
                    else
                        SSD1306_SetPixel(x + cx, y + cy, true);
                }
                cbit--;
                if (cbit < 0) {
                    cbit = 7;
                    font_idx++;
                    cbyte = *(sfont.font + font_idx);
                }
            }
        }
    }
}

/*
 * Desc: Write Text on OLED.
 * Param1:  x: character starting position on x-axis.
 * Param2:  y: character starting position on y-axis.
 * Param3:  *text: Pointer to the array of the text to be written.
 */
void SSD1306_Write_Text(int16_t x, int16_t y, char *text) {
    uint8_t count;
    uint8_t length;
    length = strlen((const char*) text);
    if (x == SSD1306_RIGHT)
        x = SSD1306_WIDTH - (length * sfont.x_size);
    if (x == SSD1306_CENTER)
        x = (SSD1306_WIDTH - (length * sfont.x_size)) / 2;
    for (count = 0; count < length; count++)
        SSD1306_Write(x + (count * (sfont.x_size)), y, *text++);
}

/*
 * Desc: Send I2C Command to OLED Controller
 * Param1:  command: command to sent to Controller
 */
static void ssd1306_command(uint8_t command) {
    uint8_t data_I2C[2];
    data_I2C[0] = SSD1306_COMMAND;
    data_I2C[1] = command;
    i2c_writeNBytes(SSD1306_ADDR, data_I2C, 2);
}

/*
 * Desc: Send I2C Data to OLED Controller
 * Param1:  value: Send Data to OLED Controller
 */
static void ssd1306_data(uint8_t value) {
    uint8_t data_I2C[2];
    data_I2C[0] = SSD1306_DATA_CONTINUE;
    data_I2C[1] = value;
    i2c_writeNBytes(SSD1306_ADDR, data_I2C, 2);
}

void SSD1306_StartScrollRight(uint8_t start, uint8_t stop) {

    ssd1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
    ssd1306_command(0X00);
    ssd1306_command(start); // start page
    ssd1306_command(0X00);
    ssd1306_command(stop); // end page
    ssd1306_command(0X00);
    ssd1306_command(0XFF);
    ssd1306_command(SSD1306_ACTIVATE_SCROLL);

}

void SSD1306_StartScrollLeft(uint8_t start, uint8_t stop) {

    ssd1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
    ssd1306_command(0X00);
    ssd1306_command(start);
    ssd1306_command(0X00);
    ssd1306_command(stop);
    ssd1306_command(0X00);
    ssd1306_command(0XFF);
    ssd1306_command(SSD1306_ACTIVATE_SCROLL);

}

void SSD1306_StartScrollDiagRight(uint8_t start, uint8_t stop) {

    ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
    ssd1306_command(0X00);
    ssd1306_command(SSD1306_HEIGHT);
    ssd1306_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
    ssd1306_command(0X00);
    ssd1306_command(start);
    ssd1306_command(0X00);
    ssd1306_command(stop);
    ssd1306_command(0X01);
    ssd1306_command(SSD1306_ACTIVATE_SCROLL);

}

void SSD1306_StartScrollDiagLeft(uint8_t start, uint8_t stop) {

    ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
    ssd1306_command(0X00);
    ssd1306_command(SSD1306_HEIGHT);
    ssd1306_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
    ssd1306_command(0X00);
    ssd1306_command(start);
    ssd1306_command(0X00);
    ssd1306_command(stop);
    ssd1306_command(0X01);
    ssd1306_command(SSD1306_ACTIVATE_SCROLL);

}

void SSD1306_StopScroll(void) {
    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
}


// Desc: rotates buffer 
// Param1: Mode 0-3. 0 normal 
void SSD1306_setRotation(uint8_t x) {
    _rotation = (x & 3);
    switch (_rotation) {
        case 0:
        case 2:
            _width = SSD1306_WIDTH;
            _height = SSD1306_HEIGHT;
            break;
        case 1:
        case 3:
            _width = SSD1306_HEIGHT;
            _height = SSD1306_WIDTH;
            break;
    }
}

// Desc: Fill the screen NOT the buffer with a datapattern
// Param1: datapattern can be set to zero to clear screen (not buffer) range 0x00 to 0ff
// NOTE: writes to screen not buffer 
void SSD1306_FillScreen(uint8_t dataPattern) {
    for (uint8_t row = 0; row < SSD1306_PAGENUM; row++) 
    {
        ssd1306_command(0xB0 | row);
        ssd1306_command(SSD1306_SET_LOWER_COLUMN);
        ssd1306_command(SSD1306_SET_HIGHER_COLUMN);
        for (uint8_t col = 0; col < SSD1306_WIDTH; col++) 
        {
            ssd1306_data(dataPattern);
        }
    }
}

// Desc: Fill the chosen page(1-8)  with a datapattern
// Param1: datapattern can be set to 0 to FF (not buffer)
// NOTE: writes to screen not buffer 
void SSD1306_FillPage(uint8_t page_num, uint8_t dataPattern) {
    uint8_t Result = 0xB0 | page_num;
    ssd1306_command(Result);
    ssd1306_command(SSD1306_SET_LOWER_COLUMN);
    ssd1306_command(SSD1306_SET_HIGHER_COLUMN);
    for (uint8_t i = 0; i < SSD1306_WIDTH; i++) {
        ssd1306_data(dataPattern);
    }
}

// ************ EOF ******* 