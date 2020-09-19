/*
* Project Name: SSD1306_GRAPH
* File: main.c
* Description: OLED 128X64 SSD1306  I2C test c file
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created Feb 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_PIC18F47K42_projects
*/


// ************ Libs ****************
#include "mcc_generated_files/mcc.h"
#include "SSD1306OLED.h"
#include "TextFonts.h"

//*************** Defines *************
#define TESTDELAY 5000
#define TESTDELAYONE 1000
#define INITDELAY 2500 

// ********* Function prototypes ************
void Setup(void); // Setup
void Test1A(void); // All Fonts
void Test1B(void); // Font Pico
void Test1C(void); // Font UNO
void Test1D(void); // Font MEGA
void Test2(void); // Fill, clear ,  invert, display
void Test3(void); // Lines
void Test4(void); // Rectangles
void Test5(void); // Circles
void Test6(void); // Triangles
void Test7(void); // Image

// ********* Main Loop ********** 
void main(void)
{
    Setup();
    while (1)
    {
        Test1A(); // All fonts
        SSD1306_UpdateDisplay();
        LED_RE0_Toggle(); 
        __delay_ms(TESTDELAY);
        SSD1306_FillBuffer(0x00); 
        
        Test1B(); // Pico fonts
        SSD1306_UpdateDisplay();
        LED_RE0_Toggle(); 
        __delay_ms(TESTDELAY);
        SSD1306_FillBuffer(0x00); 
        
        Test1C(); // UNO fonts
        SSD1306_UpdateDisplay();
        LED_RE0_Toggle(); 
        __delay_ms(TESTDELAY);
        SSD1306_FillBuffer(0x00); 
        
        Test1D(); // MEGA fonts
        SSD1306_UpdateDisplay();
        LED_RE0_Toggle(); 
        __delay_ms(TESTDELAY);
        SSD1306_FillBuffer(0x00); 
        
        Test2(); // display
         SSD1306_UpdateDisplay();
         LED_RE0_Toggle(); 
        __delay_ms(TESTDELAYONE);
        
         Test3(); // lines
         SSD1306_UpdateDisplay();
         LED_RE0_Toggle(); 
         __delay_ms(TESTDELAY);
         SSD1306_FillBuffer(0x00);
         
         Test4(); // rect
         LED_RE0_Toggle(); 
         
         Test5(); // triangles
         LED_RE0_Toggle(); 
         
        Test6(); // circles 
         SSD1306_UpdateDisplay(); // update for test 4-6 shapes 
         LED_RE0_Toggle(); 
         __delay_ms(TESTDELAY);
         SSD1306_FillBuffer(0x00); 
         
         Test7(); // Image
         SSD1306_UpdateDisplay();
         LED_RE0_Toggle(); 
         __delay_ms(TESTDELAY);
         SSD1306_FillBuffer(0x00);
         
        // End 
        SSD1306_SetFont(MEGA);
        SSD1306_Write_Text( 0, 0, "GAMEOVER");
        SSD1306_UpdateDisplay();
         while(1){
             __nop(); // test over
         }
    }
}
// *********  End of Main Loop ************


// *********  Function Space ************

// Function to Initialize the PIC device
void Setup(void)
{
    SYSTEM_Initialize();
    LED_RE0_SetHigh(); 
    SSD1306_Init();
    __delay_ms(INITDELAY);
    SSD1306_FillBuffer(0x00);
    SSD1306_UpdateDisplay();
    LED_RE0_SetLow(); 
}

void Test1A(void)
{
    SSD1306_SetFont(PICO);
    SSD1306_Write_Text( 0, 0, "PICO");
    SSD1306_Write_Text( 0, 8, "12345678901234567890123456789012");
    SSD1306_SetFont(UNO);
    SSD1306_Write_Text( 0, 15, "UNO");
    SSD1306_Write_Text( 0, 24, "123456789012345678901");
    SSD1306_SetFont(MEGA);
    SSD1306_Write_Text( 0, 33, "MEGA");
    SSD1306_Write_Text( 0, 49, "12345678");  
}

void Test1B(void)
{
    SSD1306_SetFont(PICO);
    SSD1306_Write_Text( 0, 0, "ABCDEFGHIJKLOMNPQRSTUVWXYZ");
    SSD1306_Write_Text( 0, 7, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 14, "abcdefghijklmnopqrstuvwxyz");
    SSD1306_Write_Text( 0, 21, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 28, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 35, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 42, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 49, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 56, "12345678901234567890123456789012");
}

void Test1C(void)
{
    SSD1306_SetFont(UNO);
    SSD1306_Write_Text( 0, 0, "123456789012345678901");
    SSD1306_Write_Text( 0, 9, "abcdefghijklmnopqrstu");
    SSD1306_Write_Text( 0, 18, "ABCDEFGHIJKLMNOPQRSTU");
    SSD1306_Write_Text( 0, 27, "123456789012345678901");
    SSD1306_Write_Text( 0, 36, "123456789012345678901");
    SSD1306_Write_Text( 0, 45, "123456789012345678901");
    SSD1306_Write_Text( 0, 54, "123456789012345678901");
}

void Test1D(void)
{
    SSD1306_SetFont(MEGA);
    SSD1306_Write_Text( 0, 0,  "12345678");
    SSD1306_Write_Text( 0, 16, "ABCDEFGH");
    SSD1306_Write_Text( 0, 32, "abcdefgh");
    SSD1306_Write_Text( 0, 48, "12345678");
}


void Test2(void)
{
    SSD1306_FillBuffer(0xFF);
     SSD1306_UpdateDisplay();
    __delay_ms(TESTDELAY);
    SSD1306_FillBuffer(0x00);
    // draw some pixel to watch invert
     for (uint8_t i = 0 ; i<30 ; i++) SSD1306_SetPixel( 10 , i, WHITE ); 
     SSD1306_UpdateDisplay();
    __delay_ms(TESTDELAY);
    SSD1306_InvertDisplay(true);
     SSD1306_UpdateDisplay();
    __delay_ms(TESTDELAY);
    SSD1306_InvertDisplay(false);
     SSD1306_UpdateDisplay();
    __delay_ms(TESTDELAY);
    SSD1306_FillBuffer(0x00);
}


void Test3(void)
{
    SSD1306_Line( 10, 10, 30, 30, WHITE);
    SSD1306_V_Line( 40, 60, 5, WHITE);
    SSD1306_H_Line( 10, 100, 62, WHITE);  
}

void Test4(void)
{
   SSD1306_Rectangle( 5, 5, 20, 20, WHITE);
   SSD1306_FillRectangle( 25, 25, 40, 40, WHITE);
}



void Test5(void)
{
    SSD1306_Triangle( 50, 50, 100, 50, 50, 20, WHITE);
}


void Test6(void)
{
    SSD1306_Circle( 100, 30, 10 , WHITE);
}

void Test7(void)
{
    SSD1306_BITMAP(myimage);
}