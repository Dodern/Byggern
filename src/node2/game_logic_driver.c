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

static uint8_t game_score;
extern uint8_t player_inputs[7];

void game_logic_update_score(){
    adc_print();
    int adc_data = adc_read();
    if (adc_data < 100){
        printf("Jeg oppdaterer Game Score\n\r");
        game_score++;
    }
    printf("Game score = %d\n\r", game_score);
    _delay_ms(1000);
}

int game_logic_get_score(){
    return game_score;
}

void game_logic_start_game(){
    printf("Calibrating motor\n\r");
    motor_calibrate();
    printf("Starting motor\n\r");
    motor_start();
    solenoid_timer_start();
	motor_timer_start();
}

void game_logic_game_loop(struct can_message message){
    if (player_inputs[5]){
        printf("Solenoid punch!\n\r");
        _delay_ms(500);
        solenoid_punch();
    }
    // game_logic_update_score();
    servo_input(player_inputs[2]);
    _delay_ms(1000);
}