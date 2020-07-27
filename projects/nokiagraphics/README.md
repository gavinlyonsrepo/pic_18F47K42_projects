
Table of contents
---------------------------

  * [Overview](#overview)
  * [ASCII Versions text](#ascii-versions-text)
  * [Features](#features)
  * [Output](#output)
  
Overview
--------------------------------------------
* Name: Nokia 5110
* Description: Nokia 5110 library LCD display(PCD8544) Graphics and text.
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.00

ASCII text Versions
--------------------

1. Basic ASCII Text only for the [PIC16F1619](https://github.com/gavinlyonsrepo/pic_16F1619_projects). 

2. Different ASCII text version of library one for [PIC18F47K42](https://github.com/gavinlyonsrepo/pic_18F47K42_projects) with more fonts and features. 

3. Arduino: Library number two was forked to arduino and is in the arduino [library manager](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT)


Features
----------------------

The Nokia 5110 is a basic graphic LCD screen for lots of applications. 
It was originally intended to be used as a cell phone screen.  
It uses the PCD8544 controller, which is the same used in the Nokia 3310 LCD. 
The PCD8544 is a low power CMOS LCD controller/driver, designed to drive a graphic display of 48 rows and 84 columns. 
All necessary functions for the display are provided in a single chip, including on-chip generation of LCD supply and bias voltages, 
resulting in a minimum of external components and low power consumption. 
The PCD8544 interfaces to microcontrollers through a serial bus interface(SPI).
I did not use the MCC or the in-built SPI hardware for this library,
it uses bit banging/software SPI. 

GPIO function on PIC, 5 Nokia 5110 LCD lines SPI bus

| Pic 16F1619 pin  | Nokia 5110 LCD |
| ------ | ------ |
| RC1 | LCD_CLK Pin 5 clock in |
| RC2 | LCD_DIN Pin 4 data in |
| RC3 | LCD_DC Pin 3 data/command|
| RB4 | LCD_CE Pin 2 chip enable |
| RB5 | LCD_RST Pin 1 reset|

Connect Nokia 5110 VCC(pin 6)to 3.3V.
The user may have to adjust LCD contrast and bias settings,
to the screen at hand for optimal display.
These settings are in the LCDinit function.
A resistor or potentiometer can be connected between (Nokia LCD) GND(pin8) and LIGHT(pin7) to switch on backlight
and adjust it. 

The library has 5 files (main.c, nokia.c, nokia.h, graphics.h, graphics.c).

The main.c  contains the demostartion functions and a test loop. 

[Nokia 5110 LCD dataSheet ](https://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf)

![PICTURE](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/NOKIA2.jpg)

Output
------------------------

![OUTPUT](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/nokiagraph1.jpg)
