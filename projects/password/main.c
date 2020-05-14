/*
* Project Name: Security_lock
* File: main.c 
* Desc: Security lock using a HD44780-based character LCD 16x02 using I2C PCF8574 , 
 * keypad entry and servo control
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created March 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo
*/

/* -------- libraries -------- */
#include "mcc_generated_files/mcc.h"
#include "lcd.h"    //My Custom library
#include "Keypad.h" //My Custom library
#include <string.h> 
#include <ctype.h> // for is digit function

/*---------------- Globals---------*/
char guessword[7];
char passkey[7] = "123456"; // password
char mykey =  'n';
bool door_lock = false;
uint8_t stringlength = 0;

/* ----------- Defines -----------*/
#define MAX_DUTY_CYCLE 60 // Servo 10 % Start locked position 
#define MIN_DUTY_CYCLE 30 // Servo 5 % unlocked position
#define LCD_INIT_DELAY 100 
#define LCD_DISPLAY_DELAY 2000

/* -------- Function prototypes -------- */
void Setup(void);
void lcd_redraw(void);
void Door_unlock(void);
void Wrong_guess(void);
void Right_guess(void);
void Digit_key(void);

/* --------- Main Loop ---------- */
void main(void)
{
    Setup();
    while (1)
    {
       mykey = GetKey();   // Scan for key
       Digit_key();       // check if Key pressed digit
       if (mykey == 'D')  // Was D pressed? 
       {
            //check guess word to password
            if (strcmp(guessword, passkey)==0)
            {
               Right_guess();
            }else
            {
                Wrong_guess();
            }
       }
    }
}

/* ---------- End of main loop ---------- */

/* ----------- Function Space ----------- */

// Function to setup PIC
void Setup(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    STATUS_LED_RC0_SetHigh();
    __delay_ms(LCD_INIT_DELAY); // LCD init Delay
    lcd_init(); 
    __delay_ms(LCD_INIT_DELAY);
    lcd_send_cmd (LCD_LINE1);
    PWM5_LoadDutyValue(MAX_DUTY_CYCLE); // lock servo
    lcd_send_string ("Hello");
     __delay_ms(LCD_DISPLAY_DELAY);
    lcd_redraw();
    STATUS_LED_RC0_SetLow();
}

//Function to draw or redraw code entry prompt
void lcd_redraw(void)
{
    lcd_clear();
    lcd_send_cmd (LCD_LINE1);
    lcd_send_string ("Code 6 digits:");
    lcd_send_cmd (LCD_LINE2);
}

//Function to lock the door after correct guess
void Door_lock(void)
{
    PWM5_LoadDutyValue(MAX_DUTY_CYCLE); //lock safe
    guessword[0]='\0';
    door_lock = true;
}

//Function to handle wrong user guess at password
void Wrong_guess(void)
{
    lcd_send_string (" Wrong");
    __delay_ms(LCD_DISPLAY_DELAY);
    lcd_redraw();
    guessword[0] = '\0';
}

//Function to handle correct user guess at password
void Right_guess(void)
{
    lcd_send_string (" Right");
    PWM5_LoadDutyValue(MIN_DUTY_CYCLE); //unlock
    STATUS_LED_RC0_SetHigh();
    __delay_ms(LCD_DISPLAY_DELAY);
    lcd_clear();
    lcd_send_cmd (LCD_LINE1);
    lcd_send_string ("Press C to lock");
    while(door_lock == false)
    {
        mykey = GetKey();

        if (mykey ==  'C') 
        {
            Door_lock();
        }
    }       
    STATUS_LED_RC0_SetLow();
    door_lock = false;
    lcd_redraw();
}

//Function to check if user pressed a numeric key 
void Digit_key(void)
{
    if  (isdigit(mykey))
       {
           lcd_send_data(mykey);
           strncat(guessword, &mykey, 1);  // Add char to string 
       }
}
/* --------  End of File -------- */