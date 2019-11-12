#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"
#include "timer_driver.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){
    
    USART_Init ( MYUBRR );
    can_controller_init();
    timer3_init();
    sei();

    while (1){
        printf("Vi starter her: ");
        timer3_reset();
        _delay_ms(1000);
        printf("\n\n\r");
        read_timer();
        printf("\n\n\r");
        read_timer();
        _delay_ms(500);
        read_timer();
        timer3_reset();
        _delay_ms(100);
        read_timer();
        _delay_ms(5000);
    }
    return 0;
}