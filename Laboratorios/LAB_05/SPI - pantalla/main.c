/***************************************************
 * This is an example program on how to use the
 * ST7735R based 1.8" color TFT LCD display from
 * Adafruit Industries with the Atmel ATmega328PB
 * Xplained mini developer board.
 * Note that this display also contains a micro SD
 * card socket on its back side.
 *
 * See here for further information:
 * http://www.adafruit.com/products/358
 *
 *
 * Note that a lot of this code is directly taken from
 * the C code examples found in the Atmel datasheets.
 * Other parts of the code are inspired by and based on
 * the Adafruit example programs for Arduino.
 *
 * This code is under the MIT licence.
 *
 ****************************************************/

// Few modification for work in CCS.
/*
 * Adaptations by:
 *      + Camila Turrieta
 *      + Felipe Sanchez
 *      + Jose Gutierrez
 */

//REF: base code LAB08-SPI SEP:2019-II
//REF: MSP-EXP432P401R_Software_Examples_windows - HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735
//REF SPI: MSP430F55xx_Code_Examples - MSP430F55xx_uscia0_spi_09
/****************************************************/
//Programa de prueba para TFT.

#include <msp430.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "USART/USART_implement_me.h"
#include "SPI/SPI_implement_me.h"

#include "display/ST7735_commands.h"
#include "display/graphic_shapes.h"
#include "display/testroutines.h"

/** The main function */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                           //Stop watchdog timer

    //Initialise the serial communication interface.
    struct USART_configuration config_57600_8N1 = {57600, 8, 'N', 1};
    USART_Init(config_57600_8N1);
    USART_Transmit_String("Welcome to the SPI test!\r\n");

    //SPI initialisation and TFT initialisation
    USART_Transmit_String("Initialising hardware... ");

    /***Fill here***/

    USART_Transmit_String("success.\n");

    //Variables for Color test:
    uint8_t pixel_y;
    uint8_t pixel_x;

    // Test programs. The following sequence runs many different images over the display.
    // Apart from that, feel free to adapt and explore this code and the functions called by it.

    USART_Transmit_String("Starting next run of test graphics: ");

    // RGB test
    fillScreen(ST7735_RED);     // Fully red screen.
    __delay_cycles(1048576);    //delay 1seg
    fillScreen(ST7735_GREEN);   // Fully green screen.
    __delay_cycles(1048576);    //delay 1seg
    fillScreen(ST7735_BLUE);    // Fully blue screen.
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");


    // Color test: Starts with green at (0,0) and fades to red along the x axis and
    // to blue along the z axis. Gives a good overview of the color capabilities
    // of the display.
    for(pixel_y=0; pixel_y<TFT_HEIGHT; pixel_y++)
    {
        for(pixel_x=0; pixel_x<TFT_WIDTH; pixel_x++)
        {
            int16_t green = 255-(pixel_x+pixel_y)/2;
            if (green < 0)
                green = 0;
            drawPixelRGB(pixel_x, pixel_y, pixel_x+95, green, pixel_y+127);
        }
    }
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");


    // Adds a circle to the previous image. This shows the imperfections of the
    // used algorithm very well!
    drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 50, ST7735_RED);
    drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 49, ST7735_RED);
    drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 51, ST7735_RED);
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");


    // Draws a small 2x2 square in each corner and a green pixel in the center.
    // Useful to identify the display rotation.
    fillScreen(ST7735_BLACK);
    testcorners();
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");


    // Draws rays of yellow lines originating in each of the corners.
    testlines(ST7735_YELLOW);
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");


    // Draws many boxed triangles.
    testtriangles();
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");


    // Draws many rectangles.
    testdrawrects(ST7735_GREEN);
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");


    // Draws many *filled* rectangles.
    testfillrects(ST7735_MAGENTA, ST7735_YELLOW);
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");

    // Draws discs and circles.
    fillScreen(ST7735_BLACK);
    testfillcircles(10, ST7735_BLUE);
    testdrawcircles(7, ST7735_WHITE);
    __delay_cycles(1048576);    //delay 1seg
    USART_Transmit_String("#");

    USART_Transmit_String(" finished!\n");
    __delay_cycles(1048576);    //delay 1seg

    USART_Transmit_String("Starting TFT char test: ");
    fillScreen(ST7735_BLACK);
    drawtext(0,1,"Sistemas", ST7735_GREEN2, ST7735_BLACK,1);
    drawtext(3, 4, "Electronicos",ST7735_CALYPSO, ST7735_BLACK,1);
    drawtext(9, 7,"Programables", ST7735_ORANGE, ST7735_BLACK,1);
    __delay_cycles(10486);
    drawtext(7,12, "2020 - 2", ST7735_MAGENTA, ST7735_BLACK,1);
    __delay_cycles(104858);

    USART_Transmit_String(" finished!\n");
    __delay_cycles(1048576);    //delay 1seg


    while(1)
    {
    	__no_operation;
    }

}
