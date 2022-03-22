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

#include "Nokia5110_PCD8544.h"

/* 
   Desc:  This sends the  commands to the PCD8544 to  init LCD, Note Software SPI
*/
void LCDBegin(void) {
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
  LCDwriteCommand(LCD_FUNCTIONSET | LCD_EXTENDEDINSTRUCTION );
  LCDwriteCommand(LCD_SETBIAS | 0x03);   // set bias voltage
  LCDwriteCommand( LCD_SETVOP | 0x32);   // set contrast
  LCDwriteCommand(LCD_FUNCTIONSET);   // normal mode
  // set display to normal mode
  LCDwriteCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYNORMAL);

  _rotation_LCD = 0;
  _width_LCD  = LCDWIDTH;
  _height_LCD = LCDHEIGHT;
}

/* 
   Desc:  Writes a byte to the PCD8544
   Param: data byte will be sent as command or data depending on status of DC line
*/
void LCDWriteData(uint8_t spiDataByte) {
    uint8_t i = 0 ;
    
    for (i = 0; i < 8; i++) {
        LCD_DIN_SetLow();
        if (spiDataByte & 0x80)LCD_DIN_SetHigh(); // b1000000 Mask with 0 & all zeros out.
        LCD_CLK_SetHigh();
        spiDataByte <<= 1;
        __delay_us(LCD_HIGH_FREQ_uSDELAY);
        LCD_CLK_SetLow();
    }
}

/* 
   Desc:  Writes a command byte to the PCD8544
   Param1: command There are two  banks in the LCD, data and commands. This
    function sets the DC low then sends
    the command byte if it(DC) was high it would be a data byte
*/
void LCDwriteCommand(uint8_t command) {
  LCD_DC_SetLow();
  LCD_CE_SetLow();
  LCDWriteData(command);
   LCD_CE_SetHigh();
}

/* 
 Desc: Function to set contrast passed a byte 
 Param: con, Set LCD VOP Contrast, range = ((0x00-0x7F) |0x80) 0xB5 = (0x35|0x80) try 32 - 3F possible inputs. 
 */
void LCDdisplay_setContrast(uint8_t con) {
  if (con > 0x7f)
    con = 0x7f;

  LCDwriteCommand(LCD_FUNCTIONSET | LCD_EXTENDEDINSTRUCTION );
  LCDwriteCommand( LCD_SETVOP | con); 
  LCDwriteCommand(LCD_FUNCTIONSET);
 }

/* 
 Desc: Writes the buffer to the LCD
 */
void LCDdisplay(void) {
  uint16_t i;
  LCDwriteCommand(LCD_SETYADDR);  // set y = 0
  LCDwriteCommand(LCD_SETXADDR);  // set x = 0

  LCD_DC_SetHigh(); //Data send
  LCD_CE_SetLow();

  for(i = 0; i < 504; i++)  // 504 = LCDWIDTH*LCDHEIGHT / 8
    LCDWriteData( pcd8544_buffer[i] );

  LCD_CE_SetHigh();
}


/* 
 Desc: The most basic function, set a single pixel
 */
void LCDdrawPixel(uint8_t x, uint8_t y, bool color) {

  if ( (x >= _width_LCD) || (y >= _height_LCD) )
    return;

  switch(_rotation_LCD) {
    case 1:
      _swap_int8_t_LCD(x, y);
      y =  LCDHEIGHT - 1 - y;
      break;
    case 2:
      x = LCDWIDTH - 1 - x;
      y = LCDHEIGHT - 1 - y;
      break;
    case 3:
      _swap_int8_t_LCD(x, y);
      x = LCDWIDTH - 1 - x;
  }

  if ( (x >= LCDWIDTH) || (y >= LCDHEIGHT) )
    return;

  if (color)
    pcd8544_buffer[x + (uint16_t)(y / 8) * LCDWIDTH] |=  (1 << (y & 7));

  else
    pcd8544_buffer[x + (uint16_t)(y / 8) * LCDWIDTH] &=  ~(1 << (y & 7));
}



/* 
 Desc: Writes the buffer (full of zeros) to the LCD
 */
void LCDdisplayClear(void) {
  uint16_t i;
  for (i = 0; i < 504; i++)  // 504 = LCDWIDTH*LCDHEIGHT / 8
    pcd8544_buffer[i] = 0;
}

/* 
 Desc: Writes the buffer (full of ones(0xFF)) to the LCD
 */
void LCDfillScreen() {
  uint16_t i;
  for (i = 0; i < 504; i++)  // 504 = LCDWIDTH*LCDHEIGHT / 8
    pcd8544_buffer[i] = 0xFF;
}

/* 
 Desc:  set rotation setting for display,
 Param1:  0 thru 3 corresponding to 4 cardinal rotations:
 */
void LCDsetRotation(uint8_t m) {
  _rotation_LCD = (m & 3);

  switch(_rotation_LCD) {
    case 0:
    case 2:
      _width_LCD  = LCDWIDTH;
      _height_LCD = LCDHEIGHT;
    break;
    case 1:
    case 3:
      _width_LCD  = LCDHEIGHT;
      _height_LCD = LCDWIDTH;
      break;
  }
}

void LCDinvertDisplay(bool inv) {
  if(inv == 1)
    LCDwriteCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYINVERTED);
  else
    LCDwriteCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYNORMAL);
}


void LCDenableSleep(void)
{
    _sleep_LCD = true;
    LCDwriteCommand(LCD_FUNCTIONSET |  LCD_POWERDOWN);
}

void LCDdisableSleep(void)
{
    _sleep_LCD = false;
      // get into the EXTENDED mode
  LCDwriteCommand(LCD_FUNCTIONSET | LCD_EXTENDEDINSTRUCTION );
  LCDwriteCommand(LCD_SETBIAS | 0x03);   // set bias voltage
  LCDwriteCommand( LCD_SETVOP | 0x32);   // set contrast
  LCDwriteCommand(LCD_FUNCTIONSET);   // normal mode
  // set display to normal mode
  LCDwriteCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYNORMAL);
}

/* ------------------------ EOF --------------------------- */
