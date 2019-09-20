#ifndef OLED_DRIVER_H 
#define OLED_DRIVER_H 

#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>


void oled_init();
void oled_write_command(uint8_t command);
void oled_write_data(uint8_t data);




#endif