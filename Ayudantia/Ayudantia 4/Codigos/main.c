
// MCU Clock Speed - needed for delay.h
#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Librerias propias
#include "USART/USART_implement_me.h"
#include "SPI/SPI_implement_me.h"
#include "I2C/I2C_implement_me.h"

// Librerias de enunciado
#include "display/ST7735_commands.h"
#include "display/graphic_shapes.h"
#include "display/testroutines.h"

// UART configuration
#define BAUD	57600					
#define UBRR_VALUE F_CPU/16/BAUD-1

// I2C configuration
#define TMP102_READ	 	0x91
#define TMP102_WRITE 	0x90

// Forma correcta para definir FSM (Finite State Machine)
typedef enum state{
	INICIO,
	TEMPERATURA	= '1',
	PANTALLA    = '2',
	EXIT		= '3'
} state_t;

// Funciones importantes
void menu(void);
void temperatura(void);
void pantalla(void);

int main(void)
{
	USART_Init(UBRR_VALUE);
	
	SPI_Master_Init();
	
	ST7735_Init();
	
	i2c_Init();
	
	state_t estado = INICIO;
	
	while(estado != EXIT){
		
		menu(); //HEADER DEL PROGRAMA PARA ELEGIR
		
		estado = (state_t) USART_Receive_char();
		
		switch (estado)
		{
			case TEMPERATURA:
				temperatura();
				break;
			
			case PANTALLA:
				pantalla();
				break;
			
			case EXIT:
				USART_Transmit_String("Chaolin Bombin\n\r");
				break;
			
			default:
				USART_Transmit_String("No se escogio nada...\n\r");
		}
	}

	_delay_ms(1000); // 1 seg delay
	
	return 0;
}

void menu(void)
{
USART_Transmit_String("*******************************************************\n\r");
USART_Transmit_String("***************** INTERFAZ DE USUARIO *****************\n\r");
USART_Transmit_String("*******************************************************\n\r");
USART_Transmit_String("\n\r");
USART_Transmit_String("\n\r");
USART_Transmit_String("	1:   Cuantos grados hay?\n\r");
USART_Transmit_String("\n\r");
USART_Transmit_String("	2:   Usar pantalla\n\r");
USART_Transmit_String("\n\r");
USART_Transmit_String("	3:   Exit/Salida\n\r");
}

void temperatura(void){
	uint8_t msb, lsb;
	int16_t temp;
	i2cSendStart();							// send start condition
	i2cWaitForComplete();
	i2cSendByte(TMP102_WRITE); 				// send WRITE address
	i2cWaitForComplete();
	i2cSendByte(0x00); 						//
	i2cWaitForComplete();
	
	i2cSendStart();							// send repeated start condition
	i2cWaitForComplete();
	
	i2cSendByte(TMP102_READ);				// send READ address of TMP102
	i2cWaitForComplete();
	i2cReceiveByte(true);					// receives one byte from the bus and ACKs it
	i2cWaitForComplete();
	msb = i2cGetReceivedByte(); 			// reads the MSB (it is a 12 bit value!)
	i2cWaitForComplete();
	i2cReceiveByte(false);					// receives one byte from the bus and NAKs it (last one)
	i2cWaitForComplete();
	lsb = i2cGetReceivedByte();				// reads the LSB
	i2cWaitForComplete();
	
	i2cSendStop();							// send stop condition
	TWCR = 0;								// stop everything
	
	// Convert the number to an 8-bit degree Celsius value
	temp = (msb<<8) | lsb;					// combine those two values into one 16 bit value
	temp >>= 4; 								// the values are left justified; fix that by shifting 4 right
	// negative numbers are represented in two's complement, but we just shifted the value and thereby potentially messed it up
	if(temp & (1<<11))						// Hence: if it is a negative number
	temp |= 0xF800;						// restore the uppermost bits
	
	// The 12 bit value has 0.0625°C precision, which is too much for what we want (and the sensor is anyways only about 0.5°C precise)
	// 0.0625 is 1/16 -> Dividing by 16 leaves 1°C precision for the output. Note that shifting >> 4 might go wrong here for negative numbers.
	temp /= 16;
	
	// Enviando por UART temperatura
	
	USART_Transmit_String("\r\nTemperature: ");
	char buffer[10];
	itoa(temp, buffer, 10);
	USART_Transmit_String(buffer);
	USART_Transmit_String(" deg. Celsius\r\n\r\n");
}

void pantalla(void){
	// RGB test
	fillScreen(ST7735_RED);		// Fully red screen.
	_delay_ms(1000);
	fillScreen(ST7735_GREEN);	// Fully green screen.
	_delay_ms(1000);
	fillScreen(ST7735_BLUE);	// Fully blue screen.
	_delay_ms(1000);
	USART_Transmit_String("#");
	
	
	// Color test: Starts with green at (0,0) and fades to red along the x axis and
	// to blue along the z axis. Gives a good overview of the color capabilities
	// of the display.
	for(uint8_t pixel_y=0; pixel_y<TFT_HEIGHT; pixel_y++)
	{
		for(uint8_t pixel_x=0; pixel_x<TFT_WIDTH; pixel_x++)
		{
			int16_t green = 255-(pixel_x+pixel_y)/2;
			if (green < 0)
			green = 0;
			drawPixelRGB(pixel_x, pixel_y, pixel_x+95, green, pixel_y+127);
		}
	}
	_delay_ms(1000);
	USART_Transmit_String("#");
	
	
	// Adds a circle to the previous image. This shows the imperfections of the
	// used algorithm very well!
	drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 50, ST7735_RED);
	drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 49, ST7735_RED);
	drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 51, ST7735_RED);
	_delay_ms(1000);
	USART_Transmit_String("#");
	
	
	// Draws a small 2x2 square in each corner and a green pixel in the center.
	// Useful to identify the display rotation.
	fillScreen(ST7735_BLACK);
	testcorners();
	_delay_ms(1000);
	USART_Transmit_String("#");
	
	
	// Draws rays of yellow lines originating in each of the corners.
	testlines(ST7735_YELLOW);
	_delay_ms(1000);
	USART_Transmit_String("#");
	
	
	// Draws many boxed triangles.
	testtriangles();
	_delay_ms(1000);
	USART_Transmit_String("#");
	
	
	// Draws many rectangles.
	testdrawrects(ST7735_GREEN);
	_delay_ms(1000);
	USART_Transmit_String("#");
	
	
	// Draws many *filled* rectangles.
	testfillrects(ST7735_MAGENTA, ST7735_YELLOW);
	_delay_ms(1000);
	USART_Transmit_String("#");
	
	// Draws discs and circles.
	fillScreen(ST7735_BLACK);
	testfillcircles(10, ST7735_BLUE);
	testdrawcircles(7, ST7735_WHITE);
	_delay_ms(1000);
	USART_Transmit_String("#");
}
