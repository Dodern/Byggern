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

// Node 2
#include "adc_driver.h"
#include "encoder_driver.h"
#include "game_logic_driver.h"
#include "game_utilities.h"
#include "motor_driver.h"
#include "pid.h"
#include "servo_driver.h"
#include "solenoid_driver.h"
#include "TWI_driver.h"


// Defines
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


// ISRs and global variables
volatile uint8_t player_inputs[7];
volatile uint8_t can_receive_state = STOP_GAME;

ISR(TIMER5_CAPT_vect){
    motor_input_closed_loop(player_inputs[3]);
}

ISR(BADISR_vect){
    printf("BAD ISR\n\r");
}


int main(void){
    // Initialization
    cli();
    USART_Init ( MYUBRR );
    can_controller_init();
    //servo_init();
    //servo_init_timer4();
    adc_init();
    TWI_Master_Initialise();
    solenoid_init();
    motor_init();
    encoder_init();
    motor_timer_init();
    // Turning on interrupts
    sei();

    struct can_message message;


    while (1) {
        game_util_can_receive_parser();
        // set_bit(PORTB, PB5);
        // _delay_ms(50000);
        // clear_bit(PORTB, PB5);
        // _delay_ms(50000);
        _delay_ms(100);
    }
    return 0;
}
