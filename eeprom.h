/*
 * eeprom.h
 *
 * Created: 11/24/2022 9:05:56 AM
 *  Author: vklad
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

#include "spi.h"

#define EEPROM_DIR  DDRD
#define EEPROM_PORT PORTD
#define EEPROM_OE   PORTD4
#define EEPROM_WE   PORTD5
#define EEPROM_CE   PORTD3

#define PAGE_SZ 64

void EEPROM_Init();

void readEEPROM(uint16_t);
void writeEEPROM(uint16_t, uint8_t);
void writeEEPROMPage(uint16_t, uint8_t*);
uint8_t readAddr(uint16_t);
void writeAddr(uint16_t, uint8_t);


#endif /* EEPROM_H_ */