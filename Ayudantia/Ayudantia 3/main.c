/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * receive functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate
 * in order to see the test message below.
 *
 * Hint: You can not connect your terminal to this board
 * and avrdude at the same time. Disconnect your terminal
 * software when loading a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************/


// MCU Clock Speed - needed for delay.h
#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>


// Have a look at both the .h and the .c file, thee is code missing.
//#include "USART_implement_me.h"


struct USART_configuration
{
	uint16_t baudrate;
	uint8_t databits;
	uint8_t paridad;
	uint8_t stopbits;
};






// Call once to initialise USART communication
uint8_t USART_Init(struct USART_configuration config);

// Transmits a single character
void USART_Transmit_char(uint8_t data );

// Receives a single character
char USART_Receive_char(void);








/* The main function */
int main(void)
{
	
	
	// Initialise the serial communication interface
	// You can change it if you want
	struct USART_configuration config_57600_8N1 = {57600, 8, 'N', 1};
	USART_Init(config_57600_8N1);
	//buffer_t buffer;
	//int buff_size = 20;
	//init(&buffer, buff_size);
	char recibido='a';
	
	DDRB |= (1 << DDB1)|(1 << DDB2);// PB1 and PB2 is now an output

	TCCR1A |= (1 << WGM11);// en 109 pero en 278 se ve los registros 
	TCCR1B |= (1 << WGM12)|(1 << WGM13);// set Fast PWM mode using ICR1 as TOP->110 explicado en 101
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);// set none-inverting mode-->>pag 108	
	TCCR1B |= (1 << CS11);// START the timer with no prescaler

	ICR1 = 39999;// 20ms uso clock de cpu en 16MHz
	OCR1A = 3000;// set PWM for 0° (3000) 90° (1000) -90°(5000)
	//OCR1B = 1998;// set PWM for 45° duty cycle @ 16bit Y 3996 PARA -45
	
	
	while(1)
	{
		recibido = USART_Receive_char();
		if (recibido == 'd')
		{
			USART_Transmit_char(recibido);
			if (OCR1A >= 1030) //limit of duty cycle or angle
			{
				OCR1A -= 20;
			}
		}
		if (recibido == 'a')
		{
			USART_Transmit_char(recibido);
			if (OCR1A <= 4970) //limit of duty cycle or angle
			{
				OCR1A += 20;
			}
		}		

	}
}



uint8_t USART_Init(struct USART_configuration config)
{
	uint8_t flag = 0;
	UBRR0 = ((F_CPU/((config.baudrate)*16UL)) - 1);//UL->unsigned long; en la msp es distinto con registros
	UCSR0B|=(1<<TXEN0);
	UCSR0B|=(1<<RXEN0);

	switch (config.databits)
	{
		case 5:
		UCSR0C = 0x0;
		break;
		
		case 6:
		UCSR0C = (1 << UCSZ00);
		break;
		
		case 7:
		UCSR0C = (1 << UCSZ01);
		break;
		
		case 8:
		UCSR0C = (1 << UCSZ01)|(1 << UCSZ00);
		break;
		
		default:
		flag |= (1 << 2);
		break;
	}
	
	switch (config.paridad)
	{
		case 'N':
		//UCSR0C |= 0x0;//no necesario
		break;
		
		case 'E':
		UCSR0C |= (1 << UPM01);
		break;
		
		case 'O':
		UCSR0C |= (1 << UPM01)|(1 << UPM00);
		break;
		
		default:
		flag |= (1 << 1);
		break;
	}
	switch (config.stopbits)
	{
		case 1:
		UCSR0C |= 0x0;
		break;
		
		case 2:
		UCSR0C |= (1 << USBS0);
		break;
		
		default:
		flag |= 1;
		break;
	}

	if (config.baudrate < 1200)
	{
		flag |= (1 << 3);
	}
	
	return flag;
}



// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	while(!(UCSR0A&(1<<UDRE0)))///* Wait for empty transmit buffer */
	{
	}
	UDR0 = data;///* Put data into buffer, sends the data */
}




// Receives a single character
char USART_Receive_char(void)
{
	while(!(UCSR0A&(1<<RXC0)))///* Wait for data to be received */
	{
	}
	return UDR0;/* Get and return received data from buffer */
	
}

