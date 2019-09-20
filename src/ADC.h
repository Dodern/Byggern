#ifndef ADC_H 
#define ADC_H 

#include <util/delay.h>
#include <avr/io.h>
// #include <time.h>

enum joystick_direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};

void ADC_read_all_channels();
void ADC_print_all_channels();
void ADC_select_channel(uint8_t channel);
uint8_t ADC_joystick_direction();

#endif