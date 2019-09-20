#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "uart.h"
#include "xmem.h"
#include "ADC.h"

// Hardware definitions
#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



int main(void){
    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();
    uint8_t number = 50;
    while (1) {
        xmem_write(number,1, OLED_DATA);
    };

	return 0;
}