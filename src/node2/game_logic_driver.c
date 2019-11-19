#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "uart.h"
#include "adc_driver.h"
#include "game_logic_driver.h"
#include "servo_driver.h"
#include "bit_macros.h"
#include "motor_driver.h"
#include "solenoid_driver.h"

volatile uint8_t game_score;
extern uint8_t player_inputs[7];
extern uint8_t can_receive_state;


void game_logic_update_score(){
    // adc_print();
    int adc_data = adc_read();
    if (adc_data < 700){
        can_receive_state = 2;
        printf("You lost!\n\r");
    }
    _delay_ms(50);
}

int game_logic_get_score(){
    return game_score;
}

void game_logic_start_game(){
    printf("Calibrating motor\n\r");
    motor_calibrate();
    printf("Starting motor\n\r");
    motor_start();
    motor_timer_start();
    //servo_start();
}

void game_logic_game_loop(struct can_message message){
    if (player_inputs[5] && can_receive_state == 1){
        printf("Solenoid punch!\n\r");
        _delay_ms(500);
        solenoid_punch();
    }
    game_logic_update_score();
    //servo_input_timer4(player_inputs[2]);
    _delay_ms(1000);
}
