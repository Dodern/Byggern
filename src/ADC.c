#include "ADC.h"
#include "xmem.h"
#include "uart.h"

uint8_t ADC_read_all_channels(){
    for (int i=4; i < 8; i++) {
        ADC_select_channel(i);
        uint8_t readData = xmem_read(0,ADC);
        printf("Channel %d data has been read: %d\n\r", i, readData );
        _delay_ms(40); 
    }
}

void ADC_select_channel(uint8_t channel){
    xmem_write(channel, 0, ADC);
    _delay_ms(40); 
}