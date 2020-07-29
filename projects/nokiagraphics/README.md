
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
* ASCII Text only Version of this library with fonts and features. light-weight. [PIC18F47K42](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/tree/master/projects/nokiatext)

 

Features
----------------------

The Nokia 5110 is a basic graphic LCD screen for lots of applications. 
It was originally intended to be used as a cell phone screen.  
It uses the PCD8544 controller, which is the same used in the Nokia 3310 LCD. 
The PCD8544 is a low power CMOS LCD controller/driver, designed to drive a graphic display of 48 rows and 84 columns. 
All necessary functions for the display are provided in a single chip, including on-chip generation of LCD supply and bias voltages, 
resulting in a minimum of external components and low power consumption. 
The PCD8544 interfaces to microcontrollers through a serial bus interface(SPI). 

GPIO function on PIC, 5 Nokia 5110 LCD lines SPI bus(software SPI)

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
Run the PIC at 3.3V,  If run at 5V drop voltage on control lines to 3.3V.
These settings are in the LCDinit function.
A resistor or potentiometer can be connected between (Nokia LCD) GND(pin8) and LIGHT(pin7) to switch on backlight
and adjust it. 

The library has 5 files (main.c, nokia.c, nokia.h, graphics.h, graphics.c).
It is a fork of an Arduino library in the library manager.

The main.c contains the demo functions in a test loop showing features of library. 

[Nokia 5110 LCD dataSheet ](https://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf)

![PICTURE](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/NOKIA2.jpg)

Memory usage: 

1. Program space used 23976 bytes 18.3%)
2. Data space    used 703 bytes (8.6%)

Output
------------------------

1. Bitmap Initials
2. Text Font
3. Shapes

![OUTPUT](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/nokiagraph1.jpg)
