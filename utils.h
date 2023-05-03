/*
 * utils.h
 *
 * Created: 11/13/2022 11:14:48 AM
 *  Author: vklad
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#include <avr/io.h>
#include <stdlib.h>


uint32_t conv_a2i(char*);
void conv_i2a(uint32_t, char*);
void conv_i2hex(uint8_t, char*);
uint16_t conv_a2i_hex(char*, uint8_t);


#endif /* UTILS_H_ */