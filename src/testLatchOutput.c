#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "uart.h"
#include "xmem.h"

// Hardware definitions
#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
// Address Defintions
// #define IO_MEMORY ((AVR162_IO_MEMORY_REGS*)0x1000)

// // Address Structs
// typedef struct {
//     volatile uint16_t OLED_COMMAND[32];
//     volatile uint16_t OLED_DATA[32];
//     volatile uint16_t ADC[64];
//     volatile uint16_t SRAM[128];
// }AVR162_IO_MEMORY_REGS;


int main(void){

    // Initiating various devices
	USART_Init ( MYUBRR );
    //xmem_init();

    // Setting ports as output
    // DDRA = 1;
    // DDRE |= (1 << PE1);
    DDRA = 0xFF;
    DDRE = 0xFF;

    // Setting ports high
    // PORTE |= (1 << PE1);

    while (1) {
        PORTE = 0;
        // PORTA |= (1 << PA0) | (1 << PA1);
        PORTA = 0xFF;
        _delay_ms(9000);
        PORTE = 0xFF;
        _delay_ms(9000);
        PORTA = 0;
        _delay_ms(9000);
    };

	return 0;
}