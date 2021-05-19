/* 
Name: EjemploWatchdog.c
Author: Felipe Sanchez Varas
Version: 1.0
Date: 05-19-2021
Comments:
    - Archivo de ejemplo de uso de watchdog para el curso IEE2463 SEP. 
    - Realiza un blink Led cada 250 ms controlado por el Watchdog 
*/


#include <msp430.h> 


int main(void)
{

    // Configurar el tiempo del watchdog timer

    WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL + WDTIS2 + WDTSSEL0 + WDTIS0;

    // La linea anterior puede ser reemplazada por
    // WDTCTL = WDT_ADLY_250; 
    // En Code Composer Studio. 

    // Habilitar interrupciones

    SFRIE1 |= WDTIE;

    // Habilitar pin

    P1DIR |= BIT0;

    // Habilitar modo de bajo consumo


    __bis_SR_register(LPM4_bits + GIE);
    __no_operation();


	return 0;
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{

    P1OUT ^= BIT0;
}
