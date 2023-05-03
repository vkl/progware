/*
 * spi.h
 *
 * Created: 11/24/2022 9:09:04 AM
 *  Author: vklad
 */ 


#ifndef SPI_H_
#define SPI_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define SPI_DDR  DDRB
#define SPI_PORT PORTB

#define MOSI     DDB3
#define SCK      DDB5
#define OE		 DDB2
#define RCL      DDB1
#define SRCLR    DDB0

void SPI_Init();
void SPI_MasterTransmit(char cData);



#endif /* SPI_H_ */