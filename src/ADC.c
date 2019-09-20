#include "ADC.h"
#include "xmem.h"
#include "uart.h"

const char* adc_channels[] = {
    "JOYSTICK_VERTICAL" ,
    "JOYSTICK_HORIZONTAL",
    "LEFT_SLIDER",
    "RIGHT_SLIDER"
};

void ADC_print_all_channels(uint8_t* read_data){
    ADC_read_all_channels(read_data);
    for (uint8_t i=0; i < 4; i++) {
        printf(" %s: %d ", adc_channels[i], read_data[i] );
    }
    printf("  \n\r");
}

void ADC_read_all_channels(uint8_t* array){
    for (uint8_t i = 0; i < 4; i++) {
        ADC_select_channel(i+4);
        array[i] = xmem_read(0,ADC);
        _delay_ms(40); 
    }
}

void ADC_select_channel(uint8_t channel){
    xmem_write(channel, 0, ADC);
    _delay_ms(40); 
}

uint8_t ADC_joystick_direction(uint8_t* read_data){
    uint8_t vertical_value = read_data[0];
    uint8_t horizontal_value = read_data[1];
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