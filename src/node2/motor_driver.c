#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "bit_macros.h"
#include "motor_driver.h"
#include "uart.h"
#include "TWI_driver.h"
#include "pid.h"

volatile int16_t motor_encoder_range = 0;

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

int16_t motor_encoder_read_scaled(){
    int16_t raw_read = read_encoder();
    int scale_factor = floor(-motor_encoder_range/200 ); //new resolution is 200, -100 to 100
    int16_t scaled_position = floor(raw_read/scale_factor) - 100;
    // int16_t scaled_position = floor(raw_read/floor(-motor_encoder_range/200)) - 100; //new resolution is 200, -100 to 100
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

void motor_input_open_loop(int8_t joystick_input){
    // Slave address 0101000
    // Joystick_input between 0 - 255

}

void motor_input_closed_loop(int8_t joystick_input){
    int16_t current_placement = motor_encoder_read_scaled();
    printf("Current placement = %d\n\r", current_placement);
    printf("Casta joystick input = %d\n\r", (int16_t)joystick_input);
    int16_t controlval = pid_controller(1,1,1,(int16_t)joystick_input, current_placement);
    if (controlval > 0) {
        set_motor_direction(1);
    } else {
        set_motor_direction(0);
    }
    uint16_t conversion_test = abs(controlval);
    printf("Control value = %d\n\r", controlval);
    printf("Conversion Control value = %u\n\r", conversion_test);
    send_i2c_motor_input((uint8_t)abs(controlval));
}

void motor_calibrate(){
    start_motor();
    int16_t encoder_max_val = 0;
    set_motor_direction(0);
    send_i2c_motor_input(100);
    int16_t encoderval = read_encoder();
    _delay_ms(12000);
    stop_motor();
    _delay_ms(10000);
    start_motor();
    encoder_reset();
    set_motor_direction(1);
    send_i2c_motor_input(100);
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