/***************************************************
 * 
 * *** Original licence and library information ***
 * 
 * This is the core graphics l*ibrary for all our displays, providing a common
 * set of graphics primitives (points, lines, circles, etc.).  It needs to be
 * paired with a hardware-specific library for each display device we carry
 * (to handle the lower-level functions).
 *  
 * Adafruit invests time and resources providing this open source code, please
 * support Adafruit & open-source hardware by purchasing products from Adafruit!
 *  
 * Copyright (c) 2013 Adafruit Industries.  All rights reserved.
 *  
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 * 
 * *** Information about modifications ***
 * 
 * This code is under the BSD licence. See above copyright notice and the file
 * BSD_license.txt for further information.
 * 
 * This library is based on the original GFX display library written by Limor
 * Fried/Ladyada for Adafruit Industries. The original library was designed for
 * use with the Arduino system.
 * 
 * This code is a port of the Ladyada code to plain GNU-C. It can
 * be used to control the display without any operating system or
 * additional infrastructure.
 * 
 * 
 * This file contains graphic primitives.
 *
 * The most basic object is a pixel.
 *
 * All other, more advanced routines build on the pixel routine.
 * They provide some basic shapes that might be useful for user applications.
 * The ST7735 display controller and the intended hardware combination with an
 * Atmel ATMega328PB microcontroller would allow a much more efficient
 * implementation of many of the following commands. The original Adafruit
 * libraries partially do that. In this place, the code was kept simple on
 * purpose. It is an easy-to-understand example for studies and not intended
 * for productive use.
 * 
 ****************************************************/

#include <stdlib.h>

#include "../SPI/SPI_implement_me.h"

#include "graphic_shapes.h"
#include "ST7735_commands.h"

#define swap(a, b) { int16_t t = a; a = b; b = t; }



/* Basic routines */

void drawPixel(int16_t x, int16_t y, uint16_t color)
{
	// set address window
	wc(ST7735_CASET); 	// Column addr set
	wd(0x00);
	wd(x);				// XSTART 
	wd(0x00);
	wd(x);				// XEND
	
	wc(ST7735_RASET);	// Row addr set
	wd(0x00);
	wd(y);				// YSTART
	wd(0x00);
	wd(y);				// YEND
	
	wc(ST7735_RAMWR);	// write to RAM
	
	
	wd((color>>8) & 0xff);
	wd(color & 0xff);
}


void drawPixelRGB(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
	drawPixel(x,y,color);
}


/* Advanced routines - straight lines */

void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	drawLine(x, y, x, y+h-1, color);
}


void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	drawLine(x, y, x+w-1, y, color);
}


void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}
	
	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}
	
	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);
	
	int16_t err = dx / 2;
	int16_t ystep;
	
	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}
	
	for (; x0<=x1; x0++) {
		if (steep) {
			drawPixel(y0, x0, color);
		} else {
			drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}



/* Advanced routines - draw rectangular shapes based on lines */

void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	drawFastHLine(x, y, w, color);
	drawFastHLine(x, y+h-1, w, color);
	drawFastVLine(x, y, h, color);
	drawFastVLine(x+w-1, y, h, color);
}

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	for (int16_t i=x; i<x+w; i++) {
		drawFastVLine(i, y, h, color);
	}
}

void fillScreen(uint16_t color)
{
	fillRect(0, 0, TFT_WIDTH, TFT_HEIGHT, color);
}



/* Advanced routines - draw triangular shapes based on lines */

void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}


void fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	int16_t a, b, y, last;
	
	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) {
		swap(y0, y1); swap(x0, x1);
	}
	if (y1 > y2) {
		swap(y2, y1); swap(x2, x1);
	}
	if (y0 > y1) {
		swap(y0, y1); swap(x0, x1);
	}
	
	// Handle awkward all-on-same-line case as its own thing
	if(y0 == y2)
	{
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		drawFastHLine(a, y0, b-a+1, color);
		return;
	}
	
	int16_t
	dx01 = x1 - x0,
	dy01 = y1 - y0,
	dx02 = x2 - x0,
	dy02 = y2 - y0,
	dx12 = x2 - x1,
	dy12 = y2 - y1;
	int32_t
	sa   = 0,
	sb   = 0;
	
	// For upper part of triangle, find scanline crossings for segments
	// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if(y1 == y2) last = y1;   // Include y1 scanline
	else         last = y1-1; // Skip it
	
	for(y=y0; y<=last; y++)
	{
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		/* longhand:
		 *   a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
		 *   b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		 */
		if(a > b) swap(a,b);
		drawFastHLine(a, y, b-a+1, color);
	}
	
	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++)
	{
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		/* longhand:
		 *   a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		 *   b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		 */
		if(a > b) swap(a,b);
		drawFastHLine(a, y, b-a+1, color);
	}
}



/* Advanced routines - draw round shapes */

void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;
	
	drawPixel(x0  , y0+r, color);
	drawPixel(x0  , y0-r, color);
	drawPixel(x0+r, y0  , color);
	drawPixel(x0-r, y0  , color);
	
	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		
		drawPixel(x0 + x, y0 + y, color);
		drawPixel(x0 - x, y0 + y, color);
		drawPixel(x0 + x, y0 - y, color);
		drawPixel(x0 - x, y0 - y, color);
		drawPixel(x0 + y, y0 + x, color);
		drawPixel(x0 - y, y0 + x, color);
		drawPixel(x0 + y, y0 - x, color);
		drawPixel(x0 - y, y0 - x, color);
	}
}


void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}


void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
	
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
		
		if (cornername & 0x1) {
			drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2) {
			drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
			drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}
	
///MIAS


void ESCRIBIRNUM(uint8_t numero,uint8_t x, uint8_t y){
	switch(numero){
		case 0: drawRect(x, y, 10,20, ST7735_BLACK);
				break;
		
		case 1:	drawRect(x, y, 10,20, ST7735_BLACK);
				break;
		
		case 2: drawRect(x, y, 10,20, ST7735_BLACK);
		
				break;
		case 3: drawRect(x, y, 10,20, ST7735_BLACK);
		
				break;
		case 4: drawRect(x, y, 10,20, ST7735_BLACK);
		
				break;
		case 5: drawRect(x, y, 10,20, ST7735_BLACK);
		
				break;
		case 6: drawRect(x, y, 10,20, ST7735_BLACK);
		
				break;
		case 7: drawRect(x, y, 10,20, ST7735_BLACK);
		
				break;
		case 8: drawRect(x, y, 10,20, ST7735_BLACK);
		
				break;
		case 9: drawRect(x, y, 10,20, ST7735_BLACK);
		
				break;
	}
}

void Cuadrado(void){
	drawRect(150,110,30,100,ST7735_BLUE);
}