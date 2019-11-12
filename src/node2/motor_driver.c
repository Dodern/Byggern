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
    _delay_us(125);
    uint8_t highbyte = PIN_MJ2; // READ MSB
    //printf("Highbyte = %d\n\r", highbyte);
    set_bit(PORT_MJ1, MJ1_SEL); // Select low byte
    // printf("MJ_SEL = %d\n\r", PORT_MJ1);
    _delay_us(125);
    uint8_t lowbyte = PIN_MJ2; // READ LSB
    //printf("Lowbyte = %d\n\r", lowbyte);
    encoder_reset();
    set_bit(PORT_MJ1, MJ1_OE); // Disable output of encoder
    int16_t databyte = (highbyte << 8) | (lowbyte & 0xff); 
    return databyte;   
}

void motor_init(){
    // Sets MJ1_EN, MJ1_OE, MJ1_RST, MJ1_DIR and MJ1_SEL to output
    DDRH |= (1<<MJ1_EN) | (1<<MJ1_OE) | (1<<MJ1_RST) | (1<<MJ1_DIR) | (1<<MJ1_SEL);
    set_bit(PORT_MJ1, MJ1_EN);
}

void stop_motor(){
    clear_bit(PORT_MJ1, MJ1_EN);
}

void set_motor_direction(uint8_t direction){
    if (direction == 1){
        set_bit(PORT_MJ1, MJ1_DIR);
    }
    else{
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

void motor_input_closed_loop(uint8_t joystick_input){
    // Slave address 0101000
    // Joystick_input between 0 - 255
    
}