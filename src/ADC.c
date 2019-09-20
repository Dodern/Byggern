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

int ADC_joystick_direction(){
    for (int i=4; i < 8; i++) {
        ADC_select_channel(i);
        uint8_t readData = xmem_read(0,ADC);
        
        printf(" %s: %d ", adc_channels[i-4], readData );
        // printf("%s: ", adc_channels[i]);
        _delay_ms(40); 
    }
}