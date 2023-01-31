
Table of contents
---------------------------

  * [Overview](#overview)
  * [Hardware](#hardware)
  * [Software](#software)
  * [Output](#output)
  
Overview
--------------------------------------------
* Name: Nokia 5110
* Description: Nokia 5110 library LCD display(PCD8544) Graphics and text.
* Author: Gavin Lyons.
* Complier: xc8 v2.40 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v6.0
* Credits: Library based on port's of a mikroC PRO library by [Simple Circuits](https://simple-circuit.com/pic-mikroc-nokia-5110-lcd-graphics-test-example/) and my 
arduino  [nokia5110_text](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT) library.



Hardware
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

[Nokia 5110 LCD dataSheet ](https://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf)

![PICTURE](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/NOKIA2.jpg)

Software
----------------------

The main.c contains the demo functions in a test loop showing features of library. 

There are six fonts available

Font table:

|  num | name | size xbyy | ASCII range |
| ------ | ------ | ------ | ------ |  
| 1 | Default | 5x8 | Full Extended ASCII 0x00 - 0xFF |
| 2 | Thick   | 7x8 | ASCII  0x20 - 0x5A  , no lowercase letters |
| 4 | Homespun | 7x8 | ASCII  0x20 - 0x7A |
| 4 | Seven segment | 4x8 | ASCII  0x20 - 0x7A |
| 5 | Wide | 8x8 | ASCII 0x20 - 0x5A , no lowercase letters |
| 6 | Tiny | 3x8 | ASCII  0x20 - 0x7A |


Output
------------------------

1. Bitmap (Initials) used for the splash screen , data preloaded into screen buffer.
2. Default Text Font 0-84 ASCII, full extended ASCII 0-255 available + custom characters + 5 other fonts
3. Shapes example, full graphics class included.

![OUTPUT](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/nokiagraph1.jpg)
