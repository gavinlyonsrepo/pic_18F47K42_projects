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
* Title : LNokia 5110 library LCD display (PCD8544) 
* Author: Gavin Lyons
* Pic:  pic18F47k42
* Toolchain: xc8 v2.36 , MPLABX IDE v6.00 , MCC v5

Features
-------------------------

This is a PIC version of my [Arduino Library here](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT)
. Full information and pictures of output THERE. 
Main difference between versions, is PIC version is software SPI only.
The main.c contains a sequence of tests to 
test library. If a font is not enabled nothing will show for that specific test.
Fonts are enabled in the font data header file by commenting in the relevant defines,
see FONT DEFINE SECTION .

MCU running at 12Mhz if you increase frequency user may have to 
change the uS delay define in the library header file to ensure Software Spi
can keep up.

GPIO function on PIC, 5 Nokia 5110 LCD lines, Software SPI bus

| PIC | Nokia 5110 LCD |
| ------ | ------ |
| RB1 | LCD_CLK Pin 5 clock in |
| RB2 | LCD_DIN Pin 4 data in |
| RB3 | LCD_DC Pin 3 data/command|
| RB4 | LCD_CE Pin 2 chip enable |
| RB5 | LCD_RST Pin 1 reset|

Pinout of a Nokia 5110 LCD.

![ pinout ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_PINOUT.jpg)


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

1. Graphics  library for the NOKIA 5110 XC8 PIC [PIC18F47K42.](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/tree/master/projects/nokiagraphics) 

