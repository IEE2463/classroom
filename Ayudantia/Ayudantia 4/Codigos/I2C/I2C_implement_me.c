// includes
#include <avr/io.h>

#include "I2C_implement_me.h"

void i2c_Init(void)
{
	TWBR = 12;									// 400 kHz at 16MHz crystal and no prescaler
	TWSR &= ~((1 << TWPS1) | (1 << TWPS0));		// prescaler 0
	TWDR = 0xFF;								// sending only ones equals an idle high SDA line
	TWCR = (1<<TWEN)|							// Enable TWI-interface and release TWI pins.
	(0<<TWIE)|(0<<TWINT)|				// Disable Interupt.
	(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|	// No Signal requests.
	(0<<TWWC);							
}



// Send a start condition
void i2cSendStart()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
}




// Send a stop condition
void i2cSendStop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}




// Waits for the previous operation to finish
void i2cWaitForComplete()
{
	while(!(TWCR & (1<<TWINT)));
}




// Transmits one byte over the bus to a slave
// (Can be either an address or a value.)
void i2cSendByte(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
}




// Receives one byte from a slave
// (Always a value; master has no address.)
// Send an ACK if you expect more data, NAK if not.
void i2cReceiveByte(bool sendAnACK)
{
	if(sendAnACK){
		TWCR = (1<<TWEA)|(1<<TWINT)|(1<<TWEN);;
	}
	else{
		TWCR = (1<<TWINT)|(1<<TWEN);;
	}
}




// After receiving a byte, fetch this byte from the TWDR register
// (if you are interested in it).
// It is possible to *not* call this function after a call to
// i2cReceiveByte() if you are not interested in the actual value.
unsigned char i2cGetReceivedByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	return TWDR;	
}