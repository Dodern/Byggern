#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <util/delay.h>
enum joystick_direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};

// struct adc_values{
//     int joystick_pos[2];
// };

void adc_init();
void adc_read_all_channels();
void adc_print_all_channels();
void adc_select_channel(uint8_t channel);
uint8_t adc_get_joystick_direction();
void adc_read_joystick_position();
int joystick_percent_formula(int read_index, uint8_t center_value);
void adc_get_joystick_position(uint8_t* arr);
uint8_t adc_get_right_slider_position(void);
void adc_print_current_position();
void adc_print_direction(uint8_t direction);

int adc_is_joystick_button_pressed();
int adc_is_left_button_pressed();
int adc_is_right_button_pressed();
int adc_print_button_states();

#endif
