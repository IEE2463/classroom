/******************************************************************************************************
 ***************************            Buzzer library       ******************************************
 ******************************************************************************************************/

#include "buzzer.h"

/*
 * Global auxiliary variables
 *
 */
// Aqui se deberian crear las variables a utilizar

void beep (int frequencyInHertz, long timeInMilliseconds, long pausetimeInMilliseconds)
{
    // Cambiar contador/frecuencia del timer encargado de la frecuencia de la nota
    // Cambiar contador/frecuencia del timer encargado de mantener el tiempo que debe durar la nota.

    // Un pequeño delay para mantener la separacion de las notas
    speaker_low();
    noBeep(pausetimeInMilliseconds);
}

void noBeep(int timeInMilliseconds)
{

    // Cambiar contador/frecuencia del timer encargado de mantener el tiempo que debe durar el silencio.

}

void config_speaker_gpio(void)
{
    // Buzzer conectado a pint ____: define el pin como output
}

void speaker_high(void)
{
    // P____ HIGH

}

void speaker_low(void)
{
   // P____ LOW

}

/* XX, Puede ser A0, A1, B0... */

void timer_XX_config(void)
{
    /* 
     * Configuracion Timer A0
     * Seleccionar Clock y Preescaler
     * Seleccionar modo a utilizar
     * Habilitar Interrupciones y modo
     * Cuantos Bits tiene el timers.
     */
}

void config_timer_XX_frequency(int counter)
{
    // Aqui se debe configurar el timer dependiendo de la frecuencia requerida
}

void config_timer_XX_disable(void)
{
    // Deshabilitar el timer XX
}

void config_timer_XX_enable(void)
{
    // Habilitar el timer XX
}

// Estructura de interrupcion de TIMER A0 CC1-4
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
   switch(TA0IV)
  {

   case  2: break;                          // CCR1 
   case  4: break;                          // CCR2 not used
   case  6: break;                          // CCR3 not used
   case  8: break;                          // CCR4 not used
   case 10: break;                          // CCR5 not used
   case 12: break;                          // Reserved not used
   case 14: break;                          // If input frequency < 200Hz, trap here
   default: break;
  }

}


/* 
 *
 * Posiblemente requiera de uno o mas timers, por ende de una o mas interrupciones
 * En ese caso, recomendamos que mantenga la misma estructura, 
 * cambiando el nombre de las funciones de la manera que corresponda.
 */
