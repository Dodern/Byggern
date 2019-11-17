#ifndef ENCODER_DRIVER_H
#define ENCODER_DRIVER_H

#include <avr/io.h>
#include <stdio.h>

#include "motor_driver.h"

void encoder_init();
void encoder_reset();
int16_t encoder_read();
int16_t encoder_get_scaled_position();
int16_t encoder_input_scaler(int16_t relative_input, int16_t maximum_input);
void encoder_set_motor_range(int16_t motor_encoder_data);

#endif
