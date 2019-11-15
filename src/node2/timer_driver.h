#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <avr/io.h>
#include <stdio.h>


void timer3_init();
void timer3_reset();
void read_timer();

#endif