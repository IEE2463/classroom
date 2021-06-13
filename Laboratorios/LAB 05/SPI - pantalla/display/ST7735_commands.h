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
 * This library is based on the original SPI display libraries and example
 * codes written by Limor Fried/Ladyada for Adafruit Industries.
 * The original library was designed for use with the Arduino system.
 * 
 * This code is a port of the Ladyada code to plain GNU-C. It can
 * be used to control the display without any operating system or
 * additional infrastructure.
 * 
 * 
 * This file contains various definitions.
 * They provide easier to handle literals for some SPI commands (hex
 * values). Send these commands over the SPI bus using the "wc()" macro
 * from the accompanying SPI library. The original library contains
 * many more macros. Search there and in the ST7735 display controller
 * datasheet for more information.
 * 
 * The display initialisation function provided here has to be called once
 * after powering up the display. It configures the ST7735R display controller
 * to the needed mode and does a lot of setup stuff. Seriously, this makes
 * using this display much easier! Feel free to fiddle with it, but it might be
 * a very good idea to get the display running with the provided values first.
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

#ifndef _ST7735_COMMANDS_H_
#define _ST7735_COMMANDS_H_


// TFT controller commands
#define ST7735_SWRESET 0x01
#define ST7735_SLPOUT  0x11

#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4

#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1


// Display rotation control commands
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08             //para la config de colores de la pantalla. REF: Crystalfontz128x128_ST7735
                                    //otra REF:  some low end asian-made display modules being sold on ebay and
                                    //elsewhere have red/blue reversal. ST7735_primitives.c


// Color definitions
// You can use any color value in 565 format,
// but here are a few handy shortcuts to start with.
// Color definitions
// You can use any color value in 565 format,
// but here are a few handy shortcuts to start with.
#define ST7735_BLACK   0x0000
#define ST7735_BLUE    0x001F
#define ST7735_RED     0xF800
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF


// Few modification
#define ST7735_CALYPSO 0x6FBD
#define ST7735_ORANGE  0xFC00
#define ST7735_GREEN2  0x0640



// Display controller setup code. Run once before issuing any data commands to
// the display.
void ST7735_init(void);


#endif // _ST7735_COMMANDS_H_
