#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <avr/io.h>
#include <stdio.h>

void timer_init();
void timer3_init();
void timer_input(uint8_t pwm_input);
void timer3_reset();

#endif