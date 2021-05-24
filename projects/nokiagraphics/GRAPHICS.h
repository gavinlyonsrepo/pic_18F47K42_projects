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

#ifndef GRAPHICS_H
#define GRAPHICS_H

/* -------- libraries -------- */
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "NOKIA.h"


/* ----------- Defines -----------*/
#define display_width   _width
#define display_height  _height
#define display_drawPixel   drawPixel
#define display_drawVLine   drawVLine
#define display_drawHLine   drawHLine
#define display_fillScreen  fillScreen
#define display_fillRect    fillRect
#define display_setRotation setRotation
#define display_invert      invertDisplay

/* ----------------- User Functions ---------- */

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

uint8_t  display_getRotation();
uint16_t getCursorX(void);
uint16_t getCursorY(void);
uint16_t display_getWidth();
uint16_t display_getHeight();

void display_drawBitmapV2   (uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h, uint8_t color);

/* -------------- Non User Functions ------------------- */
void writeLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);
uint8_t printNumber(uint32_t n, int8_t n_width, uint8_t _flags);
void printFloat(float float_n, int8_t f_width, int8_t decimal, uint8_t _flags);
void v_printf(const char *fmt, va_list arp);

/*----------- Variables ---------*/
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

int16_t
  cursor_x = 0,          ///< x location to start print()ing text
  cursor_y = 0;          ///< y location to start print()ing text
uint16_t
  textcolor = 0xFFFF,    ///< 16-bit background color for print()
  textbgcolor = 0xFFFF;  ///< 16-bit text color for print()
uint8_t
  textsize = 1;          ///< Desired magnification of text to print()
bool
  wrap = true;           ///< If set, 'wrap' text at right edge of display



// Standard ASCII 5x7 font
#ifndef FONT5X7_H
static const uint8_t font[256][5] = {
   0x00, 0x00, 0x00, 0x00, 0x00,
   0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
   0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
   0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
   0x18, 0x3C, 0x7E, 0x3C, 0x18,
   0x1C, 0x57, 0x7D, 0x57, 0x1C,
   0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
   0x00, 0x18, 0x3C, 0x18, 0x00,
   0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
   0x00, 0x18, 0x24, 0x18, 0x00,
   0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
   0x30, 0x48, 0x3A, 0x06, 0x0E,
   0x26, 0x29, 0x79, 0x29, 0x26,
   0x40, 0x7F, 0x05, 0x05, 0x07,
   0x40, 0x7F, 0x05, 0x25, 0x3F,
   0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
   0x7F, 0x3E, 0x1C, 0x1C, 0x08,
   0x08, 0x1C, 0x1C, 0x3E, 0x7F,
   0x14, 0x22, 0x7F, 0x22, 0x14,
   0x5F, 0x5F, 0x00, 0x5F, 0x5F,
   0x06, 0x09, 0x7F, 0x01, 0x7F,
   0x00, 0x66, 0x89, 0x95, 0x6A,
   0x60, 0x60, 0x60, 0x60, 0x60,
   0x94, 0xA2, 0xFF, 0xA2, 0x94,
   0x08, 0x04, 0x7E, 0x04, 0x08,
   0x10, 0x20, 0x7E, 0x20, 0x10,
   0x08, 0x08, 0x2A, 0x1C, 0x08,
   0x08, 0x1C, 0x2A, 0x08, 0x08,
   0x1E, 0x10, 0x10, 0x10, 0x10,
   0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
   0x30, 0x38, 0x3E, 0x38, 0x30,
   0x06, 0x0E, 0x3E, 0x0E, 0x06,
   0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x5F, 0x00, 0x00,
   0x00, 0x07, 0x00, 0x07, 0x00,
   0x14, 0x7F, 0x14, 0x7F, 0x14,
   0x24, 0x2A, 0x7F, 0x2A, 0x12,
   0x23, 0x13, 0x08, 0x64, 0x62,
   0x36, 0x49, 0x56, 0x20, 0x50,
   0x00, 0x08, 0x07, 0x03, 0x00,
   0x00, 0x1C, 0x22, 0x41, 0x00,
   0x00, 0x41, 0x22, 0x1C, 0x00,
   0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
   0x08, 0x08, 0x3E, 0x08, 0x08,
   0x00, 0x80, 0x70, 0x30, 0x00,
   0x08, 0x08, 0x08, 0x08, 0x08,
   0x00, 0x00, 0x60, 0x60, 0x00,
   0x20, 0x10, 0x08, 0x04, 0x02,
   0x3E, 0x51, 0x49, 0x45, 0x3E,
   0x00, 0x42, 0x7F, 0x40, 0x00,
   0x72, 0x49, 0x49, 0x49, 0x46,
   0x21, 0x41, 0x49, 0x4D, 0x33,
   0x18, 0x14, 0x12, 0x7F, 0x10,
   0x27, 0x45, 0x45, 0x45, 0x39,
   0x3C, 0x4A, 0x49, 0x49, 0x31,
   0x41, 0x21, 0x11, 0x09, 0x07,
   0x36, 0x49, 0x49, 0x49, 0x36,
   0x46, 0x49, 0x49, 0x29, 0x1E,
   0x00, 0x00, 0x14, 0x00, 0x00,
   0x00, 0x40, 0x34, 0x00, 0x00,
   0x00, 0x08, 0x14, 0x22, 0x41,
   0x14, 0x14, 0x14, 0x14, 0x14,
   0x00, 0x41, 0x22, 0x14, 0x08,
   0x02, 0x01, 0x59, 0x09, 0x06,
   0x3E, 0x41, 0x5D, 0x59, 0x4E,
   0x7C, 0x12, 0x11, 0x12, 0x7C,
   0x7F, 0x49, 0x49, 0x49, 0x36,
   0x3E, 0x41, 0x41, 0x41, 0x22,
   0x7F, 0x41, 0x41, 0x41, 0x3E,
   0x7F, 0x49, 0x49, 0x49, 0x41,
   0x7F, 0x09, 0x09, 0x09, 0x01,
   0x3E, 0x41, 0x41, 0x51, 0x73,
   0x7F, 0x08, 0x08, 0x08, 0x7F,
   0x00, 0x41, 0x7F, 0x41, 0x00,
   0x20, 0x40, 0x41, 0x3F, 0x01,
   0x7F, 0x08, 0x14, 0x22, 0x41,
   0x7F, 0x40, 0x40, 0x40, 0x40,
   0x7F, 0x02, 0x1C, 0x02, 0x7F,
   0x7F, 0x04, 0x08, 0x10, 0x7F,
   0x3E, 0x41, 0x41, 0x41, 0x3E,
   0x7F, 0x09, 0x09, 0x09, 0x06,
   0x3E, 0x41, 0x51, 0x21, 0x5E,
   0x7F, 0x09, 0x19, 0x29, 0x46,
   0x26, 0x49, 0x49, 0x49, 0x32,
   0x03, 0x01, 0x7F, 0x01, 0x03,
   0x3F, 0x40, 0x40, 0x40, 0x3F,
   0x1F, 0x20, 0x40, 0x20, 0x1F,
   0x3F, 0x40, 0x38, 0x40, 0x3F,
   0x63, 0x14, 0x08, 0x14, 0x63,
   0x03, 0x04, 0x78, 0x04, 0x03,
   0x61, 0x59, 0x49, 0x4D, 0x43,
   0x00, 0x7F, 0x41, 0x41, 0x41,
   0x02, 0x04, 0x08, 0x10, 0x20,
   0x00, 0x41, 0x41, 0x41, 0x7F,
   0x04, 0x02, 0x01, 0x02, 0x04,
   0x40, 0x40, 0x40, 0x40, 0x40,
   0x00, 0x03, 0x07, 0x08, 0x00,
   0x20, 0x54, 0x54, 0x78, 0x40,
   0x7F, 0x28, 0x44, 0x44, 0x38,
   0x38, 0x44, 0x44, 0x44, 0x28,
   0x38, 0x44, 0x44, 0x28, 0x7F,
   0x38, 0x54, 0x54, 0x54, 0x18,
   0x00, 0x08, 0x7E, 0x09, 0x02,
   0x18, 0xA4, 0xA4, 0x9C, 0x78,
   0x7F, 0x08, 0x04, 0x04, 0x78,
   0x00, 0x44, 0x7D, 0x40, 0x00,
   0x20, 0x40, 0x40, 0x3D, 0x00,
   0x7F, 0x10, 0x28, 0x44, 0x00,
   0x00, 0x41, 0x7F, 0x40, 0x00,
   0x7C, 0x04, 0x78, 0x04, 0x78,
   0x7C, 0x08, 0x04, 0x04, 0x78,
   0x38, 0x44, 0x44, 0x44, 0x38,
   0xFC, 0x18, 0x24, 0x24, 0x18,
   0x18, 0x24, 0x24, 0x18, 0xFC,
   0x7C, 0x08, 0x04, 0x04, 0x08,
   0x48, 0x54, 0x54, 0x54, 0x24,
   0x04, 0x04, 0x3F, 0x44, 0x24,
   0x3C, 0x40, 0x40, 0x20, 0x7C,
   0x1C, 0x20, 0x40, 0x20, 0x1C,
   0x3C, 0x40, 0x30, 0x40, 0x3C,
   0x44, 0x28, 0x10, 0x28, 0x44,
   0x4C, 0x90, 0x90, 0x90, 0x7C,
   0x44, 0x64, 0x54, 0x4C, 0x44,
   0x00, 0x08, 0x36, 0x41, 0x00,
   0x00, 0x00, 0x77, 0x00, 0x00,
   0x00, 0x41, 0x36, 0x08, 0x00,
   0x02, 0x01, 0x02, 0x04, 0x02,
   0x3C, 0x26, 0x23, 0x26, 0x3C,
   0x1E, 0xA1, 0xA1, 0x61, 0x12,
   0x3A, 0x40, 0x40, 0x20, 0x7A,
   0x38, 0x54, 0x54, 0x55, 0x59,
   0x21, 0x55, 0x55, 0x79, 0x41,
   0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
   0x21, 0x55, 0x54, 0x78, 0x40,
   0x20, 0x54, 0x55, 0x79, 0x40,
   0x0C, 0x1E, 0x52, 0x72, 0x12,
   0x39, 0x55, 0x55, 0x55, 0x59,
   0x39, 0x54, 0x54, 0x54, 0x59,
   0x39, 0x55, 0x54, 0x54, 0x58,
   0x00, 0x00, 0x45, 0x7C, 0x41,
   0x00, 0x02, 0x45, 0x7D, 0x42,
   0x00, 0x01, 0x45, 0x7C, 0x40,
   0x7D, 0x12, 0x11, 0x12, 0x7D, // A-umlaut
   0xF0, 0x28, 0x25, 0x28, 0xF0,
   0x7C, 0x54, 0x55, 0x45, 0x00,
   0x20, 0x54, 0x54, 0x7C, 0x54,
   0x7C, 0x0A, 0x09, 0x7F, 0x49,
   0x32, 0x49, 0x49, 0x49, 0x32,
   0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
   0x32, 0x4A, 0x48, 0x48, 0x30,
   0x3A, 0x41, 0x41, 0x21, 0x7A,
   0x3A, 0x42, 0x40, 0x20, 0x78,
   0x00, 0x9D, 0xA0, 0xA0, 0x7D,
   0x3D, 0x42, 0x42, 0x42, 0x3D, // O-umlaut
   0x3D, 0x40, 0x40, 0x40, 0x3D,
   0x3C, 0x24, 0xFF, 0x24, 0x24,
   0x48, 0x7E, 0x49, 0x43, 0x66,
   0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
   0xFF, 0x09, 0x29, 0xF6, 0x20,
   0xC0, 0x88, 0x7E, 0x09, 0x03,
   0x20, 0x54, 0x54, 0x79, 0x41,
   0x00, 0x00, 0x44, 0x7D, 0x41,
   0x30, 0x48, 0x48, 0x4A, 0x32,
   0x38, 0x40, 0x40, 0x22, 0x7A,
   0x00, 0x7A, 0x0A, 0x0A, 0x72,
   0x7D, 0x0D, 0x19, 0x31, 0x7D,
   0x26, 0x29, 0x29, 0x2F, 0x28,
   0x26, 0x29, 0x29, 0x29, 0x26,
   0x30, 0x48, 0x4D, 0x40, 0x20,
   0x38, 0x08, 0x08, 0x08, 0x08,
   0x08, 0x08, 0x08, 0x08, 0x38,
   0x2F, 0x10, 0xC8, 0xAC, 0xBA,
   0x2F, 0x10, 0x28, 0x34, 0xFA,
   0x00, 0x00, 0x7B, 0x00, 0x00,
   0x08, 0x14, 0x2A, 0x14, 0x22,
   0x22, 0x14, 0x2A, 0x14, 0x08,
   0x55, 0x00, 0x55, 0x00, 0x55, // #176 (25% block) missing in old code
   0xAA, 0x55, 0xAA, 0x55, 0xAA, // 50% block
   0xFF, 0x55, 0xFF, 0x55, 0xFF, // 75% block
   0x00, 0x00, 0x00, 0xFF, 0x00,
   0x10, 0x10, 0x10, 0xFF, 0x00,
   0x14, 0x14, 0x14, 0xFF, 0x00,
   0x10, 0x10, 0xFF, 0x00, 0xFF,
   0x10, 0x10, 0xF0, 0x10, 0xF0,
   0x14, 0x14, 0x14, 0xFC, 0x00,
   0x14, 0x14, 0xF7, 0x00, 0xFF,
   0x00, 0x00, 0xFF, 0x00, 0xFF,
   0x14, 0x14, 0xF4, 0x04, 0xFC,
   0x14, 0x14, 0x17, 0x10, 0x1F,
   0x10, 0x10, 0x1F, 0x10, 0x1F,
   0x14, 0x14, 0x14, 0x1F, 0x00,
   0x10, 0x10, 0x10, 0xF0, 0x00,
   0x00, 0x00, 0x00, 0x1F, 0x10,
   0x10, 0x10, 0x10, 0x1F, 0x10,
   0x10, 0x10, 0x10, 0xF0, 0x10,
   0x00, 0x00, 0x00, 0xFF, 0x10,
   0x10, 0x10, 0x10, 0x10, 0x10,
   0x10, 0x10, 0x10, 0xFF, 0x10,
   0x00, 0x00, 0x00, 0xFF, 0x14,
   0x00, 0x00, 0xFF, 0x00, 0xFF,
   0x00, 0x00, 0x1F, 0x10, 0x17,
   0x00, 0x00, 0xFC, 0x04, 0xF4,
   0x14, 0x14, 0x17, 0x10, 0x17,
   0x14, 0x14, 0xF4, 0x04, 0xF4,
   0x00, 0x00, 0xFF, 0x00, 0xF7,
   0x14, 0x14, 0x14, 0x14, 0x14,
   0x14, 0x14, 0xF7, 0x00, 0xF7,
   0x14, 0x14, 0x14, 0x17, 0x14,
   0x10, 0x10, 0x1F, 0x10, 0x1F,
   0x14, 0x14, 0x14, 0xF4, 0x14,
   0x10, 0x10, 0xF0, 0x10, 0xF0,
   0x00, 0x00, 0x1F, 0x10, 0x1F,
   0x00, 0x00, 0x00, 0x1F, 0x14,
   0x00, 0x00, 0x00, 0xFC, 0x14,
   0x00, 0x00, 0xF0, 0x10, 0xF0,
   0x10, 0x10, 0xFF, 0x10, 0xFF,
   0x14, 0x14, 0x14, 0xFF, 0x14,
   0x10, 0x10, 0x10, 0x1F, 0x00,
   0x00, 0x00, 0x00, 0xF0, 0x10,
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
   0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
   0xFF, 0xFF, 0xFF, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xFF, 0xFF,
   0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
   0x38, 0x44, 0x44, 0x38, 0x44,
   0xFC, 0x4A, 0x4A, 0x4A, 0x34, // sharp-s or beta
   0x7E, 0x02, 0x02, 0x06, 0x06,
   0x02, 0x7E, 0x02, 0x7E, 0x02,
   0x63, 0x55, 0x49, 0x41, 0x63,
   0x38, 0x44, 0x44, 0x3C, 0x04,
   0x40, 0x7E, 0x20, 0x1E, 0x20,
   0x06, 0x02, 0x7E, 0x02, 0x02,
   0x99, 0xA5, 0xE7, 0xA5, 0x99,
   0x1C, 0x2A, 0x49, 0x2A, 0x1C,
   0x4C, 0x72, 0x01, 0x72, 0x4C,
   0x30, 0x4A, 0x4D, 0x4D, 0x30,
   0x30, 0x48, 0x78, 0x48, 0x30,
   0xBC, 0x62, 0x5A, 0x46, 0x3D,
   0x3E, 0x49, 0x49, 0x49, 0x00,
   0x7E, 0x01, 0x01, 0x01, 0x7E,
   0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
   0x44, 0x44, 0x5F, 0x44, 0x44,
   0x40, 0x51, 0x4A, 0x44, 0x40,
   0x40, 0x44, 0x4A, 0x51, 0x40,
   0x00, 0x00, 0xFF, 0x01, 0x03,
   0xE0, 0x80, 0xFF, 0x00, 0x00,
   0x08, 0x08, 0x6B, 0x6B, 0x08,
   0x36, 0x12, 0x36, 0x24, 0x36,
   0x06, 0x0F, 0x09, 0x0F, 0x06,
   0x00, 0x00, 0x18, 0x18, 0x00,
   0x00, 0x00, 0x10, 0x10, 0x00,
   0x30, 0x40, 0xFF, 0x01, 0x01,
   0x00, 0x1F, 0x01, 0x01, 0x1E,
   0x00, 0x19, 0x1D, 0x17, 0x12,
   0x00, 0x3C, 0x3C, 0x3C, 0x3C,
   0x00, 0x00, 0x00, 0x00, 0x00  // #255 NBSP
};
#endif // FONT5X7_H


#endif // GRAPHICS_H
