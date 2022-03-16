/*
* Project Name: Nokia  5110 Graphic library for PIC  micro-controller
* File: GRAPHICS.hc
* Description: Source file for  graphics libraries to draw shapes lines etc
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created: July 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#include "Display_Graphics.h"

/*----------- Variables ---------*/

#define _swap_int16_t_LCD(a, b) { int16_t t = a; a = b; b = t; }

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
static const uint8_t FontOne[256][5] = {
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


/*
    Name:         writeLine
    Function Desc:   Write a line.  
    Param1:    x0  Start point x coordinate
    Param2:    y0  Start point y coordinate
    Param3:    x1  End point x coordinate
    Param4:    y1  End point y coordinate
    Param5:    color 
*/
void DisplayWriteLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color) {
    bool steep = abs((int16_t)(y1 - y0)) > abs((int16_t)(x1 - x0));
    int16_t dx, dy, err, ystep;
    if (steep) {
        _swap_int16_t_LCD(x0, y0);
        _swap_int16_t_LCD(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t_LCD(x0, x1);
        _swap_int16_t_LCD(y0, y1);
    }

    dx = x1 - x0;
    dy = abs((int16_t)(y1 - y0));

    err = dx / 2;
    

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            display_drawPixel(y0, x0, color);
        } else {
            display_drawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}


/*
   Function Desc:   Draw a line
    Param1:    x0  Start point x coordinate
    Param2:    y0  Start point y coordinate
    Param3:    x1  End point x coordinate
    Param4:    y1  End point y coordinate
    Param5:    color 
*/
void display_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color) {
    if(x0 == x1){
        if(y0 > y1) _swap_int16_t_LCD(y0, y1);
        display_drawVLine(x0, y0, y1 - y0 + 1, color);
    } else if(y0 == y1){
        if(x0 > x1) _swap_int16_t_LCD(x0, x1);
        display_drawHLine(x0, y0, x1 - x0 + 1, color);
    } else {
        DisplayWriteLine(x0, y0, x1, y1, color);
    }
}


/*
   Function Desc:   Draw a circle outline
    Param1:    x0   Center-point x coordinate
    Param2:    y0   Center-point y coordinate
    Param3:    r   Radius of circle
    Param4:    color
*/
void display_drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint8_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    display_drawPixel(x0  , y0+r, color);
    display_drawPixel(x0  , y0-r, color);
    display_drawPixel(x0+r, y0  , color);
    display_drawPixel(x0-r, y0  , color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        display_drawPixel(x0 + x, y0 + y, color);
        display_drawPixel(x0 - x, y0 + y, color);
        display_drawPixel(x0 + x, y0 - y, color);
        display_drawPixel(x0 - x, y0 - y, color);
        display_drawPixel(x0 + y, y0 + x, color);
        display_drawPixel(x0 - y, y0 + x, color);
        display_drawPixel(x0 + y, y0 - x, color);
        display_drawPixel(x0 - y, y0 - x, color);
    }
}


/*
    Function Desc:   Quarter-circle drawer, used to do circles and roundrects
    Param1:    x0   Center-point x coordinate
    Param2:    y0   Center-point y coordinate
    Param3:    r   Radius of circle
    Param4:    cornername  Mask bit #1 or bit #2 to indicate which quarters of the circle we're doing
    Param5:    color
*/

void display_drawCircleHelper(uint16_t x0, uint16_t y0, uint16_t r, uint8_t cornername, uint8_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
            display_drawPixel(x0 + x, y0 + y, color);
            display_drawPixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
            display_drawPixel(x0 + x, y0 - y, color);
            display_drawPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            display_drawPixel(x0 - y, y0 + x, color);
            display_drawPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            display_drawPixel(x0 - y, y0 - x, color);
            display_drawPixel(x0 - x, y0 - y, color);
        }
    }
}


/*
   Function Desc:   Draw a circle with filled color
    Param1:    x0   Center-point x coordinate
    Param2:    y0   Center-point y coordinate
    Param3:    r   Radius of circle
    Param4:    color 
*/
void display_fillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint8_t color) {
    display_drawVLine(x0, y0-r, 2*r+1, color);
    display_fillCircleHelper(x0, y0, r, 3, 0, color);
}



/*
    Function Desc: Quarter-circle drawer with fill, used for circles and roundrects
    Param1:  x0       Center-point x coordinate
    Param2:  y0       Center-point y coordinate
    Param3:  r        Radius of circle
    Param4:  corners  Mask bits indicating which quarters we're doing
    Param5:  delta    Offset from center-point, used for round-rects
    Param6:  color    
*/
void display_fillCircleHelper(uint16_t x0, uint16_t y0, uint16_t r, uint8_t corners, uint16_t delta, uint8_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
    int16_t px    = x;
    int16_t py    = y;

    delta++; 

    while(x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if(x < (y + 1)) {
            if(corners & 1) display_drawVLine(x0+x, y0-y, 2*y+delta, color);
            if(corners & 2) display_drawVLine(x0-x, y0-y, 2*y+delta, color);
        }
        if(y != py) {
            if(corners & 1) display_drawVLine(x0+py, y0-px, 2*px+delta, color);
            if(corners & 2) display_drawVLine(x0-py, y0-px, 2*px+delta, color);
            py = y;
        }
        px = x;
    }
}


/*
   Function Desc:  Draw a rectangle with no fill color
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    w   Width in pixels
    Param4:    h   Height in pixels
    Param5:    color
*/
void display_drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color) {
    display_drawHLine(x, y, w, color);
    display_drawHLine(x, y+h-1, w, color);
    display_drawVLine(x, y, h, color);
    display_drawVLine(x+w-1, y, h, color);
}


/*
   Function Desc:  Draw a rounded rectangle with no fill color
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    w   Width in pixels
    Param4:    h   Height in pixels
    Param5:    r   Radius of corner rounding
    Param6:    color 
*/
void display_drawRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint8_t color) {
    int16_t max_radius = ((w < h) ? w : h) / 2; 
    if(r > max_radius) r = max_radius;
    display_drawHLine(x+r  , y    , w-2*r, color); 
    display_drawHLine(x+r  , y+h-1, w-2*r, color); 
    display_drawVLine(x    , y+r  , h-2*r, color); 
    display_drawVLine(x+w-1, y+r  , h-2*r, color); 
    display_drawCircleHelper(x+r    , y+r    , r, 1, color);
    display_drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
    display_drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
    display_drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}


/*
   Function Desc:  Draw a rounded rectangle with fill color
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    w   Width in pixels
    Param4:    h   Height in pixels
    Param5:    r   Radius of corner rounding
    Param6:    color 
*/
void display_fillRoundRect(uint16_t x, uint16_t y, uint16_t w,
  uint16_t h, uint16_t r, uint8_t color) {
    int16_t max_radius = ((w < h) ? w : h) / 2; 
    if(r > max_radius) r = max_radius;
    display_fillRect(x+r, y, w-2*r, h, color);
    display_fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    display_fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}


/*
   Function Desc:  Draw a triangle with no fill color
    Param1:    x0  Vertex #0 x coordinate
    Param2:    y0  Vertex #0 y coordinate
    Param3:    x1  Vertex #1 x coordinate
    Param4:    y1  Vertex #1 y coordinate
    Param5:    x2  Vertex #2 x coordinate
    Param6:    y2  Vertex #2 y coordinate
    Param7:    color
*/
void display_drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
  uint16_t x2, uint16_t y2, uint8_t color) {
    display_drawLine(x0, y0, x1, y1, color);
    display_drawLine(x1, y1, x2, y2, color);
    display_drawLine(x2, y2, x0, y0, color);
}

/*
   Function Desc:    Draw a triangle with color-fill
    Param1:    x0  Vertex #0 x coordinate
    Param2:    y0  Vertex #0 y coordinate
    Param3:    x1  Vertex #1 x coordinate
    Param4:    y1  Vertex #1 y coordinate
    Param5:    x2  Vertex #2 x coordinate
    Param6:    y2  Vertex #2 y coordinate
    Param7:    color 
*/
void display_fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
  uint16_t x2, uint16_t y2, uint8_t color) {
    int16_t a, b, y, last, dx01, dy01, dx02, dy02, dx12, dy12;
    int32_t
    sa   = 0,
    sb   = 0;

    if (y0 > y1) {
        _swap_int16_t_LCD(y0, y1); _swap_int16_t_LCD(x0, x1);
    }
    if (y1 > y2) {
        _swap_int16_t_LCD(y2, y1); _swap_int16_t_LCD(x2, x1);
    }
    if (y0 > y1) {
        _swap_int16_t_LCD(y0, y1); _swap_int16_t_LCD(x0, x1);
    }

    if(y0 == y2) { 
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        display_drawHLine(a, y0, b-a+1, color);
        return;
    }
    
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    if(y1 == y2) last = y1;  
    else         last = y1-1; 

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;

        if(a > b) _swap_int16_t_LCD(a,b);
        display_drawHLine(a, y, b-a+1, color);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;

        if(a > b) _swap_int16_t_LCD(a,b);
        display_drawHLine(a, y, b-a+1, color);
    }
}


/*
    Function Desc: Print one byte/character of data
    Param1:  c  The 8-bit ascii character to write
*/
void display_putc(char c) {
  uint8_t i, j;
  if (c == ' ' && cursor_x == 0 && wrap)
    return;
  if(c == '\r') {
    cursor_x = 0;
    return;
  }
  if(c == '\n') {
    cursor_y += textsize * 8;
    return;
  }

  for(i = 0; i < 5; i++ ) {
    uint8_t line = FontOne[c][i];
    for(j = 0; j < 8; j++, line >>= 1) {
      if(line & 1) {
        if(textsize == 1)
          display_drawPixel(cursor_x + i, cursor_y + j, textcolor);
        else
          display_fillRect(cursor_x + i * textsize, cursor_y + j * textsize, textsize, textsize, textcolor);
      } 
      else 
        if(textbgcolor != textcolor) {
          if(textsize == 1)
            display_drawPixel(cursor_x + i, cursor_y + j, textbgcolor);
          else
            display_fillRect(cursor_x + i * textsize, cursor_y + j * textsize, textsize, textsize, textbgcolor);
        }
    }
  }

  if(textbgcolor != textcolor) { 
    if(textsize == 1)  display_drawVLine(cursor_x + 5, cursor_y, 8, textbgcolor);
    else               display_fillRect(cursor_x + 5 * textsize, cursor_y, textsize, 8 * textsize, textbgcolor);
  }

  cursor_x += textsize * 6;

  if( cursor_x > ((uint16_t)display_width + textsize * 6) )
    cursor_x = display_width;

  if (wrap && (cursor_x + (textsize * 5)) > display_width)
  {
    cursor_x = 0;
    cursor_y += textsize * 8;
    if( cursor_y > ((uint16_t)display_height + textsize * 8) )
      cursor_y = display_height;
  }
}

/* 
  Desc: prints a string 
  Param1: Pointer to a string of ASCII bytes
*/
void display_puts(char *s) {
  while(*s)
    display_putc(*s++);
}

/* 
  Desc: print custom char  (dimension: 7x5 or 8x5 pixel)
*/
void display_customChar(const uint8_t *c) {
  uint8_t i, j;
  for(i = 0; i < 5; i++ ) {
    uint8_t line = c[i];
    for(j = 0; j < 8; j++, line >>= 1) {
      if(line & 1) {
        if(textsize == 1)
          display_drawPixel(cursor_x + i, cursor_y + j, textcolor);
        else
          display_fillRect(cursor_x + i * textsize, cursor_y + j * textsize, textsize, textsize, textcolor);
      } 
      else 
        if(textbgcolor != textcolor) {
          if(textsize == 1)
            display_drawPixel(cursor_x + i, cursor_y + j, textbgcolor);
          else
            display_fillRect(cursor_x + i * textsize, cursor_y + j * textsize, textsize, textsize, textbgcolor);
        }
    }
  }

  if(textbgcolor != textcolor) {  // If opaque, draw vertical line for last column
    if(textsize == 1)  display_drawVLine(cursor_x + 5, cursor_y, 8, textbgcolor);
    else               display_fillRect(cursor_x + 5 * textsize, cursor_y, textsize, 8 * textsize, textbgcolor);
  }

  cursor_x += textsize * 6;

  if( cursor_x > ((uint16_t)display_width + textsize * 6) )
    cursor_x = display_width;

  if (wrap && (cursor_x + (textsize * 5)) > display_width)
  {
    cursor_x = 0;
    cursor_y += textsize * 8;
    if( cursor_y > ((uint16_t)display_height + textsize * 8) )
      cursor_y = display_height;
  }
}


/*
   Function Desc:  Draw a single character
    Param1:    x   Bottom left corner x coordinate
    Param2:    y   Bottom left corner y coordinate
    Param3:    c   The 8-bit font-indexed character (likely ascii)
    Param4:    color
    Param5:   (if same as color, no background)
    Param6:    size  Font magnification level, 1 is 'original' size
*/
void display_drawChar(uint16_t x, uint16_t y, uint8_t c, uint8_t color, uint16_t bg,
     uint8_t size) {
  uint16_t prev_x     = cursor_x,
           prev_y     = cursor_y,
           prev_color = textcolor,
           prev_bg    = textbgcolor;
  uint8_t  prev_size  = textsize;

  display_setCursor(x, y);
  display_setTextSize(size);
  display_setTextColor(color, bg);
  display_putc(c);

  cursor_x    = prev_x;
  cursor_y    = prev_y;
  textcolor   = prev_color;
  textbgcolor = prev_bg;
  textsize    = prev_size;
}


/*
    Function Desc: Set text cursor location
    Param1:  x    X coordinate in pixels
    Param2:  y    Y coordinate in pixels
*/
void display_setCursor(uint16_t x, uint16_t y) {
    cursor_x = x;
    cursor_y = y;
}


/*
    Function Desc: Get text cursor X location
    Returns:   X coordinate in pixels
*/
uint16_t display_getCursorX(void) {
    return cursor_x;
}


/*
    Function Desc:     Get text cursor Y location
    Returns:   Y coordinate in pixels
*/
uint16_t display_getCursorY(void) {
    return cursor_y;
}


/*
    Function Desc:  Set text 'magnification' size. Each increase in s makes 1 pixel that much bigger.
    Param1:  s  Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
*/
void display_setTextSize(uint8_t s) {
    textsize = (s > 0) ? s : 1;
}


void display_setTextColor(uint16_t c, uint16_t b) {
    textcolor   = c;
    textbgcolor = b;
}


/*
    Function Desc:     Whether text that is too long should 'wrap' around to the next line.
    Param1:  w Set true for wrapping, false for clipping
*/
void display_setTextWrap(bool w) {
    wrap = w;
}

/*
    Function Desc:     Get rotation setting for display
    Returns:   0 thru 3 corresponding to 4 cardinal rotations
*/
uint8_t display_getRotation(void) {
    return _rotation_LCD;
}

/*
    Function Desc:     Get width of the display, accounting for the current rotation
    Returns:   Width in pixels
*/
uint16_t display_getWidth(void) {
    return display_width;
}

/*
    Function Desc:     Get height of the display, accounting for the current rotation
    Returns:   Height in pixels
*/
uint16_t display_getHeight(void) {
    return display_height;
}

/*
   Function Desc:    Draw a ROM-resident 1-bit image at the specified (x,y) position,
              using the specified foreground color (unset bits are transparent).
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    bitmap  byte array with monochrome bitmap
    Param4:    w   Width of bitmap in pixels
    Param5:    h   Hieght of bitmap in pixels
    Param6:    color 
*/
void display_drawBitmapV2(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h,
  uint8_t color) {

    uint16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t _byte = 0;
    uint16_t i, j;

    for(j = 0; j < h; j++, y++) {
        for( i = 0; i < w; i++ ) {
            if(i & 7) _byte <<= 1;
            else      _byte   = bitmap[j * byteWidth + i / 8];
            if(_byte & 0x80)
              display_drawPixel(x+i, y, color);
        }
    }
}

// Called internally from display_printf
uint8_t DisplayPrintNumber(uint32_t n, int8_t n_width, uint8_t _flags) {
  uint8_t i=0, j, buff[10];
  do {
      buff[i] = (uint8_t)( n % (_flags & 0x1F) );
      if (buff[i] > 9)
        buff[i] += (_flags & 0x80) ? 0x07 : 0x27;
      buff[i++] += '0';
      n /= (_flags & 0x1F);
      } while (n);
  j = i;
  if(_flags & 0x40) {
    n_width--;
    j++;
    if(_flags & 0x20) {    // put '-' before the zeros
      display_putc('-');
      _flags &= ~0x40;
    }
  }
  while (i < n_width--) {
    if (_flags & 0x20)  display_putc('0');
    else                display_putc(' ');
  }
  if (_flags & 0x40)
    display_putc('-');
  do {
      display_putc(buff[--i]);
      } while(i);
  return j;
}

// Called internally from display_printf
void DisplayPrintFloat(float float_n, int8_t f_width, int8_t decimal, uint8_t _flags) {
  int32_t int_part = float_n;
  float rem_part;
  if(decimal == 0)  decimal = 1;
  if(float_n < 0) {
    _flags |= 0x40;
    rem_part = (float)int_part - float_n;
    int_part = ~int_part + 1;
  }
  else
    rem_part = float_n - (float)int_part;
  _flags |= 10;
  f_width -= DisplayPrintNumber(int_part, f_width - decimal - 1, _flags);
  display_putc('.');
  f_width--;
  if(f_width < 1)  f_width = 1;
  if(decimal > f_width)  decimal = f_width;
  while( decimal > 0 && (rem_part != 0 || decimal > 0) ) {
    decimal--;
    rem_part *= 10;
    display_putc( (uint8_t)rem_part + '0' );
    rem_part -= (uint8_t)rem_part;
  }
}

/*
 Desc : Called from display_printf
 port of printf to display to screen instead of console
 */
void DisplayVPrintf(const char *fmt, va_list arp) {
  uint8_t _flags, c, d=0, w=0;
  uint32_t nbr;
  while (1) 
  {
    c = *fmt++;

    if (!c)
      break;

    if (c != '%') {
      display_putc(c);
      continue;
    }

    _flags = 0;
    c = *fmt++;

    if (c == '0') {
      _flags |= 0x20;  // zero flag
      c = *fmt++;
    }

    for (w = 0; c >= '0' && c <= '9'; c = *fmt++)   // width
      w = w * 10 + c - '0';

    if (c == '.') {
      c = *fmt++;
      for (d = 0; c >= '0' && c <= '9'; c = *fmt++)   // decimals width
        d = d * 10 + c - '0';
    }
    
    if(c == 'f' || c == 'F') {    // if float number
      DisplayPrintFloat(va_arg(arp, float), w, d, _flags);
      continue;
    }

    if (c == 'l' || c == 'L') {   // long number (4 bytes)
      _flags |= 0x40;    // long number flag
      c = *fmt++;
    }

    if (!c)   // end of format?
      break;

    if(c == 'X') {
      _flags |= 0x80;   // upper case hex flag
    }
    
    if (c >= 'a')   // if lower case, switch to upper
      c -= 0x20;
    switch (c) {
      case 'C' :        // character
        display_putc( (uint8_t)va_arg(arp, uint8_t) ); continue;
      case 'B' :        // binary
        _flags |= 2;  break;
      case 'O' :        // octal
        _flags |= 8;  break;
      case 'D' :        // signed decimal
      case 'U' :        // unsigned decimal
        _flags |= 10; break;
      case 'X' :        // hexadecimal
        _flags |= 16; break;
      default:          // other
        display_putc(c); continue;
    }

    if(_flags & 0x40)  // if long number
      nbr = (c == 'D') ? va_arg(arp, int32_t) : va_arg(arp, uint32_t);
    else
      nbr = (c == 'D') ? (int32_t)va_arg(arp, int16_t) : (uint32_t)va_arg(arp, uint16_t);
    if ( (c == 'D') &&  (nbr & 0x80000000) ) {
      _flags |= 0x40;     // negative number flag
      nbr = ~nbr + 1;     // change to positive form
    }
    else
      _flags &= ~0x40;    // number is positive
    DisplayPrintNumber(nbr, w, _flags);
  }
}

/*
 * Desc: Printf port for screen
 * Param1: the format string
 * Param2: variable arguments passed
 */
void display_printf(const char *fmt, ...) {
  
  va_list arg;
  va_start(arg, fmt);
  DisplayVPrintf(fmt, arg);
  va_end(arg);
}


void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, int16_t y1, bool color) {

  bool steep = abs((int16_t)(y1 - y0)) > abs((int16_t)(x1 - x0));
  int8_t ystep;
  uint8_t dx, dy;
  int16_t err;

  if (steep) {
    _swap_int8_t_LCD(x0, y0);
    _swap_int8_t_LCD(x1, y1);
  }
  if (x0 > x1) {
    _swap_int8_t_LCD(x0, x1);
    _swap_int8_t_LCD(y0, y1);
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
      LCDdrawPixel(y0, x0, color);
    else
      LCDdrawPixel(x0, y0, color);
    err -= dy;
    if (err < 0) {
      y0  += ystep;
      err += dx;
    }
  }
}

void display_drawHLine(uint8_t x, uint8_t y, uint8_t w, bool color) {
   drawLine(x, y, x + w - 1, y, color);
}


void display_drawVLine(uint8_t x, uint8_t y, uint8_t h, bool color) {
  drawLine(x, y, x, y + h - 1, color);
}

void display_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color) {
  uint8_t i;
  for (i = x; i < x + w; i++)
    display_drawVLine(i, y, h, color);
}
/* ------------- EOF ------------------ */