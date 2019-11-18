#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "xmem.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void){
    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();
    

    can_controller_init();

    uint8_t player_inputs[7];
    int player_inputs_length = SIZE(player_inputs);
    uint8_t arr[] = {0b01010101, 0b01001111, 0b01001011, 0b0111100}; //85, 79, 75, 60

    int counter = 0;

    while (1) {
        //adc_update_all_player_inputs(&player_inputs);
        // adc_print_current_position();
        // player_inputs[2] = 255;
        // player_inputs[3] = 130; 
        // player_inputs[5] = 1; 
        // if (counter > 10) {
        //     for (int i = 0; i < 7; i++) {
        //         //player_inputs[i] = 0;
        //         printf("player_inputs[%d] = %d\n\r", i, player_inputs[i]);
        //     }
        //     printf("\n\r");
        //     counter = 0;
        // }
        //can_send_message(0, player_inputs_length, &player_inputs, 1);
        can_send_array(1, &arr, 0);
        _delay_ms(100);
        counter++;
    }
    return 0;
}