//REF: base code LAB08-SPI SEP:2019-II
//REF: MSP-EXP432P401R_Software_Examples_windows - HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735
//REF SPI: MSP430F55xx_Code_Examples - MSP430F55xx_uscia0_spi_09

/*
 * name: SPI LAB
 * Author:
 *     Camila Turrieta
 *     Felipe Sanchez
 *     Jose Gutierrez
 *
 * Microcontroller:
 *      MSP430F5529
 * Copyright (c) 2012, Texas Instruments Incorporated
 *
 */

#include <msp430.h>

#include "SPI_implement_me.h"


void SPI_Master_Init(void)
{
  //Rellenar aquí: configurar puertos GPIO (Ver datasheet del Boostek pack) y
  //configurar periférico con protocolo SPI (Ver User's Guide)
}


void SPI_Master_transmit_char(uint8_t data, bool commandmode)
{
  //Rellenar con estado del puerto RS/CS
  //HINT: revisar macros wc y wd en archivo "SPI_implement_me.h"

  //Rellenar con acción para transmitir
}
