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
#include "TWI_driver.h"
#include "motor_driver.h"
#include "encoder_driver.h"
#include "pid.h"
#include "solenoid_driver.h"
#include "game_utilities.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

volatile uint8_t player_inputs[7];

ISR(BADISR_vect){
    printf("BAD ISR\n\r");
}

ISR(TIMER5_CAPT_vect){
    motor_input_closed_loop(player_inputs[3]);
}

int main(void){
    USART_Init ( MYUBRR );
    can_controller_init();
    servo_init();
    adc_init();
    TWI_Master_Initialise();
    solenoid_init();
    motor_init();
    encoder_init();
    motor_timer_init();
    

    sei();

    solenoid_timer_start();

    struct can_message message;
    int16_t encoder = 0;

    motor_calibrate();
    motor_start();
    motor_timer_start();
    //motor_stop();

    while(1){
        message = can_read_message(0);

        game_util_receive_player_intputs(message, &player_inputs);

        // Servo and Solenoid stuff
        if (player_inputs[5]){
            printf("Solenoid punch!\n\r");
            _delay_ms(500);
            solenoid_punch();
        }
        servo_input(player_inputs[2]);
        _delay_ms(1000);
    }
    return 0;
}
