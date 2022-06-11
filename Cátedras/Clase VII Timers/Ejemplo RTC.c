/* 
Name: EjemploRTC.c
Author: Felipe Sanchez Varas
Version: 1.0
Date: 05-19-2021
Comments:
    - Archivo de ejemplo de uso de RTC para el curso IEE2463 SEP. 
    - Realiza un blink Led cada 1 seg controlado por el RTC
*/


#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    RTCCTL01 |= RTCRDYIE + RTCTEVIE + RTCAIE;
    RTCCTL01 |= RTCMODE;
    RTCCTL01 &= ~RTCHOLD;

	P1DIR |= BIT0;

    __bis_SR_register(LPM3_bits + GIE);
	return 0;
}


#pragma vector = RTC_VECTOR
__interrupt void RTC_ISR(void)
{
        switch (RTCIV)
        {
        case RTC_RTCRDYIFG:
                P1OUT ^= BIT0;
                break;
        }
}
