#include <avr/interrupt.h>
#include <util/delay.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <avr/io.h>

#include "bit_macros.h"
#include "uart.h"
#include "xmem.h"
#include "adc_driver.h"
#include "oled_driver.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "can_controller_driver.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void){
    // Initiating various devices
	USART_Init ( MYUBRR );
    xmem_init();
    adc_init();
    oled_init();

    can_controller_init();

    struct can_message message;
    message.id = 0;
    message.length = 3;
    message.data[0] = 0b01010101; //85
    message.data[1] = 0b01001111; //79
    message.data[2] = 0b01001011; //75
    //can_controller_write_struct(0b00110110, &message);
    can_controller_write_struct(MCP_TXB0D0, &message);
    can_controller_write(MCP_TXB0SIDH, 0x00);
    can_controller_write(MCP_TXB0SIDL, 0x00);
    can_controller_write(MCP_TXB0DLC, message.length);
    can_controller_request_to_send(MCP_RTS_TX0);

    int length = can_controller_read(MCP_RXB0DLC);
    printf("Message length = %d\n\r", length);
    int read_data[length];
    can_controller_read_struct(MCP_RXB0D0, &read_data, message.length);
    for (int i = 0; i < message.length; i++){
        printf("CAN recieve data %d\n\r", read_data[i]);
    }

    //int read_data = can_controller_read(0b01100110);
    //printf("CAN recieve data: %d\n\r", read_data);
    //int transmit_buffer = can_controller_read(0b00110110);
    //printf("CAN transmit buffer data preloading : %d\n\r", transmit_buffer);
    //can_controller_write(0b00110110, 0b00010101);
    //transmit_buffer = can_controller_read(0b00110110);
    //printf("CAN transmit buffer data: %d\n\r", transmit_buffer);
    //can_controller_bit_modify(MCP_TXB0CTRL,0b00001000, 0b00001000);
    

    while (1) {
        

    }
    return 0;
}