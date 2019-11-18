#ifndef GAME_LOGIC_DRIVER_H
#define GAME_LOGIC_DRIVER_H

#include <avr/io.h>
#include <stdio.h>
#include "can_controller_driver.h"

void game_logic_update_score();
int game_logic_get_score();
void game_logic_start_game();
void game_logic_game_loop(struct can_message message);

void game_logic_timer_init();
void game_logic_timer_reset();
void game_logic_timer_read();
void game_logic_timer_start();
void game_logic_timer_stop();

#endif