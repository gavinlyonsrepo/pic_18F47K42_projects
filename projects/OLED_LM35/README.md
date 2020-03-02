Overview
--------------------------------------------
* Name: OLED_LM35
* Description: Display LM35 sensor temperature on a
  OLED display (128 by 64 pixels SSD1306 I2C bus).
* Author: Gavin Lyons.
* Complier: xc8 v2.1.0
* Foundation services library: 0.2.0 (I2C)
* MCC version: 3.95
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30


Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)
  * [Output](#output)
  
Features
----------------------

In this folder the main source code in C for program can be found in file main.c.
The code generated using the MPLAB Code Configurator is in a folder called mcc_generated_files. 

There is also an Oled library(OLED.c and OLED.h),
and a font.h file that contains an ASCII pixelfont.

**Connections**

1. RD0 = LM35 Sensor line input.
2. RE2 = Status LED, toggles every sensor refresh. 
3. RC4 = SDA OLED
4. RC3 = SCLK OLED

**OLED 128 by 64 SSD1306**

The SSD1306 OLED display communicates with the master device over I2C mode.
It is controlled via the two pin I2C bus. Both pins must be held logic high by pull-up resistors. 

The ASCII based font file is a called "font.h". 
This library turns the OLED into a character 21x04 based screen.
There are no graphics in library and one font. 
Will also work on a  OLED 128 by 32 SSD1306, as well with one modification to library.
( comment in/out a block of marked code at top of oled.h).

**LM35**

It assumes vdd = 5V, which maps 0-4096 to 0-5V ranges.
The LM35 outputs a signal on pin Vout, 
The LM35 signal is read via an analog input(RD0) 10mV per degree. The ADC 0.0012207 per division.

LM35 calculation:

1. Vout=0.01/°C
2. °C=Vout/0.01
3. °C=(Vout * 100) where Vout = ADC_value * (VCC/ADC resolution)
4. °C = (ADC_value * (0.0012207)) * 100
5. °C * 100 =(ADC_value * (0.0012207)) * 10000
6. °C * 100 = 488 (Solved for an ADC value of 40) 4.88°C
7. The RHS can then be parsed by code and displayed.

Output
-----------------------
![ output ](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/output.jpg)
