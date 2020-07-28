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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F47K42
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB 	          :  MPLAB X 5.40	
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

// get/set LED_STATUS_RA0 aliases
#define LED_STATUS_RA0_TRIS                 TRISAbits.TRISA0
#define LED_STATUS_RA0_LAT                  LATAbits.LATA0
#define LED_STATUS_RA0_PORT                 PORTAbits.RA0
#define LED_STATUS_RA0_WPU                  WPUAbits.WPUA0
#define LED_STATUS_RA0_OD                   ODCONAbits.ODCA0
#define LED_STATUS_RA0_ANS                  ANSELAbits.ANSELA0
#define LED_STATUS_RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LED_STATUS_RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LED_STATUS_RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LED_STATUS_RA0_GetValue()           PORTAbits.RA0
#define LED_STATUS_RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LED_STATUS_RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LED_STATUS_RA0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define LED_STATUS_RA0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define LED_STATUS_RA0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define LED_STATUS_RA0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define LED_STATUS_RA0_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define LED_STATUS_RA0_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set LCD_CLK aliases
#define LCD_CLK_TRIS                 TRISBbits.TRISB1
#define LCD_CLK_LAT                  LATBbits.LATB1
#define LCD_CLK_PORT                 PORTBbits.RB1
#define LCD_CLK_WPU                  WPUBbits.WPUB1
#define LCD_CLK_OD                   ODCONBbits.ODCB1
#define LCD_CLK_ANS                  ANSELBbits.ANSELB1
#define LCD_CLK_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define LCD_CLK_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define LCD_CLK_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define LCD_CLK_GetValue()           PORTBbits.RB1
#define LCD_CLK_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define LCD_CLK_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define LCD_CLK_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define LCD_CLK_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define LCD_CLK_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define LCD_CLK_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define LCD_CLK_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define LCD_CLK_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set LCD_DIN aliases
#define LCD_DIN_TRIS                 TRISBbits.TRISB2
#define LCD_DIN_LAT                  LATBbits.LATB2
#define LCD_DIN_PORT                 PORTBbits.RB2
#define LCD_DIN_WPU                  WPUBbits.WPUB2
#define LCD_DIN_OD                   ODCONBbits.ODCB2
#define LCD_DIN_ANS                  ANSELBbits.ANSELB2
#define LCD_DIN_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define LCD_DIN_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define LCD_DIN_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define LCD_DIN_GetValue()           PORTBbits.RB2
#define LCD_DIN_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define LCD_DIN_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define LCD_DIN_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define LCD_DIN_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define LCD_DIN_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define LCD_DIN_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define LCD_DIN_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define LCD_DIN_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set LCD_DC aliases
#define LCD_DC_TRIS                 TRISBbits.TRISB3
#define LCD_DC_LAT                  LATBbits.LATB3
#define LCD_DC_PORT                 PORTBbits.RB3
#define LCD_DC_WPU                  WPUBbits.WPUB3
#define LCD_DC_OD                   ODCONBbits.ODCB3
#define LCD_DC_ANS                  ANSELBbits.ANSELB3
#define LCD_DC_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define LCD_DC_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define LCD_DC_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define LCD_DC_GetValue()           PORTBbits.RB3
#define LCD_DC_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define LCD_DC_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define LCD_DC_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define LCD_DC_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define LCD_DC_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define LCD_DC_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define LCD_DC_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define LCD_DC_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set LCD_CE aliases
#define LCD_CE_TRIS                 TRISBbits.TRISB4
#define LCD_CE_LAT                  LATBbits.LATB4
#define LCD_CE_PORT                 PORTBbits.RB4
#define LCD_CE_WPU                  WPUBbits.WPUB4
#define LCD_CE_OD                   ODCONBbits.ODCB4
#define LCD_CE_ANS                  ANSELBbits.ANSELB4
#define LCD_CE_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LCD_CE_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LCD_CE_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LCD_CE_GetValue()           PORTBbits.RB4
#define LCD_CE_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LCD_CE_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LCD_CE_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define LCD_CE_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define LCD_CE_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define LCD_CE_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define LCD_CE_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define LCD_CE_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set LCD_RST aliases
#define LCD_RST_TRIS                 TRISBbits.TRISB5
#define LCD_RST_LAT                  LATBbits.LATB5
#define LCD_RST_PORT                 PORTBbits.RB5
#define LCD_RST_WPU                  WPUBbits.WPUB5
#define LCD_RST_OD                   ODCONBbits.ODCB5
#define LCD_RST_ANS                  ANSELBbits.ANSELB5
#define LCD_RST_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define LCD_RST_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define LCD_RST_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define LCD_RST_GetValue()           PORTBbits.RB5
#define LCD_RST_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define LCD_RST_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define LCD_RST_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define LCD_RST_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define LCD_RST_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define LCD_RST_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define LCD_RST_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define LCD_RST_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

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