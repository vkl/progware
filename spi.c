/*
 * spi.c
 *
 * Created: 11/24/2022 9:09:15 AM
 *  Author: vklad
 */
#include "spi.h"


SPI_Init() {
	/* Set MOSI, SCK, SS as OE output, Shift Reg, Shift Reg Clear, all others input */
	SPI_DDR |= _BV(MOSI) | _BV(SCK) | _BV(OE) | _BV(RCL) | _BV(SRCLR);
	/* Enable SPI, Master,  LSB of the data word is transmitted first. Set clock rate freq clock/2 */
	SPCR |= _BV(SPE) | _BV(MSTR) | _BV(DORD);
	
	SPI_PORT |= _BV(OE); // disable output
	SPI_PORT &= ~_BV(SRCLR); // clear registry
	_delay_us(1);
	SPI_PORT |= _BV(SRCLR);
	SPI_PORT |= _BV(RCL);
	_delay_ms(1);
	SPI_PORT &= ~_BV(RCL);
	SPI_PORT &= ~_BV(OE); // enable output
}

void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}
 
