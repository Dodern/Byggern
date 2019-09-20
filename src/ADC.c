#include "ADC.h"
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

void ADC_init(){
    ADC_read_all_channels();    
    joystick_center_array[0] = read_data_array[1];
    joystick_center_array[1] = read_data_array[0];
}

void ADC_print_all_channels(){
    ADC_read_all_channels();
    for (uint8_t i=0; i < 4; i++) {
        printf(" %s: %d ", adc_channels[i], read_data_array[i] );
    }
    printf("\n\r");
}

void ADC_read_all_channels(){
    for (uint8_t i = 0; i < 4; i++) {
        ADC_select_channel(i+4);
        read_data_array[i] = xmem_read(0,ADC);
        _delay_ms(40); 
    }
}

void ADC_select_channel(uint8_t channel){
    xmem_write(channel, 0, ADC);
    _delay_ms(40); 
}

uint8_t ADC_joystick_direction(){
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

void ADC_print_direction(uint8_t direction){
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

void ADC_joystick_position(){
    uint8_t x_mid = joystick_center_array[0];
    uint8_t y_mid = joystick_center_array[1];
    printf("x_mid: %d, y_mid: %d \n\r", x_mid, y_mid);
    joystick_current_position[0] = (read_data_array[1]-x_mid)/(255.0-x_mid)*100;
    joystick_current_position[1] = (read_data_array[0]-y_mid)/(255.0-y_mid)*100;
}

void ADC_print_current_position(){
    printf("X: %d, Y: %d \n\r", joystick_current_position[0], joystick_current_position[1]);
}