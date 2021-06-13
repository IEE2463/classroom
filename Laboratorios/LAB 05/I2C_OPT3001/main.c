//REF: MSP-EXP432P401R_Software_Examples_windows - BOOSTXL-EDUMKII_LightSensor_MSP432P401R
//REF: LAB09 SEP 2019-2 AVR-CODE para TMP102 sensor
//REF: OPT3001.cpp Created by Adrian Fernandez & Dung Dang, Dec 2013

//Programa lee la intensidad de luz visible del sensor OPT3001 a traves de protocolo I2C e imprime el valor en RealTerm por UART.
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

#define OPT3001_ADR  0x // Completar con direccion
#define DEFAULT_CONFIG_OPT3001 0b1100110000010000 // 

// Register for config an read 
#define RESULT_REG_OPT3001 0x00
#define CONFIG_REG_OPT3001 0x01

// Complete the following register RN[3:0] CT M[1:0]
/*  CONFIG REGISTER BITS: RN3 RN2 RN1 RN0 CT M1 M0 OVF CRF FH FL L Pol ME FC1 FC0
    RN3 to RN0 = Range select:
                    1100 by default, __________________
    CT = Conversion time bit
                    _ = ____ ms conversion time                    
    M1 to M0 = Mode bits
                    __ = ____ mode                    
    OVF (Bit 8) –   Overflow flag. When set the conversion result is overflown.
    CRF (Bit 7) –   Conversion ready flag. Sets at end of conversion. Clears by read or write of the Configuration register.
    FH (Bit 6)  –   Flag high bit. Read only. Sets when result is higher that TH register. Clears when Config register is 
                    read or when Latch bit is ‘0’ and the result goes bellow TH register.
    FL (Bit 5)  –   Flag low bit. Read only. Sets when result is lower that TL register. Clears when Config register is read 
                    or when Latch bit is ‘0’ and the result goes above TL register.
    L (Bit 4)   –   Latch bit. Read/write bit. Default ‘1’, Controls Latch/transparent functionality of FH and FL bits. When 
                    L = 1 the Alert pin works in window comparator mode with Latched functionality When L = 0 the Alert pin 
                    works in transparent mode and the two limit registers provide the hysteresis.
    Pol (Bit 3) –   Polarity. Read/write bit. Default ‘0’, Controls the active state of the Alert pin. Pol = 0 means Alert 
                    active low.
    ME (Bit 2)  –   Exponent mask. In fixed range modes masks the exponent bits in the result register to “0000”.
    FC1 to FC0  -   Fault count bits. Read/write bits. Default “00” - the first fault will trigger the alert pin.
*/


// Config OPT3001
void opt3001_config(void);

// Read OPT3001
int16_t opt3001_read(void);


/* The main function */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                         //Stop Watchdog

    P1DIR |= BIT0;

    // Complete with the require pinout.

    // Initialise the serial communication interface.
    struct USART_configuration config_57600_8N1 = {57600, 8, 'N', 1};
    USART_Init(config_57600_8N1);

    USART_Transmit_String("Welcome to the OPT3001 I2C light sensor test!\r\n");

    int16_t light = 0;                              //Variable to store data
    
    opt3001_config();
    
    while(1)
    {
        
        light = opt3001_read();                     //Read the lux from OPT3001
    
        USART_Transmit_String("Value is: ");
    
        /* 
        Complete with the required conversion to get two decimals and send the value over UART. 
        
        Final format must be 01234

        Five Digits.

        The final value is in Lux

        */

        USART_Transmit_String(" Lux\r\n");
        
        P1OUT ^= BIT0;                              // heartbeat LED

        __delay_cycles(1048576);                    //Delay: (x*1/1048576Hz) seg
    }
}


// Config OPT3001
void opt3001_config(void)
{
    // I2C initialisation MSP
    i2cConfig(OPT3001_ADR);

    // USE Config Register and config the default mode

    // Complete

}


// Read OPT3001
int16_t opt3001_read(void){
    uint8_t msb, lsb;
    int16_t value;


    // User result Register. Follow instructions in chapter 7.5 Programming of OPT3001 Datasheet.


    value =  /* combine those two values into one 16 bit value */;


    uint16_t exponent = 0;
    uint32_t result = 0;
    int16_t raw;

    raw = value;
    /*Convert to LUX*/

    //extract result & exponent data from raw readings

    result = /* Complete with the correct operation */ ;
    exponent = /* Complete with the correct operation */ ;

    //convert raw readings to LUX
    switch(exponent){
    case 0: //*0.015625
        result = result>>6;
        break;
    case 1: //*0.03125
        result = result>>5;
        break;
    case 2: //*0.0625
        result = result>>4;
        break;
    case 3: //*0.125
        result = result>>3;
        break;
    case 4: //*0.25
        result = result>>2;
        break;
    case 5: //*0.5
        result = result>>1;
        break;
    case 6:
        result = result;
        break;
    case 7: //*2
        result = result<<1;
        break;
    case 8: //*4
        result = result<<2;
        break;
    case 9: //*8
        result = result<<3;
        break;
    case 10: //*16
        result = result<<4;
        break;
    case 11: //*32
        result = result<<5;
        break;
    }
    return result;
}