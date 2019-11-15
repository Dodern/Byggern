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

void encoder_init();
void encoder_reset();
int16_t read_encoder();
int16_t motor_encoder_read_scaled();
void motor_init();
void stop_motor();
void start_motor();
void set_motor_direction(uint8_t direction);
void send_i2c_motor_input(uint8_t motor_input);
void motor_input_open_loop(uint8_t joystick_input);
// void motor_input_closed_loop(uint8_t joystick_input, struct PID_DATA *pid);
void motor_calibrate();

#endif