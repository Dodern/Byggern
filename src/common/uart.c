#include "uart.h"

void USART_Init(unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0)|(1 << TXEN0);
	/* Set frame format: 8 data, 2 stop bit */
	#if defined (__AVR_ATmega162__)
		UCSR0C = (1 << URSEL0)|(1 << USBS0)|(3 << UCSZ00);
		printf("uart init recognized node1");
    #elif defined (__AVR_ATmega2560__)
		UCSR0C = (1 << USBS0)|(3 << UCSZ00);
		printf("uart init recognized node2");
    #endif
	fdevopen(USART_Transmit, USART_Receive);
}

int USART_Transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1 << UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
	return 0;
}

unsigned char USART_Receive(void) {
	/* Wait for data to be received */
	while ( !(UCSR0A & (1 << RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}
