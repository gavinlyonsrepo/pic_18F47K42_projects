/*
* Project Name: Nokia  5110 Graphic library for PIC  micro-controller
* File: GRAPHICS.h 
* Description: header file for  graphics libraries to draw shapes lines etc
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created: July 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#ifndef DISPLAY_GRAPHICS_H
#define DISPLAY_GRAPHICS_H

/* -------- libraries -------- */
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "Nokia5110_PCD8544.h"


/* ----------- Defines -----------*/
#define display_width   _width_LCD
#define display_height  _height_LCD
#define display_drawPixel   LCDdrawPixel
#define display_fillScreen  LCDfillScreen
#define display_setRotation LCDsetRotation
#define display_invert      LCDinvertDisplay
#define _min_LCD(a,b) (((a) < (b)) ? (a) : (b)) //used in main as well

/* ----------------- User Functions ---------- */
void display_drawHLine(uint8_t x, uint8_t y, uint8_t w, bool color);
void display_drawVLine(uint8_t x, uint8_t y, uint8_t w, bool color);
void display_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color);
void display_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);
void display_drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
void display_drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint8_t color);
void display_drawCircleHelper(uint16_t x0, uint16_t y0, uint16_t r, uint8_t cornername, uint8_t color);
void display_fillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint8_t color);
void display_fillCircleHelper(uint16_t x0, uint16_t y0, uint16_t r, uint8_t cornername, uint16_t delta, uint8_t color);
void display_drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void display_fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void display_drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint8_t color);
void display_fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint8_t color);
void display_setCursor(uint16_t x, uint16_t y);
void display_setTextColor(uint16_t c, uint16_t bg);
void display_setTextSize(uint8_t s);
void display_setTextWrap(bool w);
void display_putc(char c);
void display_puts(char *s);
void display_printf(const char *fmt, ...);
void display_customChar(const uint8_t *c);
void display_drawChar(uint16_t x, uint16_t y, uint8_t c, uint8_t color, uint16_t bg, uint8_t size);

uint8_t  display_getRotation(void);
uint16_t display_getCursorX(void);
uint16_t display_getCursorY(void);
uint16_t display_getWidth(void);
uint16_t display_getHeight(void);

void display_drawBitmapV2   (uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h, uint8_t color);

/* -------------- Non User Functions ------------------- */
void DisplayWriteLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);
uint8_t DisplayPrintNumber(uint32_t n, int8_t n_width, uint8_t _flags);
void DisplayPrintFloat(float float_n, int8_t f_width, int8_t decimal, uint8_t _flags);
void DisplayVPrintf(const char *fmt, va_list arp);

#endif // GRAPHICS_H
