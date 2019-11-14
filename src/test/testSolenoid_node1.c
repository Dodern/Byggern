#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "adc_driver.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){

    USART_Init ( MYUBRR );
    xmem_init();
    adc_init();
    can_controller_init();

    uint8_t left_button[] = {0};
    int length = SIZE(left_button);

    while(1){
        left_button[0] = adc_is_left_button_pressed();
        printf("left button = %d\n\r", left_button[0]);
        printf("length = %d\n\r", length);
        can_send_message(0, length, &left_button, 0);
        _delay_ms(5000);
    }
    return 0;
}
