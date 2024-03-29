
  * [Overview](#overview)
  * [Installation](#installation)
  * [Software](#software)
  * [Hardware](#hardware)
  * [Output](#output)
  * [Notes](#notes)

Overview
--------------------------------------------
* Name: OLED_GRAPH
* Description: SSD1306 I2C OLED graphics library for PIC microcontroller 
* Author: Gavin Lyons.
* Complier: xc8 v2.1.0
* Foundation services library: 0.2.0 (I2C)
* MCC version: 3.95
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30


Hardware
---------------
1. RB2 = SDA OLED
2. RB1 = SCLK OLED

The SSD1306 OLED display communicates with the master device over I2C mode.
It is controlled via the two pin I2C bus. Both pins must be held logic high by pull-up resistors,
if absent from module

Software
-------------------------
The I2C code and pin config generated using the MPLAB Code Configurator is in a folder called mcc_generated_files. 
There is  an OLED library in files (SSD1306OLED.c and SSD1306OLED.h),
and a TextFonts.c file that contains three ASCII pixel fonts.
Bitmap data used by test file are in separate file's. 
Main.c  contains a list of test routines to test library. 
The library can  display Graphics, text and bitmaps.
Inverse, sleep , contrast, rotate and scroll functions included.

There is a USER OPTION SELECTION section by top of header file to select screen size 
3 options. Select your screen size here.

1. 128X64 (default)
2. 128X32
3. 96X16 (not tested , no part) 

**Fonts** 

1. PICO font X by Y  = 4 by 6 . 288 characters. pFontPicoptr
2. UNO font X by Y = 6 by 8 . 147 characters. pFontUnoptr
3. MEGA font X by Y  = 16 by 16 . 32 characters pFontMegaptr

More fonts can be found here at  [link](http://www.rinkydinkelectronics.com/r_fonts.php),as  well as instructions on how to create them.


**Bitmaps** 

Two bitmap functions, 

1. SSD1306_Bitmap. Entire screen only,  Data Vertically addressed, writes directly to screen.
2. SSD1306_BitmapBuffer.  Can be any size. Data Horizontally addressed. Writes to buffer.

Output
-----------------------

1. Some Graphics.
2. Text, the 3 fonts included
3. Bitmap example.

![ output ](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/oledgraph.jpg)

Notes
----------------------

There is a light version of this library, OLED I2C SSD1306 controller library (ASCII, text only) 
in repository  as well  [here.](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/tree/master/projects/OLED_LM35)
