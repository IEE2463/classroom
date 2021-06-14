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

#ifndef _TESTROUTINES_H_
#define TESTROUTINES_H_

// Draws rays originating from each corner in the given color
void testlines(uint16_t color);

// Draws a screen full of boxed rectangles in the given color
void testdrawrects(uint16_t color);

// Draws a screen full of boxed rectangles in color2 and fills them with color1
void testfillrects(uint16_t color1, uint16_t color2);

// Draws a screen full of circles of the given radius with the given color
void testfillcircles(uint8_t radius, uint16_t color);

// Draws a screen full of filled circles (discs) of the given radius with the given color
void testdrawcircles(uint8_t radius, uint16_t color);

// Draws 15 triangles inside each other
void testtriangles();

// Draws a small 2x2 square in each corner and a single pixel in the center, useful to identify the display rotation
void testcorners();

#endif //_TESTROUTINES_H_