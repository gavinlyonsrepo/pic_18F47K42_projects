/*
* Project Name: Nokia  5110 Graphic library for PIC  microcontroller
* File: main.c
* Description: Main  File
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created: July 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

/* -------- libraries -------- */
#include "mcc_generated_files/mcc.h"
#include "NOKIA.h"   // include PCD8544 controller driver source code (Nokia 5110 LCD driver)
#include "GRAPHICS.h"  // include graphics library source code


/* ----------- Defines -----------*/
#define TESTDELAY 2000 // mS
#define INITDELAY 2000 // mS
#define CONTRAST  0x32 // 0x30 to 0x3F possible values
#define LINEDRAWDELAY 250 // mS

// needed for bitmap tests
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define FLAKE_HEIGHT 16
#define FLAKE_WIDTH  16


/*-----------Globals---------*/
const uint8_t Flake_bmp[] =
{  0b00000000,0b00000000,
  0b00000000,0b00000000,
  0b00000001,0b10000000,
  0b00000000,0b00000000,
  0b00001101,0b00100000,
  0b00001111,0b01100000,
  0b00000011,0b10000000,
  0b00000001,0b10000000,
  0b00001011,0b11010000,
  0b00000101,0b00100000,
  0b00000001,0b00110000,
  0b00000001,0b00000000,
  0b00000001,0b10000000,
  0b00000000,0b00000000,
  0b00000000,0b00000000,
  0b00000000,0b00000000};


/* -------- Function prototypes -------- */
void Setup(void);
void DisplayData(void);
void DisplayDataOne(void);
void testdrawcircle(void);
void testdrawline(void);
void testdrawchar(void);
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h);
void testfillrect(void);
void testdrawtriangle(void);
void testfilltriangle(void);
void testdrawroundrect(void);
void testfillroundrect(void);
void testdrawrect(void);

/* ------------ Main application --------------  */
void main(void)
{
	Setup();
	while (1)
	{
		DisplayData();
        //DisplayDataOne(); // sleep test comment in to test
	}
}
/* ------------------ End of main ------------ */

void DisplayDataOne(void)
{
  display_clear();
  LED_STATUS_RA0_SetLow();
  testdrawchar();
  display();
   __delay_ms(5000);
   LCDenableSleep();
  __delay_ms(5000);
  LCDdisableSleep();
  
}

// Initialize the device
void  Setup(void)
{
	SYSTEM_Initialize();
	//INTERRUPT_GlobalInterruptEnable();
	//INTERRUPT_GlobalInterruptDisable();
	LCD_begin();
	display_setContrast(CONTRAST);
	display(); // show splashscreen
    __delay_ms(INITDELAY);
	display_clear();   // clears the screen and buffer
	LED_STATUS_RA0_SetHigh();
}

// Run through a series of tests showcasing the libraries graphic's methods
void DisplayData(void)
{
  /* Tests List
  1. Draw single Pixel
  1a. Fill screen 
  2. Draw lines
  3. Draw rectangles 
  4. Draw multiple rectangles
  5. Draw multiple circles
  6. Draw a circle, 10 pixel radius
  7. Draw a rounded rectangle 
  8. Fill a rounded rectangle 
  9. Draw a triangle 
  10. Fill a triangle 
  11. Draw the first ~12 characters in the font
  12. Text display tests
  13. Rotation example
  14. Miniature bitmap display
  15. Invert the display
  16. Draw a bitmap icon and animate movement
  */
  
  // draw a single pixel
  display_drawPixel(10, 10, BLACK);
  display();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // fill screen 
  fillScreen();
  __delay_ms(TESTDELAY);
  display_clear();
  
  // draw many lines
  testdrawline();
  display();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // draw rectangles
  testdrawrect();
  display();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // draw multiple rectangles
  testfillrect();
  display();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // draw mulitple circles
  testdrawcircle();
  display();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // draw a circle, 10 pixel radius
  display_fillCircle(display_width/2, display_height/2, 10, BLACK);
  display();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // Draw a rounded rectangle 
  testdrawroundrect();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // Fill a rounded rectangle 
  testfillroundrect();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // Draw a triangle 
  testdrawtriangle();
  __delay_ms(TESTDELAY);
  display_clear();
  
  // Fill a triangle 
  testfilltriangle();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // draw the first ~12 characters in the font
  testdrawchar();
  display();
  __delay_ms(TESTDELAY);
  display_clear();
 
  // text display tests
  display_setTextSize(1);
  display_setTextColor(BLACK, WHITE);
  display_setCursor(0, 0);
  display_puts("Hello, world!\r\n");
  display_setTextColor(WHITE, BLACK); // 'inverted' text
  display_printf("%4.2f\r\n", 3.141592);
  display_setTextSize(2);
  display_setTextColor(BLACK, WHITE);
  display_printf("0x%LX\r\n", 0xDEADBEEF);
  display();
  __delay_ms(TESTDELAY);
 
  // rotation example
  display_clear();
  display_setRotation(1);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
  display_setTextSize(1);
  display_setTextColor(BLACK, WHITE);
  display_setCursor(0, 0);
  display_puts("Rotation\r\n");
  display_setTextSize(2);
  display_puts("Example!\r\n");
  display();
  __delay_ms(TESTDELAY);
 
  // revert back to no rotation
  display_setRotation(0);
 
  // miniature bitmap display
  display_clear();
  display_drawBitmapV2(30, 16,  Flake_bmp, 16, 16, BLACK);
  display();
 
  // invert the display
  display_invert(true);
  __delay_ms(1000);
  display_invert(false);
  __delay_ms(1000);
  
  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(Flake_bmp, FLAKE_WIDTH, FLAKE_HEIGHT);
}

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  static uint8_t icons[NUMFLAKES][3], f, x_pos, y_pos;
 
  // initialize
  for (f=0; f< NUMFLAKES; f++) {
	icons[f][XPOS] = rand();
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = (rand() % 5) + 1;
  }
  icons[0][XPOS] = 30;
 
  while (1) {
	uint8_t f;
	// draw each icon
	for (f=0; f< NUMFLAKES; f++) {
	  x_pos = icons[f][XPOS];
	  y_pos = icons[f][YPOS];
	  display_drawBitmapV2(x_pos, y_pos, bitmap, w, h, BLACK);
	}
	display();
	__delay_ms(200);
 
	// then erase it + move it
	for (f=0; f< NUMFLAKES; f++) {
	  x_pos = icons[f][XPOS];
	  y_pos = icons[f][YPOS];
	  display_drawBitmapV2(x_pos, y_pos, bitmap, w, h, WHITE);
	  // move it
	  icons[f][YPOS] += icons[f][DELTAY];
	  // if its gone, reinit
	  if (icons[f][YPOS] > display_height) {
		icons[f][XPOS] = rand();
		icons[f][YPOS] = 0;
		icons[f][DELTAY] = (rand() % 5) + 1;
	  }
	}
   }
}
 
void testdrawchar(void) {
  char i;
  display_setTextSize(1);
  display_setTextColor(BLACK, WHITE);
  display_setCursor(0, 0);
 
  for (i=0; i < 168; i++) {
	if (i == '\n' || i == '\r') continue;
	display_putc(i);
  }
  display();
}
 
void testdrawcircle(void) {
  char i;
  for (i=0; i<display_height; i+=2) {
	display_drawCircle(display_width/2, display_height/2, i, BLACK);
	display();
  }
}
 
void testfillrect(void) {
  char i, color = 1;
  for (i=0; i<display_height/2; i+=3) {
	// alternate colors
	display_fillRect(i, i, display_width-i*2, display_height-i*2, color%2);
	display();
	color++;
  }
}
 
void testdrawtriangle(void) {
  char i;
  for (i=0; i<min(display_width,display_height)/2; i+=5) {
	display_drawTriangle(display_width/2, display_height/2-i,
	display_width/2-i, display_height/2+i,
	 display_width/2+i, display_height/2+i, BLACK);
	display();
  }
}
 
void testfilltriangle(void) {
  short i, color = BLACK;
  for (i=min(display_width,display_height)/2; i>0; i-=5) {
	display_fillTriangle(display_width/2, display_height/2-i,
					 display_width/2-i, display_height/2+i,
					 display_width/2+i, display_height/2+i, color);
	if (color == WHITE) color = BLACK;
	else color = WHITE;
	display();
  }
}
 
void testdrawroundrect(void) {
  char i;
  for (i=0; i<display_height/2-2; i+=2) {
	display_drawRoundRect(i, i, display_width-2*i, display_height-2*i, display_height/4, BLACK);
	display();
  }
}
 
void testfillroundrect(void) {
  char i, color = BLACK;
  for (i=0; i<display_height/2-2; i+=2) {
	display_fillRoundRect(i, i, display_width-2*i, display_height-2*i, display_height/4, color);
	if (color == WHITE) color = BLACK;
	else color = WHITE;
	display();
  }
}
 
void testdrawrect(void) {
  char i;
  for (i=0; i<display_height/2; i+=2) {
	display_drawRect(i, i, display_width-2*i, display_height-2*i, BLACK);
	display();
  }
}
 
void testdrawline(void) {
  short i;
  for (i=0; i<display_width; i+=4) {
	display_drawLine(0, 0, i, display_height-1, BLACK);
	display();
  }
  for (i=0; i<display_height; i+=4) {
	display_drawLine(0, 0, display_width-1, i, BLACK);
	display();
  }
  __delay_ms(LINEDRAWDELAY);
 
  display_clear();
  for (i=0; i<display_width; i+=4) {
	display_drawLine(0, display_height-1, i, 0, BLACK);
	display();
  }
  for (i=display_height-1; i>=0; i-=4) {
	display_drawLine(0, display_height-1, display_width-1, i, BLACK);
	display();
  }
  __delay_ms(LINEDRAWDELAY);
 
  display_clear();
  for (i=display_width-1; i>=0; i-=4) {
	display_drawLine(display_width-1, display_height-1, i, 0, BLACK);
	display();
  }
  for (i=display_height-1; i>=0; i-=4) {
	display_drawLine(display_width-1, display_height-1, 0, i, BLACK);
	display();
  }
  __delay_ms(LINEDRAWDELAY);
 
  display_clear();
  for (i=0; i<display_height; i+=4) {
	display_drawLine(display_width-1, 0, 0, i, BLACK);
	display();
  }
  for (i=0; i<display_width; i+=4) {
	display_drawLine(display_width-1, 0, i, display_height-1, BLACK);
	display();
  }
  __delay_ms(LINEDRAWDELAY);
}
/*----------------------- End of File ---------------------------*/
