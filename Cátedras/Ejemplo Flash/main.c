#include <msp430.h> 
#include "USART/USART.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main.c
 */

// Function prototypes
void write_SegC(char value, unsigned int pos);
char read_SegC(unsigned int pos);
void delay_ms(unsigned int ms);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //UART INIT at 57600
    struct USART_configuration config_57600_8N1 = {57600, 8, 'N', 1};
    USART_Init(config_57600_8N1);

    char value;
    char buffer[3];


   // Read Segment
   value = read_SegC(7);

   USART_Transmit_String("Read Value is: ");

   sprintf(buffer, "%d", value);

   USART_Transmit_String(buffer);

   USART_Transmit_String("\r\n");

   value++;

   USART_Transmit_String("Write Value is: ");

   sprintf(buffer, "%d", value);

   USART_Transmit_String(buffer);

   USART_Transmit_String("\r\n");

   write_SegC(value, 7);

   USART_Transmit_String("Done!\r\n");

    while(1)
    {

     __no_operation();                       // Loop forever, SET BREAKPOINT HERE
    }


}

//------------------------------------------------------------------------------
// Input = value, holds value to write to Seg C
//------------------------------------------------------------------------------
void write_SegC(char value, unsigned int pos)
{
  unsigned int i;
  char * Flash_ptr;                         // Initialize Flash pointer
  Flash_ptr = (char *) 0x1880;
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash seg
  FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

  for (i = 0; i < pos; i++)
  {
      Flash_ptr++;                          // Move pointer to requested position value to flash
  }

  *Flash_ptr = value;                     // Write value to flash

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
}


// Read specific space of C segment.

char read_SegC(unsigned int pos)
{
  unsigned int i;
  char value;

  char * Flash_ptr;                         // Initialize Flash pointer
  Flash_ptr = (char *) 0x1880;
  FCTL3 = FWKEY;                            // Clear Lock bit


  for (i = 0; i < pos; i++)
  {
      Flash_ptr++;                          // Move pointer to requested position value to flash
  }

  value = *Flash_ptr;                       // Read value from flash

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit

  return value;
}



