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

// void SRAM_test(void);

int main(void){

    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();

    uint16_t read_data_array[4] = {0,0,0,0};

    // printf("%s", adc_channels[1] );
    while (1) {
       ADC_print_all_channels(read_data_array);
        _delay_ms(15000);
        // ADC_select_channel(LEFT_SLIDER); 
        // uint8_t readData = xmem_read( 0, ADC);
        // printf("data has been read: %d\n\r", readData);
    };

	return 0;
}