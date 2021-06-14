

#ifndef _SPI_IMPLEMENT_ME_H_
#define _SPI_IMPLEMENT_ME_H_

#include <stdint.h>
#include <stdbool.h>

void SPI_Master_Init(void);

#define wc(DATA) SPI_Master_transmit_char1(DATA, true)
#define wd(DATA) SPI_Master_transmit_char1(DATA, false)

void SPI_Master_transmit_char(uint8_t data);

void SPI_Master_transmit_char1(uint8_t data, bool commandmode);

char SPI_Master_receive_char(void);

#endif // _SPI_IMPLEMENT_ME_H_