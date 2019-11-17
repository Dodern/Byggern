#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "game_utilities.h"

void game_util_can_receive_parser(struct can_message message, uint8_t *player_inputs){
    void game_util_receive_player_intputs(message, player_inputs);
}

void game_util_receive_player_intputs(struct can_message message, uint8_t *player_inputs){
    for (int i = 0; i < 7; i++) {
      player_inputs[i] = message.data[i];
    }
}
