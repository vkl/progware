/*
 * eeprom.c
 *
 * Created: 11/24/2022 9:06:08 AM
 *  Author: vklad
 */

#include "eeprom.h"


void EEPROM_Init() {
	DDRD &= 0x3F; // PD6, PD7 input
	DDRC &= 0xC0; // PC0 - PC5 input
	EEPROM_DIR |= _BV(EEPROM_OE) | _BV(EEPROM_WE) | _BV(EEPROM_CE);
	EEPROM_PORT |= _BV(EEPROM_OE) | _BV(EEPROM_WE) | _BV(EEPROM_CE);
} 

void writeAddr(uint16_t addr, uint8_t rom_data) {
	EEPROM_PORT |= _BV(EEPROM_OE);
	EEPROM_PORT &= ~_BV(EEPROM_CE);
	
	/* Set address */
	SPI_MasterTransmit((uint8_t)(addr & 0xFF));
	SPI_MasterTransmit((uint8_t)((addr >> 8) & 0xFF));
	PORTB |= _BV(RCL);
	_delay_ms(1);
	PORTB &= ~_BV(RCL);
	
	/* Set data */
	DDRD |= 0xC0; // PD6, PD7 output
	DDRC |= 0x3F; // PC0 - PC5 output
	PORTD = (PIND & 0x3F) | (rom_data & 0xC0);
	PORTC = (PINC & 0xC0) | (rom_data & 0x3F);
	_delay_ms(50);

	EEPROM_PORT &= ~_BV(EEPROM_WE);
	_delay_us(50);

	EEPROM_PORT |= _BV(EEPROM_WE);
	EEPROM_PORT |= _BV(EEPROM_CE);
	
	DDRD &= 0x3F; // PD6, PD7 input
	DDRC &= 0xC0; // PC0 - PC5 input
}

uint8_t readAddr(uint16_t addr) {
	uint8_t data = 0;
	SPI_MasterTransmit((uint8_t)(addr & 0xFF));
	SPI_MasterTransmit((uint8_t)((addr >> 8) & 0xFF));
	PORTB |= _BV(RCL);
	_delay_ms(1);
	PORTB &= ~_BV(RCL);
	EEPROM_PORT &= ~_BV(EEPROM_OE);
	EEPROM_PORT &= ~_BV(EEPROM_CE);
	_delay_ms(1);
	data = ((PIND & 0xC0) | (PINC & 0x3F));
	_delay_ms(1);
	EEPROM_PORT |= _BV(EEPROM_OE);
	EEPROM_PORT |= _BV(EEPROM_CE);
	return data;
}

void readEEPROM(uint16_t totalAddr) {
	uint8_t data[PAGE_SZ];
	uint16_t pages = totalAddr / PAGE_SZ;
	uint16_t addr = 0;
	
	EEPROM_PORT &= ~_BV(EEPROM_OE);
	EEPROM_PORT &= ~_BV(EEPROM_CE);
	
	for (uint16_t page=0; page<pages; page++) {
		for (uint8_t byte_addr=0; byte_addr<PAGE_SZ; byte_addr++) {
			addr = page * PAGE_SZ + byte_addr;
			SPI_MasterTransmit((uint8_t)(addr & 0xFF));
			SPI_MasterTransmit((uint8_t)((addr >> 8) & 0xFF));
			PORTB |= _BV(RCL);
			_delay_us(5);
			PORTB &= ~_BV(RCL);
			_delay_us(5);
			data[byte_addr] = ((PIND & 0xC0) | (PINC & 0x3F));
		}
		for (uint8_t i=0; i<PAGE_SZ; i++) {
			USART_Transmit(data[i]);
		}
	}
	EEPROM_PORT |= _BV(EEPROM_OE);
	EEPROM_PORT |= _BV(EEPROM_CE);
}

void writeEEPROM(uint16_t pageAddr, uint8_t pageSz) {
	//PORTB |= (1 << PORTB5);
	for (uint8_t i=0; i<pageSz; i++) {
		; /* write to EEPROM */
	}
	//PORTB &= ~(1 << PORTB5);
}

void writeEEPROMPage(uint16_t pageAddr, uint8_t *data) {
	
	uint16_t addr = 0;
	pageAddr <<= 6;
	
	DDRD |= 0xC0; // PD6, PD7 output
	DDRC |= 0x3F; // PC0 - PC5 output
	EEPROM_PORT |= _BV(EEPROM_OE);
	EEPROM_PORT &= ~_BV(EEPROM_CE);
	
	for (uint8_t i=0; i<64; i++) {
		/* Set address */
		addr = pageAddr | i;
		SPI_MasterTransmit((uint8_t)(addr & 0xFF));
		SPI_MasterTransmit((uint8_t)((addr >> 8) & 0xFF));
		PORTB |= _BV(RCL);
		_delay_us(5);
		PORTB &= ~_BV(RCL);
		
		EEPROM_PORT &= ~_BV(EEPROM_WE);
		_delay_us(5);
		
		/* Set data */
		PORTD = (PIND & 0x3F) | (data[i] & 0xC0);
		PORTC = (PINC & 0xC0) | (data[i] & 0x3F);
		_delay_us(5);
		
		/* Initiate set data on EEPROM */
		EEPROM_PORT |= _BV(EEPROM_WE);
		_delay_us(5);
		
	}
	
	_delay_ms(10);
	DDRD &= 0x3F; // PD6, PD7 input
	DDRC &= 0xC0; // PC0 - PC5 input
	EEPROM_PORT |= _BV(EEPROM_CE);
	EEPROM_PORT |= _BV(EEPROM_WE);
}
