/*
* Project Name: Keypad
* File: keypad.h
* Description: library for 4 by 4 matrix keypad
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler 
* IDE:  MPLAB X v5.30
* Created March 2020
* URL: github gavinlyonsrepo 
*/


#ifndef __KEYPAD_H
#define __KEYPAD_H


#define KEYPAD_DEBOUNCE 200 // Debounce Delay in mS 

// Function declarations
char GetKey(void);
char ReadKeys(void);

#endif