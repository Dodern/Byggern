#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "uart.h"
#include "xmem.h"
#include "adc_driver.h"

// Hardware definitions
#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

// void SRAM_test(void);

int main(void){

    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();
    adc_init();

    while (1) {
        _delay_ms(1000);
        adc_print_all_channels();
        adc_print_button_states();
        // ADC_select_channel(LEFT_SLIDER); 
        // uint8_t readData = xmem_read( 0, ADC);
        // printf("data has been read: %d\n\r", readData);
    };

	return 0;
}
