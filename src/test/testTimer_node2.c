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
    sei();

    while (1){
        printf("Vi starter her: \n\r");
        _delay_ms(5000);
    }
    return 0;
}