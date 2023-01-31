/*
* Project Name: Nokia  5110 Font library for PIC  micro-controller
* File: Display_Font.h
* Description: header file for  font data, 6 fonts
* Author: Gavin Lyons.
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#ifndef DISPLAY_FONT_H
#define DISPLAY_FONT_H


/* -------- libraries -------- */
#include <stdint.h>


typedef enum {
    LCDFontType_Default = 1, // Default 5X8
    LCDFontType_Thick = 2, // Thick 7X8  (NO LOWERCASE LETTERS)
    LCDFontType_HomeSpun = 3, // homespun 7X8 
    LCDFontType_SevenSeg = 4, // seven segment 4X8
    LCDFontType_Wide = 5, // Wide  8X8 (NO LOWERCASE LETTERS)
    LCDFontType_Tiny = 6 // tiny 3x8
} LCDFontType_e; // type of font

typedef enum {
    LCDFontWidth_3 = 3, // tiny font
    LCDFontWidth_4 = 4, // seven segment font
    LCDFontWidth_5 = 5, // Default 
    LCDFontWidth_7 = 7, // thick + homeSpun
    LCDFontWidth_8 = 8 // wide
} LCDFontWidth_e; // Size width of fonts in pixels, add padding for font_width < 9

typedef enum {
    LCDFontOffset_Extend = 0x00, //   full ASCII
    LCDFontOffset_Space = 0x20, // Starts at Space
} LCDFontOffset_e; // font offset in the ASCII table

// **** FONT DEFINE SECTION ******  
// Comment in the fonts you want, X_1 is default. 
#define NOKIA5110_FONT_Default
#define NOKIA5110_FONT_Thick
#define NOKIA5110_FONT_HomeSpun
#define NOKIA5110_FONT_SevenSeg
#define NOKIA5110_FONT_Wide
#define NOKIA5110_FONT_Tiny
// **** END OF FONT DEFINE SECTION ******  

#ifdef NOKIA5110_FONT_Default 
extern const unsigned char (* pFontDefaultptr)[5];
#endif
#ifdef  NOKIA5110_FONT_Thick
extern const unsigned char (* pFontThickptr)[7];
#endif
#ifdef NOKIA5110_FONT_HomeSpun
extern const unsigned char (* pFontHomeSpunptr)[7] ;
#endif
#ifdef NOKIA5110_FONT_SevenSeg
extern const unsigned char (* pFontSevenSegptr)[4];
#endif
#ifdef NOKIA5110_FONT_Wide
extern const unsigned char (* pFontWideptr)[8];
#endif
#ifdef NOKIA5110_FONT_Tiny
extern const  unsigned char (* pFontTinyptr)[3];
#endif



#endif // DISPLAY_FONT_H
