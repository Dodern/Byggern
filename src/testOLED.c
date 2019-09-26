
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "uart.h"
#include "xmem.h"
#include "ADC.h"
#include "oled_driver.h"
// #include "fonts.h"

// Hardware definitions
#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



int main(void){
    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();
    ADC_init();
    oled_init();
    
    while (1) {
        // oled_write_data(0xFF);
        // char char1 = 'a';
        // oled_print_char(char1);
        char hello[5] = {'h','e','r','r','o'};
        oled_print_string(hello);
        _delay_ms(50);
    };


	return 0;
}