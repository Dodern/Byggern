#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "can_driver.h"

void game_util_can_receive_parser(struct can_message message, uint8_t* player_inputs);

#endif