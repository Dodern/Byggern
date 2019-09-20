#ifndef ADC_H 
#define ADC_H 

#include <util/delay.h>
#include <avr/io.h>

// #define JOYSTICK_VERTICAL 0x4
// #define JOYSTICK_HORIZONTAL 0x5
// #define LEFT_SLIDER 0x6
// #define RIGHT_SLIDER 0x7


uint8_t ADC_read_all_channels();
void ADC_select_channel(uint8_t channel);


#endif