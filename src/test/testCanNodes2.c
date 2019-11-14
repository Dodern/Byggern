#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void){
    // Initiating various devices
	USART_Init ( MYUBRR );

    can_controller_init();
    //sei();

    struct can_message message;
    struct can_message message2;

    while (1) {
    message = can_read_message(0);
    //message2 = can_read_message(0);
    printf("Message length = %d\n\r", message.length);
    
    for (int i = 0; i < message.length; i++){
        printf("CAN receive buffer 0 data %d\n\r", message.data[i]);
        //printf("CAN receive buffer 1 data %d\n\r", message2.data[i]);
    }
    printf("\n\r");
    _delay_ms(10000);
    // message2 = can_read_message(0);
    //    for (int i = 0; i < message.length; i++){
    //     //printf("CAN receive buffer 0 data %d\n\n\r", message.data[i]);
    //     printf("CAN receive buffer 1 data %d\n\r", message2.data[i]);
    // }
    // printf("\n");
    //_delay_ms(30000);
    }
    return 0;
}

ISR(BADISR_vect){
    printf("BadISR\r\n");
}