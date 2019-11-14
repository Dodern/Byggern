#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"
//#include "timer_driver.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){

    USART_Init ( MYUBRR );
    can_controller_init();
    //timer3_init();
    //sei();

    struct can_message message;

    while (1){
        message = can_read_message(0);
        printf("CAN receive buffer 0 data %d\n\r", message.data[0]);
        printf("Vi starter her: \n\r");
        _delay_ms(5000);
    }
    return 0;
}

ISR(BADISR_vect){
    printf("BadISR\r\n");
}