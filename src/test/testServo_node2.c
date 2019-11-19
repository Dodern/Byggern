#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"
#include "servo_driver.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){
    USART_Init ( MYUBRR );
    can_controller_init();
    servo_init();
    struct can_message message;
    while(1){
        message = can_read_message(0);
        for (int i = 0; i < message.length; i++){
            printf("CAN receive buffer 0 data %d\n\r", message.data[i]);
        }
        servo_input(message.data[2]);
        _delay_ms(1000);
    }
    return 0;
}
