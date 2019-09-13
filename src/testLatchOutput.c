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

    // Setting ports as output
    // DDRA = 1;
    // DDRE |= (1 << PE1);
    // DDRA = 0xFF;
    // DDRE = 0xFF;

    // Setting ports high
    // PORTE |= (1 << PE1);
    uint8_t number = 50;
    // SRAM_test();

    while (1) {
        xmem_write(number, 500, SRAM);
        printf("data has been written\n\r");
        _delay_ms(3000);
        uint16_t data = xmem_read(500, SRAM);
        printf("data has been read: %d\n\r", data);

        // // PORTE = 0;
        // // PORTA |= (1 << PA0) | (1 << PA1);
        // PORTA = 0xFF;
        // PORTE = 0xFF;
        // _delay_ms(9000);
        // PORTA = 0;
        // _delay_ms(9000);
    };

	return 0;
}

void SRAM_test(void) {
    volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n\r");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();
    printf("Seed is: %d\n\r", seed);


    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = i+10;
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i,
            retreived_value, some_value);
            write_errors++;
        }
    }

    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed); // reset the PRNG to the state it had before the write phase
    printf("Seed is: %d\n\r", seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = i+10;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n\r%4d errors in write phase and \n\r%4d errors in retrieval phase\n\n\r", write_errors, retrieval_errors);
}