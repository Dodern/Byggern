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
#include "game_logic_driver.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){
    USART_Init ( MYUBRR );
    can_controller_init();
    timer_init();
    timer3_init();

    while(1){
        game_logic_update_score();
        _delay_ms(10000);
        printf("TCNT3 = %d\n\r", TCNT3);
        printf("TCNT1 = %d\n\r", TCNT1);
    }
    return 0;
}