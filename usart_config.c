/*
 * usart_config.c
 *
 * Created: 3/19/2022 11:47:49 AM
 *  Author: vklad
 */ 


#include "usart_config.h"


void
USART_Transmit(char data) {
    while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = data;
	while ( !( UCSR0A & (1<<TXCIE0)) );
}

void
USART_SendStr(char *s) {
    while (*s) {
        USART_Transmit(*s);
        s++;
    }
}

void
USART_Init() {
    // Set Baud Rate
    UBRR0H = BAUD_PRESCALER >> 8;
    UBRR0L = BAUD_PRESCALER;
    
    // Set Frame Format
    UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
    
    // Enable Receiver and Transmitter
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    
    // Interrupt receive enable
    UCSR0B |= RX_COMPLETE_INTERRUPT; // | TX_COMPLETE_INTERRUPT;
}