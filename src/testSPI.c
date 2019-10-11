#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "uart.h"
#include "xmem.h"
#include "adc_driver.h"
#include "oled_driver.h"
#include "spi_driver.h"
#include "bit_macros.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void){
    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();
    adc_init();
    oled_init();

    spi_master_init();
    //// Setting the direction of test pin
    // set_bit(DDRB, DDB3);

    while (1) {
        clear_bit(PORTB, PORTB4);
        spi_master_transmit('c');
        set_bit(PORTB, PORTB4);
    }
    return 0;
}