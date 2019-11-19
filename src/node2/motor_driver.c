#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "motor_driver.h"
#include "encoder_driver.h"
#include "uart.h"
#include "TWI_driver.h"
#include "pid.h"

extern uint8_t player_inputs[7];

void motor_init(){
    cli();
    // Sets MJ1_EN, MJ1_OE, MJ1_RST, MJ1_DIR and MJ1_SEL to output
    DDRH |= (1<<MJ1_EN) | (1<<MJ1_OE) | (1<<MJ1_RST) | (1<<MJ1_DIR) | (1<<MJ1_SEL);
    set_bit(PORT_MJ1, MJ1_EN);
}

void motor_stop(){
    cli();
    clear_bit(PORT_MJ1, MJ1_EN);
    sei();
}

void motor_start(){
    cli();
    set_bit(PORT_MJ1, MJ1_EN);
    sei();
}

void motor_set_direction(uint8_t direction){
    cli();
    if (direction == 1){
        set_bit(PORT_MJ1, MJ1_DIR);
    } else{
        clear_bit(PORT_MJ1, MJ1_DIR);
    }
    sei();
}

void motor_send_input(uint8_t motor_input){
    unsigned char i2c_message[] = {DAC_ADDRESS, DAC_COMMAND_ADDRESS, motor_input};
    TWI_Start_Transceiver_With_Data(i2c_message, I2C_LENGTH);
}

void motor_calibrate(){
    cli();
    motor_start();
    int16_t encoder_max_val = 0;
    motor_set_direction(MOTOR_LEFT);
    motor_send_input(90);
    int16_t encoderval = encoder_read();
    _delay_ms(12000);
    motor_stop();
    _delay_ms(10000);
    motor_start();
    encoder_reset();
    motor_set_direction(MOTOR_RIGHT);
    motor_send_input(90);
    _delay_ms(50000);
    encoder_max_val = encoder_read();
    motor_stop();
    encoder_reset();
    printf("Encoder max val in motor_calibrate = %d\n\r", encoder_max_val);
    encoder_set_motor_range(-encoder_max_val);
}

void motor_input_closed_loop(uint8_t player_input){
    int16_t centered_input = encoder_input_scaler((int16_t)player_input, PLAYER_INPUT_MAX);
    int16_t current_position = encoder_get_scaled_position();
    int16_t control_val = pid_controller(100,4,20, centered_input, current_position);
    uint8_t motor_input = (uint8_t)abs(control_val);
    motor_send_input(motor_input);
}

void motor_timer_init(){
    //Disabling interrupts while setting up
    cli();

    // Interrupt
    set_bit(TIMSK5, ICIE5); // Enable interrupts when ICFn flag is set

    // Timer
    clear_bit(TCCR5A, COM5A0);
    clear_bit(TCCR5A, COM5A1); // OC3A Disconnected
    set_bit(TCCR5B, WGM52); // Clear timer on compare match bit 2 
    set_bit(TCCR5B, WGM53); // Clear timer on compare match bit 3
    set_bit(TCCR5B, CS52); // Clk active with prescaling to clk/256
    ICR5 = 0b0000110000110101; // Set TOP to 3125 (1/20 second)
    motor_timer_stop();
    //Output
    printf("TCCR5B = %d\n\r", TCCR5B);
}

void motor_timer_reset(){
    TCNT5 = 0b0;
    //printf("TCNT5 = %d\n\r", TCNT5);
}

void motor_timer_read(){
    printf("TCNT5 = %u\n\r", TCNT5);
}

void motor_timer_start(){
    set_bit(TCCR5B, CS52); // Clk active with prescaling to clk/256
}

void motor_timer_stop(){
    clear_bit(TCCR5B, CS50);
    clear_bit(TCCR5B, CS51);
    clear_bit(TCCR5B, CS52); // Clear clk bits
}
