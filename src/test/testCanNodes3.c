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
#include "testSRAM.h"
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

    struct can_message message;

    uint8_t player_inputs[7];
    int player_inputs_length = SIZE(player_inputs);
    uint8_t arr[] = {0b01010101, 0b01001111, 0b01001011, 0b0111100}; //85, 79, 75, 60

    int counter = 0;

    //SRAM_test();

    while (1) {
        message = can_read_message(0);
        if (message.id == 10){
            printf("Ready to test SRAM\n\r");
            SRAM_test_can();
        }
        //can_send_array(1, &arr, 0);
        _delay_ms(10000);
        counter++;
    }
    return 0;
}