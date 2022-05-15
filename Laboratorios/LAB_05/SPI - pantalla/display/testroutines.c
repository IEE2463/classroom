/***************************************************
 * 
 * *** Original licence and library information ***
 * 
 * This is a library for the Adafruit 1.8" SPI display.              *
 * 
 * This library works with the Adafruit 1.8" TFT Breakout w/SD card
 * ----> http://www.adafruit.com/products/358
 * The 1.8" TFT shield
 * ----> https://www.adafruit.com/product/802
 * The 1.44" TFT breakout
 * ----> https://www.adafruit.com/product/2088
 * as well as Adafruit raw 1.8" TFT display
 * ----> http://www.adafruit.com/products/618
 *  
 * Check out the links above for our tutorials and wiring diagrams
 * These displays use SPI to communicate, 4 or 5 pins are required to
 * interface (RST is optional)
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 * MIT license, all text above must be included in any redistribution
 * 
 * 
 * 
 * *** Information about modifications ***
 * 
 * This library is based on the original 'graphicstest' example sketch for
 * Arduino written by Limor Fried/Ladyada for Adafruit Industries.
 * 
 * This code is a port of the Ladyada code to plain GNU-C. It can
 * be used to test the display without any operating system or
 * additional infrastructure. * 
 * 
 * 
 * This file contains several test programs.
 * Call these routines from your main program to test your setup
 * and to get a demonstration of the display's capabilities.
 * 
 ****************************************************/
// Few modification for work in CCS.
/*
 * Adaptations by:
 *      + Camila Turrieta
 *      + Felipe Sanchez
 *      + Jose Gutierrez
 */
//****************************************************//
//REF: codigo base LAB08-SPI SEP:2019-II


#include <stdint.h>

#include "testroutines.h"
#include "ST7735_commands.h"
#include "graphic_shapes.h"

int16_t x;
int16_t y;

void testlines(uint16_t color)
{
	fillScreen(ST7735_BLACK);
	for (x=0; x < TFT_WIDTH; x+=6)
	{
		drawLine(0, 0, x, TFT_HEIGHT-1, color);
	}
	for (y=0; y < TFT_HEIGHT; y+=6)
	{
		drawLine(0, 0, TFT_WIDTH-1, y, color);
	}
	__delay_cycles(524288);
	
	fillScreen(ST7735_BLACK);
	for (x=0; x < TFT_WIDTH; x+=6)
	{
		drawLine(TFT_WIDTH-1, 0, x, TFT_HEIGHT-1, color);
	}
	for (y=0; y < TFT_HEIGHT; y+=6)
	{
		drawLine(TFT_WIDTH-1, 0, 0, y, color);
	}
	__delay_cycles(524288);
	
	fillScreen(ST7735_BLACK);
	for (x=0; x < TFT_WIDTH; x+=6)
	{
		drawLine(0, TFT_HEIGHT-1, x, 0, color);
	}
	for (y=0; y < TFT_HEIGHT; y+=6)
	{
		drawLine(0, TFT_HEIGHT-1, TFT_WIDTH-1, y, color);
	}
	__delay_cycles(524288);
	
	fillScreen(ST7735_BLACK);
	for (x=0; x < TFT_WIDTH; x+=6)
	{
		drawLine(TFT_WIDTH-1, TFT_HEIGHT-1, x, 0, color);
	}
	for (y=0; y < TFT_HEIGHT; y+=6)
	{
		drawLine(TFT_WIDTH-1, TFT_HEIGHT-1, 0, y, color);
	}
}


void testdrawrects(uint16_t color)
{
	fillScreen(ST7735_BLACK);
	for (x=0; x < TFT_WIDTH; x+=6)
	{
		drawRect(TFT_WIDTH/2 -x/2, TFT_HEIGHT/2 -x/2 , x, x, color);
	}
}


void testfillrects(uint16_t color1, uint16_t color2)
{
	fillScreen(ST7735_BLACK);
	for (x=TFT_WIDTH-1; x > 6; x-=6)
	{
		fillRect(TFT_WIDTH/2 -x/2, TFT_HEIGHT/2 -x/2 , x, x, color1);
		drawRect(TFT_WIDTH/2 -x/2, TFT_HEIGHT/2 -x/2 , x, x, color2);
	}
}


void testfillcircles(uint8_t radius, uint16_t color)
{
	for (x=radius; x < TFT_WIDTH; x+=radius*2)
	{
		for (y=radius; y < TFT_HEIGHT; y+=radius*2)
		{
			fillCircle(x, y, radius, color);
		}
	}
}


void testdrawcircles(uint8_t radius, uint16_t color)
{
	for (x=0; x < TFT_WIDTH+radius; x+=radius*2)
	{
		for (y=0; y < TFT_HEIGHT+radius; y+=radius*2)
		{
			drawCircle(x, y, radius, color);
		}
	}
}


void testtriangles()
{
	fillScreen(ST7735_BLACK);
	int color = 0xF800;
	int t;
	int w = TFT_WIDTH/2;
	int x = TFT_HEIGHT-1;
	int y = 0;
	int z = TFT_WIDTH;
	for(t = 0 ; t <= 15; t+=1)
	{
		drawTriangle(w, y, y, x, z, x, color);
		x-=4;
		y+=4;
		z-=4;
		color+=100;
	}
}


void testcorners()
{
	// (0,0) is in the top left corner
	drawPixel(0, 0, ST7735_RED);
	drawPixel(0, 1, ST7735_RED);
	drawPixel(0, 2, ST7735_RED);
	drawPixel(1, 0, ST7735_RED);
	drawPixel(1, 1, ST7735_RED);
	drawPixel(1, 2, ST7735_RED);
	drawPixel(2, 0, ST7735_RED);
	drawPixel(2, 1, ST7735_RED);
    drawPixel(2, 2, ST7735_RED);

	__delay_cycles(1048576);
	
	// (max,0) is in the top right corner
	drawPixel(TFT_WIDTH-1, 0, ST7735_MAGENTA);
	drawPixel(TFT_WIDTH-1, 1, ST7735_MAGENTA);
	drawPixel(TFT_WIDTH-2, 0, ST7735_MAGENTA);
	drawPixel(TFT_WIDTH-2, 1, ST7735_MAGENTA);
	__delay_cycles(1048576);
	
	// (0,max) is in the bottom left corner
	drawPixel(0, TFT_HEIGHT-1, ST7735_CYAN);
	drawPixel(0, TFT_HEIGHT-2, ST7735_CYAN);
	drawPixel(1, TFT_HEIGHT-1, ST7735_CYAN);
	drawPixel(1, TFT_HEIGHT-2, ST7735_CYAN);
	__delay_cycles(1048576);
	
	// (max,max) is in the bottom right corner
	drawPixel(TFT_WIDTH-1, TFT_HEIGHT-1, ST7735_BLUE);
	drawPixel(TFT_WIDTH-1, TFT_HEIGHT-2, ST7735_BLUE);
	drawPixel(TFT_WIDTH-2, TFT_HEIGHT-1, ST7735_BLUE);
	drawPixel(TFT_WIDTH-2, TFT_HEIGHT-2, ST7735_BLUE);
	__delay_cycles(1048576);
	
	// a lonely pixel in the middle of the screen
	drawPixel(TFT_WIDTH/2, TFT_HEIGHT/2, ST7735_GREEN);
}
