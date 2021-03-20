Overview
--------------------------------------------
* Name: OLED_GRAPH
* Description: SSD1306 I2C OLED graph (128 by 64) graphics library for PIC microcontroller 
* Author: Gavin Lyons.
* Complier: xc8 v2.1.0
* Foundation services library: 0.2.0 (I2C)
* MCC version: 3.95
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30

Features
----------------------

The I2C code and pin config generated using the MPLAB Code Configurator is in a folder called mcc_generated_files. 
There is  an OLED library in files (SSD1306OLED.c and SSD1306OLED.h),
and a TextFonts.h file that contains three ASCII pixel fonts and an optional bitmap image(used to test image) function.
Main.c  contains a list of basic test routines to test library. 

1. RE2 = Status LED. optional.
2. RB2 = SDA OLED
3. RB1 = SCLK OLED

The SSD1306 OLED display communicates with the master device over I2C mode.
It is controlled via the two pin I2C bus. Both pins must be held logic high by pull-up resistors. 

The library can  display Graphics, text and bitmaps.

 Will also work on a  OLED (128 by 32) & (96 by 16) SSD1306 as well, with one modification to library.
( comment in/out a define at top of header file.). 

**Fonts** 

1. PICO font X by Y  = 4 by 6 . 288 characters.
2. UNO font X by Y = 6 by 8 . 147 characters.
3. MEGA font X by Y  = 16 by 16 . 32 characters

Output
-----------------------

1. Graphics
2. Text, the 3 fonts included
3. Bitmap example.

![ output ](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/oledgraph.jpg)
