Table of contents
---------------------------

  * [Overview](#overview)
  * [Output](#output)
  * [Features](#features)
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
4. Nine ASCII text fonts.
5. Sleep mode.
6. Designed to be light weight, low memory footprint. see memory section.

Output
---------------------------------

Output Screenshots, From left to right top to bottom.

1. Custom characters + fill patterns 
2. Font 7 "Large"
3. Half screen bitmap + Font 7 "large"
4. Font 9 "Mega"  
5. Output showing first 6 (X by 8) fonts, #1-6, one font in each row block:
6. Font 8 "Huge" 

![ font pic 1 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT1.jpg)

![ font pic 2 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT2.jpg)

![ font pic 3 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT_ALL.jpg)

Features
-------------------------
The Nokia 5110 is a basic LCD screen for lots of applications. 
It was originally intended to be used as a mobile phone screen. 
It uses the PCD8544 controller, which is the same used in the Nokia 3310 LCD. 
The PCD8544 interfaces to microcontrollers through a serial bus interface(SPI).
The library has 8 custom code files (NOKIA5110_TEXT.c  NOKIA5110_TEXT.h and 9 font header files).

The screen is 84 X 48 pixels. The X-Axis has 84 columns.
The Y_Axis(rows) the 48 pixels are divided into 6 row blocks. 
Each block containing one byte of pixels. 6 * 8 = 48.

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

There are 9 fonts.
By default only Font 1 is commented in and ready to go.
So to use a non-default Font (2-9), two steps.

1. Comment in the respective define at top of library header file NOKIA5110_TEXT.h in the FONT DEFINE SECTION.
2. Call LCDFont function and pass it number of respective font.

Only include what fonts you want in order to keep program size as small as possible.
Each font is a header file, NOKIA5110_FONT_X.h where X is number of Font(1-9)
Some fonts do not have lowercase letters and others are numbers only.
For fonts 1-6 Each character is a byte of pixels in height(Y). One pixel of empty space on each side 
is added by code (padding). So a 5x8 (XxY) pixel character is in reality 7x8. 
Each of the six rowblock is one byte height. 

Total characters = (Screen Width/Character width  + padding) X (Screen height/Character height).

**Font table**

| Font num | Font name | Pixel size | total characters | Note |
| ------ | ------ | ------ | ------ |  ------ |
| 1 | Default | 5x8 | (84/5+2) * (48/8) = 72 |   ------ |
| 2 | Thick   | 7x8 | (84/7+2) * (48/8)  = 54 |  no lowercase letters  |
| 3 | Aurebesh | 5x8 | (84/5+2) * (48/8)  = 72 | ------ |
| 4 | Seven segment | 4x8 | (84/4+2) * (48/8) = 84 | ------ |
| 5 | Wide | 8x8 | (84/8+2) * (48/8) = 48 | no lowercase letters |
| 6 | Tiny | 3x8 | (84/3+2) * (48/8) = 96  | ------ |
| 7 | Large | 12x16 | (84/12) * (48/16) = 21 |  no lowercase letters |
| 8 | Huge | 16x24 | (84/16) * (48/24) = 10  | Numbers + : . only |
| 9 | Mega | 16x32 | (84/16) * (48/32) = 5  | Numbers + : . only |


Memory
---------------------------

Results of when main.c test demo file is complied.

1. Just the default font included 

* Program space used   (4.3%)
* Data space    used      (0.5%)

2.All Fonts included 
    
* Program space used (9.4%)
* Data space    used     (0.5%)


Other Versions
-------------------------------------

1. Arduino: This library was forked to arduino it is in the arduino [library manager.](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT)  

2. Graphics  library for the NOKIA 5110 XC8 PIC [PIC18F47K42.](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/tree/master/projects/nokiagraphics) 

3. STM32 library STM32F303K8T6 Nucleo-32 C [link.](https://github.com/gavinlyonsrepo/STM32_projects/tree/master/projects/nokiatext)
