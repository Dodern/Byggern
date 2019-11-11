#include <stdlib.h>
#include <util/delay.h>

#include "bit_macros.h"
#include "motor_driver.h"
#include "uart.h"
#include "TWI_driver.h"

void encoder_init(){
    // Sets all of the 
    // DDH0 = 0;
}

uint16_t read_encoder(){
    clear_bit(MJ1, MJ1_OE);
    clear_bit(MJ1, MJ1_SEL);
    // _delay_us(20);


}

void motor_init(){
    set_bit(MJ1, MJ1_EN);
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