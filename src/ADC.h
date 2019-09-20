#ifndef ADC_H 
#define ADC_H 

#include <util/delay.h>
#include <avr/io.h>

enum joystick_direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};

void ADC_read_all_channels(uint8_t* read_data);
void ADC_print_all_channels(uint8_t* array);
void ADC_select_channel(uint8_t channel);
uint8_t ADC_joystick_direction(uint8_t* read_data);


#endif