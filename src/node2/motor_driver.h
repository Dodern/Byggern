#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <avr/io.h>
#include <stdio.h>

// In normal I2C the last bit indicates R/W bit, but as the DAC only receives
// data the last bit is 0.
#define DAC_ADDRESS 0b01010000
#define DAC_COMMAND_ADDRESS 0b00000000
#define I2C_LENGTH 3

// For the encoder
#define MJ1 PORTH // _SFR_MEM8(0x102)
#define MJ1_DIR PH1 
#define MJ1_SEL PH3
#define MJ1_EN PH4
#define MJ1_OE PH5
#define MJ1_RST PH6

#define MJ2_DO0 PC0 //A8
#define MJ2_DO1 PC1 //A9
#define MJ2_DO2 PC2 //A10
#define MJ2_DO3 PC3 //A11
#define MJ2_DO4 PC4 //A12
#define MJ2_DO5 PC5 //A13
#define MJ2_DO6 PC6 //A14
#define MJ2_DO7 PC7 //A15

void send_i2c_motor_input(uint8_t motor_input);
void motor_init();
void motor_input_open_loop(uint8_t joystick_input);
void motor_input_closed_loop(uint8_t joystick_input);
uint16_t read_encoder();
//void servo_init();
//void servo_input(uint8_t pwm_input);
// void timer3_init();
// void timer3_reset();

#endif