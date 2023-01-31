/*
* Project Name: Nokia  5110 Graphic library for PIC  micro-controller
* File: Display_Graphics.c
* Description: Source file for  graphics libraries to draw shapes lines etc
* Author: Gavin Lyons.
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#include "Display_Graphics.h"

/*----------- Variables ---------*/

#define _swap_int16_t_LCD(a, b) { int16_t t = a; a = b; b = t; }


int16_t
  cursor_x = 0,          ///< x location to start print()ing text
  cursor_y = 0;          ///< y location to start print()ing text
uint8_t
  textcolor = 0xFF,    ///< 16-bit background color for print()
  textbgcolor = 0xFF;  ///< 16-bit text color for print()
uint8_t
  textsize = 1;          ///< Desired magnification of text to print()
bool
  wrap = true;           ///< If set, 'wrap' text at right edge of display

uint8_t _FontNumber = 1;
uint8_t _CurrentFontWidth = 5;
uint8_t _CurrentFontoffset = 0x00;

/*
    Name:         writeLine
    Function Desc:   Write a line.  
    Param1:    x0  Start point x coordinate
    Param2:    y0  Start point y coordinate
    Param3:    x1  End point x coordinate
    Param4:    y1  End point y coordinate
    Param5:    color 
*/
void DisplayWriteLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color) {
    bool steep = abs((int16_t)(y1 - y0)) > abs((int16_t)(x1 - x0));
    int16_t dx, dy, err, ystep;
    if (steep) {
        _swap_int16_t_LCD(x0, y0);
        _swap_int16_t_LCD(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t_LCD(x0, x1);
        _swap_int16_t_LCD(y0, y1);
    }

    dx = x1 - x0;
    dy = abs((int16_t)(y1 - y0));

    err = dx / 2;
    

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            display_drawPixel(y0, x0, color);
        } else {
            display_drawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}


/*
   Function Desc:   Draw a line
    Param1:    x0  Start point x coordinate
    Param2:    y0  Start point y coordinate
    Param3:    x1  End point x coordinate
    Param4:    y1  End point y coordinate
    Param5:    color 
*/
void display_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color) {
    if(x0 == x1){
        if(y0 > y1) _swap_int16_t_LCD(y0, y1);
        display_drawVLine(x0, y0, y1 - y0 + 1, color);
    } else if(y0 == y1){
        if(x0 > x1) _swap_int16_t_LCD(x0, x1);
        display_drawHLine(x0, y0, x1 - x0 + 1, color);
    } else {
        DisplayWriteLine(x0, y0, x1, y1, color);
    }
}


/*
   Function Desc:   Draw a circle outline
    Param1:    x0   Center-point x coordinate
    Param2:    y0   Center-point y coordinate
    Param3:    r   Radius of circle
    Param4:    color
*/
void display_drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    display_drawPixel(x0  , y0+r, color);
    display_drawPixel(x0  , y0-r, color);
    display_drawPixel(x0+r, y0  , color);
    display_drawPixel(x0-r, y0  , color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        display_drawPixel(x0 + x, y0 + y, color);
        display_drawPixel(x0 - x, y0 + y, color);
        display_drawPixel(x0 + x, y0 - y, color);
        display_drawPixel(x0 - x, y0 - y, color);
        display_drawPixel(x0 + y, y0 + x, color);
        display_drawPixel(x0 - y, y0 + x, color);
        display_drawPixel(x0 + y, y0 - x, color);
        display_drawPixel(x0 - y, y0 - x, color);
    }
}


/*
    Function Desc:   Quarter-circle drawer, used to do circles and roundrects
    Param1:    x0   Center-point x coordinate
    Param2:    y0   Center-point y coordinate
    Param3:    r   Radius of circle
    Param4:    cornername  Mask bit #1 or bit #2 to indicate which quarters of the circle we're doing
    Param5:    color
*/

void display_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
            display_drawPixel(x0 + x, y0 + y, color);
            display_drawPixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
            display_drawPixel(x0 + x, y0 - y, color);
            display_drawPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            display_drawPixel(x0 - y, y0 + x, color);
            display_drawPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            display_drawPixel(x0 - y, y0 - x, color);
            display_drawPixel(x0 - x, y0 - y, color);
        }
    }
}


/*
   Function Desc:   Draw a circle with filled color
    Param1:    x0   Center-point x coordinate
    Param2:    y0   Center-point y coordinate
    Param3:    r   Radius of circle
    Param4:    color 
*/
void display_fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color) {
    display_drawVLine(x0, y0-r, 2*r+1, color);
    display_fillCircleHelper(x0, y0, r, 3, 0, color);
}



/*
    Function Desc: Quarter-circle drawer with fill, used for circles and roundrects
    Param1:  x0       Center-point x coordinate
    Param2:  y0       Center-point y coordinate
    Param3:  r        Radius of circle
    Param4:  corners  Mask bits indicating which quarters we're doing
    Param5:  delta    Offset from center-point, used for round-rects
    Param6:  color    
*/
void display_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint8_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
    int16_t px    = x;
    int16_t py    = y;

    delta++; 

    while(x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if(x < (y + 1)) {
            if(corners & 1) display_drawVLine(x0+x, y0-y, 2*y+delta, color);
            if(corners & 2) display_drawVLine(x0-x, y0-y, 2*y+delta, color);
        }
        if(y != py) {
            if(corners & 1) display_drawVLine(x0+py, y0-px, 2*px+delta, color);
            if(corners & 2) display_drawVLine(x0-py, y0-px, 2*px+delta, color);
            py = y;
        }
        px = x;
    }
}


/*
   Function Desc:  Draw a rectangle with no fill color
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    w   Width in pixels
    Param4:    h   Height in pixels
    Param5:    color
*/
void display_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color) {
    display_drawHLine(x, y, w, color);
    display_drawHLine(x, y+h-1, w, color);
    display_drawVLine(x, y, h, color);
    display_drawVLine(x+w-1, y, h, color);
}


/*
   Function Desc:  Draw a rounded rectangle with no fill color
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    w   Width in pixels
    Param4:    h   Height in pixels
    Param5:    r   Radius of corner rounding
    Param6:    color 
*/
void display_drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint8_t color) {
    int16_t max_radius = ((w < h) ? w : h) / 2; 
    if(r > max_radius) r = max_radius;
    display_drawHLine(x+r  , y    , w-2*r, color); 
    display_drawHLine(x+r  , y+h-1, w-2*r, color); 
    display_drawVLine(x    , y+r  , h-2*r, color); 
    display_drawVLine(x+w-1, y+r  , h-2*r, color); 
    display_drawCircleHelper(x+r    , y+r    , r, 1, color);
    display_drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
    display_drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
    display_drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}


/*
   Function Desc:  Draw a rounded rectangle with fill color
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    w   Width in pixels
    Param4:    h   Height in pixels
    Param5:    r   Radius of corner rounding
    Param6:    color 
*/
void display_fillRoundRect(int16_t x, int16_t y, int16_t w,
  int16_t h, int16_t r, uint8_t color) {
    int16_t max_radius = ((w < h) ? w : h) / 2; 
    if(r > max_radius) r = max_radius;
    display_fillRect(x+r, y, w-2*r, h, color);
    display_fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    display_fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}


/*
   Function Desc:  Draw a triangle with no fill color
    Param1:    x0  Vertex #0 x coordinate
    Param2:    y0  Vertex #0 y coordinate
    Param3:    x1  Vertex #1 x coordinate
    Param4:    y1  Vertex #1 y coordinate
    Param5:    x2  Vertex #2 x coordinate
    Param6:    y2  Vertex #2 y coordinate
    Param7:    color
*/
void display_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint8_t color) {
    display_drawLine(x0, y0, x1, y1, color);
    display_drawLine(x1, y1, x2, y2, color);
    display_drawLine(x2, y2, x0, y0, color);
}

/*
   Function Desc:    Draw a triangle with color-fill
    Param1:    x0  Vertex #0 x coordinate
    Param2:    y0  Vertex #0 y coordinate
    Param3:    x1  Vertex #1 x coordinate
    Param4:    y1  Vertex #1 y coordinate
    Param5:    x2  Vertex #2 x coordinate
    Param6:    y2  Vertex #2 y coordinate
    Param7:    color 
*/
void display_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint8_t color) {
    int16_t a, b, y, last, dx01, dy01, dx02, dy02, dx12, dy12;
    int32_t sa   = 0;
    int32_t sb   = 0;

    if (y0 > y1) {
        _swap_int16_t_LCD(y0, y1); _swap_int16_t_LCD(x0, x1);
    }
    if (y1 > y2) {
        _swap_int16_t_LCD(y2, y1); _swap_int16_t_LCD(x2, x1);
    }
    if (y0 > y1) {
        _swap_int16_t_LCD(y0, y1); _swap_int16_t_LCD(x0, x1);
    }

    if(y0 == y2) { 
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        display_drawHLine(a, y0, b-a+1, color);
        return;
    }
    
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    if(y1 == y2) last = y1;  
    else         last = y1-1; 

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;

        if(a > b) _swap_int16_t_LCD(a,b);
        display_drawHLine(a, y, b-a+1, color);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;

        if(a > b) _swap_int16_t_LCD(a,b);
        display_drawHLine(a, y, b-a+1, color);
    }
}


/*
    Function Desc: Print one byte/character of data
    Param1:  c  The 8-bit ascii character to write
*/
void display_putc(char c) {
  uint8_t i, j;
  uint8_t line;
  if (c == ' ' && cursor_x == 0 && wrap)
    return;
  if(c == '\r') {
    cursor_x = 0;
    return;
  }
  if(c == '\n') {
    cursor_y += textsize * 8;
    return;
  }

  for(i = 0; i < _CurrentFontWidth; i++ ) {
      switch(_FontNumber)
      {
          case LCDFontType_Default:
          #ifdef NOKIA5110_FONT_Default
                line = pFontDefaultptr[c - _CurrentFontoffset][i];
          #endif 
          break;
          case LCDFontType_Thick:
          #ifdef NOKIA5110_FONT_Thick
                line = pFontThickptr[c - _CurrentFontoffset][i];
          #endif
          break;
          case LCDFontType_HomeSpun:
          #ifdef NOKIA5110_FONT_HomeSpun
                line = pFontHomeSpunptr[c - _CurrentFontoffset][i];
          #endif
          break;
          case LCDFontType_SevenSeg:
          #ifdef NOKIA5110_FONT_SevenSeg
                line = pFontSevenSegptr[c - _CurrentFontoffset][i];
          #endif
          break;
          case LCDFontType_Wide:
          #ifdef NOKIA5110_FONT_Wide
                line = pFontWideptr[c - _CurrentFontoffset][i];
          #endif
          break;
          case LCDFontType_Tiny:
          #ifdef NOKIA5110_FONT_Tiny
                line = pFontTinyptr[c - _CurrentFontoffset][i];
          #endif
          break;
      }


    for(j = 0; j < 8; j++, line >>= 1) {
      if(line & 1) {
        if(textsize == 1)
          display_drawPixel(cursor_x + i, cursor_y + j, textcolor);
        else
          display_fillRect(cursor_x + i * textsize, cursor_y + j * textsize, textsize, textsize, textcolor);
      } 
      else 
        if(textbgcolor != textcolor) {
          if(textsize == 1)
            display_drawPixel(cursor_x + i, cursor_y + j, textbgcolor);
          else
            display_fillRect(cursor_x + i * textsize, cursor_y + j * textsize, textsize, textsize, textbgcolor);
        }
    }
  }

  if(textbgcolor != textcolor) { 
    if(textsize == 1)  display_drawVLine(cursor_x +  _CurrentFontWidth, cursor_y, 8, textbgcolor);
    else               display_fillRect(cursor_x +  _CurrentFontWidth * textsize, cursor_y, textsize, 8 * textsize, textbgcolor);
  }

  cursor_x += textsize *  (_CurrentFontWidth+1);

  if( cursor_x > ((int16_t)display_width + textsize * (_CurrentFontWidth+1)) )
    cursor_x = display_width;

  if (wrap && (cursor_x + (textsize * _CurrentFontWidth)) > display_width)
  {
    cursor_x = 0;
    cursor_y += textsize * 8;
    if( cursor_y > ((int16_t)display_height + textsize * 8) )
      cursor_y = display_height;
  }
}

/* 
  Desc: prints a string 
  Param1: Pointer to a string of ASCII bytes
*/
void display_puts(char *s) {
  while(*s)
    display_putc(*s++);
}

/* 
  Desc: print custom char  (dimension: 7x5 or 8x5 pixel)
*/
void display_customChar(const uint8_t *c) {
  uint8_t i, j;
  for(i = 0; i < 5; i++ ) {
    uint8_t line = c[i];
    for(j = 0; j < 8; j++, line >>= 1) {
      if(line & 1) {
        if(textsize == 1)
          display_drawPixel(cursor_x + i, cursor_y + j, textcolor);
        else
          display_fillRect(cursor_x + i * textsize, cursor_y + j * textsize, textsize, textsize, textcolor);
      } 
      else 
        if(textbgcolor != textcolor) {
          if(textsize == 1)
            display_drawPixel(cursor_x + i, cursor_y + j, textbgcolor);
          else
            display_fillRect(cursor_x + i * textsize, cursor_y + j * textsize, textsize, textsize, textbgcolor);
        }
    }
  }

  if(textbgcolor != textcolor) {  // If opaque, draw vertical line for last column
    if(textsize == 1)  display_drawVLine(cursor_x + 5, cursor_y, 8, textbgcolor);
    else               display_fillRect(cursor_x + 5 * textsize, cursor_y, textsize, 8 * textsize, textbgcolor);
  }

  cursor_x += textsize * 6;

  if( cursor_x > ((int16_t)display_width + textsize * 6) )
    cursor_x = display_width;

  if (wrap && (cursor_x + (textsize * 5)) > display_width)
  {
    cursor_x = 0;
    cursor_y += textsize * 8;
    if( cursor_y > ((int16_t)display_height + textsize * 8) )
      cursor_y = display_height;
  }
}


/*
   Function Desc:  Draw a single character
    Param1:    x   Bottom left corner x coordinate
    Param2:    y   Bottom left corner y coordinate
    Param3:    c   The 8-bit font-indexed character (likely ascii)
    Param4:    color
    Param5:   (if same as color, no background)
    Param6:    size  Font magnification level, 1 is 'original' size
*/
void display_drawChar(int16_t x, int16_t y, uint8_t c, uint8_t color, uint8_t bg,
     uint8_t size) {
  int16_t prev_x     = cursor_x;
  int16_t prev_y     = cursor_y;
  uint8_t prev_color = textcolor;
  uint8_t  prev_bg    = textbgcolor;
  uint8_t  prev_size  = textsize;

  display_setCursor(x, y);
  display_setTextSize(size);
  display_setTextColor(color, bg);
  display_putc(c);

  cursor_x    = prev_x;
  cursor_y    = prev_y;
  textcolor   = prev_color;
  textbgcolor = prev_bg;
  textsize    = prev_size;
}


/*
    Function Desc: Set text cursor location
    Param1:  x    X coordinate in pixels
    Param2:  y    Y coordinate in pixels
*/
void display_setCursor(int16_t x, int16_t y) {
    cursor_x = x;
    cursor_y = y;
}


/*
    Function Desc: Get text cursor X location
    Returns:   X coordinate in pixels
*/
int16_t display_getCursorX(void) {
    return cursor_x;
}


/*
    Function Desc:     Get text cursor Y location
    Returns:   Y coordinate in pixels
*/
int16_t display_getCursorY(void) {
    return cursor_y;
}


/*
    Function Desc:  Set text 'magnification' size. Each increase in s makes 1 pixel that much bigger.
    Param1:  s  Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
*/
void display_setTextSize(uint8_t s) {
    textsize = (s > 0) ? s : 1;
}


void display_setTextColor(uint8_t c, uint8_t b) {
    textcolor   = c;
    textbgcolor = b;
}


/*
    Function Desc:     Whether text that is too long should 'wrap' around to the next line.
    Param1:  w Set true for wrapping, false for clipping
*/
void display_setTextWrap(bool w) {
    wrap = w;
}

/*
    Function Desc:     Get rotation setting for display
    Returns:   0 thru 3 corresponding to 4 cardinal rotations
*/
uint8_t display_getRotation(void) {
    return _rotation_LCD;
}

/*
    Function Desc:     Get width of the display, accounting for the current rotation
    Returns:   Width in pixels
*/
int16_t display_getWidth(void) {
    return display_width;
}

/*
    Function Desc:     Get height of the display, accounting for the current rotation
    Returns:   Height in pixels
*/
int16_t display_getHeight(void) {
    return display_height;
}

/*
   Function Desc:    Draw a 1-bit image at the specified (x,y) position,
              using the specified foreground color (unset bits are transparent).
    Param1:    x   Top left corner x coordinate
    Param2:    y   Top left corner y coordinate
    Param3:    bitmap  byte array with monochrome bitmap
    Param4:    w   Width of bitmap in pixels
    Param5:    h   Height of bitmap in pixels
    Param6:    color , black or white
*/
void display_drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h,
  uint8_t color) {

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t _byte = 0;
    int16_t i, j;

    for(j = 0; j < h; j++, y++) {
        for( i = 0; i < w; i++ ) {
            if(i & 7) _byte <<= 1;
            else      _byte   = bitmap[j * byteWidth + i / 8];
            if(_byte & 0x80)
              display_drawPixel(x+i, y, color);
        }
    }
}

// Called internally from display_printf
uint8_t DisplayPrintNumber(uint32_t n, int8_t n_width, uint8_t _flags) {
  uint8_t i=0, j, buff[10];
  do {
      buff[i] = (uint8_t)( n % (_flags & 0x1F) );
      if (buff[i] > 9)
        buff[i] += (_flags & 0x80) ? 0x07 : 0x27;
      buff[i++] += '0';
      n /= (_flags & 0x1F);
      } while (n);
  j = i;
  if(_flags & 0x40) {
    n_width--;
    j++;
    if(_flags & 0x20) {    // put '-' before the zeros
      display_putc('-');
      _flags &= ~0x40;
    }
  }
  while (i < n_width--) {
    if (_flags & 0x20)  display_putc('0');
    else                display_putc(' ');
  }
  if (_flags & 0x40)
    display_putc('-');
  do {
      display_putc(buff[--i]);
      } while(i);
  return j;
}

// Called internally from display_printf
void DisplayPrintFloat(float float_n, int8_t f_width, int8_t decimal, uint8_t _flags) {
  int32_t int_part = float_n;
  float rem_part;
  if(decimal == 0)  decimal = 1;
  if(float_n < 0) {
    _flags |= 0x40;
    rem_part = (float)int_part - float_n;
    int_part = ~int_part + 1;
  }
  else
    rem_part = float_n - (float)int_part;
  _flags |= 10;
  f_width -= DisplayPrintNumber(int_part, f_width - decimal - 1, _flags);
  display_putc('.');
  f_width--;
  if(f_width < 1)  f_width = 1;
  if(decimal > f_width)  decimal = f_width;
  while( decimal > 0 && (rem_part != 0 || decimal > 0) ) {
    decimal--;
    rem_part *= 10;
    display_putc( (uint8_t)rem_part + '0' );
    rem_part -= (uint8_t)rem_part;
  }
}

/*
 Desc : Called from display_printf
 port of printf to display to screen instead of console
 */
void DisplayVPrintf(const char *fmt, va_list arp) {
  uint8_t _flags, c, d=0, w=0;
  uint32_t nbr;
  while (1) 
  {
    c = *fmt++;

    if (!c)
      break;

    if (c != '%') {
      display_putc(c);
      continue;
    }

    _flags = 0;
    c = *fmt++;

    if (c == '0') {
      _flags |= 0x20;  // zero flag
      c = *fmt++;
    }

    for (w = 0; c >= '0' && c <= '9'; c = *fmt++)   // width
      w = w * 10 + c - '0';

    if (c == '.') {
      c = *fmt++;
      for (d = 0; c >= '0' && c <= '9'; c = *fmt++)   // decimals width
        d = d * 10 + c - '0';
    }
    
    if(c == 'f' || c == 'F') {    // if float number
      DisplayPrintFloat(va_arg(arp, float), w, d, _flags);
      continue;
    }

    if (c == 'l' || c == 'L') {   // long number (4 bytes)
      _flags |= 0x40;    // long number flag
      c = *fmt++;
    }

    if (!c)   // end of format?
      break;

    if(c == 'X') {
      _flags |= 0x80;   // upper case hex flag
    }
    
    if (c >= 'a')   // if lower case, switch to upper
      c -= 0x20;
    switch (c) {
      case 'C' :        // character
        display_putc( (uint8_t)va_arg(arp, uint8_t) ); continue;
      case 'B' :        // binary
        _flags |= 2;  break;
      case 'O' :        // octal
        _flags |= 8;  break;
      case 'D' :        // signed decimal
      case 'U' :        // unsigned decimal
        _flags |= 10; break;
      case 'X' :        // hexadecimal
        _flags |= 16; break;
      default:          // other
        display_putc(c); continue;
    }

    if(_flags & 0x40)  // if long number
      nbr = (c == 'D') ? va_arg(arp, int32_t) : va_arg(arp, uint32_t);
    else
      nbr = (c == 'D') ? (int32_t)va_arg(arp, int16_t) : (uint32_t)va_arg(arp, int16_t);
    if ( (c == 'D') &&  (nbr & 0x80000000) ) {
      _flags |= 0x40;     // negative number flag
      nbr = ~nbr + 1;     // change to positive form
    }
    else
      _flags &= ~0x40;    // number is positive
    DisplayPrintNumber(nbr, w, _flags);
  }
}

/*
 * Desc: Printf port for screen
 * Param1: the format string
 * Param2: variable arguments passed
 */
void display_printf(const char *fmt, ...) {
  
  va_list arg;
  va_start(arg, fmt);
  DisplayVPrintf(fmt, arg);
  va_end(arg);
}


void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, bool color) {

  bool steep = abs((int16_t)(y1 - y0)) > abs((int16_t)(x1 - x0));
  int8_t ystep;
  int16_t dx; 
  int16_t dy;
  int16_t err;

  if (steep) {
    _swap_int16_t_LCD(x0, y0);
    _swap_int16_t_LCD(x1, y1);
  }
  if (x0 > x1) {
    _swap_int16_t_LCD(x0, x1);
    _swap_int16_t_LCD(y0, y1);
  }
  dx = x1 - x0;
  dy = abs(y1 - y0);

  err = dx / 2;
  if (y0 < y1)
    ystep = 1;
  else
    ystep = -1;

  for (; x0 <= x1; x0++) {
    if (steep)
      LCDdrawPixel(y0, x0, color);
    else
      LCDdrawPixel(x0, y0, color);
    err -= dy;
    if (err < 0) {
      y0  += ystep;
      err += dx;
    }
  }
}

void display_drawHLine(int16_t x, int16_t y, int16_t w, bool color) {
   drawLine(x, y, x + w - 1, y, color);
}


void display_drawVLine(int16_t x, int16_t y, int16_t h, bool color) {
  drawLine(x, y, x, y + h - 1, color);
}

void display_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, bool color) {
  int16_t i;
  for (i = x; i < x + w; i++)
    display_drawVLine(i, y, h, color);
}

void display_Font(LCDFontType_e FontNumber)
{
   	_FontNumber = FontNumber;

	switch (_FontNumber) {
        case LCDFontType_Default:  // Norm default 5 by 8
            _CurrentFontWidth = LCDFontWidth_5;
            _CurrentFontoffset =  LCDFontOffset_Extend;
        break; 
        case LCDFontType_Thick: // Thick 7 by 8 (NO LOWERCASE LETTERS)
            _CurrentFontWidth = LCDFontWidth_7;
            _CurrentFontoffset = LCDFontOffset_Space;
        break; 
        case LCDFontType_HomeSpun: // homespun 7 by 8 
            _CurrentFontWidth = LCDFontWidth_7;
            _CurrentFontoffset = LCDFontOffset_Space;
        break;
        case LCDFontType_SevenSeg:  // Seven segment 4 by 8
            _CurrentFontWidth = LCDFontWidth_4;
            _CurrentFontoffset = LCDFontOffset_Space;
        break;
        case LCDFontType_Wide : // Wide  8 by 8 (NO LOWERCASE LETTERS)
            _CurrentFontWidth = LCDFontWidth_8;
            _CurrentFontoffset = LCDFontOffset_Space;
        break; 
        case LCDFontType_Tiny:  // tiny 3 by 8
            _CurrentFontWidth = LCDFontWidth_3;
            _CurrentFontoffset =  LCDFontOffset_Space;
        break;

        default: // if wrong font num passed in,  set to default
            _CurrentFontWidth = LCDFontWidth_5;
            _CurrentFontoffset =  LCDFontOffset_Extend;
            _FontNumber = LCDFontType_Default;
        break;
    }
}
/* ------------- EOF ------------------ */