// Libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

// Common
#include "bit_macros.h"
#include "uart.h"
#include "can_controller_driver.h"
#include "can_driver.h"
#include "mcp2515.h"
#include "spi_driver.h"

// Node 1/3
#include "xmem.h"

// Test-SRAM
#include "testSRAM.h"


// Defines
#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){
    // Initiating various devices
    USART_Init ( MYUBRR );
    xmem_init();

    can_controller_init();

    struct can_message message;

    while (1) {
        message = can_read_message(0);
        if (message.id == TEST_SRAM){
            printf("Ready to test SRAM\n\r");
            SRAM_test_can();
        }
        _delay_ms(10000);
    }
    return 0;
}
