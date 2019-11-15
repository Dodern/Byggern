#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"
#include "can_driver.h"
#include "servo_driver.h"
#include "game_logic_driver.h"
#include "adc_driver.h"
#include "TWI_driver.h"
#include "motor_driver.h"
#include "pid.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define TEST_SET_OUTPUT_LENGTH 3

// V_{ref} * (255/256) = 0b11111111

int main(void){
    USART_Init ( MYUBRR );
    can_controller_init();
    servo_init();
    adc_init();
    TWI_Master_Initialise();
    motor_init();
    encoder_init();

    sei();

    unsigned char test_high[] = {0b01010000, 0b00000000, 0b11111111};
    unsigned char test_medium[] = {0b01010000, 0b00000000, 0b01111111};
    unsigned char test_low[] = {0b01010000, 0b00000000, 0b00000000};

    // unsigned char test_high = TEST_SET_OUTPUT_HIGH;
    // unsigned char test_medium = TEST_SET_OUTPUT_MEDIUM;
    // unsigned char test_low = TEST_SET_OUTPUT_LOW;
    unsigned char TWI_state = 0;
    struct can_message message;
    int16_t encoder = 0;
    int center_value = 127;

    struct PID_DATA pid;

    pid_Init(1, 1, 1, &pid);
    //_delay_ms(50000);
    motor_calibrate();

    start_motor();
    motor_encoder_read_scaled();
    set_motor_direction(1);
    send_i2c_motor_input(70); 
    _delay_ms(25000);

    while(1){
        set_motor_direction(0);
        send_i2c_motor_input(70); 
        _delay_ms(5000);
        motor_encoder_read_scaled();
        _delay_ms(5000);
        motor_encoder_read_scaled();
        _delay_ms(5000);
        set_motor_direction(1);
        send_i2c_motor_input(70); 
        motor_encoder_read_scaled();
        _delay_ms(5000);
        motor_encoder_read_scaled();
        _delay_ms(5000);
        motor_encoder_read_scaled();
        _delay_ms(15000);
        // _delay_ms(1000);
        // message = can_read_message(0);
        // // printf("CAN receive buffer 0 data: %d, %d\n\r", message.data[0], message.data[1]);
        // //int horizontal_value =(message.data[0]-center_value)/(255.0-center_value)*100;
        // _delay_ms(10000);
        // int horizontal_value = message.data[0];
        // printf("Horizontal value: %d\n\r", horizontal_value);
        // int encoderval = read_encoder();
        // printf("Encoder value %d\n\r", encoderval);
        // send_i2c_motor_input(50);
        // stop_motor();
        // _delay_ms(100000);
        //motor_input_closed_loop(horizontal_value, &pid);
        // if (horizontal_value < 0) {
        //     set_motor_direction(0);
        // } else {
        //     set_motor_direction(1);
        // }
        
        // send_i2c_motor_input(abs( horizontal_value ));
        // encoder = read_encoder();
    }
    return 0;
}
