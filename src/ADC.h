#ifndef ADC_H 
#define ADC_H 

#include <util/delay.h>

#define JOYSTICK_VERTICAL 0x4
#define JOYSTICK_HORIZONTAL 0x5
#define LEFT_SLIDER 0x6
#define RIGHT_SLIDER 0x7

// enum adc_channels{
//     0 = JOYSTICK_VERTICAL,
//     1 = JOYSTICK_HORIZONTAL,
//     2 = LEFT_SLIDER,
//     3 = RIGHT_SLIDER.
// };

uint8_t ADC_read_all_channels();
void ADC_select_channel(uint8_t channel);




#endif