#include <avr/io.h>

#include "SPI_implement_me.h"

#define DD_RST  1   //PB1
#define DD_SS   2   //PB2
#define DD_MOSI 3   //PB3
#define DD_MISO 4   //PB4
#define DD_SCK  5   //PB5

#define CARD_CS 0   //PC0
#define TTF_CS 1    //PC1
#define D_C 2       //PC2

void SPI_Master_Init(void){	
	DDRB |= (1<<DD_MOSI) | (1<<DD_SCK) | (1<<DD_SS) | (1<<DD_RST);
	DDRB &= ~(1<<DD_MISO); //MASTER IN SLAVE OUT COMO INPUT
	//SSs...
	DDRC |=(1<<CARD_CS) | (1<<TTF_CS) | (1<<D_C); //SS DEL SDCARD y SS de TTF
	SPCR = (1<<SPE)|(1<<MSTR);
	PORTC |= (1<<CARD_CS) | (1<<TTF_CS);
}
void SPI_Master_transmit_char(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

void SPI_Master_transmit_char1(uint8_t data, bool commandmode)
{
	PORTC |= (1<<CARD_CS); //DESAHIBILITA COMUNIACION CON SD
	PORTC &= ~(1<<TTF_CS); //HABILITA COM CON DISPLAY
	if(commandmode) PORTC &= ~(1<<D_C);
	else PORTC |= (1<<D_C);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	PORTC |= (1<<TTF_CS); //DESAHILITA COM CON DISPLAY
	
}

char SPI_Master_receive_char(void)
{
	SPI_Master_transmit_char(0xFF);
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}