#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "xmem.h"
#include "adc_driver.h"
#include "oled_driver.h"
#include "spi_driver.h"
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
    adc_init();
    oled_init();

    oled_reset();
    oled_print_picture();
    

    can_controller_init();

    uint8_t player_inputs[7];
    int player_inputs_length = SIZE(player_inputs);

    uint8_t arr[] = {0b01010101, 0b01001111, 0b01001011, 0b0111100}; //85, 79, 75, 60
    uint8_t arr2[] = {0b01011101, 0b0100101, 0b01101011, 0b0111110}; //93, 37, 107, 62
    uint8_t arr3[] = {0,0};
    int length = SIZE(arr);
    int length2 = SIZE(arr2);
    int length3 = SIZE(arr3);

        // printf("\n\r");
        // printf("Arr 3 = %d\n\r", arr3[0]);
        // printf("\n\r");
        // printf("Arr 3 = %d\n\r", arr3[1]);
        // printf("\n\r");
        // printf("\n\r");

    while (1) {
        adc_update_all_player_inputs(&player_inputs);
        // adc_print_current_position();
        // for (int i = 0; i < 7; i++) {
        //     printf("player_inputs[%d] = %d\n\r", i, player_inputs[i]);
        // }
        // printf("\n\r");
        can_send_message(0, player_inputs_length, &player_inputs, 0);
        _delay_ms(100);
        // can_send_message(0b1, length2, &arr2, 1);
        // _delay_ms(50000);
    }
    return 0;
}