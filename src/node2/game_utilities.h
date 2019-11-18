#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "can_driver.h"
#include "can_controller_driver.h"

void game_util_can_receive_parser(struct can_message message);
void game_util_receive_player_inputs(struct can_message message);

#endif
