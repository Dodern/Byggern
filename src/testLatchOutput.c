#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "uart.h"
#include "xmem.h"
#include "testSRAM.h"

// Hardware definitions
#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

// void SRAM_test(void);

int main(void){

    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();


    uint8_t number = 50;
    // SRAM_test();

    while (1) {
        xmem_write(number, 500, SRAM);
        printf("data has been written\n\r");
        _delay_ms(3000);
        uint16_t data = xmem_read(500, SRAM);
        printf("data has been read: %d\n\r", data);
    };

	return 0;
}