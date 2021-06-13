//REF: LAB09 SEP 2019-2 AVR-CODE
/***************************************************
 * This is a I2C library for the MSP430F5529.
 *
 * It can provide basic I2C communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 ****************************************************/

// includes
#include <msp430.h>
#include "I2C_implement_me.h"

// Config I2C
void i2cConfig(uint8_t slaveAddress)
{
	// Completar con la configuración necesaria

	i2cSlaveSet(slaveAddress);

}

// Set Slave Adress
void i2cSlaveSet(uint8_t slaveAddress)
{
}

// Set transmit: Write
void i2cSetWriteMode()
{	
}

// Set Transmit: READ
void i2CSetReadMode()
{
}

// Send a start condition
void i2cSendStart()
{
}


// Send a stop condition
void i2cSendStop()
{
}


// Waits for the previous operation to finish
void i2cWaitForComplete()
{
}


// Transmits one byte over the bus to a slave
// (Can be either an address or a value.)
void i2cSendByte(unsigned char data)
{
}




// Receives one byte from a slave
// (Always a value; master has no address.)
// Send an ACK if you expect more data, NAK if not.
void i2cReceiveByte(bool sendAnACK)
{
}


// It is possible to *not* call this function after a call to
// i2cReceiveByte() if you are not interested in the actual value.
unsigned char i2cGetReceivedByte(void)
{
}
