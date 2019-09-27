#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#include "xmem.h"
#include "fonts.h"
#include "uart.h"
#include "oled_driver.h"
#include "ADC.h"

#define SCREEN_LENGTH 1024  //1024 = 8*128
#define LINE_LENGTH 127
#define CHAR_LENGTH 8 //font8
static unsigned int horizontal_pos = 0;
static unsigned int vertical_pos = 0;
static unsigned int pointer_pos = 0;
static unsigned int menu_length = 0;

void oled_init() {
    oled_write_command(0xae); // display off
    oled_write_command(0xa1); //segment remap
    oled_write_command(0xda); //common pads hardware: alternative
    oled_write_command(0x12);
    oled_write_command(0xc8); //common output scan direction:com63~com0
    oled_write_command(0xa8); //multiplex ration mode:63
    oled_write_command(0x3f);
    oled_write_command(0xd5); //display divide ratio/osc. freq. mode
    oled_write_command(0x80);
    oled_write_command(0x81); //contrast control
    oled_write_command(0x50);
    oled_write_command(0xd9); //set pre-charge period
    oled_write_command(0x21);
    oled_write_command(0x20); //Set Memory Addressing Mode
    oled_write_command(0x00);   //horizontal_pos addressing mode
    oled_write_command(0x21); //Set column address
    oled_write_command(0x00);   //start
    oled_write_command(0x7F);   //end
    oled_write_command(0x22); //Set page address
    oled_write_command(0x00);   //Start
    oled_write_command(0x07);   //End
    oled_write_command(0xdb); //VCOM deselect level mode
    oled_write_command(0x30);
    oled_write_command(0xad); //master configuration
    oled_write_command(0x00);
    oled_write_command(0xa4); //out follows RAM content
    oled_write_command(0xa6); //set normal display
    oled_write_command(0xaf); // display on
}

void oled_write_command(uint8_t command){
    xmem_write(command, 0, OLED_COMMAND);
}

void oled_write_data(uint8_t data){
    xmem_write(data, 0, OLED_DATA);
    horizontal_pos++;
    oled_pos(horizontal_pos);
}

void oled_reset(){
    for (int i = 0; i < SCREEN_LENGTH; i++) { 
        oled_write_data(0);
    }
}
    
void oled_print_picture(){
    for (int i = 0; i < 512; i++){
        oled_write_data(pgm_read_byte(&tekled[i]));
    }
}

void oled_print_char(uint8_t character){
    uint8_t font_num = character - 32;
    for (int i = 0; i < 8; i++) {
        oled_write_data(pgm_read_byte(&font8[font_num][i]));
    }
}

void oled_print_string(char* string){
    uint8_t i = 0;
    while ( string[i] != '\0') {
        oled_print_char(string[i]);
        i++;
    }
}

void oled_clear_to_line_end(){
     for (int i = horizontal_pos; i < LINE_LENGTH; i+=CHAR_LENGTH){
        oled_print_char(' ');
    }
}

void oled_clear_to_pointer(){
    for (int i = horizontal_pos; i < LINE_LENGTH-2*CHAR_LENGTH; i+=CHAR_LENGTH){
        oled_print_char(' ');
    }
}

void oled_clear_to_end(){
    for (int vert_i = vertical_pos; vert_i < CHAR_LENGTH; vert_i++)
    {
        for (int hor_i = horizontal_pos; hor_i < LINE_LENGTH; hor_i+=CHAR_LENGTH){
            oled_print_char(' ');
        }
    }
}

void oled_print_pointer(){
    oled_print_string("<-");
}

void oled_pos(){
    if (horizontal_pos > LINE_LENGTH){
        vertical_pos++;
        horizontal_pos = 0;
    }
    if (vertical_pos > 7){
        vertical_pos = 0;
        horizontal_pos = 0;
    }
}

void oled_move_pointer(int direction){
    if (direction == UP && pointer_pos != 0){
        pointer_pos--;
    }
    else if (direction == DOWN && pointer_pos < menu_length - 1){
        pointer_pos++;
    }
    //printf("Pointer pos: %d", pointer_pos);
}

void oled_line_end(){
    if (vertical_pos == pointer_pos){
        oled_clear_to_pointer(); 
        oled_print_pointer();
    }
    else {
        oled_clear_to_line_end();
    }
}

void oled_print_main_menu(){
    menu_length = 4;
    oled_print_string("Herro");
    oled_line_end();
    oled_print_string("Hello");
    oled_line_end();
    oled_print_string("Olav");
    oled_line_end();
    oled_print_string("Jacob");
    oled_line_end();
    oled_clear_to_end();
}