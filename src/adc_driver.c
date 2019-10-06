#include <avr/io.h>
#include <stdbool.h>

#include "adc_driver.h"
#include "xmem.h"
#include "uart.h"

static uint8_t read_data_array[4];
static uint8_t joystick_center_array[2];
static int8_t joystick_current_position[2];

const char* adc_channels[] = {
    "JOYSTICK_VERTICAL" ,
    "JOYSTICK_HORIZONTAL",
    "LEFT_SLIDER",
    "RIGHT_SLIDER"
};

void adc_init(){
    adc_read_all_channels();    
    joystick_center_array[0] = read_data_array[1];
    joystick_center_array[1] = read_data_array[0];
    PORTB &=  ~(1 << PB0) | ~(1 << PB1); // Setting to input for buttons
    DDRB &=  ~(1 << DDB0) | ~(1 << DDB1); // Setting to input for buttons
    // DDRB &= ~(1 << DDB0);// | ~(1 << DDB1) | ~(1 << DDB2); // Setting to input for buttons
}

void adc_print_all_channels(){
    adc_read_all_channels();
    for (uint8_t i=0; i < 4; i++) {
        printf(" %s: %d ", adc_channels[i], read_data_array[i] );
    }
    printf("\n\r");
}

void adc_read_all_channels(){
    for (uint8_t i = 0; i < 4; i++) {
        adc_select_channel(i+4);
        read_data_array[i] = xmem_read(0,ADC);
        _delay_ms(40); 
    }
}

void adc_select_channel(uint8_t channel){
    xmem_write(channel, 0, ADC);
    _delay_ms(40); 
}

uint8_t adc_get_joystick_direction(){
    adc_read_joystick_position();
    uint8_t vertical_value = read_data_array[0];
    uint8_t horizontal_value = read_data_array[1];
    enum joystick_direction dir = 0;

    if (horizontal_value > 200) {
        dir = RIGHT;
    } 
    else if  (horizontal_value < 70) {
        dir = LEFT;
    }
    else if (vertical_value > 200) {
        dir = UP;
    }
    else if (vertical_value < 70) {
        dir = DOWN;
    } else{
        dir = NEUTRAL;
    }
    return dir;
}

void adc_print_direction(uint8_t direction){
    enum joystick_direction dir = 0;
    printf("Direction: ");
    switch (direction)   
    {
    case RIGHT:
         printf("Right");
        break;
    case LEFT:
         printf("Left");
        break;
    case UP:
         printf("Up");
        break;
    case DOWN:
         printf("Down");
        break;
    case NEUTRAL:
         printf("Neutral");
        break;
    default:
        break;
    }
    printf("\n\r");
}

void adc_read_joystick_position(){
    adc_read_all_channels();
    uint8_t x_mid = joystick_center_array[0];
    uint8_t y_mid = joystick_center_array[1];
    joystick_current_position[0] = (read_data_array[1]-x_mid)/(255.0-x_mid)*100;
    joystick_current_position[0] = (read_data_array[1]-x_mid)/(255.0-x_mid)*100;
    joystick_current_position[1] = (read_data_array[0]-y_mid)/(255.0-y_mid)*100;
}

void adc_print_current_position(){
    printf("X: %d, Y: %d \n\r", joystick_current_position[0], joystick_current_position[1]);
}

int adc_is_joystick_button_pressed(){
    if (PINB == 0) {
        return true;
    } else {
        return false;
    }
};
