
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


    oled_reset();
    //char hello[6] = {'h','e','r','r','o','\0'};
   

    while (1) {
        ADC_print_all_channels();
        int direction = ADC_joystick_direction();
        ADC_print_direction(direction);
        ADC_joystick_position();
        ADC_print_current_position();
        oled_print_main_menu();
        oled_move_pointer(direction);
        _delay_ms(150);
        
    };


	return 0;
}