/*
* Project Name: OLED_LM35
* File: OLED.c
* Description: OLED 128X64 SSD1306  I2C library c file
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created Feb 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_PIC18F47K42_projects
*/

#include "mcc_generated_files/mcc.h"
#include "OLED.h"         
#include "font.h"

//Function to Send command byte to OLED, passed byte
void Oled_Command( uint8_t command )
{
  uint8_t data_I2C[2];
  
  data_I2C[0] = SSD1306_COMMAND ; 
  data_I2C[1] = command; 

 
  i2c_writeNBytes(SSD1306_ADDR, data_I2C, 2);
 
}

//Function to Send data byte to OLED, passed byte
void Oled_Data( uint8_t value )
{
  uint8_t data_I2C[2];
  
  data_I2C[0] =SSD1306_DATA_CONTINUE ; 
  data_I2C[1] = value; 
  

  i2c_writeNBytes(SSD1306_ADDR, data_I2C, 2);
 
}

//Function to init OLED
void Oled_Init(void)
{
  Oled_Command( SSD1306_DISPLAY_OFF);
  Oled_Command( SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
  Oled_Command( 0x80);
  Oled_Command( SSD1306_SET_MULTIPLEX_RATIO );
  Oled_Command( SSD1306_LCDHEIGHT - 1 );
  Oled_Command( SSD1306_SET_DISPLAY_OFFSET );
  Oled_Command(0x00);
  Oled_Command( SSD1306_SET_START_LINE|0x00);  // Line: 0
  Oled_Command( SSD1306_CHARGE_PUMP );
  Oled_Command(0x14);
  Oled_Command( SSD1306_MEMORY_ADDR_MODE );
  Oled_Command(0x00);  //Hor Addressing Mode is Used (02 is Ver)
  Oled_Command( SSD1306_SET_SEGMENT_REMAP| 0x01);
  Oled_Command( SSD1306_COM_SCAN_DIR_DEC );
  
  #if defined SSD1306_128_32
  ssd1306_command( SSD1306_SET_COM_PINS );
  ssd1306_command( 0x02 );
  ssd1306_command( SSD1306_SET_CONTRAST_CONTROL );
  ssd1306_command(0x8F);

#elif defined SSD1306_128_64
  Oled_Command( SSD1306_SET_COM_PINS );
  Oled_Command( 0x12 );
  Oled_Command( SSD1306_SET_CONTRAST_CONTROL );
  Oled_Command(0xCF);   // ssd1306_command(0x9F);  Use with External VCC
#endif

  Oled_Command( SSD1306_SET_PRECHARGE_PERIOD );
  Oled_Command( 0xF1 );
  Oled_Command( SSD1306_SET_VCOM_DESELECT );
  Oled_Command( 0x40 );
  Oled_Command( SSD1306_DISPLAY_ALL_ON_RESUME );
  Oled_Command( SSD1306_NORMAL_DISPLAY );
  Oled_Command( SSD1306_DEACTIVATE_SCROLL );
  Oled_Command( SSD1306_DISPLAY_ON );
}

//function to write a string to OLED, passed string
void Oled_WriteString(char *characters)
{
  while (*characters) Oled_WriteCharacter(*characters++);
}

//function to write a character, passed character
void Oled_WriteCharacter(char character)
{
  Oled_Data(0x00); // padding LHS
  for (uint8_t i=0; i< FONT_ONE_WIDTH; i++) Oled_Data((ASCII[character - ASCII_OFFSET][i]));
  Oled_Data(0x00); // padding RHS 
}

void Oled_SetContrast( uint8_t contrast )
{
  Oled_Command(SSD1306_SET_CONTRAST_CONTROL );
  Oled_Command(contrast);
}

//function to clear OLED by writing to it.
void Oled_Clear(void)
{
  uint16_t i =0;
    // OLED 128* 32 pixels = total pixels -> (4096 bits / 1 byte) = 512 passes.
    // SSD1306_CLEAR_SIZE  = 512 for 128* 32 or 1024  for 128*64
    for (i; i<SSD1306_CLEAR_SIZE ; i++) 
    {
      Oled_Data(0x00); // clear OLED screen  
    }
}

//function to clear OLED  line passed page number
void Oled_ClearLine(uint8_t page_num)
{
    Oled_SelectPage(page_num);
    uint8_t i =0;
  // Clear line of 128 pixels of current page
    for (i; i< SSD1306_LCDWIDTH  ; i++) 
    {
      Oled_Data(0x00); // clear oled screen  
    }
}

// Function to select [page] i.e. row or line number
// 128*32 has page 0-3
// 128* 64 has page 0-7
// Passed page num / byte
// page 0   8 
// page 1   16
// page 2   24
// page 3   32
// page 4   40
// page 5   48
// page 6   56
// page 7   64

void Oled_SelectPage(uint8_t page_num)
{
 uint8_t Result =0xB0 | page_num; // Mask or with zero lets everything thru
 Oled_Command(Result); 
 Oled_Command(SSD1306_SET_LOWER_COLUMN);
 Oled_Command(SSD1306_SET_HIGHER_COLUMN); 
}
