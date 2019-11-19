#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <avr/io.h>
#include <stdio.h>

void servo_init();
void servo_input(uint8_t pwm_input);
void servo_stop();
void servo_start();
void servo_init_timer4();
void servo_input_timer4(uint8_t pwm_input);

#endif