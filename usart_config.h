/*
 * usart_config.h
 *
 * Created: 8/1/2021 10:15:13 PM
 *  Author: kladov
 */ 

//#include "common.h"

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#define USART_BAUDRATE 57600 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

#define RX_COMPLETE_INTERRUPT         (1<<RXCIE0)
#define TX_COMPLETE_INTERRUPT         (1<<TXCIE0)   
#define DATA_REGISTER_EMPTY_INTERRUPT (1<<UDRIE0)

void USART_Init();
void USART_SendStr(char *s);
void USART_Transmit(char c);

#endif /* USART_CONFIG_H_ */