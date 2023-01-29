// URL https://github.com/gavinlyonsrepo/pic_16F1619_projects Nokia 5110 font data file

 
#ifndef XC_HEADER_NOKIAFONT_H
#define	XC_HEADER_NOKIAFONT_H


// **** FONT DEFINE SECTION ******  
// Comment in the fonts you want, X_1 is default. 
#define NOKIA5110_FONT_Default
#define NOKIA5110_FONT_Thick
#define NOKIA5110_FONT_HomeSpun
#define NOKIA5110_FONT_SevenSeg
#define NOKIA5110_FONT_Wide
#define NOKIA5110_FONT_Tiny
#define NOKIA5110_FONT_Large
#define NOKIA5110_FONT_Huge
#define NOKIA5110_FONT_Mega 
// **** END OF FONT DEFINE SECTION ******  

#ifdef NOKIA5110_FONT_Default 
extern const unsigned char (* pFontDefaultptr)[5];
#endif
#ifdef  NOKIA5110_FONT_Thick
extern const unsigned char (* pFontThickptr)[7];
#endif
#ifdef NOKIA5110_FONT_HomeSpun
extern const unsigned char (* pFontHomeSpunptr)[7] ;
#endif
#ifdef NOKIA5110_FONT_SevenSeg
extern const unsigned char (* pFontSevenSegptr)[4];
#endif
#ifdef NOKIA5110_FONT_Wide
extern const unsigned char (* pFontWideptr)[8];
#endif
#ifdef NOKIA5110_FONT_Tiny
extern const  unsigned char (* pFontTinyptr)[3];
#endif
#ifdef NOKIA5110_FONT_Large
extern const  uint16_t (* pFontLargeptr)[12];
#endif
#ifdef NOKIA5110_FONT_Huge
extern const  uint32_t (* pFontHugeptr)[16];
#endif
#ifdef NOKIA5110_FONT_Mega
extern const  uint32_t (* pFontMegaptr)[16];
#endif


#endif	// endif header guard

// ** EOF **