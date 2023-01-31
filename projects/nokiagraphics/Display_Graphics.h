/*
* Project Name: Nokia  5110 Graphic library for PIC  micro-controller
* File: Display_Graphics.h
* Description: header file for  graphics libraries to draw shapes lines etc
* Author: Gavin Lyons.
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
#include "Display_Font.h"

/* ----------- Defines -----------*/
#define display_width   _width_LCD
#define display_height  _height_LCD
#define display_drawPixel   LCDdrawPixel
#define display_fillScreen  LCDfillScreen
#define display_setRotation LCDsetRotation
#define display_invert      LCDinvertDisplay
#define _min_LCD(a,b) (((a) < (b)) ? (a) : (b)) //used in main as well

/* ----------------- User Functions ---------- */
void display_drawHLine(int16_t x, int16_t y, int16_t w, bool color);
void display_drawVLine(int16_t x, int16_t y, int16_t w, bool color);
void display_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, bool color);
void display_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
void display_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void display_drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
void display_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t color);
void display_fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
void display_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint8_t color);
void display_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);
void display_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);
void display_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint8_t color);
void display_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint8_t color);
void display_setCursor(int16_t x, int16_t y);
void display_setTextColor(uint8_t c, uint8_t bg);
void display_setTextSize(uint8_t s);
void display_setTextWrap(bool w);
void display_putc(char c);
void display_puts(char *s);
void display_printf(const char *fmt, ...);
void display_customChar(const uint8_t *c);
void display_drawChar(int16_t x, int16_t y, uint8_t c, uint8_t color, uint8_t bg, uint8_t size);

void display_Font(LCDFontType_e);

uint8_t  display_getRotation(void);
int16_t display_getCursorX(void);
int16_t display_getCursorY(void);
int16_t display_getWidth(void);
int16_t display_getHeight(void);

void display_drawBitmap   (int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint8_t color);

/* -------------- Non User Functions ------------------- */
void DisplayWriteLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
uint8_t DisplayPrintNumber(uint32_t n, int8_t n_width, uint8_t _flags);
void DisplayPrintFloat(float float_n, int8_t f_width, int8_t decimal, uint8_t _flags);
void DisplayVPrintf(const char *fmt, va_list arp);

#endif // GRAPHICS_H
