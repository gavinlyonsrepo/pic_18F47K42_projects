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
#include "BitmapTestData.h" 

//*************** Defines *************
#define TESTDELAY 5000
#define TESTDELAYONE 1000
#define TESTDELAYTHREE 3000
#define INITDELAY 1000 

// ********* Function prototypes ************
void Setup(void); // Setup
void TestResetScreen(void);

void Test0(void); // Fill screen , fill page
void Test1A(void); // All Fonts
void Test1B(void); // Font Pico
void Test1C(void); // Font UNO
void Test1D(void); // Font MEGA

void Test2(void); // bitmap to buffer
void Test3(void); // Lines + Pixels

void Test4a(void); // Rectangles
void Test4b(void); // Circles
void Test4c(void); // triangles 

void Test5a(void); // Fill Rectangles
void Test5b(void); // Fill Circles
void Test5c(void); // Fill triangles 

void Test6(void); // Round corner Rectangles

void Test7(void); //  bitmap direct to screen

//  (0) FILL screen  
//  (1) Enable and disable Screen (Sleep mode)
//  (2) Contrast screen
//  (3) Invert screen color
//  (4) Scroll Screen
//  (5) Rotate 
void Test8(void); 

void Test9(void); // invert text end tests

// ********* Main Loop ********** 
void main(void)
{
    Setup();
    while (1)
    {
        Test0(); 
        Test1A();      
        Test1B();      
        Test1C();     
        Test1D(); 
        Test2(); 
        Test3();
        Test4a(); 
        Test4b(); 
        Test4c();          
        Test5a(); 
        Test5b(); 
        Test5c();      
        Test6();  
        Test7();    
        Test8();  
        Test9();
    }
}
// *********  End of Main Loop ************


// *********  Function Space ************

// Function to Initialize the PIC device
void Setup(void)
{
    SYSTEM_Initialize();
    SSD1306_Init();
    __delay_ms(INITDELAY);
    SSD1306_FillBuffer(0x00);
    SSD1306_UpdateDisplay();
}

void TestResetScreen(void)
{
    SSD1306_UpdateDisplay(); 
    __delay_ms(TESTDELAY);
    SSD1306_FillBuffer(0x00);    
}

void Test0(void){
    SSD1306_FillScreen(0xFF);
    __delay_ms(TESTDELAYONE);
    SSD1306_FillPage(3, 0x00);
    __delay_ms(TESTDELAYONE);
    SSD1306_FillPage(1, 0x00);
    __delay_ms(TESTDELAYONE);
}

void Test1A(void)
{
#if defined SSD1306_128_64
    SSD1306_SetFont(PICO);
    SSD1306_Write_Text( 0, 0, "PICO");
    SSD1306_Write_Text( 0, 8, "12345678901234567890123456789012");
    SSD1306_SetFont(UNO);
    SSD1306_Write_Text( 0, 15, "UNO");
    SSD1306_Write_Text( 0, 24, "123456789012345678901");
    SSD1306_SetFont(MEGA);
    SSD1306_Write_Text( 0, 33, "MEGA");
    SSD1306_Write_Text( 0, 49, "12345678");  
    TestResetScreen();
#endif 
    
#if defined SSD1306_128_32
    SSD1306_SetFont(PICO);
    SSD1306_Write_Text( 0, 0, "PICO");
    SSD1306_Write_Text( 0, 8, "12345678901234567890123456789012");
    SSD1306_SetFont(UNO);
    SSD1306_Write_Text( 0, 15, "UNO");
    SSD1306_Write_Text( 0, 24, "123456789012345678901");
    TestResetScreen();
    
    SSD1306_SetFont(MEGA);
    SSD1306_Write_Text( 0, 0, "MEGA");
    SSD1306_Write_Text( 0, 17, "12345678"); 
    TestResetScreen();
#endif
}

void Test1B(void)
{

    SSD1306_SetFont(PICO);
    SSD1306_Write_Text( 0, 0, "ABCDEFGHIJKLOMNPQRSTUVWXYZ");
    SSD1306_Write_Text( 0, 7, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 14, "abcdefghijklmnopqrstuvwxyz");
    SSD1306_Write_Text( 0, 21, "12345678901234567890123456789012");
#if defined SSD1306_128_64
    SSD1306_Write_Text( 0, 28, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 35, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 42, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 49, "12345678901234567890123456789012");
    SSD1306_Write_Text( 0, 56, "12345678901234567890123456789012");
#endif
   TestResetScreen();
}

void Test1C(void)
{
    SSD1306_SetFont(UNO);
    SSD1306_Write_Text( 0, 0, "123456789012345678901");
    SSD1306_Write_Text( 0, 9, "abcdefghijklmnopqrstu");
    SSD1306_Write_Text( 0, 18, "ABCDEFGHIJKLMNOPQRSTU");
#if defined SSD1306_128_64
    SSD1306_Write_Text( 0, 27, "123456789012345678901");
    SSD1306_Write_Text( 0, 36, "123456789012345678901");
    SSD1306_Write_Text( 0, 45, "123456789012345678901");
    SSD1306_Write_Text( 0, 54, "123456789012345678901");
#endif
    TestResetScreen();
}

void Test1D(void)
{
    SSD1306_SetFont(MEGA);
    SSD1306_Write_Text( 0, 0,  "12345678");
    SSD1306_Write_Text( 0, 16, "ABCDEFGH");
 #if defined SSD1306_128_64   
    SSD1306_Write_Text( 0, 32, "abcdefgh");
    SSD1306_Write_Text( 0, 48, "12345678");
 #endif
   TestResetScreen();
}


void Test2(void)
{
    SSD1306_BitmapBuffer(10, 10, myImage20x20, 20, 20, WHITE);
    TestResetScreen();
}

void Test3(void)
{
    SSD1306_SetPixel(120, 5, WHITE);
    SSD1306_Line( 5, 5, 90, 15, WHITE);
    SSD1306_V_Line( 0, 20, 30, WHITE);
    SSD1306_H_Line( 10, 20, 50, WHITE);  
    TestResetScreen();
}

void Test4a(void)
{
   SSD1306_Rectangle( 1, 1, 20, 20, WHITE);
}


void Test4b(void)
{
    SSD1306_Triangle( 31, 31, 20, 31, 31, 20, WHITE);
}


void Test4c(void)
{
    SSD1306_Circle( 90, 20, 10 , WHITE);
    TestResetScreen();
}

void Test5a(void)
{
   SSD1306_FillRectangle( 1, 1, 20, 20, WHITE);
}


void Test5b(void)
{
    SSD1306_FillTriangle( 31, 31, 20, 31, 31, 20, WHITE);
}


void Test5c(void)
{
    SSD1306_FillCircle( 90, 20, 10 , WHITE);
    TestResetScreen();
}

void Test6(void)
{
    SSD1306_FillRoundRect(40, 10, 20, 20, 5, WHITE);
    SSD1306_DrawRoundRect(80, 10, 20, 20, 5, WHITE);
    TestResetScreen();
}

void Test7(void)
{
#if defined SSD1306_128_32
    SSD1306_Bitmap(myImage128x32);
#endif
#if defined SSD1306_128_64 
        SSD1306_Bitmap(myImage128x64);
#endif
    TestResetScreen();
}

//  (0) FILL screen  
//  (1) Enable and disable Screen (Sleep mode)
//  (2) Contrast screen
//  (3) Invert screen color
//  (4) Scroll Screen
//  (5) Rotate 
void Test8(void)
{
    SSD1306_SetFont(MEGA);
    
    // test fill
    SSD1306_FillBuffer(0xFF);
    SSD1306_UpdateDisplay();
    __delay_ms(TESTDELAY);
    
     // on and off 
    SSD1306_FillBuffer(0x00);
    SSD1306_Write_Text( 10, 10,  "ON/OFF");
    SSD1306_UpdateDisplay();
    __delay_ms(TESTDELAYTHREE);
    SSD1306_DisplayEnable(0);
     __delay_ms(TESTDELAY);
    SSD1306_DisplayEnable(1);
     __delay_ms(TESTDELAY);
     
    // contrast 
    SSD1306_FillBuffer(0xFF);
    SSD1306_InvertFont(true );
    SSD1306_Write_Text( 0, 0,  "CONTRAST");
    SSD1306_UpdateDisplay();
    SSD1306_Contrast(0x00);
	__delay_ms(TESTDELAYTHREE); //lowest
	SSD1306_Contrast(0x80);
	__delay_ms(TESTDELAYONE); // highest
	SSD1306_Contrast(0xFF);
	__delay_ms(TESTDELAYTHREE);
	SSD1306_Contrast(0x8F);  // back to norm 
	__delay_ms(TESTDELAYONE);
    SSD1306_FillBuffer(0x00);
    
    // Invert  
    
    SSD1306_InvertFont(false);
    SSD1306_Write_Text( 10, 10,  "INVERT");
    __delay_ms(TESTDELAYONE);
    SSD1306_InvertDisplay(true); // invert
    SSD1306_UpdateDisplay();
    __delay_ms(TESTDELAY);
    SSD1306_InvertDisplay(false); // normal
    TestResetScreen();
    
    
   //  Scroll 
    
	 SSD1306_Write_Text( 10, 10,  "SCROLL");
      SSD1306_UpdateDisplay();
    __delay_ms(TESTDELAYONE);

	SSD1306_StartScrollRight(0, 0x0F);
	__delay_ms(TESTDELAYTHREE);
	SSD1306_StopScroll();
	
	SSD1306_StartScrollLeft(0, 0x0F);
	__delay_ms(TESTDELAYTHREE);
	SSD1306_StopScroll();

	SSD1306_StartScrollDiagRight(0, 0x07);
	__delay_ms(TESTDELAYTHREE);
	SSD1306_StopScroll();
 	
	SSD1306_StartScrollDiagLeft(0, 0x07);
	__delay_ms(TESTDELAYTHREE);
	SSD1306_StopScroll(); 
    SSD1306_FillBuffer(0x00);
    
    // Rotate 0-4
    SSD1306_SetFont(UNO);
    SSD1306_setRotation(1);
	SSD1306_Write_Text( 5, 15,  "R1");
	SSD1306_UpdateDisplay();
	__delay_ms(TESTDELAYTHREE);
	
	SSD1306_setRotation(2);
	SSD1306_FillBuffer(0x00);
	SSD1306_Write_Text( 30, 15,  "R2");
	SSD1306_UpdateDisplay();
	__delay_ms(TESTDELAYTHREE);
	
	
	SSD1306_setRotation(3);
	SSD1306_FillBuffer(0x00);
	SSD1306_Write_Text( 5, 15,  "R3");
	SSD1306_UpdateDisplay();
	__delay_ms(TESTDELAYTHREE);
	
	SSD1306_setRotation(0); //default normal 
	SSD1306_FillBuffer(0x00);
	SSD1306_Write_Text(5, 15,  "R0");
	SSD1306_UpdateDisplay();
	__delay_ms(TESTDELAYTHREE);
    SSD1306_FillBuffer(0x00);
}


void Test9(void)
{
       SSD1306_SetFont(MEGA);
       SSD1306_InvertFont( true ); //invert text test
       SSD1306_Write_Text( 0, 0, "TESTOVER");
       SSD1306_UpdateDisplay();
        __delay_ms(TESTDELAY);
       SSD1306_DisplayEnable(0);
       while(1)
       {
             __nop(); // test over
        }
}

// **************** EOF *************