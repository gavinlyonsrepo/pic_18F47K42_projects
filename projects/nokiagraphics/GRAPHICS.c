/*
* Project Name: Nokia  5110 Graphic library for PIC  micro-controller
* File: GRAPHICS.hc
* Description: Source file for  graphics libraries to draw shapes lines etc
* Author: Gavin Lyons.
* Complier: xc8 v2.10 compiler
* PIC: PIC18F47K42
* IDE:  MPLAB X v5.30
* Created: July 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_18F47K42_projects
*/

#include "GRAPHICS.h"

/*
    Name:         writeLine
    Function Desc:   Write a line.  Bresenham's algorithm 
    Parameter1:    x0  Start point x coordinate
    Parameter2:    y0  Start point y coordinate
    Parameter3:    x1  End point x coordinate
    Parameter4:    y1  End point y coordinate
    Parameter5:    color 16-bit 5-6-5 Color to draw with
*/
void writeLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    bool steep = abs((int16_t)(y1 - y0)) > abs((int16_t)(x1 - x0));
    int16_t dx, dy, err, ystep;
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
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
    Parameter1:    x0  Start point x coordinate
    Parameter2:    y0  Start point y coordinate
    Parameter3:    x1  End point x coordinate
    Parameter4:    y1  End point y coordinate
    Parameter5:    color 16-bit 5-6-5 Color to draw with
*/

void display_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    // Update in subclasses if desired!
    if(x0 == x1){
        if(y0 > y1) _swap_int16_t(y0, y1);
        display_drawVLine(x0, y0, y1 - y0 + 1, color);
    } else if(y0 == y1){
        if(x0 > x1) _swap_int16_t(x0, x1);
        display_drawHLine(x0, y0, x1 - x0 + 1, color);
    } else {
        writeLine(x0, y0, x1, y1, color);
    }
}


/*
   Function Desc:   Draw a circle outline
    Parameter1:    x0   Center-point x coordinate
    Parameter2:    y0   Center-point y coordinate
    Parameter3:    r   Radius of circle
    Parameter4:    color 16-bit 5-6-5 Color to draw with
*/
void display_drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color) {
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
    Parameter1:    x0   Center-point x coordinate
    Parameter2:    y0   Center-point y coordinate
    Parameter3:    r   Radius of circle
    Parameter4:    cornername  Mask bit #1 or bit #2 to indicate which quarters of the circle we're doing
    Parameter5:    color 16-bit 5-6-5 Color to draw with
*/

void display_drawCircleHelper(uint16_t x0, uint16_t y0, uint16_t r, uint8_t cornername, uint16_t color) {
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
    Parameter1:    x0   Center-point x coordinate
    Parameter2:    y0   Center-point y coordinate
    Parameter3:    r   Radius of circle
    Parameter4:    color 16-bit 5-6-5 Color to fill with
*/
void display_fillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color) {
    display_drawVLine(x0, y0-r, 2*r+1, color);
    display_fillCircleHelper(x0, y0, r, 3, 0, color);
}



/*
    Function Desc: Quarter-circle drawer with fill, used for circles and roundrects
    Parameter1:  x0       Center-point x coordinate
    Parameter2:  y0       Center-point y coordinate
    Parameter3:  r        Radius of circle
    Parameter4:  corners  Mask bits indicating which quarters we're doing
    Parameter5:  delta    Offset from center-point, used for round-rects
    Parameter6:  color    16-bit 5-6-5 Color to fill with
*/
void display_fillCircleHelper(uint16_t x0, uint16_t y0, uint16_t r, uint8_t corners, uint16_t delta, uint16_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
    int16_t px    = x;
    int16_t py    = y;

    delta++; // Avoid some +1's in the loop

    while(x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        // These checks avoid double-drawing certain lines, important
        // for the SSD1306 library which has an INVERT drawing mode.
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
    Parameter1:    x   Top left corner x coordinate
    Parameter2:    y   Top left corner y coordinate
    Parameter3:    w   Width in pixels
    Parameter4:    h   Height in pixels
    Parameter5:    color 16-bit 5-6-5 Color to draw with
*/
void display_drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    display_drawHLine(x, y, w, color);
    display_drawHLine(x, y+h-1, w, color);
    display_drawVLine(x, y, h, color);
    display_drawVLine(x+w-1, y, h, color);
}


/*
   Function Desc:  Draw a rounded rectangle with no fill color
    Parameter1:    x   Top left corner x coordinate
    Parameter2:    y   Top left corner y coordinate
    Parameter3:    w   Width in pixels
    Parameter4:    h   Height in pixels
    Parameter5:    r   Radius of corner rounding
    Parameter6:    color 16-bit 5-6-5 Color to draw with
*/
void display_drawRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color) {
    int16_t max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
    if(r > max_radius) r = max_radius;
    // smarter version
    display_drawHLine(x+r  , y    , w-2*r, color); // Top
    display_drawHLine(x+r  , y+h-1, w-2*r, color); // Bottom
    display_drawVLine(x    , y+r  , h-2*r, color); // Left
    display_drawVLine(x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
    display_drawCircleHelper(x+r    , y+r    , r, 1, color);
    display_drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
    display_drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
    display_drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}


/*
   Function Desc:  Draw a rounded rectangle with fill color
    Parameter1:    x   Top left corner x coordinate
    Parameter2:    y   Top left corner y coordinate
    Parameter3:    w   Width in pixels
    Parameter4:    h   Height in pixels
    Parameter5:    r   Radius of corner rounding
    Parameter6:    color 16-bit 5-6-5 Color to draw/fill with
*/
void display_fillRoundRect(uint16_t x, uint16_t y, uint16_t w,
  uint16_t h, uint16_t r, uint16_t color) {
    int16_t max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
    if(r > max_radius) r = max_radius;
    // smarter version
    display_fillRect(x+r, y, w-2*r, h, color);
    // draw four corners
    display_fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    //display_fillCircleHelper(94, 18, 8, 1, 43, color);
    display_fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}


/*
   Function Desc:  Draw a triangle with no fill color
    Parameter1:    x0  Vertex #0 x coordinate
    Parameter2:    y0  Vertex #0 y coordinate
    Parameter3:    x1  Vertex #1 x coordinate
    Parameter4:    y1  Vertex #1 y coordinate
    Parameter5:    x2  Vertex #2 x coordinate
    Parameter6:    y2  Vertex #2 y coordinate
    Parameter7:    color 16-bit 5-6-5 Color to draw with
*/
void display_drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
  uint16_t x2, uint16_t y2, uint16_t color) {
    display_drawLine(x0, y0, x1, y1, color);
    display_drawLine(x1, y1, x2, y2, color);
    display_drawLine(x2, y2, x0, y0, color);
}

/*
   Function Desc:    Draw a triangle with color-fill
    Parameter1:    x0  Vertex #0 x coordinate
    Parameter2:    y0  Vertex #0 y coordinate
    Parameter3:    x1  Vertex #1 x coordinate
    Parameter4:    y1  Vertex #1 y coordinate
    Parameter5:    x2  Vertex #2 x coordinate
    Parameter6:    y2  Vertex #2 y coordinate
    Parameter7:    color 16-bit 5-6-5 Color to fill/draw with
*/
void display_fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
  uint16_t x2, uint16_t y2, uint16_t color) {
    int16_t a, b, y, last, dx01, dy01, dx02, dy02, dx12, dy12;
    int32_t
    sa   = 0,
    sb   = 0;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }
    if (y1 > y2) {
        _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
    }
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }

    if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
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

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) _swap_int16_t(a,b);
        display_drawHLine(a, y, b-a+1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) _swap_int16_t(a,b);
        display_drawHLine(a, y, b-a+1, color);
    }
}


/*
    Function Desc: Print one byte/character of data
    Parameter1:  c  The 8-bit ascii character to write
*/
void display_putc(char c) {
  uint8_t i, j;
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

  for(i = 0; i < 5; i++ ) {
    uint8_t line = font[c][i];
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

  if( cursor_x > ((uint16_t)display_width + textsize * 6) )
    cursor_x = display_width;

  if (wrap && (cursor_x + (textsize * 5)) > display_width)
  {
    cursor_x = 0;
    cursor_y += textsize * 8;
    if( cursor_y > ((uint16_t)display_height + textsize * 8) )
      cursor_y = display_height;
  }
}

/* 
  Function Desc : prints a string 
  Parameter1: Pointer to a string of ASCII bytes
*/
void display_puts(char *s) {
  while(*s)
    display_putc(*s++);
}

/* 
  Function Desc : print custom char  (dimension: 7x5 or 8x5 pixel)
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

  if( cursor_x > ((uint16_t)display_width + textsize * 6) )
    cursor_x = display_width;

  if (wrap && (cursor_x + (textsize * 5)) > display_width)
  {
    cursor_x = 0;
    cursor_y += textsize * 8;
    if( cursor_y > ((uint16_t)display_height + textsize * 8) )
      cursor_y = display_height;
  }
}


/*
   Function Desc:  Draw a single character
    Parameter1:    x   Bottom left corner x coordinate
    Parameter2:    y   Bottom left corner y coordinate
    Parameter3:    c   The 8-bit font-indexed character (likely ascii)
    Parameter4:    color 16-bit 5-6-5 Color to draw chraracter with
    Parameter5:    bg 16-bit 5-6-5 Color to fill background with (if same as color, no background)
    Parameter6:    size  Font magnification level, 1 is 'original' size
*/
void display_drawChar(uint16_t x, uint16_t y, uint8_t c, uint16_t color, uint16_t bg,
     uint8_t size) {
  uint16_t prev_x     = cursor_x,
           prev_y     = cursor_y,
           prev_color = textcolor,
           prev_bg    = textbgcolor;
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
    Parameter1:  x    X coordinate in pixels
    Parameter2:  y    Y coordinate in pixels
*/
void display_setCursor(uint16_t x, uint16_t y) {
    cursor_x = x;
    cursor_y = y;
}


/*
    Function Desc: Get text cursor X location
    Returns:   X coordinate in pixels
*/
uint16_t display_getCursorX(void) {
    return cursor_x;
}


/*
    Function Desc:     Get text cursor Y location
    Returns:   Y coordinate in pixels
*/
uint16_t display_getCursorY(void) {
    return cursor_y;
}


/*
    Function Desc:  Set text 'magnification' size. Each increase in s makes 1 pixel that much bigger.
    Parameter1:  s  Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
*/
void display_setTextSize(uint8_t s) {
    textsize = (s > 0) ? s : 1;
}


/*
    Function Desc:  Set text font color with custom background color
    Parameter1:   c   16-bit 5-6-5 Color to draw text with
    Parameter2:   b   16-bit 5-6-5 Color to draw background/fill with
*/
void display_setTextColor(uint16_t c, uint16_t b) {
    textcolor   = c;
    textbgcolor = b;
}


/*
    Function Desc:     Whether text that is too long should 'wrap' around to the next line.
    Parameter1:  w Set true for wrapping, false for clipping
*/

void display_setTextWrap(bool w) {
    wrap = w;
}

/*
    Function Desc:     Get rotation setting for display
    Returns:   0 thru 3 corresponding to 4 cardinal rotations
*/

uint8_t display_getRotation(void) {
    return rotation;
}

/*
    Function Desc:     Get width of the display, accounting for the current rotation
    Returns:   Width in pixels
*/
uint16_t display_getWidth(void) {
    return display_width;
}

/*
    Function Desc:     Get height of the display, accounting for the current rotation
    Returns:   Height in pixels
*/
uint16_t display_getHeight(void) {
    return display_height;
}

/*
    Function Desc:  Given 8-bit red, green and blue values, return a 'packed'
             16-bit color value in '565' RGB format (5 bits red, 6 bits
             green, 5 bits blue). This is just a mathematical operation,
             no hardware is touched.
    Parameter1:   red    8-bit red brightnesss (0 = off, 255 = max).
    Parameter2:   green  8-bit green brightnesss (0 = off, 255 = max).
    Parameter3:   blue   8-bit blue brightnesss (0 = off, 255 = max).
    returns: 'Packed' 16-bit color value (565 format).
*/
uint16_t display_color565(uint8_t red, uint8_t green, uint8_t blue) {
    return ((uint16_t)(red & 0xF8) << 8) | ((uint16_t)(green & 0xFC) << 3) | (blue >> 3);
}

/*
   Function Desc:    Draw a ROM-resident 1-bit image at the specified (x,y) position,
              using the specified foreground color (unset bits are transparent).
    Parameter1:    x   Top left corner x coordinate
    Parameter2:    y   Top left corner y coordinate
    Parameter3:    bitmap  byte array with monochrome bitmap
    Parameter4:    w   Width of bitmap in pixels
    Parameter5:    h   Hieght of bitmap in pixels
    Parameter6:    color 16-bit 5-6-5 Color to draw with
*/
void display_drawBitmapV1(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h,
     uint16_t color) {
  uint16_t i, j;
  for( i = 0; i < h/8; i++)
  {    
    for( j = 0; j < w * 8; j++)
    {      
      if( bitmap[j/8 + i*w] & (1 << (j % 8)) )
        display_drawPixel(x + j/8, y + i*8 + (j % 8), color);
    }
  }
}

/*
   Function Desc:    Draw a ROM-resident 1-bit image at the specified (x,y) position,
              using the specified foreground (for set bits) and background (unset bits) colors.
    Parameter1:    x   Top left corner x coordinate
    Parameter2:    y   Top left corner y coordinate
    Parameter3:    bitmap  byte array with monochrome bitmap
    Parameter4:    w   Width of bitmap in pixels
    Parameter5:    h   Hieght of bitmap in pixels
    Parameter6:    color 16-bit 5-6-5 Color to draw pixels with
    Parameter7:    bg 16-bit 5-6-5 Color to draw background with
*/
void display_drawBitmapV1_bg(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h,
     uint16_t color, uint16_t bg) {
  uint16_t i, j;
  for( i = 0; i < h/8; i++)
  {    
    for( j = 0; j < w * 8; j++)
    {      
      if( bitmap[j/8 + i*w] & (1 << (j % 8)) )
        display_drawPixel(x + j/8, y + i*8 + (j % 8), color);
      else
        display_drawPixel(x + j/8, y + i*8 + (j % 8), bg);
    }
  }
}

/*
   Function Desc:    Draw a ROM-resident 1-bit image at the specified (x,y) position,
              using the specified foreground color (unset bits are transparent).
    Parameter1:    x   Top left corner x coordinate
    Parameter2:    y   Top left corner y coordinate
    Parameter3:    bitmap  byte array with monochrome bitmap
    Parameter4:    w   Width of bitmap in pixels
    Parameter5:    h   Hieght of bitmap in pixels
    Parameter6:    color 16-bit 5-6-5 Color to draw pixels with
*/
void display_drawBitmapV2(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h,
  uint16_t color) {

    uint16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t _byte = 0;
    uint16_t i, j;

    for(j = 0; j < h; j++, y++) {
        for( i = 0; i < w; i++ ) {
            if(i & 7) _byte <<= 1;
            else      _byte   = bitmap[j * byteWidth + i / 8];
            if(_byte & 0x80)
              display_drawPixel(x+i, y, color);
        }
    }
}


/*
   Function Desc:    Draw a ROM-resident 1-bit image at the specified (x,y) position,
              using the specified foreground (for set bits) and background (unset bits) colors.
    Parameter1:    x   Top left corner x coordinate
    Parameter2:    y   Top left corner y coordinate
    Parameter3:    bitmap  byte array with monochrome bitmap
    Parameter4:    w   Width of bitmap in pixels
    Parameter5:    h   Hieght of bitmap in pixels
    Parameter6:    color 16-bit 5-6-5 Color to draw pixels with
    Parameter7:    bg 16-bit 5-6-5 Color to draw background with
*/
void display_drawBitmapV2_bg(uint16_t x, uint16_t y, const uint8_t *bitmap, uint16_t w, uint16_t h,
  uint16_t color, uint16_t bg) {

    uint16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t _byte = 0;
    uint16_t i, j;
    for(j = 0; j < h; j++, y++) {
        for(i = 0; i < w; i++ ) {
            if(i & 7) _byte <<= 1;
            else      _byte   = bitmap[j * byteWidth + i / 8];
            if(_byte & 0x80)
              display_drawPixel(x+i, y, color);
            else
              display_drawPixel(x+i, y, bg);
        }
    }
}


uint8_t printNumber(uint32_t n, int8_t n_width, uint8_t _flags) {
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

void printFloat(float float_n, int8_t f_width, int8_t decimal, uint8_t _flags) {
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
  f_width -= printNumber(int_part, f_width - decimal - 1, _flags);
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


void v_printf(const char *fmt, va_list arp) {
  uint8_t _flags, c, d=0, w=0;
  uint32_t nbr;
  while (1) {
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
      printFloat(va_arg(arp, float), w, d, _flags);
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
      nbr = (c == 'D') ? (int32_t)va_arg(arp, int16_t) : (uint32_t)va_arg(arp, uint16_t);
    if ( (c == 'D') &&  (nbr & 0x80000000) ) {
      _flags |= 0x40;     // negative number flag
      nbr = ~nbr + 1;     // change to positive form
    }
    else
      _flags &= ~0x40;    // number is positive
    printNumber(nbr, w, _flags);
  }
}

void display_printf(const char *fmt, ...) {
  va_list arg;
  va_start(arg, fmt);
  v_printf(fmt, arg);
}

/* ------------- EOF -------------------- */