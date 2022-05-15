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
// Few modification for work in CCS.
/*
 * Adaptations by:
 *      + Camila Turrieta
 *      + Felipe Sanchez
 *      + Jose Gutierrez
 */
//****************************************************//
//REF: codigo base LAB08-SPI SEP:2019-II

#ifndef _GRAPHIC_SHAPES_H_
#define _GRAPHIC_SHAPES_H_

#include <stdint.h>

#define TFT_HEIGHT 128
#define TFT_WIDTH 128


//NEW graphics char and strings
static const uint8_t Font[];

void drawChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size);

uint32_t drawtext(uint16_t x, uint16_t y, char *pt, int16_t textColor, int16_t bgColor, uint8_t size);

void pointp(int16_t x, int16_t y, int16_t h, uint16_t color);


/* Basic routines */

// Most basic of all graphics - set a single pixel to a certian value
// Color is in 565 format (65k colors / one 16bit value).

void SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void drawPixel(int16_t x, int16_t y, uint16_t color);

// The same as above, but with 24bit RGB colors instead of 16bit (Color565)
void drawPixelRGB(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);



/* Advanced routines - straight lines */

// Draws a 1 pixel thin straight vertical line.
void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

// Draws a 1 pixel thin straight horizontal line.
void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

// Draws a 1 pixel thin line at any angle.
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);



/* Advanced routines - draw rectangular shapes based on lines */

// Draws an 1 pixel thin rectangular frame with no fill.
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

// Fills a rectangular shape with a color.
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

// Fills the entire screen with a color.
void fillScreen(uint16_t color);



/* Advanced routines - draw triangular shapes based on lines */

// Draws an 1 pixel thin triangular shape with no fill.
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

// Fills a triangular shape with a color.
void fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);



/* Advanced routines - draw round shapes */

// Draws an 1 picel thin circle with no fill.
void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

// Fills a round shape with a color.
void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

// Helper function for the one above. Do not call directly unless you know what you are doing.
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

#endif // _GRAPHIC_SHAPES_H_
