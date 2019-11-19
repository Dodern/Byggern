#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <util/delay.h>

enum joystick_direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};

struct adc_player_inputs {
    uint8_t right_slider;
    uint8_t left_slider;
    uint8_t joystick_verticle_position;
    uint8_t joystick_horizontal_position;
    uint8_t right_button;
    uint8_t left_button;
    uint8_t joystick_button;
};

void adc_init();
void adc_select_channel(uint8_t channel);
void adc_read_all_channels();
int joystick_percent_formula(int read_index, uint8_t center_value);
void adc_read_joystick_position();

uint8_t adc_get_joystick_direction();
void adc_get_joystick_position(uint8_t* arr);
void adc_get_joystick_percent_position(uint8_t* arr);
uint8_t adc_get_right_slider_position(void);
uint8_t adc_get_left_slider_position(void);
void adc_update_all_player_inputs(uint8_t *player_inputs);

int adc_is_joystick_button_pressed();
int adc_is_left_button_pressed();
int adc_is_right_button_pressed();

void adc_print_all_channels();
void adc_print_current_position();
void adc_print_direction(uint8_t direction);
int adc_print_button_states();

#endif
