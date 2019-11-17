#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <avr/io.h>
#include <stdio.h>
#include "pid.h"

// In normal I2C the last bit indicates R/W bit, but as the DAC only receives
// data the last bit is 0.
#define DAC_ADDRESS 0b01010000
#define DAC_COMMAND_ADDRESS 0b00000000
#define I2C_LENGTH 3

// For the motor and inputs
#define SLIDER_CENTER 128
#define PLAYER_INPUT_MAX 255
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 0

// For the encoder
#define PORT_MJ1 PORTH
#define MJ1_DIR PH1
#define MJ1_SEL PH3
#define MJ1_EN PH4
#define MJ1_OE PH5
#define MJ1_RST PH6

#define PIN_MJ2 PINK
#define MJ2_DO0 PK0 //A8
#define MJ2_DO1 PK1 //A9
#define MJ2_DO2 PK2 //A10
#define MJ2_DO3 PK3 //A11
#define MJ2_DO4 PK4 //A12
#define MJ2_DO5 PK5 //A13
#define MJ2_DO6 PK6 //A14
#define MJ2_DO7 PK7 //A15

//Encoder functions and Input
void motor_encoder_init();
void motor_encoder_reset();
int16_t motor_encoder_read();
int16_t motor_get_scaled_position();
int16_t motor_input_scaler(int16_t relative_input, int16_t maximum_input);

void motor_init();
void motor_stop();
void motor_start();
void motor_set_direction(uint8_t direction);
void motor_send_input(uint8_t motor_input);
void motor_calibrate();
void motor_input_open_loop(uint8_t joystick_input);
void motor_input_closed_loop(uint8_t joystick_input);
void motor_timer_init();
void motor_timer_reset();
void motor_timer_read();
void motor_timer_start();
void motor_timer_stop();
//int16_t motor_pos_diff(uint8_t joystick_input);

#endif
