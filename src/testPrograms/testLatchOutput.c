#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "uart.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void){

	USART_Init ( MYUBRR );

	 while (1) {
		unsigned char letter = USART_Receive();
		// unsigned char letter = 'U';
		_delay_ms(3000);
		// printf("%c", letter);
		printf("hei\n");
    }

	return 0;
}