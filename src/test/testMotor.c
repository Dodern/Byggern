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
    sei();
    motor_init();

    unsigned char test_high[] = {0b01010000, 0b00000000, 0b11111111};
    unsigned char test_medium[] = {0b01010000, 0b00000000, 0b01111111};
    unsigned char test_low[] = {0b01010000, 0b00000000, 0b00000000};

    // unsigned char test_high = TEST_SET_OUTPUT_HIGH;
    // unsigned char test_medium = TEST_SET_OUTPUT_MEDIUM;
    // unsigned char test_low = TEST_SET_OUTPUT_LOW;
    unsigned char TWI_state = 0;
    struct can_message message;
    while(1){
        //send_i2c_motor_input(255);
        //_delay_ms(50000);
        send_i2c_motor_input(100);
        _delay_ms(50000);
        // PWM signal
        // message = can_read_message(0);
        // for (int i = 0; i < message.length; i++){
        //     printf("CAN receive buffer 0 data %d\n\r", message.data[i]);
        // }
        // servo_input(message.data[0]);

        // _delay_ms(10000);
        // printf("Sending command to set voltage high\n\r");
        // TWI_Start_Transceiver_With_Data(test_high,TEST_SET_OUTPUT_LENGTH);
        // TWI_state = TWI_Get_State_Info();
        // printf("TWI state: %u\n\r", TWI_state);
        // _delay_ms(10000);
        // TWI_state = TWI_Get_State_Info();
        // printf("TWI state: %u\n\r", TWI_state);
        // printf("Sending command to set voltage medium\n\r");
        // TWI_Start_Transceiver_With_Data(test_medium,TEST_SET_OUTPUT_LENGTH);
        // TWI_state = TWI_Get_State_Info();
        // printf("TWI state: %u\n\r", TWI_state);
        // _delay_ms(10000);
        // printf("Sending command to set voltage low\n\r");
        // TWI_Start_Transceiver_With_Data(test_low,TEST_SET_OUTPUT_LENGTH);
        // _delay_ms(10000);
        // TWI_state = TWI_Get_State_Info();
        // printf("TWI state: %u\n\r", TWI_state);
    }
    return 0;
}
