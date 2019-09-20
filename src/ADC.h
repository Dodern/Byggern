#ifndef ADC_H 
#define ADC_H 

#include <util/delay.h>
#include <avr/io.h>

enum joystick_direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};

void ADC_read_all_channels(uint16_t* read_data);
void ADC_print_all_channels(uint16_t* array);
void ADC_select_channel(uint8_t channel);


#endif