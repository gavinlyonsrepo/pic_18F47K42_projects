/*
* Project Name: Nokia  5110 Graphic library for PIC  micro-controller
* File: NOKIA.c
* Description: Source file for NOKIA 5110 library to communicate with LCDs, software SPI.
* PCD8544 controller.
* Author: Gavin Lyons.
* Compiler: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created: July 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#include "NOKIA.h"

/* 
   FunctionName : LCD_begin
   Function Desc:  This sends the  commands to the PCD8544 to  init LCD, Note Software SPI
*/
void LCD_begin(void) {
    __delay_ms(100);
    LCD_RST_SetHigh();
    LCD_RST_TRIS = 0;
    __delay_ms(500);
    LCD_RST_SetHigh();
    LCD_CE_SetHigh();
    LCD_CE_TRIS  = 0;
    LCD_DC_TRIS = 0; 
    LCD_DIN_TRIS  = 0;
    LCD_CLK_TRIS = 0;

  // get into the EXTENDED mode
  writeCommand(LCD_FUNCTIONSET | LCD_EXTENDEDINSTRUCTION );
  writeCommand(LCD_SETBIAS | 0x03);   // set bias voltage
  writeCommand( LCD_SETVOP | 0x32);   // set contrast
  writeCommand(LCD_FUNCTIONSET);   // normal mode
  // set display to normal mode
  writeCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYNORMAL);

  rotation = 0;
  _width  = LCDWIDTH;
  _height = LCDHEIGHT;
}

/* 
   FunctionName : PCD8544_SPI_Write
   Function Desc:  Writes a byte to the PCD8544
   Parameter: data byte will be sent as command or data depending on status of DC line
*/
void PCD8544_SPI_Write(uint8_t d) {
  uint8_t bit_n;
  for (bit_n = 0x80; bit_n; bit_n >>= 1) {
    LCD_CLK_SetLow();
    if (d & bit_n) LCD_DIN_PORT = 1;
    else           LCD_DIN_PORT = 0;
     LCD_CLK_SetHigh();
  }
}

/* 
   FunctionName : writeCommand 
   Function Desc:  Writes a command byte to the PCD8544
   Parameter1: command There are two  banks in the LCD, data and commands. This
    function sets the DC low then sends
    the command byte if it(DC) was high it would be a data byte
*/
void writeCommand(uint8_t command) {
  LCD_DC_SetLow();
  LCD_CE_SetLow();
  PCD8544_SPI_Write(command);
   LCD_CE_SetHigh();
}

/* 
 FunctionName: display_setContrast
 FunctionDesc: Function to set contrast passed a byte 
 Parameter: con, Set LCD VOP Contrast, range = ((0x00-0x7F) |0x80) 0xB5 = (0x35|0x80) try 32 - 3F possible inputs. 
 */
void display_setContrast(uint8_t con) {
  if (con > 0x7f)
    con = 0x7f;

  writeCommand(LCD_FUNCTIONSET | LCD_EXTENDEDINSTRUCTION );
  writeCommand( LCD_SETVOP | con); 
  writeCommand(LCD_FUNCTIONSET);
 }

/* 
 FunctionName: display
 FunctionDesc: Writes the buffer to the LCD
 */
void display(void) {
  uint16_t i;
  writeCommand(LCD_SETYADDR);  // set y = 0
  writeCommand(LCD_SETXADDR);  // set x = 0

  LCD_DC_SetHigh(); //Data send
  LCD_CE_SetLow();

  for(i = 0; i < 504; i++)  // 504 = LCDWIDTH*LCDHEIGHT / 8
    PCD8544_SPI_Write( pcd8544_buffer[i] );

  LCD_CE_SetHigh();
}


/* 
 FunctionName: drawPixel
 FunctionDesc: The most basic function, set a single pixel
 */
void drawPixel(uint8_t x, uint8_t y, bool color) {

  if ( (x >= _width) || (y >= _height) )
    return;

  switch(rotation) {
    case 1:
      pcd8544_swap(x, y);
      y =  LCDHEIGHT - 1 - y;
      break;
    case 2:
      x = LCDWIDTH - 1 - x;
      y = LCDHEIGHT - 1 - y;
      break;
    case 3:
      pcd8544_swap(x, y);
      x = LCDWIDTH - 1 - x;
  }

  if ( (x >= LCDWIDTH) || (y >= LCDHEIGHT) )
    return;

  if (color)
    pcd8544_buffer[x + (uint16_t)(y / 8) * LCDWIDTH] |=  (1 << (y & 7));

  else
    pcd8544_buffer[x + (uint16_t)(y / 8) * LCDWIDTH] &=  ~(1 << (y & 7));
}

/* FunctionName: drawLine */
void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, int16_t y1, bool color) {

  bool steep = abs((int16_t)(y1 - y0)) > abs((int16_t)(x1 - x0));
  int8_t ystep;
  uint8_t dx, dy;
  int16_t err;

  if (steep) {
    pcd8544_swap(x0, y0);
    pcd8544_swap(x1, y1);
  }
  if (x0 > x1) {
    pcd8544_swap(x0, x1);
    pcd8544_swap(y0, y1);
  }
  dx = x1 - x0;
  dy = abs(y1 - y0);

  err = dx / 2;
  if (y0 < y1)
    ystep = 1;
  else
    ystep = -1;

  for (; x0 <= x1; x0++) {
    if (steep)
      drawPixel(y0, x0, color);
    else
      drawPixel(x0, y0, color);
    err -= dy;
    if (err < 0) {
      y0  += ystep;
      err += dx;
    }
  }
}

/* FunctionName: drawHLine */
void drawHLine(uint8_t x, uint8_t y, uint8_t w, bool color) {
   drawLine(x, y, x + w - 1, y, color);
}

/* FunctionName: drawVLine */
void drawVLine(uint8_t x, uint8_t y, uint8_t h, bool color) {
  drawLine(x, y, x, y + h - 1, color);
}

/* FunctionName: fillRect */
void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color) {
  uint8_t i;
  for (i = x; i < x + w; i++)
    drawVLine(i, y, h, color);
}

/* 
 FunctionName: display_clear
 FunctionDesc: Writes the buffer (full of zeros) to the LCD
 */
void display_clear(void) {
  uint16_t i;
  for (i = 0; i < 504; i++)  // 504 = LCDWIDTH*LCDHEIGHT / 8
    pcd8544_buffer[i] = 0;
}

/* 
 FunctionName: display_clear
 FunctionDesc: Writes the buffer (full of ones(0xFF)) to the LCD
 */
void fillScreen() {
  uint16_t i;
  for (i = 0; i < 504; i++)  // 504 = LCDWIDTH*LCDHEIGHT / 8
    pcd8544_buffer[i] = 0xFF;
}

/* 
 FunctionName: setRotation
 FunctionDesc:  set rotation setting for display,
 Parameter1:  0 thru 3 corresponding to 4 cardinal rotations:
 */
void setRotation(uint8_t m) {
  rotation = (m & 3);

  switch(rotation) {
    case 0:
    case 2:
      _width  = LCDWIDTH;
      _height = LCDHEIGHT;
    break;
    case 1:
    case 3:
      _width  = LCDHEIGHT;
      _height = LCDWIDTH;
      break;
  }
}

/*  FunctionName: InvertDisplay */
void invertDisplay(bool inv) {
  if(inv == 1)
    writeCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYINVERTED);
  else
    writeCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYNORMAL);
}

/* ------------------------ EOF --------------------------- */
