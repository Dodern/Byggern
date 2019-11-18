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
#include "testSRAM.h"

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

    _delay_ms(15000);
    

    uint8_t player_inputs[7];
    int player_inputs_length = SIZE(player_inputs);
    uint8_t arr[1];
    arr[0] = 1;

    struct can_message message;

    int counter = 0;

    while (1) {
        oled_print_main_menu();
        oled_move_pointer(adc_get_joystick_direction());
        adc_update_all_player_inputs(&player_inputs);
        printf("Oled menu select = %d\n\r", oled_menu_select());
        if (oled_menu_select() == 1){
            if (counter > 10) {
                for (int i = 0; i < 7; i++) {
                    printf("player_inputs[%d] = %d\n\r", i, player_inputs[i]);
                }
                printf("\n\r");
                counter = 0;
            }
            can_send_message(0, player_inputs_length, &player_inputs, 1);
            counter++;
        }
        else if (oled_menu_select() == 2){
            printf("Test SRAM!\n\r");
            can_send_message(10, 1, &arr, 0);
            message = can_read_message(0);
            if (message.id == 5){
                for (int i = 0; i < 2; i++){
                printf("SRAM error %d = %d\n\r", i , message.data[i]);
                }
            }
        }
        _delay_ms(1000);
    }
    return 0;
}