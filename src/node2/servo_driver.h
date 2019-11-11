#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <avr/io.h>
#include <stdio.h>

void servo_init();
void servo_input(uint8_t pwm_input);
// void timer3_init();
// void timer3_reset();

#endif