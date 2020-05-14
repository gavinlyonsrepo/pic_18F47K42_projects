Overview
--------------------------------------------
* Name: Electronic lock
* Descriptin: 
Security electronic lock , featuring keypad input , LCD display
Servo control.
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
  
Features
----------------------

In this folder the main source code in C for program can be found in file main.c.
The code generated using the MPLAB Code Configurator is in a folder called mcc_generated_files. 

There is also two custom libraries one for the LCD and the other for keypad.
The password is currently hard-coded.  Enter code and press D.
Press C to "re-lock" after sucessfully code entry and unlock. 

**Connections**

1. RA0 = SG90 Servo line input. (servo powered from PSU 5V rail
2. RC0 = Status LED, ON at startup and when safe unlocked 
3. RC3 = SCLK I2C LCD, With 4.7 kohm pullup to VCC
4. RC4 = SDATA I2C LCD, With 4.7 kohm pullup to VCC
5. RD0 = Column 1 of keypad, Input with WPU
6. RD2 = Column 2 of keypad, Input with WPU
7. RD3 = Column 3 of keypad, Input with WPU
8. RD4 = Column 4 of keypad, Input with WPU
9. RD4 = Row A of keypad, output
10. RD5 =  Row B of keypad, output
11. RD6 = Row C of keypad, output
12. RD7 = Row D of keypad, output


**HD44780-based character LCD**

HD44780 based character LCD displays use 14 wire connections: 8 data lines (D0-D7), 3 control lines (RS, E, R/W), 
and three power lines (Vdd, Vss, Vee).
Some LCDs come with backlight features that help reading display data in low illumination conditions. 
They have two additional connections (LED+ and LED- or A and K).

In this example , a 4-pin PCF8574 Interface "backpack" board is attached to LCD.
It is controlled via the two pin I2C bus. Both pins must be held logic high by pull-up resistors. 

The LCD code is in a separate library called "lcd.h" and called "lcd.c".
The Data is sent in 4-bit mode. The upper nibble holds the data and lower nibble of byte manipulates
the control bits of LCD(enable and register select). 

![PCF8574 & LCD ](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/LCDPCF.jpg)

**Keypad**

There is a custom library in main folder called keypad.h and keypad.c.
The keypad in question is 4X4 matrix.
Which is wired as such from the top.

1.	RD3	C4 
2.	RD2	C3
3.	RD1	C2
4.	RD0	C1
5.	RD4	RowA
6.	RD5	RowB
7.	RD6	RowC
8.	RD7	RowD

Numeric 6 digit code. Pressing D for enter code, C to re-lock safe
 
RowA    7   8   9   A
RowB    4   5   6   B
RowC    1   2   3   C
RowD    n   0   n   D

![ output ](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/keypad.jpg)


**Servo SG90**

![ScreenShot servo](https://github.com/gavinlyonsrepo/RpiMotorLib/blob/master/images/sg90.jpg)

[Datasheet SG90](http://www.micropik.com/PDF/SG90Servo.pdf)

1. ground common Brown
2. 5V vcc rail form PSU red
3. Signal orange/yellow

A PWM signal based of timer 2 is used to drive this.
The freq is 50Hz on the control line and the position it moves to depends on the pulse width of the signal.
50Hz gives a period of 20mS (Freq = 1/Period).

1. The PWM duty signal for lock position is 10.0% or PWMDC value of 61.
2. The PWM duty signal for unlock position is 5.0% or PWMDC value of 30.

Given a 50 Hz frequency we can calculate the required duty cycle for any pulse width. For example:

We need a 1.5 ms pulse to center the servo, 
or a Duty Cycle = 0.0015 * 50 = 0.075 (i.e 7.5%).
Similarly, 1 ms pulse (- 90 degrees or 0 degrees) 
requires a Duty Cycle = 0.001 * 50 = 5%
2 ms pulse (+ 90 degrees or 180), Duty Cycle = 0.002 * 50 = 10%

Thus the duty cycle range should be from ~ 5 - 10% with the center at ~7.5%. 

