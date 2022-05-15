//REF: MSP-EXP432P401R_Software_Examples_windows - BOOSTXL-EDUMKII_Temperature_MSP432P401R
//REF: LAB09 SEP 2019-2 AVR-CODE para TMP102 sensor

//Programa lee la temperatura del sensor TMP006 a traves de protocolo I2C e imprime el valor en RealTerm por UART.
//Temperatura con 2 decimales
//CONEXIONES: MKII

#include <msp430F5529.h>

#include <stdlib.h>
#include <stdbool.h>

// Have a look at both the .h and the .c file, there is code missing.
// Reuse the code from previous labs!
#include "USART/USART_implement_me.h"

// Have a look here, too! You are supposed to complete the function
// bodies and enable I2C communication for your application!
#include "I2C/I2C_implement_me.h"

#define TMP006_ADR  0x // Completar con direccion

// Config TMP006
void tmp006Config(void);

// Read TMP006
int16_t tmp006Read(void);


/* The main function */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                         //Stop watchdog

    P1DIR |= BIT0;

    // Complete with the require pinout.


    // Initialise the serial communication interface.
    struct USART_configuration config_57600_8N1 = {57600, 8, 'N', 1};
    USART_Init(config_57600_8N1);

    // Configure el TMP006
    tmp006Config();

    USART_Transmit_String("Welcome to the TMP006 I2C temperature sensor test!\r\n");

    int16_t temperature = 0;                    // Variable to store data

    while(1)
    {
        temperature = tmp006Read();             //read Temperature of TMP006
        
        USART_Transmit_String("Value is: ");

        /* 
        Complete with the required conversion to get two decimals and send the value over UART. 
        
        Final format must be 24.53

        The final value is in Celsius.

        */

        USART_Transmit_String(" deg. Celsius\r\n");

        P1OUT ^= BIT0;                              // heartbeat LED

        // Bad delay
        __delay_cycles(1048576);                    //Delay: (x*1/1048576Hz) seg

    }
    return 1;
}


// Config TMP006
void tmp006Config(void)
{
    // Complete if necessary
    i2cConfig(TMP006_ADR);
}

//Read a tmp006 sensor
int16_t tmp006Read(void)
{
    uint8_t msb, lsb;
    int16_t temp;

    // Complete I2C Proccess to communicate with TMP006


    temp = /* combine those two values into one 16 bit value */;
    temp >>= 2;      // the values are left justified; fix that by shifting 2 right -> Datasheet TMP006

    // The 14 bit value has 0.03125C precision

    return(temp);
}
