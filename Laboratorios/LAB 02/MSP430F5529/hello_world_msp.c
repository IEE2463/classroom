#include <msp430.h>

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;  //Stop watchdog timer, it runs by default.
    P1DIR |= 0x01;             //Port 1 direction register, Pin0 as output

    volatile unsigned int i;

    while (1) //Infinite loop
    {
        P1OUT ^= 0x01; // Toggle P1.0 (XOR)
   		for(i = 10000; i>0; i--); // Busy wait delay
    }

    return 0;

}
