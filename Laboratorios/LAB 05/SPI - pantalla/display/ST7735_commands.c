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

 #include <msp430.h>

#include "ST7735_commands.h"
#include "../SPI/SPI_implement_me.h"


// Display controller setup code. Run once before issuing any data commands to
// the display.
// This code is based on the according Adafruit library, but greatly shortened
// and simplified at the expense of efficiency. Comments inside this function
// point at the original places where these commands were derived from. Check
// there to learn more!
void ST7735_init(void)
{
	// Reset display once before trying anything else.
	// Required by the driver IC!

  //Rellenar aquí con un RESET HIGH
  //(EJ: PxOUT |= BITy;)

	__delay_cycles(524288);

  //Rellenar aquí con un RESET LOW

	__delay_cycles(524288);

  //Rellenar aquí con un RESET HIGH
	
	__delay_cycles(524288);



	// This is like Adafruit_ST7735::initR - start there to follow the program
	// flow and understand this command sequence!

	// Initialisation sequence Rcmd1
	wc(ST7735_SWRESET); __delay_cycles(157286);
	wc(ST7735_SLPOUT);  __delay_cycles(524288);
	wc(ST7735_FRMCTR1); wd(0x01); wd(0x2C); wd(0x2D);
	wc(ST7735_FRMCTR2); wd(0x01); wd(0x2C); wd(0x2D);
	wc(ST7735_FRMCTR3); wd(0x01); wd(0x2C); wd(0x2D); wd(0x01); wd(0x2C); wd(0x2D);
	wc(ST7735_INVCTR);  wd(0x07);
	wc(ST7735_PWCTR1);  wd(0xA2); wd(0x02); wd(0x84);
	wc(ST7735_PWCTR2);  wd(0xC5);
	wc(ST7735_PWCTR3);  wd(0x0A); wd(0x00);
	wc(ST7735_PWCTR4);  wd(0x8A); wd(0x2A);
	wc(ST7735_PWCTR5);  wd(0x8A); wd(0xEE);
	wc(ST7735_VMCTR1);  wd(0x0E);
	wc(ST7735_INVOFF);
	wc(ST7735_MADCTL);  wd(0xC8);
	wc(ST7735_COLMOD);  wd(0x05);

	// Initialisation sequence Rcmd2red
	wc(ST7735_CASET);   wd(0x00); wd(0x00); wd(0x00); wd(0x7F);
	wc(ST7735_RASET);   wd(0x00); wd(0x00); wd(0x00); wd(0x9F);

	// Initialisation sequence Rcmd3
	wc(ST7735_GMCTRP1);	wd(0x02); wd(0x1c); wd(0x07); wd(0x12);
	wd(0x37); wd(0x32); wd(0x29); wd(0x2D);
	wd(0x29); wd(0x25); wd(0x2B); wd(0x39);
	wd(0x00); wd(0x01); wd(0x03); wd(0x10);
	wc(ST7735_GMCTRN1);	wd(0x03); wd(0x1d); wd(0x07); wd(0x06);
	wd(0x2E); wd(0x2C); wd(0x29); wd(0x2D);
	wd(0x2E); wd(0x2E); wd(0x37); wd(0x3F);
	wd(0x00); wd(0x00); wd(0x02); wd(0x10);
	wc(ST7735_NORON);   __delay_cycles(10486);
	wc(ST7735_DISPON);  __delay_cycles(104858);

	// Change MADCTL color filter
	wc(ST7735_MADCTL);  wd(0xC0);

	// Set rotation to widescreen (horizontal).
	// (0,0) is in the top left corner.
	// x extends to the right.
	// y extends to the bottom.
	// Compare Adafruit_ST7735::setRotation and the datasheet for more info.

	wc(ST7735_MADCTL);
	//wd(MADCTL_MX | MADCTL_MV | MADCTL_BGR);                 //ORIENTACION RIGHT

	wd(MADCTL_MX | MADCTL_MY | MADCTL_BGR);                 //ORIENTACION UP

	//wd(MADCTL_MY | MADCTL_MV | MADCTL_BGR);                 //ORIENTACION LEFT
	//wd(MADCTL_BGR);                                          //ORIENTACION DOWN

}
