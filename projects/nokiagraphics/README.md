
Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)
  * [Output](#output)
  
Overview
--------------------------------------------
* Name: Nokia 5110
* Description: Nokia 5110 library LCD display(PCD8544) Graphics and text.
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Credits: Library based on a port of a mikroC PRO library by [Simple Circuits](https://simple-circuit.com/pic-mikroc-nokia-5110-lcd-graphics-test-example/)


Features
----------------------

The Nokia 5110 is a basic graphic LCD screen for lots of applications. 
GPIO function on PIC, 5 Nokia 5110 LCD lines SPI bus(software SPI only at present)

| PIC pin  | Nokia 5110 LCD |
| ------ | ------ |
| RB1 | LCD_CLK Pin 5 clock in |
| RB2 | LCD_DIN Pin 4 data in |
| RB3 | LCD_DC Pin 3 data/command|
| RB4 | LCD_CE Pin 2 chip enable |
| RB5 | LCD_RST Pin 1 reset|

Connect Nokia 5110 VCC(pin 6)to 3.3V.
The user may have to adjust LCD contrast and bias settings,
to the screen at hand for optimal display.
Run the PIC at 3.3V,  If run at 5V drop voltage logic on control lines to 3.3V.
A resistor or potentiometer can be connected between (Nokia LCD) GND(pin8) and LIGHT(pin7) to switch on /off backlight and adjust brightness. 

The main.c contains the demo functions in a test loop showing features of library. 

[Nokia 5110 LCD dataSheet ](https://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf)

![PICTURE](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/NOKIA2.jpg)

Memory usage: 

1. Program space used 23976 bytes 18.3%)
2. Data space  used 703 bytes (8.6%)

Output
------------------------

1. Bitmap (Initials) vertically addressed data.
2. Text Font 0-84 ASCII, full extended ASCII 0-255 available + custom characters
3. Shapes example, full graphics class included.

![OUTPUT](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/nokiagraph1.jpg)
