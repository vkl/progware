/*
 * progware.c
 *
 * Created: 11/12/2022 8:59:25 AM
 * Author : vklad
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
//#include <stdlib.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

#include "usart_config.h"
#include "utils.h"
#include "state.h"
#include "eeprom.h"
#include "spi.h"


#define BUFF_SZ 33

volatile int8_t c;
volatile int8_t i = 0;
volatile int8_t buf[BUFF_SZ];
volatile int8_t curr;
volatile uint16_t pages = 0;
volatile uint16_t currPage = 0;
volatile uint8_t currByte = 0;
volatile int8_t data[PAGE_SZ];

volatile uint16_t totalAddr = 0;

/*
ISR(USART_TX_vect) {
	;;
}
*/

ISR(USART_RX_vect) {
	while ( UCSR0A & (1<<RXC0) )
	{
		curr = UDR0;
	}
	
	/* receive data */
	if (GPIOR0 & RECEIVE_DATA) {
		data[currByte] = curr;
		currByte++;
		if (currByte >= PAGE_SZ) {
			
			writeEEPROMPage(currPage, data);
			currPage++; currByte = 0;
			USART_Transmit('\r');
			
			if (currPage >= pages) {
				GPIOR0 = 0; currPage = 0;
			}
			
		}
		return;
	}
	
	if (curr == '\r') {
		
		/* receive pages number */
		if (GPIOR0 & RECEIVE_PAGES) {
			pages = (uint16_t)conv_a2i_hex(&buf[2], 4);
			USART_SendStr(buf);
			USART_SendStr("OK\r");
			GPIOR0 &= ~RECEIVE_PAGES;
			GPIOR0 |= RECEIVE_DATA;
			currPage = 0;
		}
		
		/* read from EEPROM */
		if (GPIOR0 & READ_FROM_EEPROM) {
			readEEPROM(totalAddr);
			GPIOR0 = 0;
			USART_Transmit('\r');
		}
		
		/* command mode */
		else if (GPIOR0 == 0) {
			
			if (strcmp(buf, "ping") == 0) {
				USART_SendStr("OK\r");
			
			} else if (strncmp(buf, "read addr", 9) == 0) {
				uint16_t addr = (uint16_t)conv_a2i_hex(&buf[12], 4);
				uint8_t rom_data = readAddr(addr);
				char sbuf[] = {0, 0, 0, 0, 0};
				conv_i2hex(rom_data, sbuf);
				USART_SendStr(sbuf);
				USART_SendStr(" OK\r");
			
			} else if (strncmp(buf, "write addr", 10) == 0) {
				uint16_t addr = (uint16_t)conv_a2i_hex(&buf[13], 4);
				uint8_t rom_data = (uint8_t)conv_a2i_hex(&buf[20], 2);
				writeAddr(addr, rom_data);
				USART_SendStr("OK\r");
			
			} else if (strcmp(buf, "write") == 0) {
				USART_SendStr("OK\r");
				GPIOR0 |= RECEIVE_PAGES;
			
			} else if (strncmp(buf, "read", 4) == 0) {
				totalAddr = (uint16_t)conv_a2i_hex(&buf[7], 4);
				USART_SendStr("OK\r");
				GPIOR0 |= READ_FROM_EEPROM;
	
			} else {
				USART_SendStr("ERR\r");
				GPIOR0 = 0;
		
			}
		}
		
		for (uint8_t j=0; j<16; j++) buf[j] = 0;
		i = 0;
	
	} else {
		buf[i] = curr;
		i++;
		if (i >= BUFF_SZ) i = 0;
	}	
}

void PORT_Init() {
	GPIOR0 = 0; // General purpose registry, used to keep state
	SPI_Init();
	EEPROM_Init();
	USART_Init();
}

int main(void)
{
	cli();
	PORT_Init();
	sei();
	
	/* Replace with your application code */
    while (1) 
    {
    }
}

