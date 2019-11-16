#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "motor_driver.h"
#include "uart.h"
#include "TWI_driver.h"
#include "pid.h"

volatile int16_t motor_encoder_range = 0;

#define SLIDER_CENTER 128

void encoder_init(){
    // Sets all pins in PORTC to input
    DDRK &= ~0xFF;
    encoder_reset();
}

void encoder_reset(){
    clear_bit(PORT_MJ1, MJ1_RST);
    _delay_us(200);
    set_bit(PORT_MJ1, MJ1_RST);      // Toggle reset on and off
}

int16_t read_encoder(){
    clear_bit(PORT_MJ1, MJ1_OE); // Enable output of encoder
    clear_bit(PORT_MJ1, MJ1_SEL); // Select high byte
    // printf("MJ_SEL = %d\n\r", PORT_MJ1);
    _delay_ms(1);
    //_delay_us(125);
    uint8_t highbyte = PIN_MJ2; // READ MSB
    //printf("Highbyte = %d\n\r", highbyte);
    set_bit(PORT_MJ1, MJ1_SEL); // Select low byte
    // printf("MJ_SEL = %d\n\r", PORT_MJ1);
    _delay_ms(1);
    //_delay_us(125);
    uint8_t lowbyte = PIN_MJ2; // READ LSB
    //printf("Lowbyte = %d\n\r", lowbyte);
    //encoder_reset();
    set_bit(PORT_MJ1, MJ1_OE); // Disable output of encoder
    int16_t databyte = (highbyte << 8) | (lowbyte & 0xff);
    //int16_t databyte = (highbyte << 8) | lowbyte; 
    return databyte;   
}

uint16_t motor_encoder_read_scaled(){
    int16_t raw_read = read_encoder();
    uint16_t scaled_position = floor(raw_read/(motor_encoder_range/900) + 100); //new resolution is 200, -100 to 100
    printf("Raw Read = %d\n\r", raw_read);
    printf("Scale position encoder = %d\n\r", scaled_position);
    // uint16_t scaled_position = floor(raw_read/scale_factor) - 20;
    return scaled_position;
}

void motor_init(){
    // Sets MJ1_EN, MJ1_OE, MJ1_RST, MJ1_DIR and MJ1_SEL to output
    DDRH |= (1<<MJ1_EN) | (1<<MJ1_OE) | (1<<MJ1_RST) | (1<<MJ1_DIR) | (1<<MJ1_SEL);
    set_bit(PORT_MJ1, MJ1_EN);
}

void stop_motor(){
    clear_bit(PORT_MJ1, MJ1_EN);
}

void start_motor(){
    set_bit(PORT_MJ1, MJ1_EN);
}

void set_motor_direction(uint8_t direction){
    if (direction == 1){
        set_bit(PORT_MJ1, MJ1_DIR);
    } else{
        clear_bit(PORT_MJ1, MJ1_DIR);
    }
}

void send_i2c_motor_input(uint8_t motor_input){
    unsigned char i2c_message[] = {DAC_ADDRESS, DAC_COMMAND_ADDRESS, motor_input};
    TWI_Start_Transceiver_With_Data(i2c_message, I2C_LENGTH);
}

void motor_input_open_loop(uint8_t joystick_input){
    // Slave address 0101000
    // Joystick_input between 0 - 255

}

void motor_input_closed_loop(uint8_t raw_input){
    uint16_t scaled_input = motor_input_scaler(raw_input);
    uint16_t current_placement = motor_encoder_read_scaled();
    printf("________Current placement = %u\n\r", current_placement);
    uint8_t motor_input = pid_controller(1,1,1, scaled_input, current_placement);
    printf("motor input pid: %d\n\r", motor_input);
    send_i2c_motor_input(motor_input);
}

void motor_calibrate(){
    start_motor();
    int16_t encoder_max_val = 0;
    set_motor_direction(0);
    send_i2c_motor_input(90);
    int16_t encoderval = read_encoder();
    _delay_ms(12000);
    stop_motor();
    _delay_ms(10000);
    start_motor();
    encoder_reset();
    set_motor_direction(1);
    send_i2c_motor_input(90);
    _delay_ms(50000);
    encoder_max_val = read_encoder();
    printf("Encoder max val = %d\n\r", encoder_max_val);
    // TODO: Add in move to center function via PID control.
    stop_motor();
    encoder_reset();
    motor_encoder_range = encoder_max_val;
}


// void motor_encoder_raw_to_scaled(raw_read, motor_encoder_range){
//     return floor(raw_read/floor(-motor_encoder_range/200)) - 100;
// }

void motor_timer_init(){
    //Disabling interrupts while setting up
    cli();

    // Interrupt
    //set_bit(TIMSK3, TOIE3);
    /* clear_bit(TIMSK3, ICIE3); */
    set_bit(TIMSK5, ICIE5); // Enable interrupts when ICFn flag is set

    // Timer
    clear_bit(TCCR5A, COM5A0);
    clear_bit(TCCR5A, COM5A1); // OC3A Disconnected
    set_bit(TCCR5B, WGM52); // Clear timer on compare match bit 2 
    set_bit(TCCR5B, WGM53); // Clear timer on compare match bit 3
    set_bit(TCCR5B, CS52); // Clk active with prescaling to clk/256
    ICR5 = 0b0111110000110101; // Set TOP to 3125 (1/20 second)
    motor_timer_stop();
    //Output
    printf("TCCR5B = %d\n\r", TCCR5B);
}

void motor_timer_reset(){
    TCNT5 = 0b0;
    //printf("TCNT5 = %d\n\r", TCNT5);
}

void motor_read_timer(){
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


uint16_t motor_input_scaler(uint8_t raw_input){
    // float scale_factor = 255.0/200.0;
    uint16_t scaled_input = floor(raw_input/(255.0/900.0) + 100);
    // printf("Raw input = %d\n\r", raw_input);
    // printf("Scale factor input = %.2f\n\r", scale_factor);
    // printf("Scaled input = %d\n\r", scaled_input);
    return scaled_input;
}

// int16_t motor_pos_diff(uint8_t joystick_input){
//     int center_value = 128;
//     int16_t current_placement = motor_encoder_read_scaled();
//     int horizontal_value = ((joystick_input-center_value)/(255.0-center_value)*100);
//     int16_t diff = horizontal_value - current_placement;
//     printf("Diff = %d\n\r", diff);
//     return diff;
// }

// int16_t motor_raw_to_scaled(uint8_t raw_input){
//     int centered_intput = ((raw_input-SLIDER_CENTER)/(255.0-SLIDER_CENTER)*100);
// }