#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "uart.h"
#include "adc_driver.h"
#include "game_logic_driver.h"
#include "servo_driver.h"
#include "bit_macros.h"
#include "motor_driver.h"
#include "can_driver.h"
#include "solenoid_driver.h"

volatile uint8_t game_score;
extern uint8_t player_inputs[7];
// volatile int score_timer_state = 0;
extern uint8_t can_receive_state;

// ISR(TIMER4_CAPT_vect){ 
//     score_timer_state = 0; 
//     printf("Score timer state = %d\n\r", score_timer_state); 
//     game_logic_timer_stop();
// } 


void game_logic_update_score(){
    // adc_print();
    int adc_data = adc_read();
    // printf("score_timer_state: %d\n\r", score_timer_state);
    if (adc_data < 700){
        // can_receive_state = STOP_GAME;
        // printf("You lost!\n\r");
    }
    // game_logic_timer_read();
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
    // solenoid_timer_start();
	motor_timer_start();
    servo_start();
}

void game_logic_game_loop(struct can_message message){
    if (player_inputs[5] && can_receive_state == 1){
        printf("Solenoid punch!\n\r");
        _delay_ms(500);
        solenoid_punch();
    }
    game_logic_update_score();
    servo_input(player_inputs[2]);
    _delay_ms(1000);
}

// void game_logic_timer_init(){
//     //Disabling interrupts while setting up
//     cli();

//     // Interrupt
//     //set_bit(TIMSK3, TOIE3);
//     /* clear_bit(TIMSK3, ICIE3); */
//     set_bit(TIMSK4, ICIE4); // Enable interrupts when ICFn flag is set

//     // Timer
//     clear_bit(TCCR4A, COM4A0);
//     clear_bit(TCCR4A, COM4A1); // OC3A Disconnected
//     set_bit(TCCR4B, WGM42); // Clear timer on compare match bit 2 
//     set_bit(TCCR4B, WGM43); // Clear timer on compare match bit 3
//     set_bit(TCCR4B, CS42); // Clk active with prescaling to clk/256
//     ICR4 = 0b1111010000100100; // Set TOP to 3125 (1/20 second)
//     motor_timer_stop();
//     //Output
//     printf("TCCR4B = %d\n\r", TCCR4B);
// }

// void game_logic_timer_reset(){
//     TCNT4 = 0b0;
//     //printf("TCNT4 = %d\n\r", TCNT4);
// }

// void game_logic_timer_read(){
//     printf("TCNT4 = %u\n\r", TCNT4);
// }

// void game_logic_timer_start(){
//     score_timer_state = 1;
//     set_bit(TCCR4B, CS41);
// }

// void game_logic_timer_stop(){
//     clear_bit(TCCR4B, CS40);
//     clear_bit(TCCR4B, CS41);
//     clear_bit(TCCR4B, CS42); // Clear clk bits
// }