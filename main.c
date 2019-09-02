#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "uart.h"

#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void){

	USART_Init ( MYUBRR );
	_delay_ms(5000);
	USART_Transmit("A");
	_delay_ms(5000);
	USART_Transmit("B");

	 while (1) {
		PORTA |= (1 << PA0);
		USART_Transmit("A");
		_delay_ms(3000);
		PORTA &= ~(1 << PA0);
		USART_Transmit("B");
		_delay_ms(3000);
    }

	return 0;
}