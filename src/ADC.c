#include "ADC.h"
#include "xmem.h"
#include "uart.h"

const char* adc_channels[] = {
    "JOYSTICK_VERTICAL" ,
    "JOYSTICK_HORIZONTAL",
    "LEFT_SLIDER",
    "RIGHT_SLIDER"
};

uint8_t ADC_read_all_channels(){
    for (int i=4; i < 8; i++) {
        ADC_select_channel(i);
        uint8_t readData = xmem_read(0,ADC);
        
        printf("%s: %d", adc_channels[i], readData );
        _delay_ms(40); 
    }
    printf("\n\r");
}

void ADC_select_channel(uint8_t channel){
    xmem_write(channel, 0, ADC);
    _delay_ms(40); 
}

