/*
 * state.h
 *
 * Created: 11/13/2022 7:39:34 PM
 *  Author: vklad
 */ 


#ifndef STATE_H_
#define STATE_H_

#include "avr/io.h"


#define RECEIVE_PAGES        (1 << GPIOR00)
#define RECEIVE_DATA         (1 << GPIOR01)
#define READ_FROM_EEPROM     (1 << GPIOR02)
#define RECEIVE_PAGE_SZ      (1 << GPIOR03) 


#endif /* STATE_H_ */