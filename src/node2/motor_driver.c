#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "bit_macros.h"
#include "motor_driver.h"
#include "uart.h"
#include "TWI_driver.h"

void encoder_init(){
    // Sets all pins in PORTC to input
    DDRK &= ~0xFF;
}

void read_encoder(){
    clear_bit(MJ1, MJ1_OE); // Enable output of encoder
    clear_bit(MJ1, MJ1_SEL); // Select high byte
    _delay_us(40);
    // READ MSB
    uint8_t highbyte = MJ2;
    printf("Highbyte = %d\n\r", highbyte);
    set_bit(MJ1, MJ1_SEL); // Select low byte
    _delay_us(60);
    // READ LSB
    uint8_t lowbyte = MJ2;
    printf("Lowbyte = %d\n\r", lowbyte);
    //set_bit(MJ1, MJ1_RST); 
    //clear_bit(MJ1, MJ1_RST); // Toggle reset on and off
    set_bit(MJ1, MJ1_OE); // Disable output of encoder
}

void motor_init(){
    // Sets MJ1_EN, MJ1_OE, MJ1_RST, MJ1_DIR and MJ1_SEL to output
    DDRH |= (1<<MJ1_EN) | (1<<MJ1_OE) | (1<<MJ1_RST) | (1<<MJ1_DIR) | (1<<MJ1_SEL);
    set_bit(MJ1, MJ1_EN);
}

void stop_motor(){
    clear_bit(MJ1, MJ1_EN);
}

void set_motor_direction(uint8_t direction){
    if (direction == 1){
        set_bit(MJ1, MJ1_DIR);
    }
    else{
        clear_bit(MJ1, MJ1_DIR);
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

void motor_input_closed_loop(uint8_t joystick_input){
    // Slave address 0101000
    // Joystick_input between 0 - 255
    
}