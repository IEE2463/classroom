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

#ifndef _SPI_IMPLEMENT_ME_H_
#define _SPI_IMPLEMENT_ME_H_

#include <stdint.h>
#include <stdbool.h>

// The initialisation function. Call it once from your main() program before
// issuing any SPI commands with the functions below!
void SPI_Master_Init(void);

#define wc(DATA) SPI_Master_transmit_char(DATA, true)
#define wd(DATA) SPI_Master_transmit_char(DATA, false)

void SPI_Master_transmit_char(uint8_t data, bool commandmode);

#endif // _SPI_IMPLEMENT_ME_H_
