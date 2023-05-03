/*
 * utils.c
 *
 * Created: 11/13/2022 11:15:22 AM
 *  Author: vklad
 */

#include "utils.h" 


uint32_t conv_a2i(char* s) {
	uint32_t r = 0;
	char *p = s;
	while (*p) {
		r = (r * 10) + *p - 0x30;
		p++;
	}
	return r;
}

void conv_i2a(uint32_t n, char* s) {
	uint8_t i = 0;
	uint32_t pos = 100000;
	uint8_t f = 0;
	while (pos > 0) {
		if ((n / pos == 0) && f == 0) {
			pos /= 10;
			continue;
		}
		f = 1;
		s[i] = (n / pos) + 0x30;
		n %= pos;
		i++;  
		pos /= 10;
	}
	s[i] = 0;
}

void conv_i2hex(uint8_t data, char* s) {
	s[0] = '0'; s[1] = 'x';
	uint8_t b1 = ((data >> 4) & 0xF);
	uint8_t b0 = (data & 0xF);
	if (b1 <= 9) {
		s[2] = 0x30 + b1;
	} else {
		s[2] = 55 + b1;
	}
	if (b0 <= 9) {
		s[3] = 0x30 + b0;
	} else {
		s[3] = 55 + b0;
	}
}

uint16_t conv_a2i_hex(char* s, uint8_t sz) {
	uint16_t r = 0;
	for (uint8_t i=0; i<sz; i++) {
		if (s[i] >= 0x30 && s[i] <= 0x39) {  // between 0 - 9 in ascii 
			r |= ((s[i] - 0x30) << (4 * (sz - i - 1)));
		} else if (s[i] >= 0x41 && s[i] <= 0x46) { // between A - F 
			r |= ((s[i] - 0x37) << (4 * (sz - i - 1)));
		}
	}
	return r;
}
