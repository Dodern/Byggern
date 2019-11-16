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
#include "solenoid_driver.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define TEST_SET_OUTPUT_LENGTH 3

// V_{ref} * (255/256) = 0b11111111

volatile int interruptcounter = 0;
volatile uint8_t player_inputs[7];

int main(void){
    USART_Init ( MYUBRR );
    can_controller_init();
    //servo_init();
    adc_init();
    TWI_Master_Initialise();
    motor_init();
    encoder_init();
    //motor_timer_init();
    //solenoid_init();

    sei();

    solenoid_timer_start();
    uint8_t joystick_verticle ;
    uint8_t joystick_horizontal;
    uint8_t left_slider;
    uint8_t right_slider;
    uint8_t joystick_button;
    uint8_t left_button;
    uint8_t right_button;

    // unsigned char test_high[] = {0b01010000, 0b00000000, 0b11111111};
    // unsigned char test_medium[] = {0b01010000, 0b00000000, 0b01111111};
    // unsigned char test_low[] = {0b01010000, 0b00000000, 0b00000000};

    // unsigned char test_high = TEST_SET_OUTPUT_HIGH;
    // unsigned char test_medium = TEST_SET_OUTPUT_MEDIUM;
    // unsigned char test_low = TEST_SET_OUTPUT_LOW;
    unsigned char TWI_state = 0;
    struct can_message message;
    int16_t encoder = 0;
    // int center_value = 127;
    int center_value = 128;


    //struct PID_DATA pid;

    //pid_Init(1, 1, 1, &pid);
    //_delay_ms(50000);
    motor_calibrate();

    start_motor();
    // motor_encoder_read_scaled();
    // set_motor_direction(1);
    // send_i2c_motor_input(60); 
    // _delay_ms(25000);
    // stop_motor();

    while(1){
        message = can_read_message(0);
        for (int i = 0; i < 7; i++){
            player_inputs[i] = message.data[i];
        }
        //printf("Player inputs = %d\n\r", player_inputs[3]);
        //printf("Diff main = %d\n\r", motor_pos_diff(player_inputs[3]));
        
        if (player_inputs[5]){
            printf("Solenoid punch!\n\r");
            solenoid_punch();
        }
        motor_input_closed_loop(motor_input_scaler(player_inputs[3]));
        printf("Slider Input= %d\n\r", motor_input_scaler(player_inputs[3]));
        servo_input(player_inputs[2]);
        _delay_ms(5000);
    }
    return 0;
}

ISR(BAD_ISR){
    printf("BAD ISR\n\r");
}

// ISR(TIMER5_CAPT_vect){
//     uint8_t right_slider = player_inputs[3];
//     motor_input_closed_loop(right_slider);
//     printf("In interrupt!\n\r");
// } 
