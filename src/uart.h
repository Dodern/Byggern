#include <avr/io.h>
#include <stdio.h>

void USART_Init( unsigned int ubrr );
int USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );