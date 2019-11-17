#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "motor_driver.h"
#include "encoder_driver.h"
#include "uart.h"

// This is the POSITIVE value for range
volatile int16_t motor_encoder_range = 0;

// ******* Encoder Functions ********* //

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

int16_t encoder_read(){
    clear_bit(PORT_MJ1, MJ1_OE); // Enable output of encoder
    clear_bit(PORT_MJ1, MJ1_SEL); // Select high byte
    _delay_ms(1);
    uint8_t highbyte = PIN_MJ2; // READ MSB
    set_bit(PORT_MJ1, MJ1_SEL); // Select low byte
    _delay_ms(1);
    uint8_t lowbyte = PIN_MJ2; // READ LSB
    //encoder_reset();
    set_bit(PORT_MJ1, MJ1_OE); // Disable output of encoder
    int16_t databyte = (highbyte << 8) | (lowbyte & 0xff);
    return databyte;
}

int16_t encoder_get_scaled_position(){
    int16_t raw_encoder_read = encoder_read();
    // int scale_factor = floor(); //new resolution is 200, -100 to 100
    // int16_t scaled_position = floor(raw_read/(-motor_encoder_range/200)) - 100;
    int16_t scaled_position = encoder_input_scaler(raw_encoder_read, motor_encoder_range);
    return -scaled_position;
}

int16_t encoder_input_scaler(int16_t relative_input, int16_t maximum_input){
    int16_t scaled_input = floor(relative_input/(maximum_input/200.0)) - 100;
    return scaled_input;
}

void encoder_set_motor_range(int16_t motor_encoder_data){
    motor_encoder_range = motor_encoder_data;
    printf("encoder_set_motor: %d\n\r", motor_encoder_range);
}
