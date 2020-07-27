/*
* Project Name: Nokia  5110 Graphic library for PIC  micro-controller
* File: NOKIA.h 
* Description: Header file for NOKIA 5110 library to communicate with LCD
* Author: Gavin Lyons.
* Compiler: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created: July 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#ifndef NOKIA_H
#define NOKIA_H

/* -------- libraries -------- */
#include <stdint.h>
#include <stdbool.h>
#include "mcc_generated_files/mcc.h"

/* ------ Definitions ------ */

#define BLACK 1
#define WHITE 0

#define LCDWIDTH  84
#define LCDHEIGHT 48

#define LCD_POWERDOWN            0x04
#define LCD_ENTRYMODE            0x02
#define LCD_EXTENDEDINSTRUCTION  0x01

#define LCD_DISPLAYBLANK         0x00
#define LCD_DISPLAYNORMAL        0x04
#define LCD_DISPLAYALLON         0x01
#define LCD_DISPLAYINVERTED      0x05

#define LCD_FUNCTIONSET          0x20
#define LCD_DISPLAYCONTROL       0x08
#define LCD_SETYADDR             0x40
#define LCD_SETXADDR             0x80

#define LCD_SETTEMP  0x04
#define LCD_SETBIAS  0x13
#define LCD_SETVOP   0x80

/* --------------- User Functions ------------- */
void LCD_begin(void);
void drawPixel(uint8_t x, uint8_t y, bool color);
void drawHLine(uint8_t x, uint8_t y, uint8_t w, bool color);
void drawVLine(uint8_t x, uint8_t y, uint8_t w, bool color);
void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color);
void setRotation(uint8_t m);
void display_setContrast(uint8_t con);
void display(void);
void display_clear(void);
void fillScreen(void);
void invertDisplay(bool inv);

/* ------------- Non User Functions --------- */
void PCD8544_SPI_Write(uint8_t d);
void writeCommand(uint8_t c);

/* ----------- Variables --------- */
#define pcd8544_swap(a, b) { uint8_t t = a; a = b; b = t; }
uint8_t _width, _height, rotation;

// Memory buffer for the LCD : GL in sig
uint8_t pcd8544_buffer[LCDWIDTH * LCDHEIGHT / 8] = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x8f, 
0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x1f, 0x1f, 0x1f, 0xbf, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x0f, 0x07, 0xef, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x01, 0xc0, 0xf8, 0xfc, 0xfe, 
0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xf8, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 
0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 
0xf0, 0xf0, 0xf0, 0xe0, 0xe2, 0xc6, 0x8e, 0x1e, 0x3e, 0x7e, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x01, 0x00, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xf0, 0xc1, 0x87, 0x0f, 0x1f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x0f, 0x87, 0xc6, 0xe0, 0xe0, 0xf0, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0x1f, 0x1f, 0x1f, 
0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0xbf, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 
0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf9, 0xf1, 0xf1, 0xe3, 0xe3, 0xe3, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 
0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc3, 0xe1, 0xf0, 0xfc, 0xfe, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfe, 
0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

#endif
