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
#include "game_logic_driver.h"
#include "adc_driver.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){
    USART_Init ( MYUBRR );
    can_controller_init();
    servo_init();
    adc_init();

    struct can_message message;
    while(1){
        // PWM signal
        message = can_read_message(0);
        for (int i = 0; i < message.length; i++){
        printf("CAN receive buffer 0 data %d\n\r", message.data[i]);
        }
        servo_input(message.data[0]);

        //adc and game logic
        game_logic_update_score();
        _delay_ms(5000);
    }
    return 0;
}
