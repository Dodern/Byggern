#include "oled_driver.h"
#include <stdlib.h>
#include <util/delay.h>
// #include <avr/io.h>
#include <avr/interrupt.h>
// #include <stdint.h>


#include "xmem.h"
#include "fonts.h"
#include "uart.h"

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
    oled_write_command(0x00);   //Horizontal addressing mode
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
}

void oled_print_char(uint8_t character){
    uint8_t font_num = character - 32;
    printf("fontnum = %d", font_num);
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

// // }
// // void oled_reset(){
//     for 
// }
// void oled_hello_world(){
//     oled_write_data()
// }