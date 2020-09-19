/*
* Project Name: SSD1306_GRAPH
* File: OLED.c
* Version: 1.0
* Description: OLED 128X64 SSD1306  I2C library c file
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
#include "TextFonts.h"
#include "mcc_generated_files/mcc.h"


// *********** Private Variables ***********
static Selected_Font_s sfont;

// ************** Memory Buffer Display ****
static uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8] =
{
// block 1 
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,

//block 2
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        
#if (SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH > 96*16)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,

0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,

0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
#if (SSD1306_LCDHEIGHT == 64)
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,

0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,

0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,

0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF
#endif
#endif
};

// *********** Private Function Prototypes ****************
static void ssd1306_command( uint8_t command );
static void ssd1306_data( uint8_t value );
static uint8_t width( void );
static uint8_t height( void );
//static void swap_num( uint16_t *a, uint16_t *b ); //not used in this version

// ************ Function Space ****************

/*
 * Function Desc: SSD1306_Init
 * Initialize OLED
 */
void SSD1306_Init( void )
{
  __delay_ms(100);
  ssd1306_command( SSD1306_DISPLAY_OFF);
  ssd1306_command( SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
  ssd1306_command( 0x80);
  ssd1306_command( SSD1306_SET_MULTIPLEX_RATIO );
  ssd1306_command( SSD1306_LCDHEIGHT - 1 );
  ssd1306_command( SSD1306_SET_DISPLAY_OFFSET );
  ssd1306_command(0x00);
  ssd1306_command( SSD1306_SET_START_LINE|0x00);  
  ssd1306_command( SSD1306_CHARGE_PUMP );
  ssd1306_command(0x14);
  ssd1306_command( SSD1306_MEMORY_ADDR_MODE );
  ssd1306_command(0x00);  //Horizontal Addressing Mode is Used
  ssd1306_command( SSD1306_SET_SEGMENT_REMAP| 0x01);
  ssd1306_command( SSD1306_COM_SCAN_DIR_DEC );
  
#if defined SSD1306_128_32
  ssd1306_command( SSD1306_SET_COM_PINS );
  ssd1306_command( 0x02 );
  ssd1306_command( SSD1306_SET_CONTRAST_CONTROL );
  ssd1306_command(0x8F);

#elif defined SSD1306_128_64
  ssd1306_command( SSD1306_SET_COM_PINS );
  ssd1306_command( 0x12 );
  ssd1306_command( SSD1306_SET_CONTRAST_CONTROL );
  ssd1306_command(0xCF);
#endif
  
  ssd1306_command( SSD1306_SET_PRECHARGE_PERIOD );
  ssd1306_command( 0xF1 );
  ssd1306_command( SSD1306_SET_VCOM_DESELECT );
  ssd1306_command( 0x40 );
  ssd1306_command( SSD1306_DISPLAY_ALL_ON_RESUME );
  ssd1306_command( SSD1306_NORMAL_DISPLAY );
  ssd1306_command( SSD1306_DEACTIVATE_SCROLL );
  ssd1306_command( SSD1306_DISPLAY_ON );

  SSD1306_SetFont(UNO);
  __delay_ms(100);
  SSD1306_UpdateDisplay();
}

/*
 * Function Desc: SSD1306_Width
 * Get the OLED Width
 * Return1:  Oled Width
 */
uint8_t SSD1306_Width( void )
{
  return width();
}

/*
 * Function Desc: SSD1306_Height
 * Get the OLED Height
 * Return1:  Oled Height
 */
uint8_t SSD1306_Height( void )
{
  return height();
}

/*
 * Function Desc: SSD1306_SetFont
 * Parameter1:  font: Select this font pass PICO or UNO or MEGA
 */
void SSD1306_SetFont( const uint8_t *font)
{
  sfont.font = font;
  sfont.x_size = *(font+0);
  sfont.y_size = *(font+1);
  sfont.offset  = *(font+2);
  sfont.numchars  = *(font+3);
  sfont.inverted = false;
}

/*
 * Function Desc: SSD1306_InvertFont
 * Invert the font
 * Parameter1: true or false
 */
void SSD1306_InvertFont( bool invert_status )
{
  if( invert_status )
  {
    sfont.inverted = true;
  }
  else
  {
    sfont.inverted = false;
  }
}

/*
 * Function Desc: SSD1306_UpdateDisplay
 * Update the OLED Buffer on the actual display
 */
void SSD1306_UpdateDisplay( void )
{
  uint16_t i = 0;
  uint8_t x = 0;
  ssd1306_command( SSD1306_SET_COLUMN_ADDR );
  ssd1306_command(0);   // Column start address (0 = reset)
  ssd1306_command( SSD1306_LCDWIDTH-1 ); // Column end address (127 = reset)

  ssd1306_command( SSD1306_SET_PAGE_ADDR );
  ssd1306_command(0); // Page start address (0 = reset)
  #if SSD1306_LCDHEIGHT == 64
    ssd1306_command(7); // Page end address
  #endif
  #if SSD1306_LCDHEIGHT == 32
    ssd1306_command(3); // Page end address
  #endif
  #if SSD1306_LCDHEIGHT == 16
    ssd1306_command(1); // Page end address
  #endif

  for (i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++)
  {
    // Send data for Transmission
    for ( x=0; x<16; x++)
    {
      ssd1306_data(buffer[i]);
      i++;
    }
    i--;
  }
}

/*
 * Function Desc: SSD1306_Contrast.
 * Set the OLED display contrast.
 * Parameter1:  contrast: contrast value
 */
void SSD1306_Contrast( uint8_t contrast )
{
  ssd1306_command( SSD1306_SET_CONTRAST_CONTROL );
  ssd1306_command(contrast);
}

/*
 * Function Desc: SSD1306_FillBUffer
 * Fill the OLED Buffer.
 *  Parameter1:  contrast:  Fill value,
 *  pass 0x00 to clear , 0xff to fill(normal mode)
 */
void SSD1306_FillBuffer( uint8_t pattern )
{
  memset(buffer, pattern, (SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8));
}



/*
 * Function Desc: SSD1306_InvertDisplay.
 * Invert the Display based on the parameters
 * Parameter1:  value: If True invert the display
 */
void SSD1306_InvertDisplay( bool value )
{
  if( value )
  {
    ssd1306_command( SSD1306_INVERT_DISPLAY );
  }
  else
  {
    ssd1306_command( SSD1306_NORMAL_DISPLAY );
  }
}

/**
 * Function Desc: SSD1306_SetPixel.
 * Draws a pixel on OLED by using the specified parameters.
 * Parameter1:  x: x coordinate with valid values: 0..127
 * Parameter2:  y: y coordinate with valid values: 0..63
 * Parameter3:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_SetPixel( int16_t x, int16_t y, uint8_t color)
{
  if ( (x < 0) || (x >= width()) || (y < 0) || (y >= height()))
    return;

  switch (color)
  {
    case WHITE:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] |=  (1 << (y&7)); break;
    case BLACK:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] &= ~(1 << (y&7)); break;
    case INVERSE: buffer[x+ (y/8)*SSD1306_LCDWIDTH] ^=  (1 << (y&7)); break;
  }
}
/**
 * Function Desc: Draws a line on OLED.
 * Draws a line on OLED by using the specified parameters.
 * <a href="https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm">
 * Algorithm Used</a>
 * Parameter1:  x_start: x coordinate of start point. Valid values: 0..127
 * Parameter2:  y_start: x coordinate of start point. Valid values: 0..63
 * Parameter3:  x_end: x coordinate of end point. Valid values: 0..127
 * Parameter4:  y_end: y coordinate of end point. Valid values: 0..63
 * Parameter5:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_Line( int16_t x_start, int16_t y_start, int16_t x_end, int16_t y_end, uint8_t color)
{
  int16_t x, y, addx, addy, dx, dy;
  int32_t P;
  int16_t i;
  dx = abs((int16_t)(x_end - x_start));
  dy = abs((int16_t)(y_end - y_start));
  x = x_start;
  y = y_start;

  if(x_start > x_end)
    addx = -1;
  else
    addx = 1;

  if(y_start > y_end)
    addy = -1;
  else
    addy = 1;

  if(dx >= dy)
  {
    P = 2*dy - dx;

    for(i=0; i<=dx; ++i)
    {
      SSD1306_SetPixel (x,y,color);
      if(P < 0)
      {
        P += 2*dy;
        x += addx;
      }
      else
      {
        P += 2*dy - 2*dx;
        x += addx;
        y += addy;
      }
    }
  }
  else
  {
    P = 2*dx - dy;
    for(i=0; i<=dy; ++i)
    {
      SSD1306_SetPixel (x,y,color);

      if(P < 0)
      {
        P += 2*dx;
        y += addy;
      }
      else
      {
        P += 2*dx - 2*dy;
        x += addx;
        y += addy;
      }
    }
  }
}


/**
 * Function Desc: OLED Vertical Line.
 * Draw vertical line between of length specified by y_start and y_end, and at
 * position specified by x_pos
 * Parameter1:  y_start: y position to start vertical line. Valid values: 0..63
 * Parameter2:  y_end: y position to end vertical line. Valid values: 0..63
 * Parameter3:  x_pos: x position. Valid values: 0..127
 * Parameter4:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_V_Line ( int16_t y_start, int16_t y_end, int16_t x_pos, uint8_t color)
{
  int16_t temp;
  if( y_start > y_end )
  {
    temp = y_start;
    y_start = y_end;
    y_end = temp;
  }

  while( y_start <= y_end )
  {
    SSD1306_SetPixel(x_pos, y_start, color);
    y_start++;
  }
}

/*
 * Function Desc: OLED Horizontal Line.
 * Draw horizontal line between of length specified by x_start and x_end, and at
 * position specified by y_pos
 * Parameter1:  x_start: y position to start horizontal line. Valid values: 0..127
 * Parameter2:  x_end: y position to end horizontal line. Valid values: 0..127
 * Parameter3:  y_pos: x position. Valid values: 0..63
 * Parameter4:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_H_Line( int16_t x_start, int16_t x_end, int16_t y_pos, uint8_t color)
{
  int16_t temp;
  if( x_start > x_end )
  {
    temp = x_start;
    x_start = x_end;
    x_end = temp;
  }

  while( x_start <= x_end )
  {
    SSD1306_SetPixel(x_start, y_pos, color);
    x_start++;
  }
}

/*
 * Function Desc: Draws a rectangle on OLED.
 * Draws a rectangle on OLED by using the specified parameters.
 * Parameter1:  x1: x coordinate of the upper left rectangle corner.
 * Valid values: 0..127
 * Parameter2:  y1: y coordinate of the upper left rectangle corner.
 * Valid values: 0..63
 * Parameter3:  x2: x coordinate of the lower right rectangle corner.
 * Valid values: 0..127
 * Parameter4:  y2: y coordinate of the lower right rectangle corner.
 * Valid values: 0..63
 * Parameter5:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_Rectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color)
{
  SSD1306_H_Line(x1, x2, y1, color);
  SSD1306_H_Line(x1, x2, y2, color);
  SSD1306_V_Line(y1, y2, x1, color);
  SSD1306_V_Line(y1, y2, x2, color);
}

/*
 * Function Desc: SSD1306_FillRectangle
 * Draws a rectangle on OLED by using the specified parameters with filling.
 * Parameter1:  x1: x coordinate of the upper left rectangle corner. Valid values: 0..127
 * Parameter2:  y1: y coordinate of the upper left rectangle corner. Valid values: 0..63
 * Parameter3:  x2: x coordinate of the lower right rectangle corner. Valid values: 0..127
 * Parameter4:  y2: y coordinate of the lower right rectangle corner. Valid values: 0..63
 * Parameter5:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_FillRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color)
{
  int16_t i;
  for( i=x1; i<=x2; i++ )
  {
    SSD1306_V_Line(y1, y2, i, color );
  }
}

/*
 * Function Desc: SSD1306_Triangle
 * Draw a Triangle based on the coordinates
 * Parameter1:  x0: x0 coordinate
 * Parameter2:  y0: y0 coordinate
 * Parameter3:  x1: x1 coordinate
 * Parameter4:  y1: y1 coordinate
 * Parameter5:  x2: x2 coordinate
 * Parameter6:  y2: y2 coordinate
 * Parameter7:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_Triangle( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color)
{
  SSD1306_Line(x0, y0, x1, y1, color);
  SSD1306_Line(x1, y1, x2, y2, color);
  SSD1306_Line(x2, y2, x0, y0, color);
}

/*
 * Function Desc: OLED Image.
 * Displays bitmap image on OLED.
 * Parameter1:  *image: image to be displayed. Bitmap array must be located in code
 * memory. Use https://javl.github.io/image2cpp/
 */
void SSD1306_BITMAP( const uint8_t *image)
{
  uint16_t i;
  for( i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++)
  {
    buffer[i] = *(image+i);
  }
}

/*
 * Function Desc: Draws a Circle on OLED.
 * Draws a Circle on OLED by using the specified parameters.
 * <a href="https://en.wikipedia.org/wiki/Midpoint_circle_algorithm">
 * Mid Point Circle Algorithm Weblink</a>
 * Parameter1:  x_center: x coordinate of the circle center. Valid values: 0..127
 * Parameter2:  y_center: y coordinate of the circle center. Valid values: 0..63
 * Parameter3:  radius: radius of the circle.
 * Parameter4:  color: color parameter. Valid values: 0 and 1
 */
void SSD1306_Circle( int16_t x0, int16_t y0, int16_t r, uint8_t color )
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  SSD1306_SetPixel(x0  , y0+r, color);
  SSD1306_SetPixel(x0  , y0-r, color);
  SSD1306_SetPixel(x0+r, y0  , color);
  SSD1306_SetPixel(x0-r, y0  , color);

  while (x<y)
  {
    if (f >= 0)
    {
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

/*
 * Function Desc: Write character on OLED.
 * Prints character on the OLED.
 * Parameter1:  value: Character to be written.
 * Parameter2:  x: character starting position on x-axis. Valid values: 0..127
 * Parameter3:  y: character starting position on x-axis. Valid values: 0..63
 */
void SSD1306_Write( int16_t x, int16_t y, char value )
{
  uint16_t font_idx = 0;
  uint16_t rowcount = 0;
  uint16_t count = 0;
  uint8_t index;
  uint16_t temp = 0;

  int16_t cbyte, cx, cy;
  int16_t cbit;

  if( sfont.y_size%8 == 0)
  {
    font_idx = ((value-sfont.offset)*(sfont.x_size*(sfont.y_size/8))) + 4;
    for ( rowcount=0; rowcount<(sfont.y_size/8); rowcount++ )
    {
      for( count=0; count<sfont.x_size; count++ )
      {
        temp = *(sfont.font + font_idx + count + (rowcount*sfont.x_size));
        for ( index=0; index<8; index++ )
        {
          if ( temp & (1<<index) )
          {
            if (sfont.inverted == false )
              SSD1306_SetPixel(x+count, y+(rowcount*8)+index, true);
            else
              SSD1306_SetPixel(x+count, y+(rowcount*8)+index, false);
          }
          else
          {
            if (sfont.inverted == false )
              SSD1306_SetPixel(x+count, y+(rowcount*8)+index, false);
            else
              SSD1306_SetPixel(x+count, y+(rowcount*8)+index, true);
          }
        }
      }
    }
  }
  else
  {
    font_idx = ((value-sfont.offset)*((sfont.x_size*sfont.y_size)/8)) + 4;
    cbyte = *(sfont.font + font_idx);
    cbit = 7;
    for ( cx=0; cx<sfont.x_size; cx++ )
    {
      for ( cy=0; cy<sfont.y_size; cy++ )
      {
        if ( (cbyte & (1<<cbit)) != 0)
        {
          if ( sfont.inverted == false )
            SSD1306_SetPixel(x+cx, y+cy, true);
          else
            SSD1306_SetPixel(x+cx, y+cy, false);
        }
        else
        {
          if ( sfont.inverted == false )
            SSD1306_SetPixel(x+cx, y+cy, false);
          else
            SSD1306_SetPixel(x+cx, y+cy, true);
        }
        cbit--;
        if (cbit < 0)
        {
          cbit=7;
          font_idx++;
          cbyte= *(sfont.font+font_idx);
        }
      }
    }
  }
}

/**
 * Function Desc: Write Text on OLED.
 * Prints text on the OLED.
 * Parameter1:  *text: Pointer to the array of the text to be written.
 * Parameter1:  x: character starting position on x-axis. Valid values: 0..127
 * Parameter1:  y: character starting position on x-axis. Valid values: 0..63
 */
void SSD1306_Write_Text( int16_t x, int16_t y, char *text)
{
  uint8_t count;
  uint8_t length;
  length = strlen( (const char*)text);
  if (x == RIGHT)
    x = 128-(length*sfont.x_size);
  if (x == CENTER)
    x = (128-(length*sfont.x_size))/2;
  for ( count=0; count<length; count++ )
    SSD1306_Write(x + (count*(sfont.x_size)), y, *text++ );
}

/*
 * Function Desc: Send I2C Command to OLED Controller
 * Parameter1:  command: command to sent to Controller
 */
static void ssd1306_command( uint8_t command )
{
  uint8_t data_I2C[2];
  data_I2C[0] = SSD1306_COMMAND ; 
  data_I2C[1] = command; 
  i2c_writeNBytes(SSD1306_ADDR, data_I2C, 2);
}

/*
 * Function Desc: Send I2C Data to OLED Controller
 * Parameter1:  value: Send Data to OLED Controller
 */
static void ssd1306_data( uint8_t value )
{
  uint8_t data_I2C[2];
  data_I2C[0] =SSD1306_DATA_CONTINUE; 
  data_I2C[1] = value; 
  i2c_writeNBytes(SSD1306_ADDR, data_I2C, 2);
}

/*
 * Function Desc: OLED Width
 * Return1:  Width
 */
static uint8_t width( void ){return SSD1306_LCDWIDTH;}

/*
 * Function Desc: OLED Height
 * Return1:  Height
 */
static uint8_t height( void ){return SSD1306_LCDHEIGHT;}

/*
* Not used in version  1.0
static void swap_num( uint16_t *a, uint16_t *b )
{
  uint16_t temp = *a;
  *a = *b;
  *b = temp;
}
*/