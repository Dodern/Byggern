#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "game_utilities.h"
#include "can_driver.h"
#include "uart.h"
#include "motor_driver.h"
#include "solenoid_driver.h"
#include "servo_driver.h"

extern uint8_t player_inputs[7];
extern uint8_t can_receive_state;
extern uint8_t game_score;

void game_util_can_receive_parser(){
	// printf("can_receive_state: %d\n\r");
	struct can_message message = can_read_message(0);
	switch (can_receive_state) {

		case START_GAME:
			//cli();
			// printf("Starting game\n\r");
			game_logic_start_game();
			//sei();
			break;

		case PLAY_GAME:
			// printf("playing\n\r");
			game_util_receive_player_inputs(message);
			game_logic_game_loop(message);
			break;

		default:
			game_score = 0;
			servo_stop();
			solenoid_timer_stop();
			motor_timer_stop();
			_delay_ms(1000);
			break;
	}
}

void game_util_receive_player_inputs(struct can_message message){
    for (int i = 0; i < 7; i++) {
    	player_inputs[i] = message.data[i];
    }
}
