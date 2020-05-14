/*
* Project Name: Keypad
* File: keypad.c
* Description: library for 4 by 4 matrix keypad
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler 
* IDE:  MPLAB X v5.30
* Created March 2020
* URL: github gavinlyonsrepo 
*/

#include "Keypad.h"
#include "mcc_generated_files/mcc.h"


// Function name: Read Keys
// Scan all the keypad keys to detect any pressed key, return character 
//          C1  C2  C3  C4
// Row A    7   8   9   A
// Row B    4   5   6   B
// Row C    1   2   3   C
// Row D    n   0   n   D

char ReadKeys(void)	
{	
    //Test Row A
    RowA_RD4_SetLow();
    RowB_RD5_SetHigh();
    RowC_RD6_SetHigh();
    RowD_RD7_SetHigh();

	if (C1_RD0_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C1_RD0_GetValue()==0); return '7'; }
	if (C2_RD1_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C2_RD1_GetValue()==0); return '8'; }
	if (C3_RD2_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C3_RD2_GetValue()==0); return '9'; }
	if (C4_RD3_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C4_RD3_GetValue()==0); return 'A'; }

    //Test Row B
    RowA_RD4_SetHigh();
    RowB_RD5_SetLow();
    RowC_RD6_SetHigh();
    RowD_RD7_SetHigh();
   
	if (C1_RD0_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C1_RD0_GetValue()==0); return '4'; }
	if (C2_RD1_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C2_RD1_GetValue()==0); return '5'; }
	if (C3_RD2_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C3_RD2_GetValue()==0); return '6'; }
	if (C4_RD3_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C4_RD3_GetValue()==0); return 'B'; }
	
	//Test Row C
    RowA_RD4_SetHigh();
    RowB_RD5_SetHigh();
    RowC_RD6_SetLow();
    RowD_RD7_SetHigh();

	if (C1_RD0_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C1_RD0_GetValue()==0); return '1'; }
	if (C2_RD1_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C2_RD1_GetValue()==0); return '2'; }
	if (C3_RD2_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C3_RD2_GetValue()==0); return '3'; }
	if (C4_RD3_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C4_RD3_GetValue()==0); return 'C'; }
	
    //Test Row D
    RowA_RD4_SetHigh();
    RowB_RD5_SetHigh();
    RowC_RD6_SetHigh();
    RowD_RD7_SetLow();
    
	if (C1_RD0_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C1_RD0_GetValue()==0); return 'n'; }
	if (C2_RD1_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C2_RD1_GetValue()==0); return '0'; }
	if (C3_RD2_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C3_RD2_GetValue()==0); return 'n'; }
	if (C4_RD3_GetValue()==0) { __delay_ms(KEYPAD_DEBOUNCE ); while (C4_RD3_GetValue()==0); return 'D'; }

	return 'n';           	// Return 'n' if no key pressed
}


// Function name: GetKey
// Read pressed key value from keypad and return its value
char GetKey(void)           	 // Get key from user
{
	char key = 'n';              // Assume no key pressed

	while(key=='n')              // Wait until a key is pressed
		key = ReadKeys();   // Scan the keys again and again

	return key;                  //when key pressed then return its value
}