/*
 * Project Name: Nokia 5110 Graphic library for PIC  microcontroller
 * File: main.c
 * Description: Main  File to run a series of tests
 * Complier: xc8 v2.40 compiler
 * PIC: PIC18F47K42
 * IDE:  MPLAB X v6.00
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
 */

/* -------- libraries -------- */
#include "mcc_generated_files/mcc.h"
#include "Nokia5110_PCD8544.h"   // include PCD8544 controller driver source code (Nokia 5110 LCD driver)
#include "Display_Graphics.h"  // include graphics library source code

/* ----------- Defines -----------*/
#define TESTDELAY 5000 // mS
#define INITDELAY 2000 // mS
#define CONTRAST  0x32 // 0x30 to 0x3F possible values
#define LINEDRAWDELAY 250 // mS

/* -------- Function prototypes -------- */
void Setup(void);
void screenreset(void);

void testfonts(void);
void textdrawpixel(void);
void testfillscreen(void);
void testsleepmode(void);
void testdrawcircle(void);
void testFillCircle(void);
void testdrawline(void);
void testdrawchar(void);
void testdrawbitmap(void);
void testfillrect(void);
void testdrawtriangle(void);
void testfilltriangle(void);
void testdrawroundrect(void);
void testfillroundrect(void);
void testdrawrect(void);
void testRotate(void);
void testTextModes(void);
void testInvert(void);

/* ------------ Main application --------------  */
void main(void) {
    Setup();
    while (1) 
    {
        testfonts();     //    0. Test fonts
        textdrawpixel(); //    1. Draw single Pixel
        testfillscreen(); //   1a. Fill screen
        testsleepmode(); //    1c. sleep mode
        testdrawline(); //     2. Draw lines
        testdrawrect(); //     3. Draw rectangles
        testfillrect(); //     4. Draw multiple rectangles
        testdrawcircle(); //   5.  Draw multiple circles
        testFillCircle(); //   6. draw fill  circle
        testdrawroundrect(); // 7. Draw a rounded rectangle
        testfillroundrect(); // 8. Fill a rounded rectangle
        testdrawtriangle(); //  9. Draw a triangle
        testfilltriangle(); //  10. Fill a triangle
        testdrawchar(); //      11. draw the first characters in the ASCII font
        testTextModes(); //     12. Text display tests
        testRotate(); //        13. Rotation example
        testInvert(); //        14. Invert the display
        testdrawbitmap();  //   15. test bitmap        
    } // test while loop
}
/* ------------------ End of main ------------ */

/* ----------------- function space -----------*/

// Initialize the device

void Setup(void) {
    SYSTEM_Initialize();
    //INTERRUPT_GlobalInterruptEnable();
    //INTERRUPT_GlobalInterruptDisable();
    LCDBegin();
    LCDdisplay_setContrast(CONTRAST);
    LCDdisplay(); // show splash screen
    __delay_ms(INITDELAY);
    LCDdisplayClear(); // clears the screen and buffer
    
}

void testInvert(void)
{
    LCDdisplayClear();
    display_setCursor(0, 0);
    display_puts("Invert!\r\n");
    LCDdisplay();
    __delay_ms(2000);
    display_invert(true);
    __delay_ms(2000);
    display_invert(false);
    __delay_ms(2000);
    LCDdisplayClear();
}

void testFillCircle(void)
{
    display_fillCircle(display_width / 2, display_height / 2, 10, LCD_BLACK);
    screenreset();
}

void testsleepmode(void) {
    LCDdisplayClear();
    
    display_setCursor(0, 0);
    display_setTextSize(1);
    display_puts("Sleep Mode!\r\n");
    LCDdisplay();
    __delay_ms(5000);
    LCDenableSleep();
    __delay_ms(5000);
    LCDdisableSleep();

}

void testTextModes(void) {
    // text display tests
    display_setTextSize(1);
    display_setTextColor(LCD_BLACK, LCD_WHITE);
    display_setCursor(0, 0);
    display_puts("Hello world!\r\n");
    display_setTextColor(LCD_WHITE, LCD_BLACK); // 'inverted' text
    display_printf("%4.2f\r\n", 3.141592);
    display_setTextSize(2);
    display_setTextColor(LCD_BLACK, LCD_WHITE);
    display_printf("0x%X\r\n", 0xABCD);
    LCDdisplay();
    __delay_ms(3000);
     LCDdisplayClear();
    display_setCursor(0, 0);
    display_setTextSize(4);
    display_puts("99\r\n");
    display_setTextSize(1);
    display_printf("%d\r\n", 14790);
    LCDdisplay();
    __delay_ms(4000);
}

void testRotate(void) {
    // rotation example
    LCDdisplayClear();
    display_setRotation(1); // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
    display_setTextSize(1);
    display_setTextColor(LCD_BLACK, LCD_WHITE);
    display_setCursor(0, 0);
    display_puts("Rotation\r\n");
    display_setTextSize(2);
    display_puts("Example!\r\n");
    LCDdisplay();
    __delay_ms(TESTDELAY);

    // revert back to no rotation
    display_setRotation(0);
}

void textdrawpixel(void) {
    display_drawPixel(10, 10, LCD_BLACK);
    display_drawPixel(20, 10, LCD_BLACK);
    display_drawPixel(30, 10, LCD_BLACK);
    screenreset();
}

void testdrawbitmap() {
    // snow flake 16x16 horizontally addressed
    const uint8_t Flake_bmp[] =
    {
        0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 
        0x00, 0x00, 0x0D, 0x20, 0x0F, 0x60, 
        0x03, 0x80, 0x01, 0x80, 0x0B, 0xD0,
        0x05, 0x20, 0x01, 0x30, 0x01, 0x00, 
        0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00
    };
    
    // Mobile Signal 16x8px horizontally addressed
    const uint8_t SignalIcon[16] = 
    {
        0xFE,0x02,0x92,0x0A,0x54,0x2A,0x38,0xAA,0x12,0xAA,0x12,0xAA,0x12,0xAA,0x12,0xAA
    };

    // Message icon  16x8px horizontally addressed
    const uint8_t MsgIcon[16] =  
    {
        0x1F,0xF8,0x10,0x08,0x18,0x18,0x14,0x28,0x13,0xC8,0x10,0x08,0x10,0x08,0x1F,0xF8
    };

    // Battery Icon  16x8px  horizontally addressed
    const uint8_t BatIcon[16] = 
    {
        0x0F,0xFE,0x30,0x02,0x26,0xDA,0x26,0xDA,0x26,0xDA,0x26,0xDA,0x30,0x02,0x0F,0xFE
    };

    display_drawBitmap(20, 20, Flake_bmp, 16, 16, LCD_BLACK);
    display_drawBitmap(0, 0, SignalIcon, 16, 8, LCD_BLACK);
    display_drawBitmap(40, 0, MsgIcon, 16, 8, LCD_BLACK);
    display_drawBitmap(68, 0, BatIcon, 16, 8, LCD_BLACK);
    screenreset();
}

void testdrawchar(void) {

    char i;
     const uint8_t mycustomchar[] = {0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00};
    display_setTextSize(1);
    display_setTextColor(LCD_BLACK, LCD_WHITE);
    display_setCursor(0, 0);
    display_setTextWrap(true);
    for (i = 0; i < 83; i++) 
    {
        if (i == '\n' || i == '\r') continue;
        display_putc(i);
    }
    screenreset();
    display_setCursor(0, 0);
    for (i = 84; i < 168; i++) 
    {
        if (i == '\n' || i == '\r') continue;
        display_putc(i);
    }
    screenreset();
    display_setCursor(0, 0);
    for (i = 168; i < 250; i++) 
    {
        if (i == '\n' || i == '\r') continue;
        display_putc(i);
    }
    screenreset();
    __delay_ms(TESTDELAY);
    display_setCursor(0, 0);
    display_customChar(mycustomchar);
    display_setCursor(40, 20);
    display_drawChar(40,20,'A',1,0,1);
    screenreset();
}

void testdrawcircle(void) {
    display_drawCircle(display_width / 2, display_height / 2, 10, LCD_BLACK);
    display_drawCircle(display_width / 2, display_height / 2, 15, LCD_BLACK);
    display_drawCircle(display_width / 2, display_height / 2, 20, LCD_BLACK);
    screenreset();
}

void testfillrect(void) {
    char i, color = 1;
    for (i = 0; i < display_height / 2; i += 3) {
        // alternate colors
        display_fillRect(i, i, display_width - i * 2, display_height - i * 2, color % 2);
        LCDdisplay();
        color++;
    }
    screenreset();
}

void testdrawtriangle(void) {
    char i;
    for (i = 0; i < _min_LCD(display_width, display_height) / 2; i += 5) {
        display_drawTriangle(display_width / 2, display_height / 2 - i,
                display_width / 2 - i, display_height / 2 + i,
                display_width / 2 + i, display_height / 2 + i, LCD_BLACK);
        LCDdisplay();
    }
    __delay_ms(TESTDELAY);
   LCDdisplayClear();
}

void testfilltriangle(void) {
    int16_t i; 
    uint8_t color = LCD_BLACK;
    for (i = _min_LCD(display_width, display_height) / 2; i > 0; i -= 5) {
        display_fillTriangle(display_width / 2, display_height / 2 - i,
                display_width / 2 - i, display_height / 2 + i,
                display_width / 2 + i, display_height / 2 + i, color);
        if (color == LCD_WHITE) color = LCD_BLACK;
        else color = LCD_WHITE;
        LCDdisplay();
    }
    __delay_ms(TESTDELAY);
    LCDdisplayClear();
}

void testdrawroundrect(void) {
    char i;
    for (i = 0; i < display_height / 2 - 2; i += 2) {
        display_drawRoundRect(i, i, display_width - 2 * i, display_height - 2 * i, display_height / 4, LCD_BLACK);
        LCDdisplay();
    }
    __delay_ms(TESTDELAY);
    LCDdisplayClear();
}

void testfillroundrect(void) {
    char i, color = LCD_BLACK;
    for (i = 0; i < display_height / 2 - 2; i += 2) {
        display_fillRoundRect(i, i, display_width - 2 * i, display_height - 2 * i, display_height / 4, color);
        if (color == LCD_WHITE) color = LCD_BLACK;
        else color = LCD_WHITE;
        LCDdisplay();
    }
    __delay_ms(TESTDELAY);
    LCDdisplayClear();
}

void testdrawrect(void) {
    char i;
    for (i = 0; i < display_height / 2; i += 2) {
        display_drawRect(i, i, display_width - 2 * i, display_height - 2 * i, LCD_BLACK);
        LCDdisplay();
    }
}

void testdrawline(void) {
    int16_t i;
    for (i = 0; i < display_width; i += 4) {
        display_drawLine(0, 0, i, display_height - 1, LCD_BLACK);
        LCDdisplay();
    }
    for (i = 0; i < display_height; i += 4) {
        display_drawLine(0, 0, display_width - 1, i, LCD_BLACK);
        LCDdisplay();
    }
    __delay_ms(LINEDRAWDELAY);

    LCDdisplayClear();
    for (i = 0; i < display_width; i += 4) {
        display_drawLine(0, display_height - 1, i, 0, LCD_BLACK);
        LCDdisplay();
    }
    for (i = display_height - 1; i >= 0; i -= 4) {
        display_drawLine(0, display_height - 1, display_width - 1, i, LCD_BLACK);
        LCDdisplay();
    }
    __delay_ms(LINEDRAWDELAY);

    LCDdisplayClear();
    for (i = display_width - 1; i >= 0; i -= 4) {
        display_drawLine(display_width - 1, display_height - 1, i, 0, LCD_BLACK);
        LCDdisplay();
    }
    for (i = display_height - 1; i >= 0; i -= 4) {
        display_drawLine(display_width - 1, display_height - 1, 0, i, LCD_BLACK);
        LCDdisplay();
    }
    __delay_ms(LINEDRAWDELAY);

    LCDdisplayClear();
    for (i = 0; i < display_height; i += 4) {
        display_drawLine(display_width - 1, 0, 0, i, LCD_BLACK);
        LCDdisplay();
    }
    for (i = 0; i < display_width; i += 4) {
        display_drawLine(display_width - 1, 0, i, display_height - 1, LCD_BLACK);
        LCDdisplay();
    }
    __delay_ms(LINEDRAWDELAY);
    screenreset();
}

void testfillscreen(void){
    LCDfillScreen();
    __delay_ms(TESTDELAY);
    LCDdisplayClear();
}

void screenreset(void) {
    LCDdisplay();
    __delay_ms(TESTDELAY);
    LCDdisplayClear();
}

void testfonts(void)
{
    display_setTextSize(1);
    display_setTextColor(LCD_BLACK, LCD_WHITE);
    
    // Font 1 default
    display_setCursor(0, 0);
    display_Font(LCDFontType_Default);
    display_puts("Hello world!\r\n");  
    // Font 2 thick
    display_setCursor(0, 9);
    display_Font(LCDFontType_Thick);
    display_puts("123THICK!");
    // Font 3 homespun
    display_setCursor(0, 18);
    display_Font(LCDFontType_HomeSpun);
    display_puts("123 Home");
    // Font 4 seven segment
    display_setCursor(0, 26);
    display_Font(LCDFontType_SevenSeg);
    display_puts("192 Seven");
    // Font 5 wide
    display_setCursor(0, 34);
    display_Font(LCDFontType_Wide);
    display_puts("196 WIDE");
    // Font 6 tiny 
    display_setCursor(0, 42);
    display_Font(LCDFontType_Tiny);
    display_puts("196 tiny");
    screenreset();
     
    // size 2
    display_setTextSize(2);
    display_setCursor(0, 0);
    display_Font(LCDFontType_Thick);
    display_puts("THICK");
    display_setCursor(0, 24);
    display_Font(LCDFontType_SevenSeg);
    display_puts("1234");
    screenreset();
    display_Font(LCDFontType_Default);
}
/*----------------------- End of File ---------------------------*/
