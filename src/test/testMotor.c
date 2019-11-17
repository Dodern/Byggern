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

int main(void){
    USART_Init ( MYUBRR );
    can_controller_init();
    servo_init();
    adc_init();
    TWI_Master_Initialise();
    motor_init();
    encoder_init();
    motor_timer_init();
    solenoid_init();

    sei();

    solenoid_timer_start();

    struct can_message message;
    int16_t encoder = 0;

    motor_calibrate();
    // motor_start();
    // motor_timer_start();

    while(1){
        message = can_read_message(0);

        game_util_receive_player_intputs(message, &player_inputs);
        // for (int i = 0; i < 7; i++){
        //     player_inputs[i] = message.data[i];
        //     // printf("player_inputs[%d] = %d\n\r", i, message.data[i]);
        // }


        //printf("Player inputs = %d\n\r", player_inputs[3]);
        //printf("Diff main = %d\n\r", motor_pos_diff(player_inputs[3]));
        motor_input_closed_loop(encoder_input_scaler(player_inputs[3], PLAYER_INPUT_MAX));
        int16_t current_position = encoder_get_scaled_position();
        printf("encoder_input_scaler - current position = %d\n\r", current_position);


        // Servo and Solenoid stuff
        if (player_inputs[5]){
            printf("Solenoid punch!\n\r");
            solenoid_punch();
        }
        // servo_input(player_inputs[2]);
        _delay_ms(10000);
    }
    return 0;
}

ISR(BADISR_vect){
    printf("BAD ISR\n\r");
}

// ISR(TIMER5_CAPT_vect){
//     uint8_t right_slider = player_inputs[3];
//     motor_input_closed_loop(right_slider);
//     printf("In interrupt!\n\r");
// }
