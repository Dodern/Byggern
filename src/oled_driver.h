#ifndef OLED_DRIVER_H 
#define OLED_DRIVER_H 

// #include <avr/pgmspace.h>
// #include "fonts.h"

void oled_init();
void oled_write_command(uint8_t command);
void oled_write_data(uint8_t data);
void oled_reset();
void oled_home();
void oled_clear_to_line_end();
void oled_clear_to_end();
void oled_clear_to_pointer();
void oled_print_pointer();
void oled_move_pointer(int direction);
void oled_print_char(uint8_t character);
void oled_print_string(char* string);
void oled_print_main_menu();
void oled_pos();
void oled_line_end();

#endif