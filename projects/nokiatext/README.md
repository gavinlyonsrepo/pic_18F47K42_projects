Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)
  * [Hardware](#hardware)
  * [Fonts](#fonts)
  * [Memory](#memory)
  * [Other Versions](#other-versions)
  
Overview
--------------------
* Name : NOKIA5110_TEXT
* Title : Library for Nokia 5110 LCD (PCD8544 controller) for the PIC18F47K42
* Author: Gavin Lyons
* IDE :  MPLAB X v5.30
* Complier : Xc8 v2.10
* Description : 

1. PIC library.      
2. Inverse, Bias and contrast control. 
3. ASCII strings and character text display.
4. Six ASCII text fonts.
5. Sleep mode.
6. Designed to be light weight, low memory footprint. see memory section.

Features
-------------------------
The Nokia 5110 is a basic LCD screen for lots of applications. 
It was originally intended to be used as a mobile phone screen. 
It uses the PCD8544 controller, which is the same used in the Nokia 3310 LCD. 
The PCD8544 interfaces to microcontrollers through a serial bus interface(SPI).
The library has 8 custom code files (NOKIA5110_TEXT.c  NOKIA5110_TEXT.h and 6 font header files).

The screen is 84 X 48 pixels. The X-Axis has 84 columns.
The Y_Axis(rows) the 48 pixels are divided into 6 row blocks. 
Each block containing one byte of pixels. 6 * 8 = 48.

| Block number   | Pixel number Y axis|
| ------ | ------ |
| Block 0 | 0-7 |
| Block 1 | 8-15 |
| Block 2 | 16-23|
| Block 3 | 24-31 |
| Block 4 | 32-39 |
| Block 5 | 40-47 |

Hardware 
---------------------------

GPIO function on PIC, 5 Nokia 5110 LCD lines SPI bus.
Software SPI is implemented.

| PIC | Nokia 5110 LCD |
| ------ | ------ |
| RB1 | LCD_CLK Pin 5 clock in |
| RB2 | LCD_DIN Pin 4 data in |
| RB3 | LCD_DC Pin 3 data/command|
| RB4 | LCD_CE Pin 2 chip enable |
| RB5 | LCD_RST Pin 1 reset|

Pinout of a Nokia 5110 LCD.

![ pinout ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_PINOUT.jpg)


Fonts 
---------------------------

There are 6 fonts.
By default only Font 1 is commented in and ready to go.
So to use a non-default Font (2-6), two steps.

1. Comment in the respective define at top of library header file NOKIA5110_TEXT.h in the FONT DEFINE SECTION.
2. Call LCDFont function and pass it number of respective font.

Only include what fonts you want in order to keep program size as small as possible.
Each font is a header file, NOKIA5110_FONT_X.h where X is number of Font(1-6)

**Font table**

| Font num | Font name | Pixel size | total characters | 
| ------ | ------ | ------ | ------ |
| 1 | default | 5x8 | 12*6 = 72 |
| 2 | thick   | 7x8 | 9*6 = 54 |
| 3 | Aurebesh | 5x8 | 12*6 = 72 |
| 4 | Segment | 4x8 | 14*6 = 84 |
| 5 | Wide | 8x8 | 8*6 = 48 |
| 6 | tiny | 3x8 | 16*6 = 96  |

| Font num | Font file  | Font define  | uppercase letters only |
| ------ | ------ | ------ | ------ | 
| 1 | NOKIA5110_FONT.h | NOKIA5110_FONT_1 | --- |
| 2 | NOKIA5110_FONT_TWO.h | NOKIA5110_FONT_2 | yes |
| 3 | NOKIA5110_FONT_THREE.h | NOKIA5110_FONT_3 | --- | 
| 4 | NOKIA5110_FONT_FOUR.h | NOKIA5110_FONT_4 | --- |
| 5 | NOKIA5110_FONT_FIVE.h | NOKIA5110_FONT_5 | yes |
| 6 | NOKIA5110_FONT_SIX.h | NOKIA5110_FONT_6 | --- |

Note:
Each character is a byte of pixels in height(Y). One pixel of empty space on each side 
is added by code. So a 5x8 (XxY) pixel character is in reality 7x8. 
Each of the six rowblock is one byte height. So to get total number of characters,
divide screen width ( 84 ) by number of characters across and multiple by number of rowblocks ( 6 ).
For example with "default" is a 5x8 pixel font with the two blank spaces is 7x8 for each character, 
So (84/7) = 12 characters across columns. 
There are (48/8) = 6 row blocks that gives (12 x 06) = 72 characters in total.

**Font 1 default**

![ default  font ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT1.jpg)

**All Fonts**
 
Output showing all 6 fonts, 1-6, one font in each row block:

![all font](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT_ALL.jpg)

Memory
---------------------------

Results of when main.c test demo file is complied.

1. One Font

* Program space used   3126 bytes (2.4%)
* Data space    used     26 bytes (0.3%)

2.All Fonts included 
    
* Program space used 5736 bytes (4.4%)
* Data space    used     27 bytes (0.3%)


Other Versions
-------------------------------------

1. Arduino: This library was forked to arduino it is in the arduino [library manager](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT)

2. Graphics version of this library for the [PIC18F47K42](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/tree/master/projects/nokiagraphics) 