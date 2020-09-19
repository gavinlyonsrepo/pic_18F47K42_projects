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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
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

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSELB2 = 0; } while(0)

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

// get/set SW_RE2 aliases
#define SW_RE2_TRIS                 TRISEbits.TRISE2
#define SW_RE2_LAT                  LATEbits.LATE2
#define SW_RE2_PORT                 PORTEbits.RE2
#define SW_RE2_WPU                  WPUEbits.WPUE2
#define SW_RE2_OD                   ODCONEbits.ODCE2
#define SW_RE2_ANS                  ANSELEbits.ANSELE2
#define SW_RE2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define SW_RE2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define SW_RE2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define SW_RE2_GetValue()           PORTEbits.RE2
#define SW_RE2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define SW_RE2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define SW_RE2_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define SW_RE2_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define SW_RE2_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define SW_RE2_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define SW_RE2_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define SW_RE2_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

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