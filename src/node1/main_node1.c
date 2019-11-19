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
#include "adc_driver.h"

// Node 1
#include "xmem.h"
#include "oled_driver.h"

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
    int selection = 3;

    while (1) {
        selection = oled_menu_select(selection);
        oled_print_main_menu();
        oled_move_pointer(adc_get_joystick_direction());
        adc_update_all_player_inputs(&player_inputs);
        switch (selection) {

            case 1:
                can_send_message(START_GAME, player_inputs_length, &player_inputs, 0);
                printf("Send start game message\n\r");
                _delay_ms(10000);
                selection = 4;
                break;
            case 2:
                printf("Test SRAM!\n\r");
                can_send_message(TEST_SRAM, 1, &arr, 1);
                message = can_read_message(0); // Change to can interrupt for reading from SRAM test and game score
                if (message.id == SRAM_TESTED){
                    for (int i = 0; i < 2; i++){
                        printf("SRAM error %d = %d\n\r", i , message.data[i]);
                    }
                }
                break;
            case 3:
                printf("Stopping game\n\r");
                can_send_message(STOP_GAME, 1, &arr, 0);
                break;
            case 4:
                if (counter > 10) {
                    for (int i = 0; i < 7; i++) {
                        printf("player_inputs[%d] = %d\n\r", i, player_inputs[i]);
                    }
                    printf("\n\r");
                    counter = 0;
                }
                can_send_message(PLAY_GAME, player_inputs_length, &player_inputs, 0);
                counter++;
                break;
            default:
                break;
            }
            _delay_ms(100);
    }
    return 0;
}