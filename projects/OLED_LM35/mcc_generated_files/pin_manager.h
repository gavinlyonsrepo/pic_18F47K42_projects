/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78.1
        Device            :  PIC18F47K42
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set LM35_AND0 aliases
#define LM35_AND0_TRIS                 TRISDbits.TRISD0
#define LM35_AND0_LAT                  LATDbits.LATD0
#define LM35_AND0_PORT                 PORTDbits.RD0
#define LM35_AND0_WPU                  WPUDbits.WPUD0
#define LM35_AND0_OD                   ODCONDbits.ODCD0
#define LM35_AND0_ANS                  ANSELDbits.ANSELD0
#define LM35_AND0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define LM35_AND0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define LM35_AND0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define LM35_AND0_GetValue()           PORTDbits.RD0
#define LM35_AND0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define LM35_AND0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define LM35_AND0_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define LM35_AND0_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define LM35_AND0_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define LM35_AND0_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define LM35_AND0_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define LM35_AND0_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set LED_RE0 aliases
#define LED_RE0_TRIS                 TRISEbits.TRISE0
#define LED_RE0_LAT                  LATEbits.LATE0
#define LED_RE0_PORT                 PORTEbits.RE0
#define LED_RE0_WPU                  WPUEbits.WPUE0
#define LED_RE0_OD                   ODCONEbits.ODCE0
#define LED_RE0_ANS                  ANSELEbits.ANSELE0
#define LED_RE0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED_RE0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED_RE0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED_RE0_GetValue()           PORTEbits.RE0
#define LED_RE0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED_RE0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED_RE0_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LED_RE0_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LED_RE0_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LED_RE0_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LED_RE0_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define LED_RE0_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/