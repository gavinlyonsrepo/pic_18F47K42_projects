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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC18F47K42
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.35	
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

// get/set RA0 procedures
#define RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define RA0_GetValue()              PORTAbits.RA0
#define RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define RA0_SetPullup()             do { WPUAbits.WPUA0 = 1; } while(0)
#define RA0_ResetPullup()           do { WPUAbits.WPUA0 = 0; } while(0)
#define RA0_SetAnalogMode()         do { ANSELAbits.ANSELA0 = 1; } while(0)
#define RA0_SetDigitalMode()        do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set STATUS_LED_RC0 aliases
#define STATUS_LED_RC0_TRIS                 TRISCbits.TRISC0
#define STATUS_LED_RC0_LAT                  LATCbits.LATC0
#define STATUS_LED_RC0_PORT                 PORTCbits.RC0
#define STATUS_LED_RC0_WPU                  WPUCbits.WPUC0
#define STATUS_LED_RC0_OD                   ODCONCbits.ODCC0
#define STATUS_LED_RC0_ANS                  ANSELCbits.ANSELC0
#define STATUS_LED_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define STATUS_LED_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define STATUS_LED_RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define STATUS_LED_RC0_GetValue()           PORTCbits.RC0
#define STATUS_LED_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define STATUS_LED_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define STATUS_LED_RC0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define STATUS_LED_RC0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define STATUS_LED_RC0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define STATUS_LED_RC0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define STATUS_LED_RC0_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define STATUS_LED_RC0_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

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

// get/set C1_RD0 aliases
#define C1_RD0_TRIS                 TRISDbits.TRISD0
#define C1_RD0_LAT                  LATDbits.LATD0
#define C1_RD0_PORT                 PORTDbits.RD0
#define C1_RD0_WPU                  WPUDbits.WPUD0
#define C1_RD0_OD                   ODCONDbits.ODCD0
#define C1_RD0_ANS                  ANSELDbits.ANSELD0
#define C1_RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define C1_RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define C1_RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define C1_RD0_GetValue()           PORTDbits.RD0
#define C1_RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define C1_RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define C1_RD0_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define C1_RD0_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define C1_RD0_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define C1_RD0_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define C1_RD0_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define C1_RD0_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set C2_RD1 aliases
#define C2_RD1_TRIS                 TRISDbits.TRISD1
#define C2_RD1_LAT                  LATDbits.LATD1
#define C2_RD1_PORT                 PORTDbits.RD1
#define C2_RD1_WPU                  WPUDbits.WPUD1
#define C2_RD1_OD                   ODCONDbits.ODCD1
#define C2_RD1_ANS                  ANSELDbits.ANSELD1
#define C2_RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define C2_RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define C2_RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define C2_RD1_GetValue()           PORTDbits.RD1
#define C2_RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define C2_RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define C2_RD1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define C2_RD1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define C2_RD1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define C2_RD1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define C2_RD1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define C2_RD1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set C3_RD2 aliases
#define C3_RD2_TRIS                 TRISDbits.TRISD2
#define C3_RD2_LAT                  LATDbits.LATD2
#define C3_RD2_PORT                 PORTDbits.RD2
#define C3_RD2_WPU                  WPUDbits.WPUD2
#define C3_RD2_OD                   ODCONDbits.ODCD2
#define C3_RD2_ANS                  ANSELDbits.ANSELD2
#define C3_RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define C3_RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define C3_RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define C3_RD2_GetValue()           PORTDbits.RD2
#define C3_RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define C3_RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define C3_RD2_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define C3_RD2_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define C3_RD2_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define C3_RD2_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define C3_RD2_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define C3_RD2_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set C4_RD3 aliases
#define C4_RD3_TRIS                 TRISDbits.TRISD3
#define C4_RD3_LAT                  LATDbits.LATD3
#define C4_RD3_PORT                 PORTDbits.RD3
#define C4_RD3_WPU                  WPUDbits.WPUD3
#define C4_RD3_OD                   ODCONDbits.ODCD3
#define C4_RD3_ANS                  ANSELDbits.ANSELD3
#define C4_RD3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define C4_RD3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define C4_RD3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define C4_RD3_GetValue()           PORTDbits.RD3
#define C4_RD3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define C4_RD3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define C4_RD3_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define C4_RD3_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define C4_RD3_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define C4_RD3_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define C4_RD3_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define C4_RD3_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set RowA_RD4 aliases
#define RowA_RD4_TRIS                 TRISDbits.TRISD4
#define RowA_RD4_LAT                  LATDbits.LATD4
#define RowA_RD4_PORT                 PORTDbits.RD4
#define RowA_RD4_WPU                  WPUDbits.WPUD4
#define RowA_RD4_OD                   ODCONDbits.ODCD4
#define RowA_RD4_ANS                  ANSELDbits.ANSELD4
#define RowA_RD4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define RowA_RD4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define RowA_RD4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define RowA_RD4_GetValue()           PORTDbits.RD4
#define RowA_RD4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define RowA_RD4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define RowA_RD4_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define RowA_RD4_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define RowA_RD4_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define RowA_RD4_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define RowA_RD4_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define RowA_RD4_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set RowB_RD5 aliases
#define RowB_RD5_TRIS                 TRISDbits.TRISD5
#define RowB_RD5_LAT                  LATDbits.LATD5
#define RowB_RD5_PORT                 PORTDbits.RD5
#define RowB_RD5_WPU                  WPUDbits.WPUD5
#define RowB_RD5_OD                   ODCONDbits.ODCD5
#define RowB_RD5_ANS                  ANSELDbits.ANSELD5
#define RowB_RD5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define RowB_RD5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define RowB_RD5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define RowB_RD5_GetValue()           PORTDbits.RD5
#define RowB_RD5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define RowB_RD5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define RowB_RD5_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define RowB_RD5_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define RowB_RD5_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define RowB_RD5_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define RowB_RD5_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define RowB_RD5_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set RowC_RD6 aliases
#define RowC_RD6_TRIS                 TRISDbits.TRISD6
#define RowC_RD6_LAT                  LATDbits.LATD6
#define RowC_RD6_PORT                 PORTDbits.RD6
#define RowC_RD6_WPU                  WPUDbits.WPUD6
#define RowC_RD6_OD                   ODCONDbits.ODCD6
#define RowC_RD6_ANS                  ANSELDbits.ANSELD6
#define RowC_RD6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define RowC_RD6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define RowC_RD6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define RowC_RD6_GetValue()           PORTDbits.RD6
#define RowC_RD6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define RowC_RD6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define RowC_RD6_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define RowC_RD6_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define RowC_RD6_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define RowC_RD6_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define RowC_RD6_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define RowC_RD6_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set RowD_RD7 aliases
#define RowD_RD7_TRIS                 TRISDbits.TRISD7
#define RowD_RD7_LAT                  LATDbits.LATD7
#define RowD_RD7_PORT                 PORTDbits.RD7
#define RowD_RD7_WPU                  WPUDbits.WPUD7
#define RowD_RD7_OD                   ODCONDbits.ODCD7
#define RowD_RD7_ANS                  ANSELDbits.ANSELD7
#define RowD_RD7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define RowD_RD7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define RowD_RD7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define RowD_RD7_GetValue()           PORTDbits.RD7
#define RowD_RD7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define RowD_RD7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define RowD_RD7_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define RowD_RD7_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define RowD_RD7_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define RowD_RD7_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define RowD_RD7_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define RowD_RD7_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

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