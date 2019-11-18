#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "game_utilities.h"
#include "uart.h"

extern uint8_t player_inputs[7];

void game_util_can_receive_parser(struct can_message message){
	if (message.id == 0){
		//printf("Message id = 0 \n\r");
    	game_util_receive_player_inputs(message);
	} else{
		//printf("Message id = 1 \n\r");
		for (int i = 0; i < message.length; i++){
			//printf("Arr[%d] = %d\n\r", i, message.data[i]);
		}
		//printf("\n\r");
	}
}

void game_util_receive_player_inputs(struct can_message message){
    for (int i = 0; i < 7; i++) {
    	player_inputs[i] = message.data[i];
    }
}
