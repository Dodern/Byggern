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

	 while (1) {
		PORTA |= (1 << PA0);
		_delay_ms(1000);
		PORTA &= ~(1 << PA0);
		_delay_ms(1000);
    }

	return 0;
}