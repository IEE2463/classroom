/***************************************************
 *This is a USART library for the MSP430.
 *
 * It can provide basic USART (serial) communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 * 
 * 
 * 
 * FOR STUDENTS:
 * 
 * This file will be given to you in an 'empty' state. The function bodies are
 * provided, but not their content. You are supposed to add the proper code
 * and complete these functions.
 * 
 * 
 * Hint 1: We do not expect you to write the most performant or exceptionally
 * well-engineered code, but it should work. If in doubt, sacrifice speed for
 * reliability. 
 * 
 ****************************************************/


// includes
#include <msp430.h>
#include <string.h>

#include "USART_implement_me.h"



// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
//
// Call it at any time to change the USART communication parameters.
//
// Returns zero in case of success, non-zero for errors.
uint8_t USART_Init(struct USART_configuration config)
{
	// You can recycle your previous code. But remember, this time you are
	// supposed to configure interrupts! Maybe you]ll have to extend it a little bit?
}



// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	// A nice hint: With interrupts, you can send bytes whenever the register UCA1TXBUF
	// is free. And there is an interrupt called UCTXIFG that *tells you*
	// whenever UCA1TXBUF is free.
	// This requires you to have some bytes in the buffer that you would like to
	// send, of course. You have a buffer, don't you?
}



// Transmits a given string
void USART_Transmit_String(char* string)
{
}



// Receives a single character.
char USART_Receive_char(void)
{
	// A nice hint: With interrupts, your microcontroller can inform you whenever
	// a character comes in. There is an interrupt called UCRXIFG for that.
	// If such an interrupt would fill a buffer with the received data, this
	// function here could return you one character from this buffer. You would no
	// longer need to 'wait for the byte to arrive', but could just fetch it out
	// of this buffer at any later point. And of course you've got a buffer,
	// right?
	// If the buffer is actually empty, you could maybe return a 0 or so to
	// indicate that to the user?
}


// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
uint8_t USART_Receive_String(char* buffer, uint8_t bufflen)
{
	// Your previous code might need little adaptions here. As a nice hint: A
	// string consists of many characters. If a user gives you a buffer to fill
	// for him, and you have a buffer full of already received characters...
} 

