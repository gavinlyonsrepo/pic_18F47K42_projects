/*
* Project Name: Oled I2C graphics project 
* File: TextFonts.h
* Description: 3 fonts pixel ASCII font
 PICO (4 by 6) UNO (6 by 8) MEGA (16 by 16)  
* Author: Gavin Lyons.
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#ifndef _text_font_H
#define _text_font_H

#include <stdint.h>

// Pointers to the text fonts, stored in the c file 
extern const uint8_t * pFontMegaptr;
extern const uint8_t * pFontUnoptr;
extern const uint8_t * pFontPicoptr;

#endif
