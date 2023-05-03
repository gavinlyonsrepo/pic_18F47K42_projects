/*
* Project Name: SSD1306_GRAPH
* File: SSD1306OLED.h 
* Description: OLED SSD1306 I2C library header file
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created: SEP  2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#ifndef _SSD1306_H
#define	_SSD1306_H

// ************ Libs ****************
#include "mcc_generated_files/mcc.h"
#include "TextFonts.h"

// ******* SSD1306 Display Type **********
// ******* USER OPTION SELECTION *********
#define SSD1306_128_64   
//#define SSD1306_128_32 
// #define SSD1306_96_16
// ***************************************


#if defined SSD1306_128_64
  #define SSD1306_WIDTH                  128
  #define SSD1306_HEIGHT                 64
  #define SSD1306_PAGENUM                8
  #define SSD1306_CLEAR_SIZE             1024
#endif
#if defined SSD1306_128_32
  #define SSD1306_WIDTH                  128
  #define SSD1306_HEIGHT                 32
  #define SSD1306_PAGENUM                4
  #define SSD1306_CLEAR_SIZE             512
#endif
#if defined SSD1306_96_16
  #define SSD1306_WIDTH                  96
  #define SSD1306_HEIGHT                 16
  #define SSD1306_PAGENUM                 2
  #define SSD1306_CLEAR_SIZE             192
#endif

#define SSD1306_LEFT                  0
#define SSD1306_RIGHT                 254
#define SSD1306_CENTER                255

#define SSD1306_BLACK                 0
#define SSD1306_WHITE                 1
#define SSD1306_INVERSE               2

// ***********  SSD1306 Command Set   ***********

// Fundamental Commands
#define SSD1306_SET_CONTRAST_CONTROL                    0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME                   0xA4
#define SSD1306_DISPLAY_ALL_ON                          0xA5
#define SSD1306_NORMAL_DISPLAY                          0xA6
#define SSD1306_INVERT_DISPLAY                          0xA7
#define SSD1306_DISPLAY_OFF                             0xAE
#define SSD1306_DISPLAY_ON                              0xAF
#define SSD1306_NOP                                     0xE3

// Scrolling Commands
#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3

// Addressing Setting Commands
#define SSD1306_SET_LOWER_COLUMN                        0x00
#define SSD1306_SET_HIGHER_COLUMN                       0x10
#define SSD1306_MEMORY_ADDR_MODE                        0x20
#define SSD1306_SET_COLUMN_ADDR                         0x21
#define SSD1306_SET_PAGE_ADDR                           0x22

// Hardware Configuration Commands
#define SSD1306_SET_START_LINE                          0x40
#define SSD1306_SET_SEGMENT_REMAP                       0xA0
#define SSD1306_SET_MULTIPLEX_RATIO                     0xA8
#define SSD1306_COM_SCAN_DIR_INC                        0xC0
#define SSD1306_COM_SCAN_DIR_DEC                        0xC8
#define SSD1306_SET_DISPLAY_OFFSET                      0xD3
#define SSD1306_SET_COM_PINS                            0xDA
#define SSD1306_CHARGE_PUMP                             0x8D

// Timing & Driving Scheme Setting Commands
#define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO             0xD5
#define SSD1306_SET_PRECHARGE_PERIOD                    0xD9
#define SSD1306_SET_VCOM_DESELECT                       0xDB

// I2C related
#define SSD1306_COMMAND                     0x00
#define SSD1306_DATA                        0xC0
#define SSD1306_DATA_CONTINUE               0x40
#define SSD1306_ADDR          0x3C //0x3D

#define SSD1306_swap(a, b) { int16_t t = a; a = b; b = t; }

// ******** Function Prototypes  *****************

// Display related
void SSD1306_Init( void );
void SSD1306_UpdateDisplay( void );
void SSD1306_Contrast( uint8_t contrast );
void SSD1306_FillBuffer( uint8_t pattern);
void SSD1306_InvertDisplay( bool value );
void SSD1306_DisplayEnable(uint8_t on);
void SSD1306_setRotation(uint8_t r);
void SSD1306_FillScreen(uint8_t pattern);
void SSD1306_FillPage(uint8_t page_num, uint8_t pattern);  

// Graphics related 
void SSD1306_SetPixel( int16_t x, int16_t y, uint8_t color );
void SSD1306_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
void SSD1306_V_Line(int16_t x, int16_t y, int16_t h, uint8_t color);
void SSD1306_H_Line(int16_t x, int16_t y, int16_t w, uint8_t color);

void SSD1306_Rectangle( int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void SSD1306_FillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);

void SSD1306_Triangle( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);
void SSD1306_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	  int16_t x2, int16_t y2, uint8_t color);

void SSD1306_Circle( int16_t x_center, int16_t y_center, int16_t radius, uint8_t color);
void SSD1306_DrawCircleHelper( int16_t x0, int16_t y0,
				 int16_t r, uint8_t cornername, uint8_t color);

void SSD1306_FillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
void SSD1306_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
	  int16_t delta, uint8_t color);

void SSD1306_DrawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	  int16_t radius, uint8_t color);
void SSD1306_FillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
	  int16_t radius, uint8_t color);

// Bitmap
void SSD1306_Bitmap( const uint8_t *image );
void SSD1306_BitmapBuffer(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h,
  uint8_t color);

// Text related 
void SSD1306_SetFont( const uint8_t *font);
void SSD1306_InvertFont( bool invert_status );
void SSD1306_Write( int16_t x, int16_t y, char value );
void SSD1306_Write_Text( int16_t x, int16_t y, char *text);

// Scroll
void SSD1306_StartScrollRight(uint8_t start, uint8_t stop); 
void SSD1306_StartScrollLeft(uint8_t start, uint8_t stop) ;
void SSD1306_StartScrollDiagRight(uint8_t start, uint8_t stop) ;
void SSD1306_StartScrollDiagLeft(uint8_t start, uint8_t stop) ;
void SSD1306_StopScroll(void) ;

#endif	// header guard
