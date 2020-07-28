

#include "mcc_generated_files/mcc.h"
#include "NOKIA5110_TEXT.h"

#define inverse  false
#define contrast 0xB1 // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
#define bias 0x13 // LCD bias mode 1:48: Try 0x13 or 0x14
#define FontNumber 1 //1-6, 1 is default ,  Comment in  defines at top of  NOKIA5110_TEXT.h if using non default
#define TEST_DELAY 2000

void TestLoop(void);
void TestTwoLoop(void); // For testing all  fonts  Comment in  defines at top of  NOKIA5110_TEXT.h if using non default
void Setup(void);

/* --------- Main application --------------- */
void main(void)
{
    Setup();
    while (1)
    {
        __delay_ms(TEST_DELAY);
        LED_STATUS_RA0_Toggle();
        TestLoop();
        LED_STATUS_RA0_Toggle();
        TestTwoLoop();
    }
}

// Text and  function tests
void TestLoop(void)
{
  bool drawtext = true; //enable  TEST 1
  bool clearline = true; //enable  TEST 2
  bool sleepmodetest = true;// enable TEST 3
  bool pixeltest = true; // enable TEST 4 5 6
    //TEST 1 writing text to blocks
  if (drawtext == true)
  {
    __delay_ms(TEST_DELAY);
    LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
    LCDString("Block 0"); //print to block 0 (0-5 blocks or row bytes)
    __delay_ms(TEST_DELAY);
    LCDgotoXY(2, 1); // (go to (X , Y) (0-84 columns, 0-5 blocks)
    LCDString("Block 1"); //print to block 1 indented by two
    __delay_ms(TEST_DELAY);
    LCDgotoXY(4, 2); // (go to (X , Y) (0-84 columns, 0-5 blocks)
    LCDString("Block 2"); //print to block 2   indented by four
    __delay_ms(TEST_DELAY);
    LCDgotoXY(6, 3); // (go to (X , Y) (0-84 columns, 0-5 blocks)
    LCDString("Block 3"); //print to block 3  indented by six
    __delay_ms(TEST_DELAY);
    LCDgotoXY(8, 4);
    LCDString("Block 4"); //print to block 4 indented by 8 col
    __delay_ms(TEST_DELAY);
    LCDgotoXY(10, 5);
    LCDString("Block 5"); //print to block 5 indented by 10 col
    __delay_ms(TEST_DELAY);
  }


  // TEST 2 clearing by  blocks
  if (clearline == true)
  {
    LCDClearBlock(0);  //clear line/block 0
    __delay_ms(TEST_DELAY);
    LCDClearBlock(5); //clear line/block 5
    __delay_ms(TEST_DELAY);
  }

  //TEST 3 sleep mode
  if (sleepmodetest  ==  true)
  {
    LCDenableSleep(); //goto sleep
    __delay_ms(TEST_DELAY);
    __delay_ms(TEST_DELAY);
    LCDdisableSleep(); //wake up
    __delay_ms(TEST_DELAY);
  }

  //whole screen clear
  __delay_ms(TEST_DELAY);
  LCDClear();
  __delay_ms(TEST_DELAY);


  if (pixeltest  ==  true)
  {
    // TEST 4 Draw some pixel
    LCDSetPixel(5, 10);
    __delay_ms(TEST_DELAY);
    LCDSetPixel(40, 22);
    __delay_ms(TEST_DELAY);
    LCDSetPixel(75, 30);
    __delay_ms(TEST_DELAY);
    __delay_ms(TEST_DELAY);

    // TEST 5 Draw a horizontal line with SetPixel across screen at row 10 
    for (uint8_t col = 0 ; col < 83 ; col++)
    {
      LCDSetPixel(col, 8);
    }
    __delay_ms(TEST_DELAY);
    
    // TEST 6 Draw a vertical line in block 2 of one byte at column 3  
    LCDgotoXY(3, 2);
    LCDWrite(LCD_DATA, 0xFF);
    __delay_ms(TEST_DELAY);
  }
  
  //whole screen clear again
  LCDClear();
  __delay_ms(TEST_DELAY);
}

// Differnt fonts tests,  Note  fonts  must be  commented in header file 
void TestTwoLoop() {
   uint8_t fontnumber = 1;  // use Font one
 
  __delay_ms(TEST_DELAY);
  LCDFont(fontnumber); //font 1
  LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  LCDString("1234567890AB"); //print to block 0 
  __delay_ms(TEST_DELAY);
  fontnumber ++;
  LCDFont(fontnumber); // font 2 
  LCDgotoXY(0, 1); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  LCDString("VOLTAGE 2"); //print to block 1
  __delay_ms(TEST_DELAY);
  fontnumber ++;
  LCDFont(fontnumber); //font 3
  LCDgotoXY(0, 2); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  LCDString("ABCDEFGHIJK"); //print to block 2
  __delay_ms(TEST_DELAY);
  fontnumber ++;
  LCDFont(fontnumber); //font 4
  LCDgotoXY(0, 3); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  LCDString("VOLTAGE 5.843"); //print to block 3
  __delay_ms(TEST_DELAY);
  fontnumber ++;
  LCDFont(fontnumber); //font 5
  LCDgotoXY(0, 4); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  LCDString("VOLTAGE"); //print to block 4
  __delay_ms(TEST_DELAY);
  fontnumber ++;
  LCDFont(fontnumber); //font 6
  LCDgotoXY(0, 5); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  LCDString("1234567890123456"); //print to block 5
  __delay_ms(TEST_DELAY);
  fontnumber = 1;
  LCDFont(fontnumber);
  LCDClear();
}
void Setup(void)
{
    SYSTEM_Initialize();
    LCDInit(inverse, contrast, bias); // init the lCD
    LCDClear(); // Clear whole screen
    LCDFont(FontNumber); //
}
/* ------------- End of File -----------  */