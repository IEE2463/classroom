/***************************************************
 * This is a I2C library for the ATMega328P.
 *
 * It can provide basic I2C communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 * 
 * 
 * 
 * FOR STUDENTS:
 * 
 * This file is complete, but the according .c file not. See there and
 * implement the function bodies!
 * 
 ****************************************************/

#ifndef _I2C_IMPLEMENT_ME_H_
#define _I2C_IMPLEMENT_ME_H_

#include <stdbool.h>

// Init Configuration of I2C
void i2c_Init(void);

// Send a start condition
void i2cSendStart();

// Send a stop condition
void i2cSendStop();

// Waits for the previous operation to finish
void i2cWaitForComplete();

// Transmits one byte over the bus to a slave
// (Can be either an address or a value.)
void i2cSendByte(unsigned char data);

// Receives one byte from a slave
// (Always a value; master has no address.)
// Send an ACK if you expect more data, NAK if not.
void i2cReceiveByte(bool sendAnACK);

// After receiving a byte, fetch this byte from the TWDR register
// (if you are interested in it).
// It is possible to *not* call this function after a call to
// i2cReceiveByte() if you are not interested in the actual value.
unsigned char i2cGetReceivedByte(void);

#endif // _I2C_IMPLEMENT_ME_H_