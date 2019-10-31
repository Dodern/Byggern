
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>

#include "uart.h"
#include "xmem.h"
#include "adc_driver.h"
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
    adc_init();
    oled_init();


    oled_reset();
    oled_print_picture();
    _delay_ms(15000);
   

    while (1) {    
        // oled_print_main_menu();
        // oled_move_pointer(adc_get_joystick_direction());
        // _delay_ms(150);
        // printf("PB0 is: %d\n\r", PINB);
        if (adc_is_joystick_button_pressed()) {
            printf("Joystick button has been pressed!\n\r");
        }
    };


	return 0;
}
